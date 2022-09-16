#include "lessons.h"

Lessons::Lessons()
{

}

void Lessons::showLessons()
{
    qInfo()<<this->l_number<<" "
          <<this->l_name<<" "
         <<this->l_length<<" "
        <<this->l_room<<" "
       <<this->l_class<<" "
      <<this->l_score<<" "
     <<this->l_time;
}
