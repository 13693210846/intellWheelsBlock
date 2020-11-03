#include "clxbufqueue.h"

CLxBufQueue::CLxBufQueue()
{

}

int CLxBufQueue::InputData(char *pData, qint64 iLen)
{
    CLxDataBuf* pDataBuf = nullptr;
    m_mutexBufPool.lock();
    if(!m_listBufPool.isEmpty())
        {
        pDataBuf =m_listBufPool.takeFirst();
    }
    m_mutexBufPool.unlock();
    if(nullptr == pDataBuf)
        {
        pDataBuf = new CLxDataBuf;
    }
    pDataBuf->InputData(pData,iLen);
    m_dataMutex.lock();
    m_listData.push_back(pDataBuf);
    m_dataMutex.unlock();
}

CLxDataBuf *CLxBufQueue::GetABuf()
{
    CLxDataBuf* pDataBuf = nullptr;
    m_dataMutex.lock();
    if(!m_listData.isEmpty())
        {
        pDataBuf = m_listData.takeFirst();
    }
    m_dataMutex.unlock();
    return pDataBuf;
}
/*
 *函数名：      GetDataList
 * 功能：          获取数据列表中的所有数据
 * 参数：  pOutList，输入参数，外部定义的QList类型的指针
返回值：如果没有数据，返回0，如果有数据，返回1
*/
int CLxBufQueue::GetDataList(QList<CLxDataBuf *> *pOutList)
{
    int iNum = 0;
    m_dataMutex.lock();
    if(!m_listData.isEmpty())
        {
        iNum = 1;
        pOutList->append(m_listData);
        m_listData.clear();
    }
    m_dataMutex.unlock();
    return iNum;
}
/*
 *函数名：      ReturnTOBufPool
 * 功能：          把使用过的缓冲去，还回数据池
 * 参数：  pOutList，输入参数，外部的QList类型的指针，包含有使用过的数据缓冲区
返回值：0为正确，其它值表示有错误发生
*/
int CLxBufQueue::ReturnTOBufPool(QList<CLxDataBuf *> *pOutList)
{
    m_mutexBufPool.lock();
    m_listBufPool.append(*pOutList);
    pOutList->clear();
    m_mutexBufPool.unlock();
   return 0;
}
