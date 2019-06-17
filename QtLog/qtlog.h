#ifndef QTLOG_H
#define QTLOG_H
#define qtLog QtLog::Instance()
/**
 * @brief The QtLog class
 * 该类用来控制全局qDebug、qWarning、qCritical、qFatal的行为；
 * 默认使用原装QT模式；
 * 日志存放路径初始化为桌面，命名为“log.txt”
 * @author Alvin
 */
#include <QString>
class QDebug;
class QtLog
{
public:
    enum LogMode{
        File,//输出到文件
        Qt//原装QT输出
    };
    /**
     * @brief setLogMode：设置QT输出行为
     * @param mode
     */
    void setLogMode(LogMode mode);
    /**
     * @brief setLogFilePath：设置当输出模式为File的时候的日志路径
     * @param path
     */
    inline void setLogFilePath(QString path);
    inline void setLogFileName(QString name){m_fileName = name;}
    inline void setLogFileSufix(QString sufix){m_sufix = sufix;}

    /**
     * @brief setEnableOutPut：控制调试信息是否输出；
     * @param boutput：设置为true，正常输出；设置false，无输出，既不会输出到命令行也不会输出到文件
     */
    void setEnableOutPut(bool boutput);

    /**
     * @brief clearLogs:清空记录文件所在的文件
     * @param path
     */
    static void clearLogs(QString path);
    /**
     * @brief Instance
     * @return：单例指针
     */
    static QtLog *Instance();
public:
    /**
     * @brief logMode
     * @return：返回当前输出模式
     */
    inline LogMode logMode() const {return m_logMode;}
    /**
     * @brief Release:释放单例指针
     */
    static void Release();

    /**
     * @brief isOutputAble
     * @return：返回是否有调试输出
     */
    inline bool isOutputAble() const;
    /**
     * @brief printInfo：静态函数，输出日志到文件,默认名字为log.txt
     * @param path：日志文件路径
     * @param str：日志信息
     */
    static void printInfo(const QString &path, QString str, QString fileName = "log.txt");
    /**
     * @brief increaseCount
     * 增加log文件后缀，
     */
    void increaseCount(){m_count++;}
    /**
     * @brief logFilePath
     * @return：返回日志路径
     */
    QString logFilePath();
private:
    LogMode m_logMode;
    QString m_logPath;
    QString m_fileName;
    QString m_sufix;
    bool m_bOutPutAble;
    int m_count;
    struct {
        bool bchange;
        LogMode preMode;
    }m_ableSwithRecord;//为了连续调用setEnableOutPut()
private:
    QtLog();
    ~QtLog();
};

#endif // QTLOG_H
