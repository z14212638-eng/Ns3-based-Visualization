#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>
#include "page1_model_chose.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // add one page(scene choosing page)
    Page1_model_chose *ppage1 = new(Page1_model_chose);

private slots:
    void on_pushButton_clicked();//once the next button is clicked, check the situation of the checkbox.

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
