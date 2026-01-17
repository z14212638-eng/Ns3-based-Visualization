#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page1_model_chose.h"
#include <QtWidgets>
MainWindow::MainWindow(QWidget *parent)
    : IndustrialWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 确保窗口大小已设置好
    ui->pushButton->resize(100, 30); // 调整按钮大小
    
    this->showMaximized();

    // 连接子窗口返回信号
    connect(ppage1, &Page1_model_chose::BackToMain, this, [=]()
            {
                ppage1->close();
                this->showMaximized();
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// once the next button is clicked,check the situation of the checkbox
void MainWindow::on_pushButton_clicked()
{

        this->close();
        this->ppage1->showMaximized();
;

}
