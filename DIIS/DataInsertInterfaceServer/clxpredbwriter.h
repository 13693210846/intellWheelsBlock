#ifndef CLXPREDBWRITER_H
#define CLXPREDBWRITER_H
#include <QtCore/qmutex.h>
#include <QObject>
#include <QtCore/QThread>
#include "clxdatabuf.h"
/*
 * 数据处理前的前置类，数据库写入之前的唯一入口
 * 此类不涉及数据库的任何操作，只是根据设置创建不同的数据库实例
 * 接受到数据后，缓冲数据，通过线程池处理缓冲中的数据
*/
class IDatabaseWriter
        {
    public:
    virtual int InitDB() = 0;
    };

class CLxPreDbWriter:QThread
{
public:
    CLxPreDbWriter();
    ~CLxPreDbWriter();
    void InputData(char* pData,qint64 nLen);
private:
    int OpenDatabase();
  class CLxBufQueue* m_pBufQueue;
  virtual void run();
  void PrintToLog(CLxDataBuf* pBuf);
  IDatabaseWriter* m_pDb;
};

#endif // CLXPREDBWRITER_H
