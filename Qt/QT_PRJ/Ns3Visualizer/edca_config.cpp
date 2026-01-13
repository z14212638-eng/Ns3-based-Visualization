#include "edca_config.h"
#include "ui_edca_config.h"

Edca_config::Edca_config(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Edca_config)
{
    ui->setupUi(this);
}

Edca_config::~Edca_config()
{
    delete ui;
}

void Edca_config::on_buttonBox_accepted()
{
     AC_VO_cwmin = ui->spinBox->value();
     AC_VO_cwmax = ui->spinBox_2->value();
     AC_VO_AIFSN = ui->spinBox_3->value();
     AC_VO_TXOP_LIMIT = ui->spinBox_4->value();

     AC_VI_cwmin = ui->spinBox_5->value();
     AC_VI_cwmax = ui->spinBox_7->value();
     AC_VI_AIFSN = ui->spinBox_9->value();
     AC_VI_TXOP_LIMIT = ui->spinBox_8->value();

     AC_BE_cwmin = ui->spinBox_6->value();
     AC_BE_cwmax = ui->spinBox_10->value();
     AC_BE_AIFSN = ui->spinBox_11->value();
     AC_BE_TXOP_LIMIT = ui->spinBox_12->value();

     AC_BK_cwmin = ui->spinBox_13->value();
     AC_BK_cwmax = ui->spinBox_14->value();
     AC_BK_AIFSN = ui->spinBox_15->value();
     AC_BK_TXOP_LIMIT = ui->spinBox_16->value();

     Msdu_aggregation = ui->checkBox->isChecked();
     AMsdu_type = ui->comboBox->currentText();
     MaxAMsduSize = ui->spinBox_17->value();

     Mpdu_aggregation = ui->checkBox_2->isChecked();
     AMpdu_type = ui->comboBox_2->currentText();
     MaxAMpduSize = ui->spinBox_18->value();
     Density = ui->spinBox_19->value();
}

