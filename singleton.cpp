#include "singleton.h"
template <class T>
T* singleton<T>::m_instance = Q_NULLPTR;

template <class T>
QMutex singleton<T>::mutex(QMutex::RecursionMode::Recursive);

template <class T>
T* singleton<T>::GetInstance(){
    if(m_instance == Q_NULLPTR){
        mutex.lock();
        if(m_instance == Q_NULLPTR){
            T* ptemp = new T();
            m_instance = ptemp;
        }
        mutex.unlock();
    }
    return m_instance;
}
