#include "clxdatabuf.h"
#include<QCoreApplication>
CLxDataBuf::CLxDataBuf(qint64 iLen)
{
    m_nBufLen = iLen;
    m_nDataLen = 0;
    m_pBuffer = new char[m_nBufLen+8];
}

 int CLxDataBuf::InputData(char* pBuf,qint64 iLen)
 {
     if(iLen>m_nBufLen)
         {
            m_nBufLen = iLen+1024;
            delete[] m_pBuffer;
            m_pBuffer = new char[m_nBufLen+8];
        }
     m_nDataLen = iLen;
     memcpy(m_pBuffer,pBuf,iLen);
 }

  char* CLxDataBuf::CLxDataBuf::GetData(qint64* pDataLen)
  {
      *pDataLen = m_nDataLen ;
      return m_pBuffer;
  }
