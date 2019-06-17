# QtLog
一个支持将qDebug信息输出到调试窗口或文件的类。

#调用方法：
```c

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
```

# 输出到命令行
![img](https://github.com/alvin-xian/QtLog/blob/master/QtLog/log-commandline.jpg)

# 输出到文件
![img](https://github.com/alvin-xian/QtLog/blob/master/QtLog/log-file.jpg)
