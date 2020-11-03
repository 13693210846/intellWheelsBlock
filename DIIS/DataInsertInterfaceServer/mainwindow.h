#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clxtcpdevclient.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //客户map表
    QMap<long,CLxTcpDevClient*> m_mapClient;
   class QTcpServer* m_pListenServer=nullptr;
    QString m_strLocalIP4;
    class CLxPreDbWriter* m_pPreDbWriter;
    short unsigned  int m_nListenPort;
    int InitParam();
    void OnRcvConnecter();
    void displayError(QAbstractSocket::SocketError socketError);
public:
  // static class CLxLogFile* m_pLogFile;
};

#endif // MAINWINDOW_H
