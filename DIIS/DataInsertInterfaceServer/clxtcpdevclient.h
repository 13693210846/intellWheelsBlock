#ifndef CLXTCPDEVCLIENT_H
#define CLXTCPDEVCLIENT_H
#include <QtNetwork/QTcpSocket>
class CLxTcpDevClient:public QObject
{
public:
    CLxTcpDevClient();
    class CLxPreDbWriter* m_pDataProcessor;
    QTcpSocket* m_pTcpSocket = 0;
    void ReadData();
 private:
    char* m_pReadBuf;
    qint64 m_iReadBufLen;
    qint64     m_iReadDataLen;
};

#endif // CLXTCPDEVCLIENT_H
