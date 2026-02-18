/********************************************************************************
** Form generated from reading UI file 'simu_config.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMU_CONFIG_H
#define UI_SIMU_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "configgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_Simu_Config
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QPushButton *pushButton_7;
    QLabel *label;
    QWidget *widget_10;
    QLabel *label_2;
    QComboBox *comboBox;
    QDoubleSpinBox *doubleSpinBox;
    QWidget *widget_12;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QCommandLinkButton *commandLinkButton;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QWidget *widget_13;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_4;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTableWidget *tableWidget;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_8;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget_4;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_9;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_3;
    QLabel *label_4;
    QLCDNumber *lcdNumber;
    QLabel *label_5;
    QLCDNumber *lcdNumber_2;
    ConfigGraphicsView *graphicsView;

    void setupUi(QWidget *Simu_Config)
    {
        if (Simu_Config->objectName().isEmpty())
            Simu_Config->setObjectName("Simu_Config");
        Simu_Config->resize(2078, 1122);
        verticalLayout = new QVBoxLayout(Simu_Config);
        verticalLayout->setObjectName("verticalLayout");
        widget_9 = new QWidget(Simu_Config);
        widget_9->setObjectName("widget_9");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_9->sizePolicy().hasHeightForWidth());
        widget_9->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget_9);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_11 = new QWidget(widget_9);
        widget_11->setObjectName("widget_11");
        sizePolicy.setHeightForWidth(widget_11->sizePolicy().hasHeightForWidth());
        widget_11->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(widget_11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tabWidget = new QTabWidget(widget_11);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(0, 800));
        tabWidget->setMaximumSize(QSize(16777215, 1300));
        QFont font;
        font.setBold(false);
        tabWidget->setFont(font);
        tabWidget->setIconSize(QSize(27, 28));
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName("gridLayout");
        pushButton_7 = new QPushButton(tab_4);
        pushButton_7->setObjectName("pushButton_7");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy1);
        pushButton_7->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        pushButton_7->setFont(font1);

        gridLayout->addWidget(pushButton_7, 5, 2, 1, 1);

        label = new QLabel(tab_4);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 60));
        label->setMaximumSize(QSize(16777215, 80));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(true);
        label->setFont(font2);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        widget_10 = new QWidget(tab_4);
        widget_10->setObjectName("widget_10");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy2);
        widget_10->setMaximumSize(QSize(16777215, 800));
        label_2 = new QLabel(widget_10);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 50, 274, 80));
        label_2->setMaximumSize(QSize(16777215, 80));
        label_2->setFont(font2);
        comboBox = new QComboBox(widget_10);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(0, 160, 221, 40));
        comboBox->setMinimumSize(QSize(0, 40));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(false);
        comboBox->setFont(font3);
        comboBox->setMouseTracking(false);

        gridLayout->addWidget(widget_10, 3, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(tab_4);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setMinimumSize(QSize(0, 40));
        doubleSpinBox->setFont(font3);
        doubleSpinBox->setValue(10.000000000000000);

        gridLayout->addWidget(doubleSpinBox, 1, 0, 1, 1);

        widget_12 = new QWidget(tab_4);
        widget_12->setObjectName("widget_12");
        sizePolicy2.setHeightForWidth(widget_12->sizePolicy().hasHeightForWidth());
        widget_12->setSizePolicy(sizePolicy2);
        widget_12->setMinimumSize(QSize(0, 800));
        widget_12->setMaximumSize(QSize(16777215, 800));
        label_3 = new QLabel(widget_12);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 60, 181, 80));
        label_3->setMaximumSize(QSize(16777215, 80));
        label_3->setFont(font2);
        comboBox_2 = new QComboBox(widget_12);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(30, 160, 201, 40));
        comboBox_2->setMinimumSize(QSize(0, 40));
        comboBox_2->setFont(font3);

        gridLayout->addWidget(widget_12, 3, 1, 1, 1);

        commandLinkButton = new QCommandLinkButton(tab_4);
        commandLinkButton->setObjectName("commandLinkButton");
        sizePolicy2.setHeightForWidth(commandLinkButton->sizePolicy().hasHeightForWidth());
        commandLinkButton->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setPointSize(18);
        font4.setBold(false);
        commandLinkButton->setFont(font4);
        commandLinkButton->setIconSize(QSize(30, 40));

        gridLayout->addWidget(commandLinkButton, 5, 0, 1, 2);

        doubleSpinBox_3 = new QDoubleSpinBox(tab_4);
        doubleSpinBox_3->setObjectName("doubleSpinBox_3");
        doubleSpinBox_3->setMinimumSize(QSize(0, 40));
        doubleSpinBox_3->setFont(font3);
        doubleSpinBox_3->setValue(5.000000000000000);

        gridLayout->addWidget(doubleSpinBox_3, 1, 2, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(tab_4);
        doubleSpinBox_2->setObjectName("doubleSpinBox_2");
        doubleSpinBox_2->setMinimumSize(QSize(0, 40));
        doubleSpinBox_2->setFont(font3);
        doubleSpinBox_2->setValue(10.000000000000000);

        gridLayout->addWidget(doubleSpinBox_2, 1, 1, 1, 1);

        widget_13 = new QWidget(tab_4);
        widget_13->setObjectName("widget_13");
        sizePolicy2.setHeightForWidth(widget_13->sizePolicy().hasHeightForWidth());
        widget_13->setSizePolicy(sizePolicy2);
        widget_13->setMaximumSize(QSize(16777215, 800));
        label_6 = new QLabel(widget_13);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 50, 241, 80));
        label_6->setMaximumSize(QSize(16777215, 80));
        label_6->setFont(font2);
        doubleSpinBox_4 = new QDoubleSpinBox(widget_13);
        doubleSpinBox_4->setObjectName("doubleSpinBox_4");
        doubleSpinBox_4->setGeometry(QRect(20, 160, 241, 40));
        doubleSpinBox_4->setMinimumSize(QSize(0, 40));
        doubleSpinBox_4->setFont(font3);

        gridLayout->addWidget(widget_13, 2, 2, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName("gridLayout_2");
        tableWidget_2 = new QTableWidget(tab_2);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QFont font5;
        font5.setPointSize(14);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font5);
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font5);
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font5);
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_2->setObjectName("tableWidget_2");

        gridLayout_2->addWidget(tableWidget_2, 0, 0, 1, 3);

        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(pushButton_6, 1, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        pushButton = new QPushButton(tab);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 50));

        gridLayout_3->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 50));

        gridLayout_3->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 50));

        gridLayout_3->addWidget(pushButton_3, 1, 2, 1, 1);

        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font5);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font5);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font5);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");

        gridLayout_3->addWidget(tableWidget, 0, 0, 1, 3);

        tabWidget->addTab(tab, QString());

        horizontalLayout_3->addWidget(tabWidget);

        frame = new QFrame(widget_11);
        frame->setObjectName("frame");
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        QFont font6;
        font6.setBold(true);
        frame->setFont(font6);
        frame->setStyleSheet(QString::fromUtf8("border-color: rgb(158, 158, 158);\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        widget = new QWidget(frame);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMaximumSize(QSize(16777215, 1500));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(460, 20, 272, 451));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(10);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy4);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_8 = new QPushButton(widget_2);
        pushButton_8->setObjectName("pushButton_8");
        sizePolicy1.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy1);
        pushButton_8->setMinimumSize(QSize(0, 70));

        verticalLayout_2->addWidget(pushButton_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(0, 53));
        checkBox = new QCheckBox(widget_4);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(0, 10, 291, 36));
        checkBox->setMinimumSize(QSize(200, 36));
        QFont font7;
        font7.setPointSize(16);
        checkBox->setFont(font7);
        checkBox->setChecked(false);

        verticalLayout_2->addWidget(widget_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_4);

        pushButton_9 = new QPushButton(widget_2);
        pushButton_9->setObjectName("pushButton_9");
        sizePolicy1.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy1);
        pushButton_9->setMinimumSize(QSize(0, 70));
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(false);
        font8.setItalic(true);
        font8.setUnderline(true);
        pushButton_9->setFont(font8);

        verticalLayout_2->addWidget(pushButton_9);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(10, 10, 241, 331));
        widget_3->setMinimumSize(QSize(0, 40));
        widget_3->setMaximumSize(QSize(16777215, 700));
        label_4 = new QLabel(widget_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 50, 121, 40));
        label_4->setMinimumSize(QSize(0, 40));
        QFont font9;
        font9.setPointSize(14);
        font9.setItalic(true);
        label_4->setFont(font9);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0)"));
        lcdNumber = new QLCDNumber(widget_3);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(20, 110, 81, 31));
        lcdNumber->setFont(font6);
        lcdNumber->setStyleSheet(QString::fromUtf8("color:black"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 200, 121, 17));
        QFont font10;
        font10.setPointSize(14);
        font10.setBold(false);
        font10.setItalic(true);
        label_5->setFont(font10);
        label_5->setStyleSheet(QString::fromUtf8("color:rgb(0, 117, 175)"));
        lcdNumber_2 = new QLCDNumber(widget_3);
        lcdNumber_2->setObjectName("lcdNumber_2");
        lcdNumber_2->setGeometry(QRect(20, 250, 81, 31));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("color:black"));
        graphicsView = new ConfigGraphicsView(widget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(20, 500, 791, 641));
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);
        graphicsView->setMinimumSize(QSize(140, 120));
        graphicsView->setMaximumSize(QSize(16777215, 700));

        horizontalLayout_2->addWidget(widget);


        horizontalLayout_3->addWidget(frame);


        horizontalLayout->addWidget(widget_11);


        verticalLayout->addWidget(widget_9);


        retranslateUi(Simu_Config);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Simu_Config);
    } // setupUi

    void retranslateUi(QWidget *Simu_Config)
    {
        Simu_Config->setWindowTitle(QCoreApplication::translate("Simu_Config", "Simulation Config", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Simu_Config", "Finish", nullptr));
        label->setText(QCoreApplication::translate("Simu_Config", "Building Boundaries   (0,0,0)min-(X,Y,Z)max", nullptr));
        label_2->setText(QCoreApplication::translate("Simu_Config", "Building Type", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Simu_Config", "Residential", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Simu_Config", "Office", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Simu_Config", "Commercial", nullptr));

        label_3->setText(QCoreApplication::translate("Simu_Config", "Wall Type", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("Simu_Config", "Wood", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("Simu_Config", "ConcreteWithoutWindows", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("Simu_Config", "ConcreteWithWindows", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("Simu_Config", "StoneBlocks", nullptr));

        commandLinkButton->setText(QCoreApplication::translate("Simu_Config", "Draw the rooms", nullptr));
        label_6->setText(QCoreApplication::translate("Simu_Config", "Simulation Time(s)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("Simu_Config", "General", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Simu_Config", "Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Simu_Config", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Simu_Config", "Mobility", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Simu_Config", "Add", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Simu_Config", "Delete", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Simu_Config", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Simu_Config", "Access Point", nullptr));
        pushButton->setText(QCoreApplication::translate("Simu_Config", "Add ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Simu_Config", "Delete", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Simu_Config", "Clear", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Simu_Config", "Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Simu_Config", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Simu_Config", "Mobility", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Simu_Config", "Station", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Simu_Config", "Update", nullptr));
        checkBox->setText(QCoreApplication::translate("Simu_Config", "Presenting All PPDU", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Simu_Config", "START", nullptr));
        label_4->setText(QCoreApplication::translate("Simu_Config", "Ap Num", nullptr));
        label_5->setText(QCoreApplication::translate("Simu_Config", "Sta Num", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simu_Config: public Ui_Simu_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMU_CONFIG_H
