#include "qtlog.h"
#include <QDebug>
#include <QMutex>
#include <QtGlobal>
#include <QFile>
#include <QDateTime>
#include "stdio.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
QtLog *m_pInstance = NULL;
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QtLog::QtLog():
    m_count(0)
{
    m_bOutPutAble = true;
    setLogFilePath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    m_fileName = "log";
    m_sufix = "txt";
    setLogMode(m_logMode);
}

QtLog::~QtLog()
{
    qInstallMessageHandler(NULL);
    m_pInstance = NULL;
}

QtLog *QtLog::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new QtLog();
    }
    return m_pInstance;
}

void QtLog::Release()
{
    if(m_pInstance){
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

void QtLog::setLogMode(QtLog::LogMode mode)
{
    m_ableSwithRecord.bchange = false;
    m_ableSwithRecord.preMode = m_logMode;
    m_logMode = mode;
    switch (mode) {
    case File:
        qInstallMessageHandler(outputMessage);
        break;
    case Qt:
        qInstallMessageHandler(NULL);
        break;
    default:
        qInstallMessageHandler(NULL);
        break;
    }
}

#include <QDir>
void QtLog::setLogFilePath(QString path)
{
    m_logPath = path;
    QDir dir(m_logPath);
    dir.mkpath(m_logPath);
}

QString QtLog::logFilePath()
{
    QString path = m_logPath + "/" + m_fileName + ".txt";
    while(1){
        path = m_logPath + "/"
                + m_fileName
                + (m_count > 0 ? QString::number(m_count) : QString())
                + QString(m_sufix.isEmpty()?"":QString(".%1").arg(m_sufix));
        QFile file(path);
        if(file.exists() && file.size() >= 1024*1024*5){
            increaseCount();
        }else{
            break;
        }
    }
    return path;
}

void QtLog::printInfo(const QString &path, QString str, QString fileName)
{
    QFile file(path + fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        file.write(qPrintable(QString("[msg : %1]\n").arg(str)));
        file.close();
    }
}

void QtLog::setEnableOutPut(bool boutput)
{
    m_bOutPutAble = boutput;
    if(!boutput){
        setLogMode(File);//To control output;
        m_ableSwithRecord.bchange = true;
    }else if(m_ableSwithRecord.bchange){
        setLogMode(m_ableSwithRecord.preMode);
    }

}

bool QtLog::isOutputAble() const
{
    return m_bOutPutAble;
}

#include <QDir>
void QtLog::clearLogs(QString path)
{
    QDir dir(path);
    QStringList list = dir.entryList(QDir::NoDotAndDotDot|QDir::Files);
    foreach (QString file, list) {
        if(file.contains("log") && file.contains(".txt")){
            QFile::remove(path + "/" + file);
        }
    }
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(!m_pInstance || !m_pInstance->isOutputAble()){
        return;
    }
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }

    switch (m_pInstance->logMode()) {
    case QtLog::File:{
        //QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
        QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        QString current_date = QString("(%1)").arg(current_date_time);
        QString message = QString("[%1 %2]: %3\r\n").arg(current_date).arg(text).arg(msg);
        QFile file(m_pInstance->logFilePath());
        file.setPermissions(QFile::ReadOther|QFile::WriteOther);
        if(file.open(QIODevice::WriteOnly | QIODevice::Append)){
            QTextStream text_stream(&file);
            text_stream <<message<< "\r\n";
            file.close();
        }

    }
    default:
        break;
    }
    mutex.unlock();
}
