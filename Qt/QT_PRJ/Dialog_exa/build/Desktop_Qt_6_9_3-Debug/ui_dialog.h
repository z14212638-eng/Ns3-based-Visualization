/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QGroupBox *groupBox_1;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(800, 289);
        frame = new QFrame(Dialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 30, 741, 231));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(440, 180, 81, 25));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu Mono")});
        font.setPointSize(11);
        font.setBold(true);
        font.setItalic(false);
        pushButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/go-next.png"), QSize(), QIcon::Mode::Selected, QIcon::State::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(20, 20));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(600, 180, 81, 22));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(220, 180, 81, 25));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu Mono")});
        font1.setPointSize(11);
        font1.setBold(true);
        pushButton_2->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("icons/go-previous.png"), QSize(), QIcon::Mode::Selected, QIcon::State::On);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(20, 20));
        textEdit = new QTextEdit(frame);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(60, 10, 631, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu Sans Mono")});
        font2.setBold(true);
        font2.setItalic(false);
        textEdit->setFont(font2);
        groupBox_1 = new QGroupBox(frame);
        groupBox_1->setObjectName("groupBox_1");
        groupBox_1->setGeometry(QRect(20, 160, 701, 61));
        textEdit->raise();
        groupBox_1->raise();
        pushButton->raise();
        checkBox->raise();
        pushButton_2->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "next", nullptr));
        checkBox->setText(QCoreApplication::translate("Dialog", "I agree", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "Back", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans Mono'; font-size:9pt; font-weight:700; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt;\">NS-3 Visualizer</span></p></body></html>", nullptr));
        groupBox_1->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
