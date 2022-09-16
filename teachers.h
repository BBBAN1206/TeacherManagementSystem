#ifndef TEACHERS_H
#define TEACHERS_H
#include<QString>
#include<QDebug>
class Teachers
{
public:
    Teachers();

    void showTeachers();

    int t_number;
    QString t_name;
    QString t_sex;
    QString t_birth;
    QString t_work;
    QString t_education;
    QString t_marry;
    double t_salary;
    QList<QString> t_lessons;
};

#endif // TEACHERS_H
