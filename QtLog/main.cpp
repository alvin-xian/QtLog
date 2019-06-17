#include <QCoreApplication>
#include "qtlog.h"
#include <QDebug>
#include <QStandardPaths>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//---------------test---------------------------
    //初始化文件打印信息
    QString location = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    qtLog->setLogFilePath(location+"/Log");
    qtLog->setLogFileName("Qt_Log");
    qtLog->setLogFileSufix("txt");

    //调试信息输出到文件
    qDebug()<<"Log in file:"<<qtLog->logFilePath();
    qtLog->setLogMode(QtLog::File);
    qDebug()<<"Log in file "<<qtLog->logFilePath();

    //调试信息输出到命令行
    qtLog->setLogMode(QtLog::Qt);
    qDebug()<<"Log in commanline ";
//---------------end---------------------------
    return a.exec();
}
