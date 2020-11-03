#include "clxmysqldb.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore/QSettings>
#include <QMessageBox>
#include "clxlogfile.h"
extern CLxLogFile* m_pLogFile;
CLxMysqlDb::CLxMysqlDb()
{
    m_pDB = nullptr;
    m_pSqlQuery = nullptr;
}

CLxMysqlDb::~CLxMysqlDb()
{
    if(nullptr != m_pSqlQuery)
        {
        delete m_pSqlQuery;
    }
    if(nullptr != m_pDB)
        {
            m_pDB->close();
            delete m_pDB;
        }
}

int CLxMysqlDb::InitDB()
{
   return OpenDataBase();
}

int CLxMysqlDb::OpenDataBase()
{
//    QSqlError varQsqlErr;
    QString qsTemp;
   //从配置文件读取设置
   QString qsConfFile = QApplication::applicationFilePath();
   qsConfFile+=".conf";
   /*打开数据库
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   m_pDB = new QSqlDatabase(db);
  // *m_pDB = QSqlDatabase::addDatabase("QMYSQL");
   m_pDB->setHostName("localhost");
 //  m_pDB->setPort(3306);
   m_pDB->setDatabaseName("test");       //这里输入你的数据库名 lxtd_bow_DB
   m_pDB->setUserName("root");
   m_pDB->setPassword("");                          //这里输入你的密码
   if (!m_pDB->open())
   {
       //m_pLogFile->WriteLog("无法打开数据库");
        QMessageBox::critical(0, QObject::tr("无法打开数据库"),"无法创建数据库连接！ ", QMessageBox::Cancel);
        return -1;
   }
   m_pSqlQuery = new QSqlQuery(*m_pDB);
   QString qsTable="CREATE TABLE GPS_ORIGIN_DATA(iIndex int,rcvTime datetime,data varchar(255))";//数据库表 GPS_ORIGIN_DATA
   m_pSqlQuery->prepare(qsTable);
   if(!m_pSqlQuery->exec())
       {
       QMessageBox::critical(0, QObject::tr("创建数据表失败"),"创建数据表GPS_ORIGIN_DATA失败\n程序不能运行 ", QMessageBox::Cancel);
       return -1;
   }
   //*/
   //*
   //QSqlDatabase db = QSqlDatabase::addDatabase("QMARIADB");
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   //db.setHostName("127.0.0.1");
  // db.setPort(3306);
   db.setHostName("localhost");
   db.setDatabaseName("test");       //这里输入你的数据库名
   db.setUserName("root");
   db.setPassword("");                          //这里输入你的密码
   if (!db.open())
   {
       //m_pLogFile->WriteLog("无法打开数据库");
      // qsTemp
       //varQsqlErr = db.lastError();
       QStringList listDrivers = QSqlDatabase::drivers();
       qsTemp = QString::asprintf("%d\n",listDrivers.size());
       for(int i=0;i<listDrivers.size();i++)
           {
           qsTemp+="\n";
           qsTemp+=listDrivers.at(i);
       }
       QMessageBox::critical(0, QObject::tr("无法打开数据库"),qsTemp, QMessageBox::Cancel);
       QMessageBox::critical(0, QObject::tr("无法打开数据库"),db.lastError().text(), QMessageBox::Cancel);
       //QMessageBox::critical(0, QObject::tr("无法打开数据库"),"打开或创建数据库失败", QMessageBox::Cancel);
        return -1;
   }
   //*/
//*/
   /*创建并打开数据库

        //*/
   /*创建数据表GPS_ORIGIN_DATA

//*/
   return 0;
}
