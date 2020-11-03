#include "clxpredbwriter.h"
#include "clxbufqueue.h"
#include "clxlogfile.h"
#include "clxmysqldb.h"
CLxPreDbWriter::CLxPreDbWriter()
{
    m_pBufQueue = new CLxBufQueue;
    OpenDatabase();
}
CLxPreDbWriter::~CLxPreDbWriter()
{
    delete m_pDb;
    delete m_pBufQueue;
}

void CLxPreDbWriter::InputData(char *pData, qint64 nLen)
{
    m_pBufQueue->InputData(pData,nLen);
}

int CLxPreDbWriter::OpenDatabase()
{
    m_pDb = new CLxMysqlDb();
    return m_pDb->InitDB();
}
/*
 *函数名：run
 * 功能：  线程的处理函数
 * 每1秒处理一次数据
*/
void CLxPreDbWriter::run()
{
    CLxDataBuf* pDataBuf = NULL;
    QList<CLxDataBuf*>  listTmp;
    int iRes = 0;
    do
        {
        sleep(1000);
        iRes = m_pBufQueue->GetDataList(&listTmp);
        if(iRes<1)
            {
            continue;
        }
        //打印数据
       for(QList<CLxDataBuf*>::const_iterator it=listTmp.constBegin();it!=listTmp.constEnd();++it)
           {
           pDataBuf = (CLxDataBuf*)*it;
           PrintToLog(pDataBuf);
       }
        //处理数据
        //还回缓冲区
        m_pBufQueue->ReturnTOBufPool(&listTmp);
    }while(1);
}

void CLxPreDbWriter::PrintToLog(CLxDataBuf *pBuf)
{
    char szLog[1024];
    qint64 iLen = 0;
    char* pData = pBuf->GetData(&iLen);
    m_pLogFile->WriteLog(pData,iLen);
}
