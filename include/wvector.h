#ifndef CVECTOR_H
#define CVECTOR_H

template <typename T> class CVector
{
private:
    T* m_pVector;
    int m_size;

public:
    CVector()
    {
        m_pVector = nullptr;
        m_size = 0;
    }

    ~CVector()
    {
    }

    void PushBack(T val)
    {
        if(m_pVector != nullptr) {
            T* pVec = new T[m_size + 1] { 0 };
            T* pVecEnd = pVec + m_size;
            for(T* a = pVec; a < pVecEnd; a++)
                *a = *m_pVector++;
            *pVecEnd = val;
            m_pVector = pVec;
        } else
            m_pVector = new T[1] { val };

        m_size++;
    }

    T Get(int count)
    {
        if(count < m_size) {
            return *(m_pVector + count);
        }
    }

    int Size()
    {
        return m_size;
    }
};

#endif // CVECTOR_H