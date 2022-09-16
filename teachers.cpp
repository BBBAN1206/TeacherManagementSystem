#include "teachers.h"

Teachers::Teachers()
{

}

void Teachers:: showTeachers()
{
    qInfo()<<this->t_number<<" "
          <<this->t_name<<" "
         <<this->t_sex<<" "
        <<this->t_birth<<" "
       <<this->t_work<<" "
      <<this->t_education<<" "
     <<this->t_marry<<" "
    <<this->t_salary;
    for(auto i: t_lessons)
    {
        qInfo()<<i<<" ";
    }
}
