/********************************************************************************
** Form generated from reading UI file 'edca_config.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDCA_CONFIG_H
#define UI_EDCA_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Edca_config
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QLabel *label_3;
    QSpinBox *spinBox_4;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QSpinBox *spinBox_5;
    QLabel *label_8;
    QSpinBox *spinBox_7;
    QLabel *label_11;
    QSpinBox *spinBox_9;
    QLabel *label_14;
    QSpinBox *spinBox_8;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QLabel *label_6;
    QSpinBox *spinBox_6;
    QLabel *label_9;
    QSpinBox *spinBox_10;
    QLabel *label_12;
    QSpinBox *spinBox_11;
    QLabel *label_15;
    QSpinBox *spinBox_12;
    QWidget *tab_4;
    QGridLayout *gridLayout_6;
    QLabel *label_7;
    QSpinBox *spinBox_13;
    QLabel *label_10;
    QSpinBox *spinBox_14;
    QLabel *label_13;
    QSpinBox *spinBox_15;
    QLabel *label_16;
    QSpinBox *spinBox_16;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QLabel *label_17;
    QSpinBox *spinBox_17;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_2;
    QComboBox *comboBox_2;
    QLabel *label_18;
    QSpinBox *spinBox_18;
    QLabel *label_19;
    QSpinBox *spinBox_19;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Edca_config)
    {
        if (Edca_config->objectName().isEmpty())
            Edca_config->setObjectName("Edca_config");
        Edca_config->resize(1166, 842);
        gridLayout = new QGridLayout(Edca_config);
        gridLayout->setObjectName("gridLayout");
        frame = new QFrame(Edca_config);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        label = new QLabel(tab);
        label->setObjectName("label");

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(tab);
        spinBox->setObjectName("spinBox");
        spinBox->setMaximum(65535);
        spinBox->setValue(3);

        gridLayout_3->addWidget(spinBox, 0, 1, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        spinBox_2 = new QSpinBox(tab);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setMaximum(65535);
        spinBox_2->setValue(7);

        gridLayout_3->addWidget(spinBox_2, 1, 1, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        spinBox_3 = new QSpinBox(tab);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setMaximum(1023);
        spinBox_3->setValue(2);

        gridLayout_3->addWidget(spinBox_3, 2, 1, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        spinBox_4 = new QSpinBox(tab);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setMaximum(1023);
        spinBox_4->setValue(47);

        gridLayout_3->addWidget(spinBox_4, 3, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName("gridLayout_4");
        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        spinBox_5 = new QSpinBox(tab_2);
        spinBox_5->setObjectName("spinBox_5");
        spinBox_5->setMaximum(65535);
        spinBox_5->setValue(7);

        gridLayout_4->addWidget(spinBox_5, 0, 1, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        spinBox_7 = new QSpinBox(tab_2);
        spinBox_7->setObjectName("spinBox_7");
        spinBox_7->setMaximum(65535);
        spinBox_7->setValue(15);

        gridLayout_4->addWidget(spinBox_7, 1, 1, 1, 1);

        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");

        gridLayout_4->addWidget(label_11, 2, 0, 1, 1);

        spinBox_9 = new QSpinBox(tab_2);
        spinBox_9->setObjectName("spinBox_9");
        spinBox_9->setValue(2);

        gridLayout_4->addWidget(spinBox_9, 2, 1, 1, 1);

        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");

        gridLayout_4->addWidget(label_14, 3, 0, 1, 1);

        spinBox_8 = new QSpinBox(tab_2);
        spinBox_8->setObjectName("spinBox_8");
        spinBox_8->setMaximum(65535);
        spinBox_8->setValue(94);

        gridLayout_4->addWidget(spinBox_8, 3, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName("gridLayout_5");
        label_6 = new QLabel(tab_3);
        label_6->setObjectName("label_6");

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        spinBox_6 = new QSpinBox(tab_3);
        spinBox_6->setObjectName("spinBox_6");
        spinBox_6->setMaximum(65532);
        spinBox_6->setValue(15);

        gridLayout_5->addWidget(spinBox_6, 0, 1, 1, 1);

        label_9 = new QLabel(tab_3);
        label_9->setObjectName("label_9");

        gridLayout_5->addWidget(label_9, 1, 0, 1, 1);

        spinBox_10 = new QSpinBox(tab_3);
        spinBox_10->setObjectName("spinBox_10");
        spinBox_10->setMaximum(65535);
        spinBox_10->setValue(1023);

        gridLayout_5->addWidget(spinBox_10, 1, 1, 1, 1);

        label_12 = new QLabel(tab_3);
        label_12->setObjectName("label_12");

        gridLayout_5->addWidget(label_12, 2, 0, 1, 1);

        spinBox_11 = new QSpinBox(tab_3);
        spinBox_11->setObjectName("spinBox_11");
        spinBox_11->setValue(3);

        gridLayout_5->addWidget(spinBox_11, 2, 1, 1, 1);

        label_15 = new QLabel(tab_3);
        label_15->setObjectName("label_15");

        gridLayout_5->addWidget(label_15, 3, 0, 1, 1);

        spinBox_12 = new QSpinBox(tab_3);
        spinBox_12->setObjectName("spinBox_12");

        gridLayout_5->addWidget(spinBox_12, 3, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout_6 = new QGridLayout(tab_4);
        gridLayout_6->setObjectName("gridLayout_6");
        label_7 = new QLabel(tab_4);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 0, 0, 1, 1);

        spinBox_13 = new QSpinBox(tab_4);
        spinBox_13->setObjectName("spinBox_13");
        spinBox_13->setMaximum(65535);
        spinBox_13->setValue(15);

        gridLayout_6->addWidget(spinBox_13, 0, 1, 1, 1);

        label_10 = new QLabel(tab_4);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        spinBox_14 = new QSpinBox(tab_4);
        spinBox_14->setObjectName("spinBox_14");
        spinBox_14->setMaximum(65535);
        spinBox_14->setValue(1023);

        gridLayout_6->addWidget(spinBox_14, 1, 1, 1, 1);

        label_13 = new QLabel(tab_4);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 2, 0, 1, 1);

        spinBox_15 = new QSpinBox(tab_4);
        spinBox_15->setObjectName("spinBox_15");
        spinBox_15->setValue(7);

        gridLayout_6->addWidget(spinBox_15, 2, 1, 1, 1);

        label_16 = new QLabel(tab_4);
        label_16->setObjectName("label_16");

        gridLayout_6->addWidget(label_16, 3, 0, 1, 1);

        spinBox_16 = new QSpinBox(tab_4);
        spinBox_16->setObjectName("spinBox_16");

        gridLayout_6->addWidget(spinBox_16, 3, 1, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        verticalLayout = new QVBoxLayout(tab_5);
        verticalLayout->setObjectName("verticalLayout");
        checkBox = new QCheckBox(tab_5);
        checkBox->setObjectName("checkBox");

        verticalLayout->addWidget(checkBox);

        comboBox = new QComboBox(tab_5);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        label_17 = new QLabel(tab_5);
        label_17->setObjectName("label_17");

        verticalLayout->addWidget(label_17);

        spinBox_17 = new QSpinBox(tab_5);
        spinBox_17->setObjectName("spinBox_17");
        spinBox_17->setMaximum(65535);
        spinBox_17->setValue(65535);

        verticalLayout->addWidget(spinBox_17);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        verticalLayout_2 = new QVBoxLayout(tab_6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        checkBox_2 = new QCheckBox(tab_6);
        checkBox_2->setObjectName("checkBox_2");

        verticalLayout_2->addWidget(checkBox_2);

        comboBox_2 = new QComboBox(tab_6);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout_2->addWidget(comboBox_2);

        label_18 = new QLabel(tab_6);
        label_18->setObjectName("label_18");

        verticalLayout_2->addWidget(label_18);

        spinBox_18 = new QSpinBox(tab_6);
        spinBox_18->setObjectName("spinBox_18");
        spinBox_18->setMaximum(65535);
        spinBox_18->setValue(65535);

        verticalLayout_2->addWidget(spinBox_18);

        label_19 = new QLabel(tab_6);
        label_19->setObjectName("label_19");

        verticalLayout_2->addWidget(label_19);

        spinBox_19 = new QSpinBox(tab_6);
        spinBox_19->setObjectName("spinBox_19");
        spinBox_19->setMaximum(65535);
        spinBox_19->setValue(40);

        verticalLayout_2->addWidget(spinBox_19);

        tabWidget->addTab(tab_6, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(frame);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(Edca_config);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Edca_config, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Edca_config, qOverload<>(&QDialog::reject));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Edca_config);
    } // setupUi

    void retranslateUi(QDialog *Edca_config)
    {
        Edca_config->setWindowTitle(QCoreApplication::translate("Edca_config", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Edca_config", "Cw_min", nullptr));
        label_2->setText(QCoreApplication::translate("Edca_config", "Cw_max", nullptr));
        label_4->setText(QCoreApplication::translate("Edca_config", "AIFSN", nullptr));
        label_3->setText(QCoreApplication::translate("Edca_config", "TXOP_LIMIT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Edca_config", "AC_VO", nullptr));
        label_5->setText(QCoreApplication::translate("Edca_config", "Cw_min", nullptr));
        label_8->setText(QCoreApplication::translate("Edca_config", "Cw_max", nullptr));
        label_11->setText(QCoreApplication::translate("Edca_config", "AIFSN", nullptr));
        label_14->setText(QCoreApplication::translate("Edca_config", "TXOP_LIMIT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Edca_config", "AC_VI", nullptr));
        label_6->setText(QCoreApplication::translate("Edca_config", "Cw_min", nullptr));
        label_9->setText(QCoreApplication::translate("Edca_config", "Cw_max", nullptr));
        label_12->setText(QCoreApplication::translate("Edca_config", "AIFSN", nullptr));
        label_15->setText(QCoreApplication::translate("Edca_config", "TXOP_LIMIT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Edca_config", "AC_BE", nullptr));
        label_7->setText(QCoreApplication::translate("Edca_config", "Cw_min", nullptr));
        label_10->setText(QCoreApplication::translate("Edca_config", "Cw_max", nullptr));
        label_13->setText(QCoreApplication::translate("Edca_config", "AIFSN", nullptr));
        label_16->setText(QCoreApplication::translate("Edca_config", "TXOP_LIMIT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("Edca_config", "AC_BK", nullptr));
        checkBox->setText(QCoreApplication::translate("Edca_config", "AMsdu", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Edca_config", "AC_VO", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Edca_config", "AC_VI", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Edca_config", "AC_BE", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Edca_config", "AC_BK", nullptr));

        label_17->setText(QCoreApplication::translate("Edca_config", "Max AMsdu Size", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("Edca_config", "AMsdu", nullptr));
        checkBox_2->setText(QCoreApplication::translate("Edca_config", "AMpdu", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("Edca_config", "AC_VO", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("Edca_config", "AC_VI", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("Edca_config", "AC_BE", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("Edca_config", "AC_BK", nullptr));

        label_18->setText(QCoreApplication::translate("Edca_config", "Max AMsdu Size", nullptr));
        label_19->setText(QCoreApplication::translate("Edca_config", "Density(us)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("Edca_config", "AMpdu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edca_config: public Ui_Edca_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDCA_CONFIG_H
