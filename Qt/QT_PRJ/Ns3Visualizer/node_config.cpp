#include "node_config.h"
#include "ui_node_config.h"

node_config::node_config(QWidget *parent)
    : QWidget(parent), ui(new Ui::node_config)
{
    ui->setupUi(this);

    centerWindow(this);

    if (!ui->checkBox_2->isChecked())
    {
        pos_set = true;
    }

    if (!ui->checkBox->isChecked())
    {
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->doubleSpinBox_8->setEnabled(false);
        ui->doubleSpinBox_9->setEnabled(false);
        ui->doubleSpinBox_10->setEnabled(false);
        ui->doubleSpinBox_11->setEnabled(false);
        ui->doubleSpinBox_4->setEnabled(false);
        ui->doubleSpinBox_5->setEnabled(false);
    }

    if (phymac_set != true)
    {
        ui->tabWidget->setTabEnabled(3, false);
    }
    ui->tableWidget->setRowCount(0);

    // deduce the GI from the selected protocol
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
                    ui->comboBox_15->setCurrentIndex(1);
                    ui->comboBox_15->setEnabled(true);
                    ui->comboBox_15->setItemData(
                        0, QVariant(0), Qt::UserRole - 1);

                default:
                    break;
                }
            });
    // Default setting the GI
    auto text = ui->comboBox_5->currentText();
    ui->comboBox_15->currentTextChanged(text);
}

node_config::~node_config()
{
    delete ui;
}

// Page1_Finished
void node_config::on_pushButton_clicked()
{
    if (!ui->checkBox_2->isChecked())
    {
        if (ui->doubleSpinBox->value() != 0.00 || ui->doubleSpinBox_2->value() != 0.00 || ui->doubleSpinBox_3->value() != 0.00)
        {
            ui->tabWidget->setCurrentIndex(1);
            this->one_sta->m_position = {ui->doubleSpinBox->value(),
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

        this->one_sta->m_position = {x_rand, y_rand, z_rand};
        std::cout << "The position of STA is: " << x_rand << " " << y_rand << " " << z_rand << std::endl;
        ui->tabWidget->setCurrentIndex(1);
    }
}

// Page2_Finished
void node_config::on_pushButton_4_clicked()
{
    // If mobility is not set
    if (!ui->checkBox->isChecked())
    {
        ui->tabWidget->setCurrentIndex(2);
        mobility_set = true;
        this->one_sta->Mobility = false;
        return;
    }

    // If mobility is set and "random" mode is selected
    else if (ui->checkBox->isChecked() && ui->comboBox->currentText() == "Random Mobility Model")
    {
        this->one_sta->Mobility = true;
        this->one_sta->mode = "Random Mobility Model";
        double x_max = this->Building_range[0];
        double y_max = this->Building_range[1];
        double z_max = this->Building_range[2];
        double x_rand_1 = get_true_random_double(0, x_max);
        double y_rand_1 = get_true_random_double(0, y_max);
        double z_rand_1 = get_true_random_double(0, z_max);
        double x_rand_2 = get_true_random_double(0, x_max);
        double y_rand_2 = get_true_random_double(0, y_max);
        double z_rand_2 = get_true_random_double(0, z_max);

        ui->doubleSpinBox_8->setValue((x_rand_1 > x_rand_2) ? x_rand_2 : x_rand_1);
        ui->doubleSpinBox_9->setValue((x_rand_1 > x_rand_2) ? x_rand_1 : x_rand_2);
        ui->doubleSpinBox_10->setValue((y_rand_1 > y_rand_2) ? y_rand_2 : y_rand_1);
        ui->doubleSpinBox_11->setValue((y_rand_1 > y_rand_2) ? y_rand_1 : y_rand_2);

        // set the boundaries of mobility
        this->one_sta->boundaries = {ui->doubleSpinBox_8->value(), ui->doubleSpinBox_9->value(), ui->doubleSpinBox_10->value(), ui->doubleSpinBox_11->value()};
        this->one_sta->time_change_interval = ui->doubleSpinBox_4->value();
        this->one_sta->mode = ui->comboBox_2->currentText();
        this->one_sta->distance_change_interval = ui->doubleSpinBox_5->value();
        this->one_sta->random_velocity = ui->doubleSpinBox_7->value();

        std::cout << "The boundaries of Sta is: " << this->one_sta->boundaries[0] << " " << this->one_sta->boundaries[1] << " " << this->one_sta->boundaries[2] << " " << this->one_sta->boundaries[3] << std::endl;
        std::cout << "The time change interval of Sta is: " << this->one_sta->time_change_interval << std::endl;
        std::cout << "The distance change interval of Sta is: " << this->one_sta->distance_change_interval << std::endl;
        std::cout << "The random velocity of Sta is: " << this->one_sta->random_velocity << std::endl;
        std::cout << "The mode of Sta is: " << this->one_sta->mode.toStdString() << std::endl;

        ui->tabWidget->setCurrentIndex(2);
        this->one_sta->Mobility = true;
        return;
    }
    // If not choosing the "random" mode,check if the conditions are valid
    else if ((ui->doubleSpinBox_9->value() > ui->doubleSpinBox_8->value()) &&
             (ui->doubleSpinBox_11->value() > ui->doubleSpinBox_10->value()) &&
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
            "Please set the Position",
            QMessageBox::Ok);
    }

    else
    {
        if (mobility_set)
        {
            ui->tabWidget->setCurrentIndex(2);
            this->one_sta->Mobility = true;
        }

        else
        {
            QMessageBox::critical(
                this,
                "Error",
                "Please set the Mobility correctly",
                QMessageBox::Ok);
        }
    }
}

// Page1_Random_Position
void node_config::on_checkBox_2_clicked(bool checked)
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
void node_config::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->doubleSpinBox_8->setEnabled(true);
        ui->doubleSpinBox_9->setEnabled(true);
        ui->doubleSpinBox_10->setEnabled(true);
        ui->doubleSpinBox_11->setEnabled(true);
        ui->doubleSpinBox_4->setEnabled(true);
        ui->doubleSpinBox_5->setEnabled(true);
        ui->doubleSpinBox_7->setEnabled(true);
        mobility_set = false;
    }
    else
    {
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->doubleSpinBox_8->setEnabled(false);
        ui->doubleSpinBox_9->setEnabled(false);
        ui->doubleSpinBox_10->setEnabled(false);
        ui->doubleSpinBox_11->setEnabled(false);
        ui->doubleSpinBox_4->setEnabled(false);
        ui->doubleSpinBox_5->setEnabled(false);
        ui->doubleSpinBox_7->setEnabled(false);
        mobility_set = true;
    }
}

// Page3_Rts_Cts

void node_config::on_checkBox_5_clicked(bool checked)
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

void node_config::on_checkBox_6_clicked(bool checked)
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
void node_config::on_pushButton_8_clicked()
{
    this->edca_page->show();
}

// Antenna_Config
void node_config::on_pushButton_9_clicked()
{
    this->antenna_page->show();
}

// Page3_Finished
void node_config::on_pushButton_6_clicked()
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
    this->one_sta->channel_number = ui->spinBox->value();
    qint16 channel_number = ui->spinBox->value();

    // set the frequency
    if (ui->comboBox_3->currentText() == "5G")
    {
        this->one_sta->Frequency = 5000 + channel_number * 5;
    }
    else if (ui->comboBox_3->currentText() == "2.4G")
    {
        this->one_sta->Frequency = 2400 + (channel_number - 1) * 5;
    }

    // set the GI
    QString GI_str = ui->comboBox_15->currentText();
    if (ui->comboBox_3->currentText() == "5G")
    {
        this->one_sta->Frequency = 5000 + channel_number * 5;
    }
    else if (ui->comboBox_3->currentText() == "2.4G")
    {
        this->one_sta->Frequency = 2400 + (channel_number - 1) * 5;
    }

    if (ui->comboBox_15->currentText() == "400ns")
    {
        this->one_sta->GI = 400;
    }
    else if (ui->comboBox_15->currentText() == "800ns")
    {
        this->one_sta->GI = 800;
    }
    else if (ui->comboBox_15->currentText() == "1600ns")
    {
        this->one_sta->GI = 1600;
    }
    else if (ui->comboBox_15->currentText() == "3200ns")
    {
        this->one_sta->GI = 3200;
    }

    // set the bandwidth
    this->one_sta->bandwidth = ui->spinBox_2->value();
    // set the Tx power
    this->one_sta->TxPower = ui->doubleSpinBox_6->value();
    // set the Ssid
    this->one_sta->Ssid = ui->lineEdit->text();
    // set the phy_model
    this->one_sta->Phy_model = ui->comboBox_4->currentText();
    // set the Standard
    this->one_sta->Standard = ui->comboBox_5->currentText();

    // set the MaxMissedBeacons
    this->one_sta->MaxMissedBeacons = ui->spinBox_4->value();
    // set the ProbeRequestTimeout
    this->one_sta->ProbeRequestTimeout = ui->spinBox_5->value();
    // set the EnableAssocFailRetry
    this->one_sta->EnableAssocFailRetry = ui->checkBox_7->isChecked();
    // set the ActiveProbing
    this->one_sta->active_probing = ui->checkBox_12->isChecked();
    // set the Rts_Cts
    this->one_sta->RtsCts = ui->checkBox_5->isChecked();
    this->one_sta->RtsCts_Threshold = ui->spinBox_3->value();
    // set the Rate_ctr_algo
    this->one_sta->Rate_ctr_algo = ui->comboBox_7->currentText();
    // set the TxQueue
    this->one_sta->TxQueue = ui->comboBox_8->currentText();

    // set the Qos
    this->one_sta->Qos = ui->checkBox_6->isChecked();
    this->one_sta->Edca = ui->comboBox_6->currentText();

    this->one_sta->AC_VO_cwmin = this->edca_page->AC_VO_cwmin;
    this->one_sta->AC_VO_cwmax = this->edca_page->AC_VO_cwmax;
    this->one_sta->AC_VO_AIFSN = this->edca_page->AC_VO_AIFSN;
    this->one_sta->AC_VO_TXOP_LIMIT = this->edca_page->AC_VO_TXOP_LIMIT;

    this->one_sta->AC_VI_cwmin = this->edca_page->AC_VI_cwmin;
    this->one_sta->AC_VI_cwmax = this->edca_page->AC_VI_cwmax;
    this->one_sta->AC_VI_AIFSN = this->edca_page->AC_VI_AIFSN;
    this->one_sta->AC_VI_TXOP_LIMIT = this->edca_page->AC_VI_TXOP_LIMIT;

    this->one_sta->AC_BE_cwmin = this->edca_page->AC_BE_cwmin;
    this->one_sta->AC_BE_cwmax = this->edca_page->AC_BE_cwmax;
    this->one_sta->AC_BE_AIFSN = this->edca_page->AC_BE_AIFSN;
    this->one_sta->AC_BE_TXOP_LIMIT = this->edca_page->AC_BE_TXOP_LIMIT;

    this->one_sta->AC_BK_cwmin = this->edca_page->AC_BK_cwmin;
    this->one_sta->AC_BK_cwmax = this->edca_page->AC_BK_cwmax;
    this->one_sta->AC_BK_AIFSN = this->edca_page->AC_BK_AIFSN;
    this->one_sta->AC_BK_TXOP_LIMIT = this->edca_page->AC_BK_TXOP_LIMIT;

    this->one_sta->Msdu_aggregation = this->edca_page->Msdu_aggregation;
    this->one_sta->AMsdu_type = this->edca_page->AMsdu_type;
    this->one_sta->MaxAMsduSize = this->edca_page->MaxAMsduSize;

    this->one_sta->Mpdu_aggregation = this->edca_page->Mpdu_aggregation;
    this->one_sta->AMpdu_type = this->edca_page->AMpdu_type;
    this->one_sta->MaxAMpduSize = this->edca_page->MaxAMpduSize;
    this->one_sta->Density = this->edca_page->Density;

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
        this->one_sta->Antenna_list.push_back(std::move(item));
    }

    phymac_set = true;
    ui->tabWidget->setTabEnabled(3, true);
    if (!this->one_sta->Qos)
    {
        ui->checkBox_8->setEnabled(false);
        ui->comboBox_11->setEnabled(false);
        ui->spinBox_22->setEnabled(false);
        ui->spinBox_23->setEnabled(false);
        ui->spinBox_24->setEnabled(false);
        ui->checkBox_9->setEnabled(false);
        ui->comboBox_12->setEnabled(false);
        ui->spinBox_25->setEnabled(false);
        ui->doubleSpinBox_21->setEnabled(false);
        ui->checkBox_10->setEnabled(true);
        ui->checkBox_11->setEnabled(false);
        ui->comboBox_14->setEnabled(false);
        ui->spinBox_28->setEnabled(false);
        ui->spinBox_29->setEnabled(false);
        ui->scrollArea->ensureWidgetVisible(ui->checkBox_10);
    }
    else
    {
        ui->checkBox_8->setEnabled(true);
        ui->comboBox_11->setEnabled(true);
        ui->spinBox_22->setEnabled(true);
        ui->spinBox_23->setEnabled(true);
        ui->spinBox_24->setEnabled(true);
        ui->checkBox_9->setEnabled(true);
        ui->comboBox_12->setEnabled(true);
        ui->spinBox_25->setEnabled(true);
        ui->doubleSpinBox_21->setEnabled(true);
        ui->checkBox_10->setEnabled(true);
        ui->checkBox_11->setEnabled(true);
        ui->comboBox_14->setEnabled(true);
        ui->spinBox_28->setEnabled(true);
        ui->spinBox_29->setEnabled(true);
    }
    ui->tabWidget->setCurrentIndex(3);
}

bool node_config::Integrity_Check()
{
    return true;
}

// Add one traffic
void node_config::on_pushButton_2_clicked()
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
        viTraffic->enabled = ui->checkBox_8->isChecked();
        viTraffic->trafficType = ui->comboBox_11->currentText();
        viTraffic->packetSize = ui->spinBox_22->value();
        viTraffic->meanDataRate = ui->spinBox_23->value();
        viTraffic->peakDataRate = ui->spinBox_24->value();
    }

    auto voTraffic = std::dynamic_pointer_cast<AC_VO_Traffic>(new_traffic.m_edca[AcType::VO]);
    if (voTraffic)
    {
        voTraffic->enabled = ui->checkBox_9->isChecked();
        voTraffic->trafficType = ui->comboBox_12->currentText();
        voTraffic->packetSize = ui->spinBox_25->value();
        voTraffic->interval = ui->doubleSpinBox_21->value();
    }

    auto beTraffic = std::dynamic_pointer_cast<AC_BE_Traffic>(new_traffic.m_edca[AcType::BE]);
    if (beTraffic)
    {
        beTraffic->enabled = ui->checkBox_10->isChecked();
        beTraffic->trafficType = ui->comboBox_13->currentText();
        beTraffic->packetSize = ui->spinBox_26->value();
        beTraffic->DataRate = ui->spinBox_27->value();
    }

    auto bkTraffic = std::dynamic_pointer_cast<AC_BK_Traffic>(new_traffic.m_edca[AcType::BK]);
    if (bkTraffic)
    {
        bkTraffic->enabled = ui->checkBox_11->isChecked();
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
    this->one_sta->Traffic_list.push_back(new_traffic);
}

// Delete one traffic
void node_config::on_pushButton_3_clicked()
{
    int rowCount = ui->tableWidget->rowCount() - 1;
    if (rowCount < 0)
        return;
    ui->tableWidget->removeRow(rowCount);
}

// Page4_Traffic_Finished
void node_config::on_pushButton_7_clicked()
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

    StaIndex++;
    this->json_helper->SetStaToJson(this->one_sta.get(), StaIndex);
    this->one_sta->Traffic_list.clear();
    this->one_sta->Antenna_list.clear();
    emit Finish_setting_sta();
}
