#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFile>
#include<QDebug>
#include<QTextStream>
#include<QFileDialog>
#include<QDialog>
#include"teachers.h"
#include"lessons.h"
#define TEACHERS_FILENAME "C:/Users/22604/Desktop/TeacherManagementSystem1.0/TeacherManagementSystem/System/teachers.txt"
#define LESSONS_FILENAME "C:/Users/22604/Desktop/TeacherManagementSystem1.0/TeacherManagementSystem/System/lessons.txt"
#define LOG_FILENAME "C:/Users/22604/Desktop/TeacherManagementSystem1.0/TeacherManagementSystem/System/log.txt"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化
    is_admin = false;
    ui->stackedWidget->setCurrentWidget(ui->logpage);
    teacherFileName = TEACHERS_FILENAME;
    //加载文件
    loadData();
    //创建展示教师表格
    creatTeacherTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//加载文件
void MainWindow::loadData()
{
    m_teachers.clear();
    //teachers文件
    QFile teacher_file(teacherFileName);

    if(!teacher_file.open(QIODevice::ReadOnly))
    {
        qInfo()<<"teachers文件打开失败";
    }

    QTextStream t_stream(&teacher_file);

    while(!t_stream.atEnd())
    {
        QStringList lineData = t_stream.readLine().split(",",QString::SplitBehavior::SkipEmptyParts);
        auto t = new Teachers;

        t->t_number     =   lineData[0].toInt();
        t->t_name       =   lineData[1];
        t->t_sex        =   lineData[2];
        t->t_birth      =   lineData[3];
        t->t_work       =   lineData[4];
        t->t_education  =   lineData[5];
        t->t_salary     =   lineData[6].toDouble();
        t->t_marry      =   lineData[7];
        for(int i = 8;i < lineData.size(); ++i)
        {
            t->t_lessons.push_back(lineData[i]);
        }
        m_teachers.push_back(t);
    }

    //lessons文件
    QFile lessons_file(LESSONS_FILENAME);

    if(!lessons_file.open(QIODevice::ReadOnly))
    {
        qInfo()<<"lessons文件打开失败";
    }

    QTextStream l_stream(&lessons_file);

    while(!l_stream.atEnd())
    {
        QStringList lineData = l_stream.readLine().split(",",QString::SplitBehavior::SkipEmptyParts);
        auto l = new Lessons;

        l->l_number     =   lineData[0];
        l->l_name       =   lineData[1];
        l->l_length     =   lineData[2].toDouble();
        l->l_room       =   lineData[3];
        l->l_class      =   lineData[4];
        l->l_score      =   lineData[5].toDouble();
        l->l_time       =   lineData[6];
        m_lessons.push_back(l);
    }

    //log文件
    QFile log_file(LOG_FILENAME);

    if(!log_file.open(QIODevice::ReadOnly))
    {
        qInfo()<<"log文件打开失败";
    }

    QTextStream log_stream(&log_file);

    while(!log_stream.atEnd())
    {
        QStringList lineData = log_stream.readLine().split(",",QString::SplitBehavior::SkipEmptyParts);
        auto log = new Log;

        log->log_usename    =   lineData[0];
        log->log_password   =   lineData[1];
        m_log.push_back(log);
    }

    //关闭文件
    teacher_file.close();
    lessons_file.close();
    log_file.close();
}

//建立teacher表格
void MainWindow::creatTeacherTable()
{
    //设置列数
    ui->teachertable->setColumnCount(8);
    ui->teachertable_2->setColumnCount(8);
    //设置水平标头标签
    ui->teachertable->setHorizontalHeaderLabels(QStringList()<<"教师编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资"<<"婚否");
    ui->teachertable_2->setHorizontalHeaderLabels(QStringList()<<"教师编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资"<<"婚否");
    //设置行数
    ui->teachertable->setRowCount(m_teachers.size());
    ui->teachertable_2->setRowCount(m_teachers.size());
    //显示数据
    for(int row = 0; row < m_teachers.size(); ++row)
    {
        int col = 0;
        //管理员查看表
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(QString::number(m_teachers[row]->t_number)));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_name));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_sex));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_birth));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_work));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_education));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(QString::number( m_teachers[row]->t_salary)));
        ui->teachertable->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_marry));
        //游客查看表
        col = 0;
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(QString::number(m_teachers[row]->t_number)));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_name));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_sex));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_birth));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_work));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_education));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(QString::number( m_teachers[row]->t_salary)));
        ui->teachertable_2->setItem(row,col++,new QTableWidgetItem(m_teachers[row]->t_marry));    }
}

//建立lesson表格
void MainWindow::creatLessonTable(Teachers &t)
{
    ui->lessonstable->setColumnCount(7);
    ui->lessonstable_4->setColumnCount(7);

    ui->lessonstable->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"课时"<<"教室"<<"授课班级"<<"学分"<<"学期");
    ui->lessonstable_4->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"课时"<<"教室"<<"授课班级"<<"学分"<<"学期");

    ui->lessonstable->setRowCount(t.t_lessons.size());
    ui->lessonstable_4->setRowCount(t.t_lessons.size());

    for(int row = 0; row < t.t_lessons.size(); ++row)
    {
        int col =0;
        bool is_find = false;
        int flag = 0;

        for(int i = 0; i < m_lessons.size(); ++i)
        {
            if(m_lessons[i]->l_number == t.t_lessons[row])
            {
                is_find = true;
                flag = i;
            }
        }
        if(is_find)
        {
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_number));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_name));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(QString::number(m_lessons[flag]->l_length)));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_room));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_class));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(QString::number(m_lessons[flag]->l_score)));
            ui->lessonstable->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_time));

            col = 0;
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_number));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_name));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(QString::number(m_lessons[flag]->l_length)));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_room));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_class));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(QString::number(m_lessons[flag]->l_score)));
            ui->lessonstable_4->setItem(row,col++,new QTableWidgetItem(m_lessons[flag]->l_time));
        }
        else
        {
            QMessageBox::information(this,"提示","课程编号有误！");
        }
    }
}

//性别、婚否查询
void MainWindow::creatFindTable(int flag)
{
    QList<Teachers*> temp;

    switch (flag)
    {
    //男
    case 1:
        for(auto i: m_teachers)
        {
            if(i->t_sex == "男")
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
        break;
        //女
    case 2:
        for(auto i: m_teachers)
        {
            if(i->t_sex == "女")
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
        break;
        //已婚
    case 3:
        for(auto i: m_teachers)
        {
            if(i->t_marry == "已婚")
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
        break;
        //未婚
    case 4:
        for(auto i: m_teachers)
        {
            if(i->t_marry == "未婚")
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
        break;
    }
    //设置列数
    ui->teachertable_3->setColumnCount(8);
    //设置水平标头标签
    ui->teachertable_3->setHorizontalHeaderLabels(QStringList()<<"教师编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资"<<"婚否");
    //设置行数
    ui->teachertable_3->setRowCount(temp.size());
    //显示数据
    for(int row = 0; row < temp.size(); ++row)
    {
        int col = 0;
        //管理员查看表
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number(temp[row]->t_number)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_name));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_sex));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_birth));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_work));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_education));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number( temp[row]->t_salary)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_marry));
    }
}

//出生年月查询
void MainWindow::creatFindTable(double time, bool beforeOrAfter)
{
    QList<Teachers*> temp;

    //true为之前 false为之后
    if(beforeOrAfter)
    {
        for(auto i:m_teachers)
        {
            if(i->t_birth.toDouble() <= time)
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
    }
    else if(!beforeOrAfter)
    {
        for(auto i:m_teachers)
        {
            if(i->t_birth.toDouble() >= time)
            {
                auto t = new Teachers;
                t = i;
                temp.push_back(t);
            }
        }
    }
    //设置列数
    ui->teachertable_3->setColumnCount(8);
    //设置水平标头标签
    ui->teachertable_3->setHorizontalHeaderLabels(QStringList()<<"教师编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资"<<"婚否");
    //设置行数
    ui->teachertable_3->setRowCount(temp.size());
    //显示数据
    for(int row = 0; row < temp.size(); ++row)
    {
        int col = 0;
        //管理员查看表
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number(temp[row]->t_number)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_name));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_sex));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_birth));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_work));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_education));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number( temp[row]->t_salary)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_marry));
    }
}

//职称查询
void MainWindow::creatFindTable(QString work)
{
    QList<Teachers*> temp;

    for(auto i: m_teachers)
    {
        if(i->t_work == work)
        {
            auto t = new Teachers;
            t = i;
            temp.push_back(t);
        }
    }
    //设置列数
    ui->teachertable_3->setColumnCount(8);
    //设置水平标头标签
    ui->teachertable_3->setHorizontalHeaderLabels(QStringList()<<"教师编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资"<<"婚否");
    //设置行数
    ui->teachertable_3->setRowCount(temp.size());
    //显示数据
    for(int row = 0; row < temp.size(); ++row)
    {
        int col = 0;
        //管理员查看表
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number(temp[row]->t_number)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_name));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_sex));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_birth));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_work));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_education));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(QString::number( temp[row]->t_salary)));
        ui->teachertable_3->setItem(row,col++,new QTableWidgetItem(temp[row]->t_marry));
    }
}

void MainWindow::on_lookbtn_released()
{
    if(is_admin)
    {
        ui->stackedWidget->setCurrentWidget(ui->lookpage);
    }
    else
    {
        ui->stackedWidget->setCurrentWidget(ui->vistorlookpage);
    }
}

void MainWindow::on_lastpage_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}

void MainWindow::on_lastpage_2_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

void MainWindow::on_lastpage_3_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}

void MainWindow::on_vistorbtn_released()
{
    is_admin = false;
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}

void MainWindow::on_re_logbtn_released()
{
    is_admin = false;
    ui->stackedWidget->setCurrentWidget(ui->logpage);
}

void MainWindow::on_lastpage_4_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

//添加老师
void MainWindow::on_addbtn_released()
{
    //数据保存
    auto t = new Teachers;
    for(auto i: m_teachers)
    {
        if(i->t_number == ui->numberline->text().toInt())
        {
            QMessageBox::information(this,"提示","该教师编号已存在！");
            return;
        }
    }
    t->t_number = ui->numberline->text().toInt();
    t->t_name = ui->nameline->text();
    if(ui->manbtn->isChecked())
    {
        t->t_sex = ui->manbtn->text();
    }
    else if(ui->womanbtn->isChecked())
    {
        t->t_sex = ui->womanbtn->text();
    }
    t->t_birth=ui->birthline->text();
    t->t_work=ui->workline->text();
    t->t_education=ui->eduline->text();
    t->t_salary=ui->salaryline->text().toDouble();
    if(ui->marriedbtn->isChecked())
    {
        t->t_marry = ui->marriedbtn->text();
    }
    else if(ui->notmarriedbtn->isChecked())
    {
        t->t_marry = ui->notmarriedbtn->text();
    }

    QStringList lineData = ui->lessonline->text().split(",",QString::SplitBehavior::SkipEmptyParts);
    for(auto i: lineData)
    {
        bool is_have = false;
        for(auto j:m_lessons)
        {
            if(j->l_number == i)
            {
                is_have = true;
            }
        }
        if(is_have)
        {
            t->t_lessons.push_back(i);
        }
        else
        {
            QMessageBox::information(this,"提示","课程不存在！");
            return;
        }
    }

    m_teachers.push_back(t);
    //提示保存成功
    QMessageBox::information(this,"提示","操作完成！");
    //回到查询界面
    creatTeacherTable();
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

//删除老师
void MainWindow::on_deletebtn_released()
{
    bool is_find = false;
    int flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == ui->deleteline->text().toInt())
        {
            is_find =true;
            flag = i;
        }
    }

    if(is_find)
    {
        m_teachers.removeAt(flag);
        QMessageBox::information(this,"提示","删除成功！");
    }
    else
    {
        QMessageBox::information(this,"提示","操作失败！");
    }
    creatTeacherTable();
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

void MainWindow::on_to_addbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->addpage);
}

void MainWindow::on_to_deletebtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->deletepage);
}

void MainWindow::on_registerbtn_released()
{
    for(auto i: m_log)
    {
        if(i->log_usename == ui->usenameline->text() && i->log_password == ui->passwordline->text())
        {
            is_admin = true;
            break;
        }
    }
    if(is_admin)
    {
        QMessageBox::information(this,"提示","登陆成功！");
        ui->stackedWidget->setCurrentWidget(ui->menupage);
    }
    else
    {
        QMessageBox::information(this,"提示","用户名或密码错误！");
    }
}

void MainWindow::on_looklessonbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->looklessonpage);
}

void MainWindow::on_lastpage_5_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

//管理员查询课程
void MainWindow::on_looklessonbtn_2_released()
{
    bool is_find = false;
    int flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == ui->looklessonline->text().toInt())
        {
            is_find = true;
            flag = i;
        }
    }

    if(is_find)
    {
        lookLessonNumber = ui->looklessonline->text().toInt();
        creatLessonTable(*m_teachers[flag]);
        ui->stackedWidget->setCurrentWidget(ui->lessontablepage);
    }
    else
    {
        QMessageBox::information(this,"提示","输入有误！");
    }
}

void MainWindow::on_lastpage_6_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
}

void MainWindow::on_lastpagebtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lessontablepage);
}

//增加课程信息
void MainWindow::on_confirmbtn_released()
{
    //判断要添加的课程是否为新的课程
    bool is_have = false;
    for(auto i: m_lessons)
    {
        if(i->l_number == ui->lessonnumberline->text())
        {
            is_have = true;
        }
    }

    int flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == lookLessonNumber)
        {
            flag = i;
        }
    }

    for(auto i: m_teachers[flag]->t_lessons)
    {
        if(i == ui->lessonnumberline->text())
        {
            QMessageBox::information(this,"提示","该课程已经存在！");
            return ;
        }
    }
    //如果该课程已经存在，则直接将课程编号加入该老师的授课集
    if(is_have)
    {
        m_teachers[flag]->t_lessons.push_back(ui->lessonnumberline->text());
    }
    //如果课程不存在，则额外在全部课程中加入此课程
    else
    {
        auto l = new Lessons;
        l->l_number = ui->lessonnumberline->text();
        l->l_name = ui->lessonnameline->text();
        l->l_length = ui->lengthline->text().toDouble();
        l->l_room = ui->roomline->text();
        l->l_class = ui->classline->text();
        l->l_score = ui->scoreline->text().toDouble();
        l->l_time = ui->timeline->text();

        m_lessons.push_back(l);
        m_teachers[flag]->t_lessons.push_back(ui->lessonnumberline->text());
    }

    int t_flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == lookLessonNumber)
        {
            t_flag = i;
        }
    }

    creatLessonTable(*m_teachers[t_flag]);
    QMessageBox::information(this,"提示","添加成功！");
    ui->stackedWidget->setCurrentWidget(ui->lessontablepage);
}

//删除当前老师的课程
void MainWindow::on_deletelessonbtn_released()
{
    bool is_find = false;
    int t_flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == lookLessonNumber)
        {
            t_flag = i;
        }
    }

    int l_flag = 0;
    for(int i = 0; i < m_teachers[t_flag]->t_lessons.size(); ++i)
    {
        if(m_teachers[t_flag]->t_lessons[i] == ui->deletelessonline->text())
        {
            is_find = true;
            l_flag = i;
        }
    }

    if(is_find)
    {
        m_teachers[t_flag]->t_lessons.removeAt(l_flag);
        QMessageBox::information(this,"提示","删除成功！");
    }
    else
    {
        QMessageBox::information(this,"提示","操作失败！");
    }
    //回到查询界面
    creatLessonTable(*m_teachers[t_flag]);
    ui->stackedWidget->setCurrentWidget(ui->lessontablepage);
}

void MainWindow::on_lastpagebtn_2_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lessontablepage);
}

void MainWindow::on_addlessonbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->addlessonpage);
}

void MainWindow::on_eraselessonbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->eraselessonpage);
}

void MainWindow::on_visitorlooklessonbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->visitorlessonpage);
}

//游客查询课程
void MainWindow::on_visitorlooklessonbtn_2_released()
{
    bool is_find = false;
    int flag = 0;
    for(int i = 0; i < m_teachers.size(); ++i)
    {
        if(m_teachers[i]->t_number == ui->visitornumberline->text().toInt())
        {
            is_find = true;
            flag = i;
        }
    }

    if(is_find)
    {
        creatLessonTable(*m_teachers[flag]);
        ui->stackedWidget->setCurrentWidget(ui->visitorlessontable);
    }
    else
    {
        QMessageBox::information(this,"提示","输入有误！");
    }
}

void MainWindow::on_lastpage_20_released()
{
    ui->stackedWidget->setCurrentWidget(ui->vistorlookpage);
}

void MainWindow::on_lastpage_19_released()
{
    ui->stackedWidget->setCurrentWidget(ui->vistorlookpage);
}

//保存并退出
void MainWindow::on_quitbtn_released()
{
    //保存teachers文件
    QFile t_file(teacherFileName);
    if(!t_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"teachers文件打开失败";
        return;
    }

    for(auto i: m_teachers)
    {
        QString context = QString::number(i->t_number)+","+ i->t_name+","
                +i->t_sex+","+i->t_birth+","+i->t_work+","+i->t_education+","
                +QString::number(i->t_salary)+","+i->t_marry;
        for(auto j: i->t_lessons)
        {
            context +=","+j;
        }

        QTextStream t_stream(&t_file);
        t_stream << context << endl;
    }

    //保存lessons文件
    QFile l_file(LESSONS_FILENAME);
    if(!l_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"lessons文件打开失败";
        return;
    }

    for(auto i: m_lessons)
    {
        QString context = i->l_number+","+i->l_name+","+QString::number(i->l_length)+","+i->l_room+","
                +i->l_class+","+QString::number(i->l_score)+","+i->l_time;

        QTextStream l_stream(&l_file);
        l_stream << context << endl;
    }

    //保存log文件
    QFile log_file(LOG_FILENAME);
    if(!log_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"log文件打开失败";
        return;
    }

    for(auto i: m_log)
    {
        QString context = i->log_usename+","+i->log_password;
        QTextStream log_stream(&log_file);
        log_stream << context<< endl;
    }

    //关闭文件
    t_file.flush();
    t_file.close();
    l_file.flush();
    l_file.close();
    log_file.flush();
    log_file.close();

    //退出
    this->close();
}

//保存
void MainWindow::on_saveaction_triggered()
{
    //保存teachers文件
    QFile t_file(teacherFileName);
    if(!t_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"teachers文件打开失败";
        return;
    }

    for(auto i: m_teachers)
    {
        QString context = QString::number(i->t_number)+","+ i->t_name+","
                +i->t_sex+","+i->t_birth+","+i->t_work+","+i->t_education+","
                +QString::number(i->t_salary)+","+i->t_marry;
        for(auto j: i->t_lessons)
        {
            context +=","+j;
        }

        QTextStream t_stream(&t_file);
        t_stream << context << endl;
    }

    //保存lessons文件
    QFile l_file(LESSONS_FILENAME);
    if(!l_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"lessons文件打开失败";
        return;
    }

    for(auto i: m_lessons)
    {
        QString context = i->l_number+","+i->l_name+","+QString::number(i->l_length)+","+i->l_room+","
                +i->l_class+","+QString::number(i->l_score)+","+i->l_time;

        QTextStream l_stream(&l_file);
        l_stream << context << endl;
    }

    //保存log文件
    QFile log_file(LOG_FILENAME);
    if(!log_file.open(QIODevice::WriteOnly))
    {
        qInfo()<<"log文件打开失败";
        return;
    }

    for(auto i: m_log)
    {
        QString context = i->log_usename+","+i->log_password;
        QTextStream log_stream(&log_file);
        log_stream << context<< endl;
    }
    //关闭文件
    t_file.flush();
    t_file.close();
    l_file.flush();
    l_file.close();
    log_file.flush();
    log_file.close();
    QMessageBox::information(this,"提示","保存成功");
}

void MainWindow::on_quitaction_triggered()
{
    if( QMessageBox::Yes == QMessageBox::question(this,"提示","确定退出吗？",QMessageBox::Yes | QMessageBox::No))
    {
        this->close();
    }
}

void MainWindow::on_tomenuaction_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}

void MainWindow::on_reloginaction_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->logpage);
}

void MainWindow::on_findbtn_released()
{
    //flag用来标志不同的查询方式
    int flag = 0;

    QDialog dlg(this);
    dlg.setWindowTitle("分类查询");
    dlg.setFixedSize(300,400);

    QRadioButton sexBtn;
    sexBtn.setParent(&dlg);
    sexBtn.setText("性别");
    sexBtn.move(100,50);

    QRadioButton birthBtn;
    birthBtn.setParent(&dlg);
    birthBtn.setText("出生年月");
    birthBtn.move(100,110);

    QRadioButton workBtn;
    workBtn.setParent(&dlg);
    workBtn.setText("职称");
    workBtn.move(100,170);

    QRadioButton marryBtn;
    marryBtn.setParent(&dlg);
    marryBtn.setText("婚否");
    marryBtn.move(100,230);

    QPushButton confirmBtn(&dlg);
    confirmBtn.setText("确认");
    confirmBtn.move(120,290);

    connect(&confirmBtn,&QPushButton::released,[&](){
        //性别
        if(sexBtn.isChecked())
        {
            dlg.close();
            QDialog sexDlg(this);
            sexDlg.setWindowTitle("按照性别选择");
            sexDlg.setFixedSize(150,150);

            //flag = 1
            QRadioButton manBtn(&sexDlg);
            manBtn.setText("男");
            manBtn.move(30,30);
            //flag= = 2
            QRadioButton womanBtn(&sexDlg);
            womanBtn.setText("女");
            womanBtn.move(30,60);

            QPushButton sexConfirmBtn(&sexDlg);
            sexConfirmBtn.setText("确认");
            sexConfirmBtn.move(30,100);
            connect(&sexConfirmBtn,&QPushButton::released,[&](){
                if(manBtn.isChecked())
                {
                    flag = 1;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);

                }
                else if(womanBtn.isChecked())
                {
                    flag = 2;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                }
                sexDlg.close();
            });
            qInfo()<<"sex";
            sexDlg.exec();
        }
        //出生年月
        else if(birthBtn.isChecked())
        {
            dlg.close();

            bool beforeOrAfter = false;

            QDialog birthDlg(this);
            birthDlg.setWindowTitle("按照出生年月选择");
            birthDlg.setFixedSize(500,500);

            QRadioButton beforeBtn(&birthDlg);
            beforeBtn.setText("之前");
            beforeBtn.move(200,200);

            QRadioButton afterBtn(&birthDlg);
            afterBtn.setText("之后");
            afterBtn.move(200,270);

            QPushButton birthConfirmBtn(&birthDlg);
            birthConfirmBtn.setText("确认");
            birthConfirmBtn.move(220,350);

            QLabel birthLabel(&birthDlg);
            birthLabel.setText("请输入出生年月 :");
            birthLabel.move(50,100);

            QLineEdit birthLine(&birthDlg);
            birthLine.move(200,100);

            connect(&birthConfirmBtn,&QPushButton::released,[&](){
                if(beforeBtn.isChecked())
                {
                    beforeOrAfter = true;
                }
                else if(beforeBtn.isChecked())
                {
                    beforeOrAfter = false;
                }
                creatFindTable(birthLine.text().toDouble(), beforeOrAfter);
                ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                birthDlg.close();
            });
            qInfo()<<"birth";
            birthDlg.exec();
        }
        //婚否
        else if(marryBtn.isChecked())
        {
            dlg.close();
            QDialog marryDlg(this);
            marryDlg.setWindowTitle("按照婚否选择");
            marryDlg.setFixedSize(150,150);

            //flag = 3
            QRadioButton marriedBtn(&marryDlg);
            marriedBtn.setText("已婚");
            marriedBtn.move(30,30);
            //flag= = 4
            QRadioButton notMarriedBtn(&marryDlg);
            notMarriedBtn.setText("未婚");
            notMarriedBtn.move(30,60);

            QPushButton marryConfirmBtn(&marryDlg);
            marryConfirmBtn.setText("确认");
            marryConfirmBtn.move(30,100);
            connect(&marryConfirmBtn,&QPushButton::released,[&](){
                if(marriedBtn.isChecked())
                {
                    flag = 3;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);

                }
                else if(notMarriedBtn.isChecked())
                {
                    flag = 4;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                }
                marryDlg.close();
            });
            qInfo()<<"marry";
            marryDlg.exec();
        }
        //职称
        else if(workBtn.isChecked())
        {
            dlg.close();
            QDialog workDlg(this);
            workDlg.setWindowTitle("按照职称选择");
            workDlg.setFixedSize(500,300);

            QLabel workLabel(&workDlg);
            workLabel.setText("请输入职称 :");
            workLabel.move(50,100);

            QLineEdit workLine(&workDlg);
            workLine.move(200,100);

            QPushButton workConfirmBtn(&workDlg);
            workConfirmBtn.setText("确认");
            workConfirmBtn.move(220,200);
            connect(&workConfirmBtn,&QPushButton::released,[&](){
                creatFindTable(workLine.text());
                qInfo()<<workLine.text();
                ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                workDlg.close();
            });
            qInfo()<<"work";
            workDlg.exec();
        }
    });
    dlg.exec();
}

//游客分类查询
void MainWindow::on_visitorfindbtn_released()
{
    //flag用来标志不同的查询方式
    int flag = 0;

    QDialog dlg(this);
    dlg.setWindowTitle("分类查询");
    dlg.setFixedSize(300,400);

    QRadioButton sexBtn;
    sexBtn.setParent(&dlg);
    sexBtn.setText("性别");
    sexBtn.move(100,50);

    QRadioButton birthBtn;
    birthBtn.setParent(&dlg);
    birthBtn.setText("出生年月");
    birthBtn.move(100,110);

    QRadioButton workBtn;
    workBtn.setParent(&dlg);
    workBtn.setText("职称");
    workBtn.move(100,170);

    QRadioButton marryBtn;
    marryBtn.setParent(&dlg);
    marryBtn.setText("婚否");
    marryBtn.move(100,230);

    QPushButton confirmBtn(&dlg);
    confirmBtn.setText("确认");
    confirmBtn.move(120,290);

    connect(&confirmBtn,&QPushButton::released,[&](){
        //性别
        if(sexBtn.isChecked())
        {
            dlg.close();
            QDialog sexDlg(this);
            sexDlg.setWindowTitle("按照性别选择");
            sexDlg.setFixedSize(150,150);

            //flag = 1
            QRadioButton manBtn(&sexDlg);
            manBtn.setText("男");
            manBtn.move(30,30);
            //flag= = 2
            QRadioButton womanBtn(&sexDlg);
            womanBtn.setText("女");
            womanBtn.move(30,60);

            QPushButton sexConfirmBtn(&sexDlg);
            sexConfirmBtn.setText("确认");
            sexConfirmBtn.move(30,100);
            connect(&sexConfirmBtn,&QPushButton::released,[&](){
                if(manBtn.isChecked())
                {
                    flag = 1;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);

                }
                else if(womanBtn.isChecked())
                {
                    flag = 2;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                }
                sexDlg.close();
            });
            qInfo()<<"sex";
            sexDlg.exec();
        }
        //出生年月
        else if(birthBtn.isChecked())
        {
            dlg.close();

            bool beforeOrAfter = false;

            QDialog birthDlg(this);
            birthDlg.setWindowTitle("按照出生年月选择");
            birthDlg.setFixedSize(500,500);

            QRadioButton beforeBtn(&birthDlg);
            beforeBtn.setText("之前");
            beforeBtn.move(200,200);

            QRadioButton afterBtn(&birthDlg);
            afterBtn.setText("之后");
            afterBtn.move(200,270);

            QPushButton birthConfirmBtn(&birthDlg);
            birthConfirmBtn.setText("确认");
            birthConfirmBtn.move(220,350);

            QLabel birthLabel(&birthDlg);
            birthLabel.setText("请输入出生年月 :");
            birthLabel.move(50,100);

            QLineEdit birthLine(&birthDlg);
            birthLine.move(200,100);

            connect(&birthConfirmBtn,&QPushButton::released,[&](){
                if(beforeBtn.isChecked())
                {
                    beforeOrAfter = true;
                }
                else if(beforeBtn.isChecked())
                {
                    beforeOrAfter = false;
                }
                creatFindTable(birthLine.text().toDouble(), beforeOrAfter);
                ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                birthDlg.close();
            });
            qInfo()<<"birth";
            birthDlg.exec();
        }
        //婚否
        else if(marryBtn.isChecked())
        {
            dlg.close();
            QDialog marryDlg(this);
            marryDlg.setWindowTitle("按照婚否选择");
            marryDlg.setFixedSize(150,150);

            //flag = 3
            QRadioButton marriedBtn(&marryDlg);
            marriedBtn.setText("已婚");
            marriedBtn.move(30,30);
            //flag= = 4
            QRadioButton notMarriedBtn(&marryDlg);
            notMarriedBtn.setText("未婚");
            notMarriedBtn.move(30,60);

            QPushButton marryConfirmBtn(&marryDlg);
            marryConfirmBtn.setText("确认");
            marryConfirmBtn.move(30,100);
            connect(&marryConfirmBtn,&QPushButton::released,[&](){
                if(marriedBtn.isChecked())
                {
                    flag = 3;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);

                }
                else if(notMarriedBtn.isChecked())
                {
                    flag = 4;
                    creatFindTable(flag);
                    ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                }
                marryDlg.close();
            });
            qInfo()<<"marry";
            marryDlg.exec();
        }
        //职称
        else if(workBtn.isChecked())
        {
            dlg.close();
            QDialog workDlg(this);
            workDlg.setWindowTitle("按照职称选择");
            workDlg.setFixedSize(500,300);

            QLabel workLabel(&workDlg);
            workLabel.setText("请输入职称 :");
            workLabel.move(50,100);

            QLineEdit workLine(&workDlg);
            workLine.move(200,100);

            QPushButton workConfirmBtn(&workDlg);
            workConfirmBtn.setText("确认");
            workConfirmBtn.move(220,200);
            connect(&workConfirmBtn,&QPushButton::released,[&](){
                creatFindTable(workLine.text());
                qInfo()<<workLine.text();
                ui->stackedWidget->setCurrentWidget(ui->findpage_1);
                workDlg.close();
            });
            qInfo()<<"work";
            workDlg.exec();
        }
    });
    dlg.exec();
}

void MainWindow::on_lastpage_7_released()
{
    if(is_admin)
    {
        ui->stackedWidget->setCurrentWidget(ui->lookpage);
    }
    else
    {
        ui->stackedWidget->setCurrentWidget(ui->vistorlookpage);
    }
}

void MainWindow::on_registeradminbtn_released()
{
     ui->stackedWidget->setCurrentWidget(ui->registerpage_2);
}

void MainWindow::on_lastpage_8_released()
{
    ui->stackedWidget->setCurrentWidget(ui->logpage);
}

//注册账号
void MainWindow::on_registerconfirmbtn_2_released()
{
    bool is_exit = false;
    for(auto i: m_log)
    {
        if(i->log_usename == ui->usenameline_2->text())
        {
            is_exit == true;
        }
    }

    if(is_exit)
    {
        QMessageBox::information(this,"提示","该账号已存在!");
    }
    else if(!is_exit)
    {
        QMessageBox::information(this,"提示","注册成功!");

        auto log = new Log;
        log->log_usename = ui->usenameline_2->text();
        log->log_password = ui->passwordline_2->text();
        m_log.push_back(log);

        ui->stackedWidget->setCurrentWidget(ui->logpage);
    }
}

//打开文件
void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"打开文件",TEACHERS_FILENAME,"text file(*.txt)");
    teacherFileName = fileName;
    qInfo() << teacherFileName;
    loadData();
    creatTeacherTable();
    QMessageBox::information(this,"提示","打开成功");
}
