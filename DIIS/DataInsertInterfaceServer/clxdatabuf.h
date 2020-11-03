#ifndef CLXDATABUF_H
#define CLXDATABUF_H
#include <QApplication>
/*
    数据缓冲区，保存有缓冲区的长度+数据的长度
*/
class CLxDataBuf
{
public:
    CLxDataBuf(qint64 iLen=1024);
    int InputData(char* pBuf,qint64 iLen);
    char* GetData(qint64* pDataLen);
    char* m_pBuffer;
    qint64 m_nBufLen;
    qint64 m_nDataLen;
};

#endif // CLXDATABUF_H
