#pragma once

#include <cstring>
#include <functional>
#include <string>
#include <vector>

enum EStatus : int { Success = 0, Error, Ready, Unready };

struct SKey {

    typedef int(FuncKey)(const SKey&);

    const char* data = nullptr;
    const unsigned int size = 0;
    const unsigned int level = 0;
    std::function<FuncKey> func = nullptr;
    EStatus status = EStatus::Unready;
    std::vector<std::string> args;
};

class CNode
{
public:
    typedef int(FuncKey)(int argc, char** argv);

public:
    const char* mData = nullptr;
    const unsigned int mSize = 0;
    std::function<FuncKey> mFunc = nullptr;

    // std::vector<SKey> keys;
    CNode* mParent = nullptr;
    std::vector<CNode*> childs;

    // std::vector<std::string> args;

    CNode(CNode* parent, const char* data, const int& size, const std::function<FuncKey>& func = nullptr)
        : mParent(parent)
        , mData(data)
        , mSize(size)
        , mFunc(func) {};

    CNode(CNode* parent, const char* data, const std::function<FuncKey>& func = nullptr)
        : mParent(parent)
        , mData(data)
        , mSize(strlen(data))
        , mFunc(func) {};

    ~CNode() = default;
};

class CArgs
{
private:
    std::vector<SKey> mKeys;

    CNode* mRoot = nullptr;

    SKey* mFuncKey[256] = { nullptr };

    void findOrSetArg(const char* arg, SKey*& key);

public:
    CArgs();
    // CArgs() = default;
    ~CArgs() = default;

    void add(const char* data,
        const unsigned int& size,
        const unsigned int& level,
        const std::function<int(const SKey&)>& func = nullptr);

    void add(const char* data, const unsigned int& level, const std::function<int(const SKey&)>& func = nullptr);

    void parse(int argc, char** argv);

    void round(int argc, char** argv, CNode* node, const int& level = 1);

    // CNode* addNode(CNode* parent);

    CNode* addNode(CNode* parent, const char* data, const std::function<CNode::FuncKey>& func = nullptr);

    CNode*
    addNode(CNode* parent, const char* data, const int& size, const std::function<CNode::FuncKey>& func = nullptr);

    CNode* getRoot();

    // void addArg(CNode* node, const char* data, const std::function<int(const SKey&)>& func);

    void process(int argc, char** argv);

    void execute(char** argv, int argc, int argn, CNode* node);

    bool roundParents(const char* arg, CNode* node);
};