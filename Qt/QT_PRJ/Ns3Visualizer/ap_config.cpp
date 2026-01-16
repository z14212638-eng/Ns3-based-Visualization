#include "ap_config.h"
#include "ui_ap_config.h"

Ap_config::Ap_config(QWidget *parent)
    : QWidget(parent), ui(new Ui::Ap_config)
{
    ui->setupUi(this);

    centerWindow(this);

    if (!ui->checkBox_4->isChecked())
    {
        pos_set = true;
    }

    if (!ui->checkBox_3->isChecked())
    {
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->doubleSpinBox_4->setEnabled(false);
        ui->doubleSpinBox_5->setEnabled(false);
        ui->doubleSpinBox_14->setEnabled(false);
        ui->doubleSpinBox_15->setEnabled(false);
        ui->doubleSpinBox_16->setEnabled(false);
        ui->doubleSpinBox_17->setEnabled(false);
    }

    if (phymac_set != true)
    {
        ui->tabWidget->setTabEnabled(3, false);
    }
    ui->tableWidget->setRowCount(0);

    //deduce the GI from the selected protocol
    ui->comboBox_5->setCurrentIndex(5);
    ui->comboBox_15->setEnabled(false);
    connect(ui->comboBox_5,
            &QComboBox::currentTextChanged,
            this,
            [this](const QString &text)
            {
                auto gi = get_gi_from_string(text.toStdString());

                for (int i = 0; i < ui->comboBox_15->count(); ++i)
                {
                    ui->comboBox_15->setItemData(
                        i, QVariant(), Qt::UserRole - 1);
                }

                switch (gi)
                {
                case GI_MAP::k80211a:
                case GI_MAP::k80211b:
                case GI_MAP::k80211g:
                    ui->comboBox_15->setCurrentIndex(1);
                    ui->comboBox_15->setEnabled(false);
                    break;

                case GI_MAP::k80211n:
                case GI_MAP::k80211ac:
                    ui->comboBox_15->setEnabled(true);
                    ui->comboBox_15->setCurrentIndex(1);
                    ui->comboBox_15->setItemData(
                        2, QVariant(0), Qt::UserRole - 1);
                    ui->comboBox_15->setItemData(
                        3, QVariant(1), Qt::UserRole - 1);
                    break;

                case GI_MAP::k80211ax:
                    ui->comboBox_15->setEnabled(true);
                    ui->comboBox_15->setCurrentIndex(1);
                    ui->comboBox_15->setItemData(
                        0, QVariant(0), Qt::UserRole - 1);

                default:
                    break;
                }
            });
}

Ap_config::~Ap_config()
{
    delete ui;
}

// Page1_Finished
void Ap_config::on_pushButton_clicked()
{
    if (!ui->checkBox_4->isChecked())
    {

        if (ui->doubleSpinBox->value() != 0.00 || ui->doubleSpinBox_2->value() != 0.00 || ui->doubleSpinBox_3->value() != 0.00)
        {

            ui->tabWidget->setCurrentIndex(1);
            this->one_ap->m_position = {ui->doubleSpinBox->value(),
                                        ui->doubleSpinBox_2->value(),
                                        ui->doubleSpinBox_3->value()};
            pos_set = true;
        }
        else
        {
            QMessageBox::critical(
                this,
                "Error",
                "The position can not be (0,0,0)",
                QMessageBox::Ok);
        }
    }
    else
    {
        pos_set = true;

        // Random position
        double x_max = this->Building_range[0];
        double y_max = this->Building_range[1];
        double z_max = this->Building_range[2];
        double x_rand = get_true_random_double(0, x_max);
        double y_rand = get_true_random_double(0, y_max);
        double z_rand = get_true_random_double(0, z_max);

        this->one_ap->m_position = {x_rand, y_rand, z_rand};
        std::cout << "The position of AP is: " << x_rand << " " << y_rand << " " << z_rand << std::endl;
        ui->tabWidget->setCurrentIndex(1);
    }
}

// Page2_Finished
void Ap_config::on_pushButton_4_clicked()
{
    // If mobility is not set
    if (!ui->checkBox_3->isChecked())
    {
        ui->tabWidget->setCurrentIndex(2);
        mobility_set = true;
        this->one_ap->Mobility = false;
        return;
    }

    // If mobility is set and "random" mode is selected
    else if (ui->checkBox_3->isChecked() && ui->comboBox->currentText() == "Random Mobility Model")
    {
        this->one_ap->Mobility = true;
        this->one_ap->mode = "Random Mobility Model";
        double x_max = this->Building_range[0];
        double y_max = this->Building_range[1];
        double z_max = this->Building_range[2];
        double x_rand_1 = get_true_random_double(0, x_max);
        double y_rand_1 = get_true_random_double(0, y_max);
        double z_rand_1 = get_true_random_double(0, z_max);
        double x_rand_2 = get_true_random_double(0, x_max);
        double y_rand_2 = get_true_random_double(0, y_max);
        double z_rand_2 = get_true_random_double(0, z_max);

        ui->doubleSpinBox_14->setValue((x_rand_1 > x_rand_2) ? x_rand_2 : x_rand_1);
        ui->doubleSpinBox_15->setValue((x_rand_1 > x_rand_2) ? x_rand_1 : x_rand_2);
        ui->doubleSpinBox_16->setValue((y_rand_1 > y_rand_2) ? y_rand_2 : y_rand_1);
        ui->doubleSpinBox_17->setValue((y_rand_1 > y_rand_2) ? y_rand_1 : y_rand_2);

        // set the boundaries of mobility
        this->one_ap->boundaries = {ui->doubleSpinBox_14->value(), ui->doubleSpinBox_15->value(), ui->doubleSpinBox_16->value(), ui->doubleSpinBox_17->value()};
        this->one_ap->time_change_interval = ui->doubleSpinBox_4->value();
        this->one_ap->mode = ui->comboBox_2->currentText();
        this->one_ap->distance_change_interval = ui->doubleSpinBox_5->value();
        this->one_ap->random_velocity = ui->doubleSpinBox_18->value();

        std::cout << "The boundaries of AP is: " << this->one_ap->boundaries[0] << " " << this->one_ap->boundaries[1] << " " << this->one_ap->boundaries[2] << " " << this->one_ap->boundaries[3] << std::endl;
        std::cout << "The time change interval of AP is: " << this->one_ap->time_change_interval << std::endl;
        std::cout << "The distance change interval of AP is: " << this->one_ap->distance_change_interval << std::endl;
        std::cout << "The random velocity of AP is: " << this->one_ap->random_velocity << std::endl;
        std::cout << "The mode of AP is: " << this->one_ap->mode.toStdString() << std::endl;

        ui->tabWidget->setCurrentIndex(2);
        this->one_ap->Mobility = true;
        return;
    }
    // If not choosing the "random" mode,check if the conditions are valid
    else if ((ui->doubleSpinBox_15->value() > ui->doubleSpinBox_14->value()) &&
             (ui->doubleSpinBox_17->value() > ui->doubleSpinBox_16->value()) &&
             (ui->doubleSpinBox_4->value() != 0.00 || ui->doubleSpinBox_5->value() != 0.00) &&
             (ui->comboBox->currentText() == "Draw the Route Manually"))
    {
        mobility_set = true;
    }
    else
    {
        mobility_set = false;
    }
    if (!pos_set)
    {
        ui->tabWidget->setCurrentIndex(0);
        QMessageBox::critical(
            this,
            "Error",
            "Please set the position",
            QMessageBox::Ok);
    }

    else
    {
        if (mobility_set)
        {
            ui->tabWidget->setCurrentIndex(2);
            this->one_ap->Mobility = true;
        }

        else
        {
            QMessageBox::critical(
                this,
                "Error",
                "Please set the mobility correctly",
                QMessageBox::Ok);
        }
    }
}

// Page1_Random_Position
void Ap_config::on_checkBox_4_clicked(bool checked)
{
    if (checked)
    {
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox_2->setEnabled(false);
        ui->doubleSpinBox_3->setEnabled(false);
        pos_set = true;
    }
    else
    {
        ui->doubleSpinBox->setEnabled(true);
        ui->doubleSpinBox_2->setEnabled(true);
        ui->doubleSpinBox_3->setEnabled(true);
    }
}

// Page2_Mobility
void Ap_config::on_checkBox_3_clicked(bool checked)
{
    if (checked)
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->doubleSpinBox_4->setEnabled(true);
        ui->doubleSpinBox_5->setEnabled(true);
        ui->doubleSpinBox_14->setEnabled(true);
        ui->doubleSpinBox_15->setEnabled(true);
        ui->doubleSpinBox_16->setEnabled(true);
        ui->doubleSpinBox_17->setEnabled(true);
        ui->doubleSpinBox_18->setEnabled(true);
        mobility_set = false;
    }
    else
    {
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->doubleSpinBox_4->setEnabled(false);
        ui->doubleSpinBox_5->setEnabled(false);
        ui->doubleSpinBox_14->setEnabled(false);
        ui->doubleSpinBox_15->setEnabled(false);
        ui->doubleSpinBox_16->setEnabled(false);
        ui->doubleSpinBox_17->setEnabled(false);
        ui->doubleSpinBox_18->setEnabled(false);
        mobility_set = true;
    }
}

// Page3_Beacon
void Ap_config::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        beacon_set = true;
        ui->doubleSpinBox_12->setEnabled(true);
        ui->doubleSpinBox_13->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
    }
    else
    {
        beacon_set = false;
        ui->doubleSpinBox_12->setEnabled(false);
        ui->doubleSpinBox_13->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
    }
}

// Page3_Rts_Cts
void Ap_config::on_checkBox_5_clicked(bool checked)
{
    if (checked)
    {
        ui->spinBox_3->setEnabled(true);
        Rts_Cts_set = true;
    }
    else
    {
        ui->spinBox_3->setEnabled(false);
        Rts_Cts_set = false;
    }
}

// Page3_Qos

void Ap_config::on_checkBox_6_clicked(bool checked)
{
    if (checked)
    {
        ui->comboBox_6->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        Qos_set = true;
    }
    else
    {
        ui->comboBox_6->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        Qos_set = false;
    }
}

// Edca_Config
void Ap_config::on_pushButton_8_clicked()
{
    this->edca_page->show();
}

// Antenna_Config
void Ap_config::on_pushButton_9_clicked()
{
    this->antenna_page->show();
}

// Page3_Finished
void Ap_config::on_pushButton_6_clicked()
{
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(
            this,
            "Error",
            "Please set the Ssid",
            QMessageBox::Ok);
        return;
    }

    // set the channel number
    this->one_ap->channel_number = ui->spinBox->value();
    qint16 channel_number = ui->spinBox->value();

    // set the frequency
    if (ui->comboBox_3->currentText() == "5G")
    {
        this->one_ap->Frequency = 5000 + channel_number * 5;
    }
    else if (ui->comboBox_3->currentText() == "2.4G")
    {
        this->one_ap->Frequency = 2400 + (channel_number - 1) * 5;
    }

    //set the GI
    if(ui->comboBox_15->currentText() == "400ns")
    {
        this->one_ap->GI = 400;
    }
    else if(ui->comboBox_15->currentText() == "800ns")
    {
        this->one_ap->GI = 800;
    }
    else if(ui->comboBox_15->currentText() == "1600ns")
    {
        this->one_ap->GI = 1600;
    }
    else if(ui->comboBox_15->currentText() == "3200ns")
    {
        this->one_ap->GI = 3200;
    }

    // set the bandwidth
    this->one_ap->bandwidth = ui->spinBox_2->value();
    // set the Tx power
    this->one_ap->TxPower = ui->doubleSpinBox_6->value();
    // set the Ssid
    this->one_ap->Ssid = ui->lineEdit->text();
    // set the phy_model
    this->one_ap->Phy_model = ui->comboBox_4->currentText();
    // set the Standard
    this->one_ap->Standard = ui->comboBox_5->currentText();
    // set the Slot
    this->one_ap->Slot = ui->doubleSpinBox_7->value();
    // set the Sifs
    this->one_ap->Sifs = ui->doubleSpinBox_8->value();
    // set the RxSensitivity
    this->one_ap->RxSensitivity = ui->doubleSpinBox_9->value();
    // set the CcaEdThreshold
    this->one_ap->CcaThreshold = ui->doubleSpinBox_10->value();
    // set the CcaSensitivity
    this->one_ap->CcaSensitivity = ui->doubleSpinBox_11->value();
    // set the Beacon
    this->one_ap->Beacon = ui->checkBox->isChecked();
    this->one_ap->Beacon_interval = ui->doubleSpinBox_12->value();
    this->one_ap->Beacon_Rate = ui->doubleSpinBox_13->value();
    this->one_ap->EnableBeaconJitter = ui->checkBox_5->isChecked();
    // set the Rts_Cts
    this->one_ap->RtsCts = ui->checkBox_5->isChecked();
    this->one_ap->RtsCts_Threshold = ui->spinBox_3->value();
    // set the Rate_ctr_algo
    this->one_ap->Rate_ctr_algo = ui->comboBox_7->currentText();
    // set the TxQueue
    this->one_ap->TxQueue = ui->comboBox_8->currentText();

    // set the Qos
    this->one_ap->Qos = ui->checkBox_6->isChecked();
    this->one_ap->Edca = ui->comboBox_6->currentText();

    this->one_ap->AC_VO_cwmin = this->edca_page->AC_VO_cwmin;
    this->one_ap->AC_VO_cwmax = this->edca_page->AC_VO_cwmax;
    this->one_ap->AC_VO_AIFSN = this->edca_page->AC_VO_AIFSN;
    this->one_ap->AC_VO_TXOP_LIMIT = this->edca_page->AC_VO_TXOP_LIMIT;

    this->one_ap->AC_VI_cwmin = this->edca_page->AC_VI_cwmin;
    this->one_ap->AC_VI_cwmax = this->edca_page->AC_VI_cwmax;
    this->one_ap->AC_VI_AIFSN = this->edca_page->AC_VI_AIFSN;
    this->one_ap->AC_VI_TXOP_LIMIT = this->edca_page->AC_VI_TXOP_LIMIT;

    this->one_ap->AC_BE_cwmin = this->edca_page->AC_BE_cwmin;
    this->one_ap->AC_BE_cwmax = this->edca_page->AC_BE_cwmax;
    this->one_ap->AC_BE_AIFSN = this->edca_page->AC_BE_AIFSN;
    this->one_ap->AC_BE_TXOP_LIMIT = this->edca_page->AC_BE_TXOP_LIMIT;

    this->one_ap->AC_BK_cwmin = this->edca_page->AC_BK_cwmin;
    this->one_ap->AC_BK_cwmax = this->edca_page->AC_BK_cwmax;
    this->one_ap->AC_BK_AIFSN = this->edca_page->AC_BK_AIFSN;
    this->one_ap->AC_BK_TXOP_LIMIT = this->edca_page->AC_BK_TXOP_LIMIT;

    this->one_ap->Msdu_aggregation = this->edca_page->Msdu_aggregation;
    this->one_ap->AMsdu_type = this->edca_page->AMsdu_type;
    this->one_ap->MaxAMsduSize = this->edca_page->MaxAMsduSize;

    this->one_ap->Mpdu_aggregation = this->edca_page->Mpdu_aggregation;
    this->one_ap->AMpdu_type = this->edca_page->AMpdu_type;
    this->one_ap->MaxAMpduSize = this->edca_page->MaxAMpduSize;
    this->one_ap->Density = this->edca_page->Density;

    // set the Antenna
    std::cout << "the number of antenna is: " << this->antenna_page->antenna_list.size() << std::endl;

    if (this->antenna_page->AntennaCount() == 0)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Please set the antenna",
            QMessageBox::Ok);
        return;
    }

    std::cout << this->antenna_page->antenna_list[0]->Antenna_type.toStdString() << std::endl;
    for (auto item : this->antenna_page->antenna_list)
    {
        this->one_ap->Antenna_list.push_back(std::move(item));
    }

    phymac_set = true;
    ui->tabWidget->setTabEnabled(3, true);
    // check if the Qos is on,if not, disable the Qos related settings
    if (!this->one_ap->Qos)
    {
        ui->checkBox_7->setEnabled(false);
        ui->comboBox_11->setEnabled(false);
        ui->spinBox_22->setEnabled(false);
        ui->spinBox_23->setEnabled(false);
        ui->spinBox_24->setEnabled(false);
        ui->checkBox_8->setEnabled(false);
        ui->comboBox_12->setEnabled(false);
        ui->spinBox_25->setEnabled(false);
        ui->doubleSpinBox_21->setEnabled(false);
        ui->checkBox_9->setEnabled(true);
        ui->checkBox_10->setEnabled(false);
        ui->comboBox_14->setEnabled(false);
        ui->spinBox_28->setEnabled(false);
        ui->spinBox_29->setEnabled(false);
        ui->scrollArea->ensureWidgetVisible(ui->checkBox_9);
    }
    else
    {
        ui->checkBox_7->setEnabled(true);
        ui->comboBox_11->setEnabled(true);
        ui->spinBox_22->setEnabled(true);
        ui->spinBox_23->setEnabled(true);
        ui->spinBox_24->setEnabled(true);
        ui->checkBox_8->setEnabled(true);
        ui->comboBox_12->setEnabled(true);
        ui->spinBox_25->setEnabled(true);
        ui->doubleSpinBox_21->setEnabled(true);
        ui->checkBox_9->setEnabled(true);
        ui->checkBox_10->setEnabled(true);
        ui->comboBox_14->setEnabled(true);
        ui->spinBox_28->setEnabled(true);
        ui->spinBox_29->setEnabled(true);
    }
    ui->tabWidget->setCurrentIndex(3);
}

bool Ap_config::Integrity_Check()
{
    return true;
}

// Finish setting Page4
void Ap_config::on_pushButton_7_clicked()
{
    // check if the flow id is set
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(
            this,
            "Error",
            "Please set the FlowId",
            QMessageBox::Ok);
        return;
    }

    // load the settings of the traffic
    if (ui->tableWidget->rowCount() == 0)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Please set the traffic",
            QMessageBox::Ok);
        return;
    }

    ApIndex++;
    this->json_helper->SetApToJson(this->one_ap.get(), ApIndex);
    this->one_ap->Traffic_list.clear();
    this->one_ap->Antenna_list.clear();
    emit Finish_setting_ap();
}

// add Traffic
void Ap_config::on_pushButton_2_clicked()
{
    if (ui->tableWidget->rowCount() == 1 && ui->tableWidget->item(0, 1) == nullptr)
    {
        ui->tableWidget->setRowCount(0);
    }
    // Information to be shown in the table
    QString FlowId = ui->lineEdit_2->text();
    QString Protocol = ui->comboBox_9->currentText();
    QString Direction = ui->comboBox_10->currentText();
    double StartTime = ui->doubleSpinBox_19->value();
    double EndTime = ui->doubleSpinBox_20->value();

    // Information to be stored in the data structure
    TrafficConfig new_traffic;
    new_traffic.Flow_id = FlowId;
    new_traffic.Protocol = Protocol;
    new_traffic.Direction = Direction;
    new_traffic.StartTime = StartTime;
    new_traffic.EndTime = EndTime;

    auto viTraffic = std::dynamic_pointer_cast<AC_VI_Traffic>(new_traffic.m_edca[AcType::VI]);
    if (viTraffic)
    {
        viTraffic->enabled = ui->checkBox_7->isChecked();
        viTraffic->trafficType = ui->comboBox_11->currentText();
        viTraffic->packetSize = ui->spinBox_22->value();
        viTraffic->meanDataRate = ui->spinBox_23->value();
        viTraffic->peakDataRate = ui->spinBox_24->value();
    }

    auto voTraffic = std::dynamic_pointer_cast<AC_VO_Traffic>(new_traffic.m_edca[AcType::VO]);
    if (voTraffic)
    {
        voTraffic->enabled = ui->checkBox_8->isChecked();
        voTraffic->trafficType = ui->comboBox_12->currentText();
        voTraffic->packetSize = ui->spinBox_25->value();
        voTraffic->interval = ui->doubleSpinBox_21->value();
    }

    auto beTraffic = std::dynamic_pointer_cast<AC_BE_Traffic>(new_traffic.m_edca[AcType::BE]);
    if (beTraffic)
    {
        beTraffic->enabled = ui->checkBox_9->isChecked();
        beTraffic->trafficType = ui->comboBox_13->currentText();
        beTraffic->packetSize = ui->spinBox_26->value();
        beTraffic->DataRate = ui->spinBox_27->value();
    }

    auto bkTraffic = std::dynamic_pointer_cast<AC_BK_Traffic>(new_traffic.m_edca[AcType::BK]);
    if (bkTraffic)
    {
        bkTraffic->enabled = ui->checkBox_10->isChecked();
        bkTraffic->trafficType = ui->comboBox_14->currentText();
        bkTraffic->packetSize = ui->spinBox_28->value();
        bkTraffic->DataRate = ui->spinBox_29->value();
    }
    // Show the information in the table
    int rowCount = ui->tableWidget->rowCount();
    qint8 lastrow = rowCount;

    ui->tableWidget->insertRow(lastrow);
    ui->tableWidget->setItem(lastrow, 0, new QTableWidgetItem(FlowId));
    ui->tableWidget->setItem(lastrow, 1, new QTableWidgetItem(QString::number(StartTime)));
    ui->tableWidget->setItem(lastrow, 2, new QTableWidgetItem(QString::number(EndTime)));
    ui->tableWidget->setItem(lastrow, 3, new QTableWidgetItem(Protocol));
    ui->tableWidget->setItem(lastrow, 4, new QTableWidgetItem(Direction));

    // Insert the data structure into the vector
    this->one_ap->Traffic_list.push_back(new_traffic);
}

void Ap_config::on_pushButton_3_clicked()
{
    int rowCount = ui->tableWidget->rowCount() - 1;
    if (rowCount < 0)
        return;
    ui->tableWidget->removeRow(rowCount);
}
