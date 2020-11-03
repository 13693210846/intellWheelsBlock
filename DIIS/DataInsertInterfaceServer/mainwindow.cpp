#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QSettings>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "clxlogfile.h"
#include "clxpredbwriter.h"
extern CLxLogFile* m_pLogFile;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitParam();
}

MainWindow::~MainWindow()
{
    delete m_pListenServer;
    delete ui;
    delete m_pLogFile;
}

int MainWindow::InitParam()
{
    //
    m_pLogFile = new CLxLogFile;
    m_pLogFile->InitPath(qPrintable(QApplication::applicationFilePath()));
    m_pLogFile->WriteLog(LOG_TYPE_INFO,">>>>>%s_程序启动<<<<<",qPrintable(QApplication::applicationName()));
    //读取配置参数
    QString qsfileName = QApplication::applicationFilePath() + ".conf";
    QSettings *configIni = new QSettings(qsfileName, QSettings::IniFormat);
    m_strLocalIP4=configIni->value("comm/localIP",QVariant("127.0.0.1") ).toString();
    m_nListenPort=configIni->value("comm/localPort",QVariant(8998) ).toInt();
    delete configIni;
    QHostAddress varqHostAddr(m_strLocalIP4);
    //数据前置写入
    m_pPreDbWriter = new CLxPreDbWriter;
    //启动侦听
    m_pListenServer =new QTcpServer(this);
    connect(m_pListenServer, &QTcpServer::newConnection, this, &MainWindow::OnRcvConnecter);
    connect(m_pListenServer, &QTcpServer::acceptError, this, &MainWindow::displayError);

    //3. 启动服务端
    if (!m_pListenServer->listen( varqHostAddr, m_nListenPort))
    {
        m_pLogFile->WriteLog(LOG_TYPE_INFO,"服务器在%s:%d开启网络侦听失败",qPrintable(m_strLocalIP4),m_nListenPort);
    }
    else
        {
        m_pLogFile->WriteLog(LOG_TYPE_INFO,"服务器开启网络侦听，IP地址=%s,网络侦听端口:%d",qPrintable(m_strLocalIP4),m_nListenPort);
    }
    return 0;
}

void MainWindow::OnRcvConnecter()
{
         //获取与客户端通信的socket
      QTcpSocket* pClientConnection = m_pListenServer->nextPendingConnection();
      CLxTcpDevClient* pDevClient = new CLxTcpDevClient;
      pDevClient->m_pTcpSocket = pClientConnection;
      pDevClient->m_pDataProcessor = m_pPreDbWriter;
      m_mapClient[(long)pClientConnection] = pDevClient;
      connect(pClientConnection, &QTcpSocket::readyRead, pDevClient, &CLxTcpDevClient::ReadData);
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    m_pLogFile->WriteLog(LOG_TYPE_INFO,"侦听socket出错，错误码：%x",socketError);
}
