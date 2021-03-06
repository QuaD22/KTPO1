#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(&graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    float x, y;
    x=ui->doubleSpinBox->value();
    y=ui->doubleSpinBox_2->value();
    graph.cx=x;
    graph.cy=y;
    int z=check(x,y);
    switch (z)
    {
    case -1:
        ui->label->setText("Точка не принадлежит области.");
        break;
    case 0:
        ui->label->setText("Точка лежит на границе области.");
        break;
    case 1:
        ui->label->setText("Точка принадлежит области.");
        break;
    }

    graph.update();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(this,tr("Открыть"),"//",tr("TXT(*.txt)")));
}

void MainWindow::on_pushButton_3_clicked()
{
    int i=0;
    int z;
    QList <float> array;
    QFile fread(ui->lineEdit->text());
    if (!fread.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QFile fsave(ui->lineEdit_2->text());
    QString fname=ui->lineEdit_2->text();
    if(!fname.endsWith(".txt"))
    {
        ui->label->setText("Неверный формат.");
        return;
    }
    if (!fsave.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QString line;
    QString num;
    float n;
    line=fread.readLine();
    QTextStream out(&fsave);
    QString num2;
    while(!line.isEmpty())
    {
        num=line.section(' ',0,0);
        n=num.toFloat();
        num=num.trimmed();
        num2=QLocale::system().toString(n,'f',1);
        num2=num2.trimmed();
        num2.replace(",",".");
        //out<<"\n1."<<num<<" "<<num2;
        if(num!=num2)
        {
            ui->label->setText("Неверный формат.");
            return;
        }
        array.push_back(n);
        line.remove(0,line.indexOf(' '));
        num=line.section(' ',1,1);
        n=num.toFloat();
        num=num.trimmed();
        num2=QLocale::system().toString(n,'f',1);
        num2=num2.trimmed();
        num2.replace(",",".");
        //out<<"\n2."<<num<<" "<<num2;
        if(num!=num2)
        {
            ui->label->setText("Неверный формат.");
            return;
        }
        array.push_back(n);
        line=fread.readLine();
    }
    fread.close();
    for(i=0;i<array.size();i=i+2)
    {
        z=check(array[i],array[i+1]);
        switch (z)
        {
        case -1:
            out<<array[i]<<" "<<array[i+1]<<tr(" Точка не принадлежит области.")<<endl;
            break;
        case 0:
           out<<array[i]<<" "<<array[i+1]<<tr(" Точка лежит на границе области.")<<endl;
            break;
        case 1:
            out<<array[i]<<" "<<array[i+1]<<tr(" Точка принадлежит области.")<<endl;
            break;
        }
    }
    fsave.close();
    ui->label->setText("Результаты записаны в файл.");

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit_2->setText(QFileDialog::getSaveFileName(this,tr("Сохранить"),"//",tr("TXT(*.txt)"),0,0));
}
