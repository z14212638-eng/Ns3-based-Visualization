#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include "JsonHelper.h"
#include "edca_config.h"
#include "antennas.h"
#include "utils.h"

namespace Ui {
class node_config;
}

class node_config : public QWidget
{
    Q_OBJECT

public:
    explicit node_config(QWidget *parent = nullptr);
    ~node_config();

    QVector<double> Building_range = {0, 0, 0};
    QVector<double> m_position = {0, 0, 0};
    qint8 StaIndex = 0;
    
    void setPosition(Sta &);
    void setMobility(Sta &);
    void Load_One_Config(Sta &);
    void Get_Edca_Config(Sta &, Edca_config &);
    void Get_Antenna_Config(Sta &, Antenna &);
    void Get_Traffic_Config(Sta &);

signals:
    void Finish_setting_sta();
    void Edca_to_config(); 
    void Antenna_to_config();
    void LoadOneStaConfig();
    void Page1();
    void Page2();
    void Traffic_Set();
    void RemoveLastTraffic();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_2_clicked(bool checked);
    
    void on_checkBox_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    bool Integrity_Check();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void Restrict_channel();

private:
    Ui::node_config *ui;
    bool pos_set = false;
    bool mobility_set = false;
    bool phymac_set = false;

    bool beacon_set = false;
    bool Rts_Cts_set = false;
    bool Qos_set = false;

    bool Ssid_set = false;
};

#endif // NODE_CONFIG_H
