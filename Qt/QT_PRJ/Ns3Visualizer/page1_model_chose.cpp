#include "page1_model_chose.h"
#include "ui_page1_model_chose.h"

Page1_model_chose::Page1_model_chose(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page1_model_chose)
{
    ui->setupUi(this);
    connect(ui->checkBox, &QCheckBox::toggled, ui->textBrowser, [=](){
        ui->textBrowser->clear();
        ui->pushButton->setDisabled(ui->checkBox->isChecked());
        ui->pushButton_2->setDisabled(ui->checkBox->isChecked());
    });

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
    ui->textBrowser->setText(this->GetSceneName());
}


void Page1_model_chose::on_pushButton_3_clicked()
{
    if(ui->checkBox->isChecked()){
        this->hide();
        this->simu_config->show();
    }
    else{
        ;
    }

}

