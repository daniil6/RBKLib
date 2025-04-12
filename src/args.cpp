#include "args.h"

CArgs::CArgs()
{
    mRoot = addNode(nullptr, "root");

    /*mRoot = addNode(nullptr, "root", [=](int argc, char** argv) {
        round(argc, argv, mRoot);
        return 0; //
    });*/
}

void CArgs::add(const char* data,
    const unsigned int& size,
    const unsigned int& level,
    const std::function<int(const SKey&)>& func)
{
    mKeys.push_back({ data, size, level, func });
}

void CArgs::add(const char* data, const unsigned int& level, const std::function<int(const SKey&)>& func)
{
    mKeys.push_back({ data, (unsigned int)strlen(data), level, func });
}

/*CNode* CArgs::addNode(CNode* parent)
{
    CNode* node = new CNode();

    if(parent == nullptr)
        mRoot = node;
    else
        parent->childs.push_back(node);

    return node;
}*/

CNode* CArgs::addNode(CNode* parent, const char* data, const std::function<CNode::FuncKey>& func)
{
    return addNode(parent, data, strlen(data), func);
}

CNode* CArgs::addNode(CNode* parent, const char* data, const int& size, const std::function<CNode::FuncKey>& func)
{
    CNode* node = new CNode(parent, data, size, func);

    if(parent != nullptr) {

        parent->childs.push_back(node);
    }

    return node;
}

/*void CArgs::addArg(CNode* node, const char* data, const std::function<int(const SKey&)>& func)
{
    node->keys.push_back({ data, (unsigned int)strlen(data), 0xFFFF, func });
}*/

void CArgs::parse(int argc, char** argv)
{
    SKey* pKey = nullptr;

    if(mKeys.empty() == false) {

        pKey = &mKeys.front();

        for(int i = 1; i < argc; i++)
            findOrSetArg(argv[i], pKey);

        for(auto& p : mFuncKey)
            if(p->func != nullptr)
                if(p->status == EStatus::Ready)
                    if(p->func(*p) != 0)
                        break;
    }
}

void CArgs::findOrSetArg(const char* arg, SKey*& key)
{
    for(auto& iKey : mKeys) {
        if(memcmp(arg, iKey.data, iKey.size) == 0) {
            key = &iKey;
            if(mFuncKey[iKey.level] == nullptr) {
                mFuncKey[iKey.level] = &iKey;
                key->status = EStatus::Ready;
            }
            return;
        }
    }

    key->args.push_back(arg);
}

void CArgs::process(int argc, char** argv)
{
    for(int i = 1; i < argc; i++) {

        round(argc, argv, mRoot, i);
    }
}

bool CArgs::roundParents(const char* arg, CNode* node)
{
    if(node != nullptr) {

        for(auto child : node->childs) {

            if(memcmp(arg, child->mData, child->mSize) == 0) {

                return true;
            }
        }

        return roundParents(arg, node->mParent);
    }

    return false;
}

void CArgs::execute(char** argv, int argc, int argn, CNode* node)
{
    if(node != nullptr) {

        for(int i = argn; i < argc; i++) {

            for(auto child : node->childs) {

                if(memcmp(argv[i], child->mData, child->mSize) == 0) {

                    child->mFunc(i, argv);
                }
            }

            if(roundParents(argv[i], node->mParent) == true)
                break;
        }
    }
}

void CArgs::round(int argc, char** argv, CNode* node, const int& level)
{
    int iChild = 0;
    int sChild = 0;

    char* arg = nullptr;

    if(level < argc) {

        arg = argv[level];

        sChild = node->childs.size();

        for(; iChild < sChild; iChild++) {

            CNode* child = node->childs[iChild];

            if(memcmp(arg, child->mData, child->mSize) == 0) {

                execute(argv, argc, level, child);

                round(argc, argv, child, level + 1);

                break;
            }
        }
    }
}

CNode* CArgs::getRoot()
{
    return mRoot;
}