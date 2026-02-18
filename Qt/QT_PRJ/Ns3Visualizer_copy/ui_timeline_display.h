/********************************************************************************
** Form generated from reading UI file 'timeline_display.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMELINE_DISPLAY_H
#define UI_TIMELINE_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Timeline_Display
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_3;

    void setupUi(QWidget *Timeline_Display)
    {
        if (Timeline_Display->objectName().isEmpty())
            Timeline_Display->setObjectName("Timeline_Display");
        Timeline_Display->resize(1842, 994);
        gridLayout = new QGridLayout(Timeline_Display);
        gridLayout->setObjectName("gridLayout");
        widget_2 = new QWidget(Timeline_Display);
        widget_2->setObjectName("widget_2");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMaximumSize(QSize(600, 600));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(widget_2);
        frame->setObjectName("frame");
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(800, 800));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout->addWidget(frame);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        widget_3 = new QWidget(Timeline_Display);
        widget_3->setObjectName("widget_3");
        widget_3->setMaximumSize(QSize(16777215, 600));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        frame_2 = new QFrame(widget_3);
        frame_2->setObjectName("frame_2");
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMaximumSize(QSize(16777215, 800));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        textEdit = new QTextEdit(frame_2);
        textEdit->setObjectName("textEdit");

        horizontalLayout_3->addWidget(textEdit);


        horizontalLayout->addWidget(frame_2);


        gridLayout->addWidget(widget_3, 1, 1, 1, 1);

        widget = new QWidget(Timeline_Display);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        frame_3 = new QFrame(widget);
        frame_3->setObjectName("frame_3");
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setMaximumSize(QSize(16777215, 4000));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_2->addWidget(frame_3);


        gridLayout->addWidget(widget, 0, 0, 1, 2);


        retranslateUi(Timeline_Display);

        QMetaObject::connectSlotsByName(Timeline_Display);
    } // setupUi

    void retranslateUi(QWidget *Timeline_Display)
    {
        Timeline_Display->setWindowTitle(QCoreApplication::translate("Timeline_Display", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Timeline_Display: public Ui_Timeline_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINE_DISPLAY_H
