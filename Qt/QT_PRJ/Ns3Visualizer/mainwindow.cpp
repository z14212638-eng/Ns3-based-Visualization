#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page1_model_chose.h"
#include <QtWidgets>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();

        //Horizontal centering of the main window
        int x = (screenGeometry.width() - this->width()) / 2;
        int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);
        ui->setupUi(this);
        
        //Connect the Main Window with subwindows' signals
        connect(ppage1,&Page1_model_chose::BackToMain,this,[=](){
            ppage1->hide();
            this->show();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

//once the next button is clicked,check the situation of the checkbox
void MainWindow::on_pushButton_clicked()
{
    if(!this->ui->checkBox->isChecked())
    {
        QMessageBox::warning(this, "User Agreement", "Please agree to the user agreement before using.");
        this->ui->tabWidget->setCurrentIndex(2);
    }
    else
    {
    this->hide();
    this->ppage1->show();
    }
}

