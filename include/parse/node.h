#ifndef CNODE_H
#define CNODE_H


template <class T> class CNode
{
public:
    T m_data;

    CNode* m_left;
    CNode* m_right;
    CNode* m_parent;

public:
    CNode()
    {
        m_parent = nullptr;
        m_left = nullptr;
        m_right = nullptr;
    }

    ~CNode()
    {
    }

    CNode(const T& value)
        : m_data(value)
    {
        m_parent = nullptr;
        m_left = nullptr;
        m_right = nullptr;
    }

    T GetData()
    {
        return m_data;
    }
    CNode* GetParent()
    {
        return m_parent;
    }
    CNode* GetLeft()
    {
        return m_left;
    }
    CNode* GetRight()
    {
        return m_right;
    }
    //----------
    void SetData(T data)
    {
        m_data = data;
    }
    void SetParent(CNode* parent)
    {
        m_parent = parent;
    }
    void SetLeft(CNode* left)
    {
        m_left = left;
    }
    void SetRight(CNode* right)
    {
        m_right = right;
    }
};

#endif // CNODE_H