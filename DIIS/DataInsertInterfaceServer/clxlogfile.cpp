#include "clxlogfile.h"

CLxLogFile::CLxLogFile()
{
    m_pLogBuf = new char[4100];
}

CLxLogFile::~CLxLogFile()
{
    if(m_pfileLog->isOpen())
        {
    m_pfileLog->close();
    delete m_pfileLog;
    }
    delete[] m_pLogBuf;
}

bool CLxLogFile::InitPath(const char *szFilePath)
{
    QDateTime qcTime = QDateTime::currentDateTime();
    QString qsFilePath = szFilePath;
    if(qcTime.isValid())
        {
        qsFilePath+=qcTime.toString(Qt::ISODate);
    }
    qsFilePath+=".log\0";
    m_pfileLog = new QFile(qsFilePath);
    m_pfileLog->open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);//|QIODevice::NewOnly);
    return true;
}

void CLxLogFile::WriteLog(const char *pMsg)
{
    QDateTime qDataTime = QDateTime::currentDateTime();
    sprintf(m_pLogBuf,"info>[%s] %s",qPrintable(qDataTime.toString( Qt::ISODate)),pMsg);
    //*m_pQTextOut<<m_pLogBuf;
}

void CLxLogFile::WriteLog(char *pbuf, qint64 iLen)
{
    QString varVaStr;
     QDateTime qDataTime = QDateTime::currentDateTime();
     varVaStr = QString::asprintf("\ninfo>[%s] ",qPrintable(qDataTime.toString( Qt::ISODate)));
     m_pfileLog->write(varVaStr.toLocal8Bit());
     m_pfileLog->write(pbuf,iLen);
}

void CLxLogFile::WriteLog(int logType,char* szFormat,...)
{
    QString varVaStr;
     QDateTime qDataTime = QDateTime::currentDateTime();
    switch(logType)
      {
        case LOG_TYPE_INFO:
            varVaStr = QString::asprintf("\ninfo>[%s] ",qPrintable(qDataTime.toString( Qt::ISODate)));
        break;
    }
    //可变参数部分
    va_list vaList;
    va_start(vaList, szFormat);
    varVaStr.append( QString::vasprintf(szFormat,vaList));
    va_end(vaList);
     m_pfileLog->write(varVaStr.toLocal8Bit());
}
