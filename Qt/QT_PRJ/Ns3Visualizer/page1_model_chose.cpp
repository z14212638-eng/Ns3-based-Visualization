#include "page1_model_chose.h"
#include "ui_page1_model_chose.h"

Page1_model_chose::Page1_model_chose(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page1_model_chose)
{
    ui->setupUi(this);
    centerWindow(this);

}

QString  Page1_model_chose::GetSceneName()
{
    QString name_selected = "";
    // QString name_1 = "";
    
    // if(ui->listWidget->currentItem()->text() != "None")
    // {
    //     name_1 = ui->listWidget->currentItem()->text();
    //     ui->listWidget_2->setCurrentRow(0);
    // }
    // else
    // {
    //     ui->listWidget->setCurrentRow(0);
    //     name_1 = ui->listWidget_2->currentItem()->text();
    // }

    // name_selected = ui->toolBox->currentWidget()->findChild<QListWidget*>("listWidget")->currentItem()->text();
    if(ui->toolBox->currentWidget()->findChild<QListWidget*>("listWidget"))
    {
        return name_selected = ui->toolBox->currentWidget()->findChild<QListWidget*>("listWidget")->currentItem()->text();
    }
    else if(ui->toolBox->currentWidget()->findChild<QListWidget*>("listWidget_2"))
    {
        return name_selected = ui->toolBox->currentWidget()->findChild<QListWidget*>("listWidget_2")->currentItem()->text();
    }
}

Page1_model_chose::~Page1_model_chose()
{
    delete ui;
}

void Page1_model_chose::on_pushButton_4_clicked()
{
    emit BackToMain();
}

void Page1_model_chose::on_pushButton_clicked()
{
    ;
}


void Page1_model_chose::on_pushButton_3_clicked()
{
    if(ui->checkBox->isChecked()){
        this->close();
        this->simu_config->showMaximized();
;
    }
    else{
        ;
    }

}

