#ifndef SINGLETON_H
#define SINGLETON_H
#include <QMutex>
template<class T>
class singleton
{
protected:
   singleton();
private:
   singleton(const singleton&) = delete;
   singleton& operator=(const singleton&) = delete;
   static T* m_instance ;
   static QMutex mutex;
public:
   static T* GetInstance();
//   {
//       if(m_instance == Q_NULLPTR){
//           mutex.lock();
//           if(m_instance == Q_NULLPTR){
//               T* ptemp = new T();
//               m_instance = ptemp;
//           }
//           mutex.unlock();
//       }
//       return m_instance;
//   }

};

#endif // SINGLETON_H
