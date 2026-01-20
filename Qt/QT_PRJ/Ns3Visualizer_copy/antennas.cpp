#include "antennas.h"
#include "ui_antennas.h"
#include <iostream>

Antenna::Antenna(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Antenna)
{
    ui->setupUi(this);
    centerWindow(this);
    ui->widget->close();
    on_buttonBox_accepted();
}

Antenna::~Antenna()
{
    delete ui;
}

void Antenna::on_pushButton_clicked()
{
    ui->widget->show();
    qint8 item_num = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(item_num+1);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->buttonBox->setEnabled(false);
}

//Page_antenna_Confirm(adding a new antenna to the list)
void Antenna::on_pushButton_3_clicked()
{
    QString antenna_type = ui->comboBox->currentText();
    qint16 MaxGain = ui->spinBox->value();
    qint16 BeamWidth = ui->spinBox_2->value();
    qint8 rowCount = ui->tableWidget->rowCount();
    qint8 lastrow = rowCount - 1;
    std::cout<<antenna_type.toStdString()<<"  "<<MaxGain<<" "<<BeamWidth<<" "<<rowCount<<std::endl;
    ui->tableWidget->setItem(lastrow,0,new QTableWidgetItem(antenna_type));
    ui->tableWidget->setItem(lastrow,1,new QTableWidgetItem(QString::number(MaxGain)));
    ui->tableWidget->setItem(lastrow,2,new QTableWidgetItem(QString::number(BeamWidth)));
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->buttonBox->setEnabled(true);
    emit (this->is_ap ? BackToLastPage_AP() : BackToLastPage_STA());
}


void Antenna::on_pushButton_2_clicked()
{
    qint8 rowCount = ui->tableWidget->rowCount();
    qint8 lastrow = rowCount - 1;
    ui->tableWidget->removeRow(lastrow);
}



void Antenna::on_buttonBox_accepted() {
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++) {
        if (!ui->tableWidget->item(i, 0) || !ui->tableWidget->item(i, 1) || !ui->tableWidget->item(i, 2)) {
            qWarning() << "Missing table item at row" << i;
            continue;
        }
        auto new_antenna = std::make_shared<Antenna_Config>(
            ui->tableWidget->item(i, 0)->text(),
            ui->tableWidget->item(i, 1)->text().toInt(),
            ui->tableWidget->item(i, 2)->text().toInt()
        );
        antenna_list.append(std::move(new_antenna));
    }
}

qint16 Antenna::AntennaCount() const {
    return ui->tableWidget->rowCount();
}
