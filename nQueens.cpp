#include "nQueens.h"
#include "start.h"
#include "ui_nQueens.h"

table1::table1(int Queen_num, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table1)
{
    ui->setupUi(this);
    //Queen_num个皇后及表格行列数
    this->Queen_num = Queen_num;

//    开辟堆空间
    this->timer = new QTimer();
    redcolor = new QColor(230,215,142);
    greencolor = new QColor(0,200,0);
    whitecolor = new QColor(255,255,255);
    bluecolor = new QColor(0,0,255);
    purplecolor = new QColor(157,99,188);
    S = new StackType();

//  实现结果保存功能
    output_file = new QFile("Output_1111.txt");
    output_file->open(QIODevice::WriteOnly);
    output_file->write("");
    output_file->open(QIODevice::Append);


//初始化局部变量以及标志
    num = 0;
    y = 1;
    x = S->rsp;
    find_count =0;
    start_btn_flag = 1;
    next_slt_flag = 0;
    stack_num = 0;
    currentStep = PLACE_TEST;
    speed =  ui->speed_Slider->value();

//链接信号和槽
    connect(this->timer,&QTimer::timeout,this,&table1::timeoutEvent);
    connect(S,&StackType::sgn_pop,this,&table1::pop_slot);
    connect(S,&StackType::sgn_push,this,&table1::push_slot);

//    初始化运行表格
    ui->tableWidget->setColumnCount(Queen_num);
    ui->tableWidget->setRowCount(Queen_num);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(50);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
//    初始化栈表格
    ui->stack_table->setColumnCount(1);
    ui->stack_table->setRowCount(Queen_num+1);
    ui->stack_table->horizontalHeader()->hide();
    ui->stack_table->verticalHeader()->hide();
    ui->stack_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->stack_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->stack_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stack_table->setSelectionMode(QAbstractItemView::NoSelection);

    //初始化布局
    ui->step_btn->setAutoRepeat(true);
    ui->step_btn->setAutoRepeatDelay(400);
    ui->step_btn->setAutoRepeatInterval(200);
    ui->status_label->setText("待程序开始");
    item = new QTableWidgetItem("Stack top");
    item->setTextAlignment(Qt::AlignCenter);
    item->setBackground(*purplecolor);
    ui->stack_table->setItem(0,Queen_num,item);
    QPixmap img(":/src/hs.jpg");

    ui->cpu_statu->setPixmap(img);
    QPixmap play(":/src/play.png");
    ui->start_btn->setIcon(play);

    QPixmap save(":/src/save.png");
    ui->pushButton_2->setIcon(save);
    QPixmap reboot(":/src/reboot.png");
    ui->pushButton->setIcon(reboot);
    QPixmap next(":/src/next.png");
    ui->next_slt_btn->setIcon(next);
    QPixmap step(":/src/step.png");
    ui->step_btn->setIcon(step);
    QSize size(25,25);
    ui->start_btn->setIconSize(size);
    ui->next_slt_btn->setIconSize(size);
    size.setWidth(20);
    size.setHeight(20);
    ui->step_btn->setIconSize(size);
//    on_pushButton_clicked();//bug,程序刚开始不能双击表格触发槽函数
//    ui->start_btn->setStyleSheet("text-align:center; padding-left:20px;");

}

table1::~table1()
{
    delete ui;
}
//开始按钮
void table1::on_start_btn_clicked()
{
    if(start_btn_flag)
    {
        timer->start(speed);
//        next_slt_flag = 0;
        ui->start_btn->setText("Stop");
        QPixmap pause(":/src/pause.png");
        ui->start_btn->setIcon(pause);
        ui->status_label->setText("查找中......");
        start_btn_flag = 0;
    }
    else
    {
        timer->stop();
        ui->start_btn->setText("Start");
        QPixmap play(":/src/play.png");
        ui->start_btn->setIcon(play);
        ui->status_label->setText("暂停中");
        start_btn_flag = 1;
    }
}

//单步按钮
void table1::on_step_btn_clicked()
{
    start_btn_flag = 0;
    speed_change_flag = 0;
    on_start_btn_clicked();
    QTimer::singleShot(0,this,&table1::timeoutEvent);
}

//下一个解按钮
void table1::on_next_slt_btn_clicked()
{
    start_btn_flag = 1;
    speed = 0;
    on_start_btn_clicked();
    ui->status_label->setText("正在寻找下一个解......");
    next_slt_flag = 1;
}

//速度滑动条设置
void table1::on_speed_Slider_valueChanged(int value)
{
    speed = value;
    if(ui->speed_Slider->value()>180)
    {
        QPixmap img(":/src/xdm.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    else if(ui->speed_Slider->value()>=140)
    {
        QPixmap img(":/src/x2.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    else if(ui->speed_Slider->value()>=100)
    {
        QPixmap img(":/src/zbj.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    else if(ui->speed_Slider->value()>=60)
    {
        QPixmap img(":/src/nxbj.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    else if(ui->speed_Slider->value()>=10)
    {
        QPixmap img(":/src/Alice.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    else
    {
        QPixmap img(":/src/default.jpg");
        ui->cpu_statu->setPixmap(img);
    }
    speed_change_flag = 1;
}

//重置按钮
void table1::on_pushButton_clicked()
{
    ui->start_btn->setText("Start");
    ui->step_num->clear();
    start_btn_flag = 0;
    on_start_btn_clicked();
    y = 1;
    x = 0;
    num = 0;
    S->rsp = 0;
    stack_num = 0;
    find_count =0;
    S->isFound = false;
    start_btn_flag = 1;
    next_slt_flag = 0;
    currentStep = PLACE_TEST;
    output_file->close();
    output_file->open(QIODevice::WriteOnly);
    output_file->write("");
    output_file->open(QIODevice::Append);
    for (int i = 1;i<=Queen_num;i++) {
        item = new QTableWidgetItem();
        ui->stack_table->setItem(i-1,0,item);
        for (int j = 1;j<=Queen_num;j++) {
            setColor(i,j,*whitecolor);
        }
    }

    ui->status_label->setText("重开");
    ui->solution_lable->clear();
    item = new QTableWidgetItem("Stack top");
    item->setBackground(*purplecolor);
    item->setTextAlignment(Qt::AlignCenter);
    ui->stack_table->setItem(Queen_num,0,item);

}


//栈表格设置push
void table1::push_slot()
{
    qDebug() << "push:" << S->rsp<<","<<S->col[S->rsp];
    //提升栈顶
    item = new QTableWidgetItem("Stack top");
    item->setBackground(*purplecolor);
    item->setTextAlignment(Qt::AlignCenter);
    ui->stack_table->setItem(Queen_num-S->rsp,0,item);

    //数据入栈
    QString data = QString("(%1,%2)").arg(QString::number(S->rsp)).arg(QString::number(y));
    item = new QTableWidgetItem(data);
    item->setTextAlignment(Qt::AlignCenter);
    ui->stack_table->setItem(Queen_num-S->rsp+1,0,item);
}

//栈表格设置pop
void table1::pop_slot()
{
    qDebug() << "pop:" << S->rsp<<","<<S->col[S->rsp];
    //数据出栈
    item = new QTableWidgetItem();
    ui->stack_table->setItem(Queen_num-S->rsp-1,0,item);
    //栈顶下降
    item = new QTableWidgetItem("Stack top");
    item->setBackground(*purplecolor);
    item->setTextAlignment(Qt::AlignCenter);
    ui->stack_table->setItem(Queen_num-S->rsp,0,item);
}

//设置表格颜色
void table1::setColor(int inputx,int inputy,QColor c)
{
    item = new QTableWidgetItem();
    item->setBackground(c);
    ui->tableWidget->setItem(inputx-1,inputy-1,item);
}

//栈回溯算法，并且实现单步运行
void table1::timeoutEvent()
{
    //基于QT滑动条机制改良 实现丝滑变速
    if(speed_change_flag)
    {
        timer->start(speed);
        speed_change_flag = 0;
    }

    //遍历结束条件:第一行的测试位置越界
    if((x==0&&y==Queen_num+1)||(Queen_num==1&&num==1))//Queen_num==1时y不能等于Queen_num+1特殊情况特殊处理
    {
        timer->stop();
        on_start_btn_clicked();
        QString output = QString("共找到%1组解\n步数：%2").arg(QString::number(num)).arg(QString::number(find_count));
        QMessageBox::information(this,"Finish",output);
        output_file->close();
        return;
    }

    switch (currentStep)
    {
    case PLACE_TEST://测试位置是否符合放置条件
    {
        find_count++;
        QString step = QString("搜索步数:%1").arg(QString::number(find_count));
        ui->step_num->setText(step);
        if(y!=1)
            setColor(x+1,y-1,*whitecolor);
        setColor(x+1,y,*redcolor);
        if(S->place(S,x+1,y))
            currentStep = PLACED;//下一步跳转位置
        else
            currentStep = CANT_PLACED;//下一步跳转位置
        break;
    }
    case PLACED://符合放置条件,入栈
    {
        S->push(y);
        x = S->rsp;
        setColor(x,y,*greencolor);
        if(x==Queen_num)
        {
            currentStep = SOLUTION;//若到达最后一行,转跳至输出解
        }
        else
        {
            y = 1;
            currentStep = PLACE_TEST;//否则y置1,返回测试遍历下一行
        }
        break;
    }
    case CANT_PLACED://该位置不符合放置条件
    {
        if(y==Queen_num)
        {
            currentStep = RET_LAST_COL;//如果已遍历完该行,则退一行找下个位置
            setColor(x+1,y,*whitecolor);
        }
        else
        {
            y++;
            currentStep = PLACE_TEST;//返回测试下一列是否符合条件
            timeoutEvent();//这里为了实现动画连贯而再次调该函数
        }
        break;
    }
    case RET_LAST_COL:
    {
        y = S->pop() + 1;//用pop函数获取上一行放置的列数,+1为下个位置
        setColor(x,y-1,*whitecolor);
        x = S->rsp;
        currentStep = OVERFLOW_CHECK;//测试上一行+1的位置是否越界了
        break;
    }
    case OVERFLOW_CHECK://越界检测
    {
        if(y>Queen_num)
        {
            setColor(x,y-1,*whitecolor);
            y = S->pop() + 1;
            x = S->rsp;
            currentStep = PLACE_TEST;
        }
        else
        {
            currentStep = PLACE_TEST;
        }
        timeoutEvent();//这里为了实现动画连贯而再次调该函数
        break;
    }
    case SOLUTION:
    {
        //输出解
        this->num++;
        QByteArray ba;
        QString output = QString("已找到%1组解!").arg(QString::number(num));
        ui->solution_lable->setText(output);
        ba.append(output);
        ba.append('\n');
//        S->ShowStack();
        for (int i = 1; i <= S->rsp; i++)
        {
            //将结果加到输出字节流里，用于保存文件结果用
            ba.append('<');
            ba.append(QString::number(i));
            ba.append(',');
            ba.append(QString::number(S->col[i]));
            ba.append(">\n");
            //控制台输出结果
            qDebug() << '<' << i << ',' << S->col[i] << ">  ";
        }
        ba.append('\n');
        output_file->write(ba);
        if(this->num%10==0)
            output_file->flush();

        currentStep = AFTER_SLT;//得到一个解后恢复程序变量

        for (int i = 1;i<=S->rsp;i++) {
            setColor(i,S->col[i],*bluecolor);//让表格元素变为蓝色
        }

        //下面代码用于配合Next Solution按钮实现点击一下搜索出一个解
        if(next_slt_flag)
        {
            timer->stop();
            speed = ui->speed_Slider->value();
            start_btn_flag = 0;
            next_slt_flag = 0;
            on_start_btn_clicked();
        }
        break;
    }
    case AFTER_SLT://得出解后恢复程序数据 继续遍历
    {
        for (int i = 1;i<=S->rsp;i++) {
            setColor(i,S->col[i],*greencolor);
        }
        setColor(x,y,*whitecolor);
        y = S->pop();
        x = S->rsp;
        currentStep = RET_LAST_COL;
        break;
    }
    }
}

//保存按钮槽函数
void table1::on_pushButton_2_clicked()
{
//    QString fileName = QFileDialog::getSaveFileName(this,"你想保存在哪?", QCoreApplication::applicationFilePath());
    QString fileName = QFileDialog::getSaveFileName(this,"你想保存在哪?", "../../../../../../../../Solutions.txt");

    if(!fileName.isEmpty())
    {
        //        output_file->open(QIODevice::Append);
        //        QByteArray step;
        //        step.append(QString("搜索步数:%1").arg(QString::number(find_count)));
        //        output_file->write(step);
        output_file->flush();
        QFile::remove(fileName);
        QFile::copy("Output_1111.txt",fileName);
        qDebug() << "文件已保存至:" << fileName;
    }
}
