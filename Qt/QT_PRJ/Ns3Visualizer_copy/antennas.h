#ifndef ANTENNAS_H
#define ANTENNAS_H

#include "JsonHelper.h"
#include "utils.h"
#include <QDialog>

namespace Ui
{
    class Antenna;
}

class Antenna : public QDialog
{
    Q_OBJECT

public:
    explicit Antenna(QWidget *parent = nullptr);
    ~Antenna();
    qint16 AntennaCount() const;
    QVector<std::shared_ptr<Antenna_Config>> antenna_list = {};

    bool is_ap = false;
    bool is_sta = false;

signals:
    void BackToLastPage();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Antenna *ui;
};

#endif // ANTENNAS_H
