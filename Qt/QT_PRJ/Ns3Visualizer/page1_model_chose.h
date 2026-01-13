#ifndef PAGE1_MODEL_CHOSE_H
#define PAGE1_MODEL_CHOSE_H

#include <QWidget>
#include "simu_config.h"

namespace Ui {
class Page1_model_chose;
}

class Page1_model_chose : public QWidget
{
    Q_OBJECT

public:
    explicit Page1_model_chose(QWidget *parent = nullptr);
    ~Page1_model_chose();
    QString GetSceneName();
    QString Scene = "";
    Simu_Config *simu_config = new(Simu_Config);
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

signals:
    void BackToMain();
private:
    Ui::Page1_model_chose *ui;
};

#endif // PAGE1_MODEL_CHOSE_H
