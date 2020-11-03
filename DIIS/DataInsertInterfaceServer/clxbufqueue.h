#ifndef CLXBUFQUEUE_H
#define CLXBUFQUEUE_H

#include <QObject>
#include <QtCore/qmutex.h>
#include "clxdatabuf.h"
/*
 * 单独线程处理数缓冲，把处理函数和它所在的对象传递进来
*/
class CLxBufQueue
{
public:
    CLxBufQueue();
    int InputData(char* pData,qint64 iLen);
    CLxDataBuf* GetABuf();
    int GetDataList(QList<CLxDataBuf*>* pOutList);
    int ReturnTOBufPool(QList<CLxDataBuf*>* pOutList);
private:
    QMutex m_dataMutex;
    QMutex m_mutexBufPool;
    QList<CLxDataBuf*> m_listData;
    QList<CLxDataBuf*> m_listBufPool;
};

#endif // CLXBUFQUEUE_H
