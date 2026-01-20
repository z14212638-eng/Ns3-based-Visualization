#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>
#include <QStackedWidget>
#include <QMainWindow>

#include "page1_model_chose.h"
#include "utils.h"
#include "indus_widget.h"
#include "antennas.h"
#include "ap_config.h"
#include "node_config.h"
#include "configgraphicsview.h"
#include "edca_config.h"
#include "JsonHelper.h"
#include "legend_overlay.h"
#include "ppdu_timeline_view.h"
#include "simu_config.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stack;

    Page1_model_chose *page1;
    Simu_Config *simuConfig;
    node_config *nodeConfig;
    Ap_config *apConfig;
    Edca_config *edcaConfig;
    Antenna *antenna;

};
#endif // MAINWINDOW_H
