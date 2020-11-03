#ifndef CLXLOGFILE_H
#define CLXLOGFILE_H
#include<QtCore/QtCore>
enum LOGTYPE
{
    LOG_TYPE_INFO = 0,		// 一般信息
    LOG_TYPE_IMPORTANT,		// 重要信息
    LOG_TYPE_WARNING,		// 警告信息
    LOG_TYPE_ERROR,			// 错误信息
    LOG_TYPE_NETSEND,		// 网络发送信息
    LOG_TYPE_NETRECV,		// 网络接收信息
    LOG_TYPE_NETERROR		// 网络数据错误
};
class CLxLogFile
{
public:
    CLxLogFile();
    ~CLxLogFile();
    bool InitPath(const char* szFilePath);
    void WriteLog(const char* pMsg);
    void WriteLog(char* pbuf,qint64 iLen);
    void WriteLog(int logType,char* szFormat,...);
private:
    QFile* m_pfileLog;
    QString m_qsFileName;
    char* m_pLogBuf;
    int     m_iInfoLen;
};
static CLxLogFile* m_pLogFile=nullptr;
#endif // CLXLOGFILE_H
