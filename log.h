#ifndef LOG_H
#define LOG_H
#include<QString>
#include<QDebug>

class Log
{
public:
    Log();

    void showLog();
    QString log_usename;
    QString log_password;
};

#endif // LOG_H
