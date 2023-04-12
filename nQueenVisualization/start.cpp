#include "start.h"
#include "ui_start.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&MainWindow::on_pushButton_clicked);
    connect(ui->comboBox,SIGNAL(QComboBox::),this,SLOT(this::on_comboBox_currentIndexChanged(int index)));
    ui->lineEdit->clear();
    ui->lineEdit->setEchoMode(QLineEdit::Normal);
    ui->lineEdit->setPlaceholderText("0<N≤20");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int Queen_num = ui->lineEdit->text().toInt();
    //正常输入检测
    if(Queen_num>20)
    {
        QMessageBox::information(this,"不干","CPU:你想累死我啊?😅\n");
        ui->lineEdit->clear();
    }
    else if(Queen_num<=0)
    {
        QMessageBox::information(this,"?????????","你正常点😅\n");
        ui->lineEdit->clear();
    }
    else
    {
        table1 *t1 = new table1(Queen_num);
        QPixmap img(":/src/hinata.png");
        t1->setWindowIcon(img);
        t1->setWindowTitle("有点喉咙痛");
        t1->show();
        this->close();
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<ui->comboBox->currentIndex();
    if(ui->comboBox->currentIndex()==1)
    {
        QString fileName = QFileDialog::getOpenFileName(this,"选择一个测试案例", "../../../../../../../../test.txt");
        QFile f(fileName);
        f.open(QFile::ReadOnly);
        QString n =  f.readLine();
        if((n[0]>='0'&&n[0]<='9')||(n[1]>='0'&&n[1]<='9'))//摆烂,随便过滤一下做做样子
        {
            ui->lineEdit->setText(n);
            ui->comboBox->setCurrentIndex(0);
            ui->label->setText("文件读取：");
        }
        else if(n.isEmpty())
        {

        }
        else
        {
            QMessageBox::warning(this,"格式错误","请在文件第一行输入皇后个数");
            ui->comboBox->setCurrentIndex(0);
        }
    }
}
