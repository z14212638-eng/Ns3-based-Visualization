/********************************************************************************
** Form generated from reading UI file 'page1_model_chose.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE1_MODEL_CHOSE_H
#define UI_PAGE1_MODEL_CHOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page1_model_chose
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_21;
    QVBoxLayout *verticalLayout_2;
    QToolBox *toolBox;
    QWidget *page;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QWidget *page_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget_2;
    QWidget *page_3;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_6;
    QListWidget *listWidget_3;
    QWidget *widget_22;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_5;
    QWidget *widget;
    QWidget *widget_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QWidget *widget_20;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser_2;
    QLabel *label_3;
    QWidget *widget_23;
    QGridLayout *gridLayout;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_4;
    QWidget *tab_2;
    QWidget *tab_3;

    void setupUi(QWidget *Page1_model_chose)
    {
        if (Page1_model_chose->objectName().isEmpty())
            Page1_model_chose->setObjectName("Page1_model_chose");
        Page1_model_chose->resize(1910, 965);
        gridLayout_2 = new QGridLayout(Page1_model_chose);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(Page1_model_chose);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(16777215, 800));
        QFont font;
        font.setBold(false);
        tabWidget->setFont(font);
        tabWidget->setIconSize(QSize(20, 20));
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        widget_21 = new QWidget(tab);
        widget_21->setObjectName("widget_21");
        widget_21->setMinimumSize(QSize(50, 0));
        widget_21->setMaximumSize(QSize(1000, 800));
        verticalLayout_2 = new QVBoxLayout(widget_21);
        verticalLayout_2->setObjectName("verticalLayout_2");
        toolBox = new QToolBox(widget_21);
        toolBox->setObjectName("toolBox");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy1);
        toolBox->setMinimumSize(QSize(400, 0));
        toolBox->setMaximumSize(QSize(450, 600));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(false);
        toolBox->setFont(font1);
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 450, 256));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy2);
        scrollArea = new QScrollArea(page);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 400, 800));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(400, 200));
        scrollArea->setMaximumSize(QSize(400, 800));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 398, 400));
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        scrollAreaWidgetContents->setMaximumSize(QSize(400, 400));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName("horizontalLayout");
        listWidget = new QListWidget(scrollAreaWidgetContents);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(0, 200));
        listWidget->setMaximumSize(QSize(400, 800));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(false);
        listWidget->setFont(font2);

        horizontalLayout->addWidget(listWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);
        toolBox->addItem(page, QString::fromUtf8("Simple Scenes"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setGeometry(QRect(0, 0, 400, 256));
        sizePolicy2.setHeightForWidth(page_2->sizePolicy().hasHeightForWidth());
        page_2->setSizePolicy(sizePolicy2);
        page_2->setMinimumSize(QSize(0, 200));
        page_2->setMaximumSize(QSize(400, 400));
        scrollArea_2 = new QScrollArea(page_2);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(0, 0, 400, 400));
        sizePolicy.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy);
        scrollArea_2->setMinimumSize(QSize(0, 0));
        scrollArea_2->setMaximumSize(QSize(400, 400));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 398, 398));
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy2);
        scrollAreaWidgetContents_2->setMinimumSize(QSize(0, 0));
        scrollAreaWidgetContents_2->setMaximumSize(QSize(400, 400));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        listWidget_2 = new QListWidget(scrollAreaWidgetContents_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        listWidget_2->setObjectName("listWidget_2");
        sizePolicy.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
        listWidget_2->setSizePolicy(sizePolicy);
        listWidget_2->setMinimumSize(QSize(0, 0));
        listWidget_2->setMaximumSize(QSize(400, 400));
        listWidget_2->setFont(font2);

        horizontalLayout_2->addWidget(listWidget_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        toolBox->addItem(page_2, QString::fromUtf8("Complex Scenes"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 400, 256));
        page_3->setMinimumSize(QSize(0, 200));
        page_3->setMaximumSize(QSize(400, 400));
        scrollArea_3 = new QScrollArea(page_3);
        scrollArea_3->setObjectName("scrollArea_3");
        scrollArea_3->setGeometry(QRect(-1, -1, 400, 251));
        scrollArea_3->setMaximumSize(QSize(400, 400));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 398, 249));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        listWidget_3 = new QListWidget(scrollAreaWidgetContents_3);
        listWidget_3->setObjectName("listWidget_3");
        listWidget_3->setMaximumSize(QSize(400, 400));
        listWidget_3->setFont(font1);

        verticalLayout_6->addWidget(listWidget_3);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        toolBox->addItem(page_3, QString::fromUtf8("Scratch"));

        verticalLayout_2->addWidget(toolBox);

        widget_22 = new QWidget(widget_21);
        widget_22->setObjectName("widget_22");
        sizePolicy2.setHeightForWidth(widget_22->sizePolicy().hasHeightForWidth());
        widget_22->setSizePolicy(sizePolicy2);
        widget_22->setMaximumSize(QSize(400, 400));
        verticalLayout_3 = new QVBoxLayout(widget_22);
        verticalLayout_3->setObjectName("verticalLayout_3");
        pushButton_5 = new QPushButton(widget_22);
        pushButton_5->setObjectName("pushButton_5");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy3);
        pushButton_5->setMinimumSize(QSize(300, 80));

        verticalLayout_3->addWidget(pushButton_5);

        widget = new QWidget(widget_22);
        widget->setObjectName("widget");

        verticalLayout_3->addWidget(widget);

        widget_2 = new QWidget(widget_22);
        widget_2->setObjectName("widget_2");

        verticalLayout_3->addWidget(widget_2);

        pushButton = new QPushButton(widget_22);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(300, 80));

        verticalLayout_3->addWidget(pushButton);

        label_2 = new QLabel(widget_22);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setMaximumSize(QSize(250, 50));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(false);
        label_2->setFont(font3);

        verticalLayout_3->addWidget(label_2);

        textBrowser = new QTextBrowser(widget_22);
        textBrowser->setObjectName("textBrowser");
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMaximumSize(QSize(200, 50));
        textBrowser->setFont(font3);

        verticalLayout_3->addWidget(textBrowser);


        verticalLayout_2->addWidget(widget_22);


        horizontalLayout_3->addWidget(widget_21);

        widget_20 = new QWidget(tab);
        widget_20->setObjectName("widget_20");
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_20->sizePolicy().hasHeightForWidth());
        widget_20->setSizePolicy(sizePolicy4);
        widget_20->setMinimumSize(QSize(0, 0));
        widget_20->setMaximumSize(QSize(800, 800));
        verticalLayout = new QVBoxLayout(widget_20);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(widget_20);
        label->setObjectName("label");
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMaximumSize(QSize(16777215, 90));
        QFont font4;
        font4.setPointSize(24);
        font4.setBold(true);
        label->setFont(font4);

        verticalLayout->addWidget(label);

        textBrowser_2 = new QTextBrowser(widget_20);
        textBrowser_2->setObjectName("textBrowser_2");
        sizePolicy.setHeightForWidth(textBrowser_2->sizePolicy().hasHeightForWidth());
        textBrowser_2->setSizePolicy(sizePolicy);
        textBrowser_2->setMaximumSize(QSize(500, 400));
        textBrowser_2->setFont(font1);

        verticalLayout->addWidget(textBrowser_2);

        label_3 = new QLabel(widget_20);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(500, 130));

        verticalLayout->addWidget(label_3);


        horizontalLayout_3->addWidget(widget_20);

        widget_23 = new QWidget(tab);
        widget_23->setObjectName("widget_23");
        sizePolicy4.setHeightForWidth(widget_23->sizePolicy().hasHeightForWidth());
        widget_23->setSizePolicy(sizePolicy4);
        widget_23->setMinimumSize(QSize(0, 0));
        widget_23->setMaximumSize(QSize(400, 800));
        gridLayout = new QGridLayout(widget_23);
        gridLayout->setObjectName("gridLayout");
        widget_4 = new QWidget(widget_23);
        widget_4->setObjectName("widget_4");
        widget_4->setMaximumSize(QSize(200, 800));
        verticalLayout_5 = new QVBoxLayout(widget_4);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_5->addItem(verticalSpacer_2);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy3.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy3);
        pushButton_3->setMaximumSize(QSize(170, 60));
        QFont font5;
        font5.setPointSize(14);
        font5.setBold(true);
        font5.setUnderline(true);
        pushButton_3->setFont(font5);
        pushButton_3->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_5->addWidget(pushButton_3);


        gridLayout->addWidget(widget_4, 0, 1, 1, 1);

        widget_3 = new QWidget(widget_23);
        widget_3->setObjectName("widget_3");
        widget_3->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer);

        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy3.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy3);
        pushButton_4->setMaximumSize(QSize(170, 60));
        pushButton_4->setFont(font5);

        verticalLayout_4->addWidget(pushButton_4);


        gridLayout->addWidget(widget_3, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(widget_23);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Page1_model_chose);

        tabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Page1_model_chose);
    } // setupUi

    void retranslateUi(QWidget *Page1_model_chose)
    {
        Page1_model_chose->setWindowTitle(QCoreApplication::translate("Page1_model_chose", "Scene Selection", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Page1_model_chose", "None", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_2", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_3", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_4", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_5", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_6", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_7", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_8", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_9", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget->item(17);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget->item(18);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget->item(19);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("Page1_model_chose", "Tutorial_1", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget->item(20);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("Page1_model_chose", "df", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget->item(21);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("Page1_model_chose", "ga", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget->item(22);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("Page1_model_chose", "gf", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget->item(23);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("Page1_model_chose", "ag", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget->item(24);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("Page1_model_chose", "g", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget->item(25);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("Page1_model_chose", "dfg", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget->item(26);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("Page1_model_chose", "dg", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidget->item(27);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("Page1_model_chose", "gs", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget->item(28);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("Page1_model_chose", "hn", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget->item(29);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("Page1_model_chose", "f", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget->item(30);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("Page1_model_chose", "hs", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget->item(31);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("Page1_model_chose", "dhg", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget->item(32);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("Page1_model_chose", "fdh", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget->item(33);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("Page1_model_chose", "sg", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget->item(34);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("Page1_model_chose", "fhsd", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget->item(35);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("Page1_model_chose", "g", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidget->item(36);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("Page1_model_chose", "afv", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget->item(37);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("Page1_model_chose", "New Item", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("Page1_model_chose", "Simple Scenes", nullptr));

        const bool __sortingEnabled1 = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem38 = listWidget_2->item(0);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("Page1_model_chose", "None", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget_2->item(1);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("Page1_model_chose", "RTS test", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget_2->item(2);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("Page1_model_chose", "Throughput test", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget_2->item(3);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("Page1_model_chose", "CTS test", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget_2->item(4);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("Page1_model_chose", "SNR margin test", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget_2->item(5);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("Page1_model_chose", "PPDU Collection", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = listWidget_2->item(6);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("Page1_model_chose", "fd", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget_2->item(7);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("Page1_model_chose", "j", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget_2->item(8);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("Page1_model_chose", "ghj", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidget_2->item(9);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("Page1_model_chose", "gs", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget_2->item(10);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("Page1_model_chose", "gfdh", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget_2->item(11);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("Page1_model_chose", "gf", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget_2->item(12);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("Page1_model_chose", "hf", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget_2->item(13);
        ___qlistwidgetitem51->setText(QCoreApplication::translate("Page1_model_chose", "h", nullptr));
        QListWidgetItem *___qlistwidgetitem52 = listWidget_2->item(14);
        ___qlistwidgetitem52->setText(QCoreApplication::translate("Page1_model_chose", "gdfh", nullptr));
        QListWidgetItem *___qlistwidgetitem53 = listWidget_2->item(15);
        ___qlistwidgetitem53->setText(QCoreApplication::translate("Page1_model_chose", "d", nullptr));
        QListWidgetItem *___qlistwidgetitem54 = listWidget_2->item(16);
        ___qlistwidgetitem54->setText(QCoreApplication::translate("Page1_model_chose", "hf", nullptr));
        QListWidgetItem *___qlistwidgetitem55 = listWidget_2->item(17);
        ___qlistwidgetitem55->setText(QCoreApplication::translate("Page1_model_chose", "hf", nullptr));
        QListWidgetItem *___qlistwidgetitem56 = listWidget_2->item(18);
        ___qlistwidgetitem56->setText(QCoreApplication::translate("Page1_model_chose", "dh", nullptr));
        QListWidgetItem *___qlistwidgetitem57 = listWidget_2->item(19);
        ___qlistwidgetitem57->setText(QCoreApplication::translate("Page1_model_chose", "ghgfd", nullptr));
        QListWidgetItem *___qlistwidgetitem58 = listWidget_2->item(20);
        ___qlistwidgetitem58->setText(QCoreApplication::translate("Page1_model_chose", "h", nullptr));
        QListWidgetItem *___qlistwidgetitem59 = listWidget_2->item(21);
        ___qlistwidgetitem59->setText(QCoreApplication::translate("Page1_model_chose", "New Item", nullptr));
        listWidget_2->setSortingEnabled(__sortingEnabled1);

        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("Page1_model_chose", "Complex Scenes", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QCoreApplication::translate("Page1_model_chose", "Scratch", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Page1_model_chose", "Select", nullptr));
        pushButton->setText(QCoreApplication::translate("Page1_model_chose", "(Not Implemented)", nullptr));
        label_2->setText(QCoreApplication::translate("Page1_model_chose", "Simulation Selected", nullptr));
        label->setText(QCoreApplication::translate("Page1_model_chose", "Select Model From the List", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("Page1_model_chose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:700;\">click &quot;Simple scenes&quot; or &quot;Complex scenes&quot; to select the existed scene in ns-3.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:700;\">Or you could click &quot;Design by myself&quot; to customize your "
                        "simulation configs.</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Page1_model_chose", "View", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Page1_model_chose", "Apply", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Page1_model_chose", "Back", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Page1_model_chose", "Simulation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Page1_model_chose", "File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Page1_model_chose", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page1_model_chose: public Ui_Page1_model_chose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE1_MODEL_CHOSE_H
