#include "log.h"

Log::Log()
{

}

void Log::showLog()
{
    qInfo()<<this->log_usename<<" "
          <<this->log_password;
}
