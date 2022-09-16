#ifndef LESSONS_H
#define LESSONS_H
#include<QString>
#include<QDebug>

class Lessons
{
public:
    Lessons();

    void showLessons();

    QString l_number;
    QString l_name;
    double l_length;
    QString l_room;
    QString l_class;
    double  l_score;
    QString l_time;
};

#endif // LESSONS_H
