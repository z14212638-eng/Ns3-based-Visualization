/********************************************************************************
** Form generated from reading UI file 'greeting.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREETING_H
#define UI_GREETING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Greeting
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QWidget *widget_5;
    QWidget *widget_6;
    QPushButton *pushButton_2;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *title;
    QWidget *widget_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_7;
    QLabel *label_2;
    QTextEdit *lineEdit;

    void setupUi(QWidget *Greeting)
    {
        if (Greeting->objectName().isEmpty())
            Greeting->setObjectName("Greeting");
        Greeting->resize(1802, 1018);
        gridLayout = new QGridLayout(Greeting);
        gridLayout->setObjectName("gridLayout");
        widget_3 = new QWidget(Greeting);
        widget_3->setObjectName("widget_3");
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");

        gridLayout_3->addWidget(widget_5, 0, 0, 1, 1);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");

        gridLayout_3->addWidget(widget_6, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_3->addWidget(pushButton_2, 1, 1, 1, 1);


        gridLayout->addWidget(widget_3, 2, 1, 1, 1);

        widget_4 = new QWidget(Greeting);
        widget_4->setObjectName("widget_4");
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName("gridLayout_2");
        title = new QLabel(widget_4);
        title->setObjectName("title");
        title->setMaximumSize(QSize(900, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("NotoSerifTamilSlanted Thin")});
        font.setPointSize(48);
        title->setFont(font);

        gridLayout_2->addWidget(title, 0, 0, 1, 1);


        gridLayout->addWidget(widget_4, 0, 0, 1, 1);

        widget_2 = new QWidget(Greeting);
        widget_2->setObjectName("widget_2");

        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        widget = new QWidget(Greeting);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(900, 400));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        widget_7 = new QWidget(widget);
        widget_7->setObjectName("widget_7");

        verticalLayout->addWidget(widget_7);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(900, 100));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        lineEdit = new QTextEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMaximumSize(QSize(800, 40));

        verticalLayout->addWidget(lineEdit);


        gridLayout->addWidget(widget, 2, 0, 1, 1);


        retranslateUi(Greeting);

        QMetaObject::connectSlotsByName(Greeting);
    } // setupUi

    void retranslateUi(QWidget *Greeting)
    {
        Greeting->setWindowTitle(QCoreApplication::translate("Greeting", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Greeting", "Continue", nullptr));
        title->setText(QCoreApplication::translate("Greeting", "NS-3 Visualizer", nullptr));
        label_2->setText(QCoreApplication::translate("Greeting", "Ns3 Directory (click \"PATH\" button in the menu to set)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Greeting: public Ui_Greeting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREETING_H
