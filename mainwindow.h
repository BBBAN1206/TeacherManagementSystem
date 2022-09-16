#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QList>
#include<QStringList>
#include<QTableWidget>
#include"teachers.h"
#include"lessons.h"
#include"log.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void loadData();

    void creatTeacherTable();

    void creatLessonTable(Teachers &t);

    //性别、婚查询
    void creatFindTable(int flag);

    //出生年月查询
    void creatFindTable(double time, bool beforeOrAfter);

    //职称查询
    void creatFindTable(QString work);

private slots:
    void on_lookbtn_released();

    void on_lastpage_released();

    void on_lastpage_2_released();

    void on_confirmbtn_released();

    void on_lastpage_3_released();

    void on_vistorbtn_released();

    void on_re_logbtn_released();

    void on_lastpage_4_released();

    void on_addbtn_released();

    void on_deletebtn_released();

    void on_to_addbtn_released();

    void on_to_deletebtn_released();

    void on_registerbtn_released();

    void on_looklessonbtn_released();

    void on_lastpage_5_released();

    void on_lastpagebtn_released();

    void on_looklessonbtn_2_released();

    void on_lastpage_6_released();

    void on_deletelessonbtn_released();

    void on_lastpagebtn_2_released();

    void on_addlessonbtn_released();

    void on_eraselessonbtn_released();

    void on_visitorlooklessonbtn_released();

    void on_visitorlooklessonbtn_2_released();

    void on_lastpage_20_released();

    void on_lastpage_19_released();

    void on_quitbtn_released();

    void on_saveaction_triggered();

    void on_quitaction_triggered();

    void on_tomenuaction_triggered();

    void on_reloginaction_triggered();

    void on_findbtn_released();

    void on_visitorfindbtn_released();

    void on_lastpage_7_released();

    void on_registeradminbtn_released();

    void on_lastpage_8_released();

    void on_registerconfirmbtn_2_released();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;

    QList<Teachers*> m_teachers;

    QList<Lessons*> m_lessons;

    QList<Log*> m_log;

    //是否为管理员登录
    bool is_admin;

    //保存查询课程的教师编号
    int lookLessonNumber;

    QString teacherFileName;
};
#endif // MAINWINDOW_H
