/********************************************************************************
** Form generated from reading UI file 'antennas.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANTENNAS_H
#define UI_ANTENNAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Antenna
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Antenna)
    {
        if (Antenna->objectName().isEmpty())
            Antenna->setObjectName("Antenna");
        Antenna->resize(1148, 883);
        gridLayout = new QGridLayout(Antenna);
        gridLayout->setObjectName("gridLayout");
        frame = new QFrame(Antenna);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        tableWidget = new QTableWidget(frame);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");

        gridLayout_2->addWidget(tableWidget, 0, 0, 2, 2);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 0, 2, 1, 1);

        widget = new QWidget(frame);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName("spinBox");
        spinBox->setValue(20);

        verticalLayout->addWidget(spinBox);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setValue(30);

        verticalLayout->addWidget(spinBox_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);


        gridLayout_2->addWidget(widget, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_2->addWidget(pushButton_2, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(frame);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 1, 1, 2);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(Antenna);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Antenna, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Antenna, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Antenna);
    } // setupUi

    void retranslateUi(QDialog *Antenna)
    {
        Antenna->setWindowTitle(QCoreApplication::translate("Antenna", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Antenna", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Antenna", "Max Gain", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Antenna", "BeamWidth", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Antenna", "Isotropic", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Antenna", "20", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Antenna", "30", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QCoreApplication::translate("Antenna", "Add", nullptr));
        label_3->setText(QCoreApplication::translate("Antenna", "Type", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Antenna", "Isotropic", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Antenna", "Cosine", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Antenna", "Parabolic", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Antenna", "Circular Aperture", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Antenna", "Three Gpp", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Antenna", "UPA", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("Antenna", "Phased Array", nullptr));

        label->setText(QCoreApplication::translate("Antenna", "MaxGain", nullptr));
        label_2->setText(QCoreApplication::translate("Antenna", "BeamWidth", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Antenna", "Confirm", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Antenna", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Antenna: public Ui_Antenna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANTENNAS_H
