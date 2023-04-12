#ifndef TABLE1_H
#define TABLE1_H
#include "start.h"
#include <QWidget>
#include <QTableWidget>
#include <QDebug>
#include <QTableView>
#include <QTimer>
#include <stacktype.h>
#include <QMessageBox>
#include <QThread>
#include <QMovie>
#include <QPixmap>
#include <QTableWidget>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#define FINISHED 0
#define PLACE_TEST 1
#define PLACED 2
#define CANT_PLACED 3
#define RET_LAST_COL 4
#define OVERFLOW_CHECK 5
#define SOLUTION 6
#define AFTER_SLT 7
namespace Ui {
class table1;
}

class table1 : public QWidget
{
    Q_OBJECT

public:
    explicit table1(int Queen_num,QWidget *parent = nullptr);
    ~table1();

private slots:
    void pop_slot();

    void push_slot();

    void on_start_btn_clicked();

    void on_step_btn_clicked();

    void timeoutEvent();

    void setColor(int x,int y,QColor c);

    void on_pushButton_clicked();

    void on_next_slt_btn_clicked();

    void on_speed_Slider_valueChanged(int value);

    void on_pushButton_2_clicked();

private:
    Ui::table1 *ui;
    QTableView*  tableView;
    QTableWidgetItem *item;
    QTimer *timer;
    QFile *output_file;
    QColor *redcolor;
    QColor *whitecolor;
    QColor *greencolor;
    QColor *bluecolor;
    QColor *purplecolor;
    StackType *S;
    int Queen_num;
    int x,y;
    int num;
    int currentStep;
    int stack_num;
    int start_btn_flag;
    int next_slt_flag;
    int speed;
    bool speed_change_flag;
    long int find_count;
};

#endif // TABLE1_H
