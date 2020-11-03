#ifndef CLXMYSQLDB_H
#define CLXMYSQLDB_H
/*
 * mysqlserver database
*/
#include "clxpredbwriter.h"
class CLxMysqlDb:public IDatabaseWriter
{
public:
    CLxMysqlDb();
    ~CLxMysqlDb();
    virtual int InitDB();
private:
    int OpenDataBase();
    class QSqlDatabase* m_pDB;
    class QSqlQuery*      m_pSqlQuery;
};

#endif // CLXMYSQLDB_H
