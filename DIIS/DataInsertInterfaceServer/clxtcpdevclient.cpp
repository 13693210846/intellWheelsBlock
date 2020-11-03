#include "clxtcpdevclient.h"
#include "clxpredbwriter.h"
CLxTcpDevClient::CLxTcpDevClient()
{
    m_iReadBufLen = 2048;
    m_pReadBuf = new char[m_iReadBufLen+8];
}

void CLxTcpDevClient::ReadData()
{
    if(0 == m_pTcpSocket)
        {
       return;
    }

       //循环读取到来的数据，直到全部读取
    do
        {
            m_iReadDataLen = m_pTcpSocket->read(m_pReadBuf,m_iReadBufLen);
            if(m_iReadDataLen>0)
                {
                    m_pDataProcessor->InputData(m_pReadBuf,m_iReadDataLen);
                }
        }while(m_iReadDataLen==m_iReadBufLen);
}
