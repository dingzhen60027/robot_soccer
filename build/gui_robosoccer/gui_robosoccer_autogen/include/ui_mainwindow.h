/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <HSIslider.h>
#include <ImageLabelColor.h>
#include <ImageLabelControl.h>
#include <ImageLabelDrawI.h>
#include <ImageLabelEnlarge.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *Lab_Image_P;
    ImageLabelControl *Lab_Image_C;
    QLabel *Lab_FPS1_Process;
    QLabel *Lab_FPS2_Capture;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *Btn_Save;
    QPushButton *Btn_Load;
    QPushButton *Btn_Open;
    QPushButton *Btn_Close;
    QPushButton *Btn_Start;
    QPushButton *Btn_Quit;
    QTextEdit *Lab_StatusText;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *Btn_PointLeft;
    QPushButton *Btn_PointRight;
    QPushButton *Btn_PointUp;
    QPushButton *Btn_PointDown;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Btn_PointRecord;
    QPushButton *Btn_PointDelone;
    QPushButton *Btn_PointDelall;
    QPushButton *Btn_PointCalib;
    QLabel *Lab_PointSel;
    QWidget *tab_2;
    ImageLabelEnlarge *Lab_ColorEnlarge;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *Sel_Team;
    QRadioButton *Sel_Mem1;
    QRadioButton *Sel_Mem2;
    QRadioButton *Sel_Mem3;
    QRadioButton *Sel_Mem4;
    QRadioButton *Sel_Mem5;
    QRadioButton *Sel_Ball;
    QRadioButton *Sel_Opp;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Btn_Sampling;
    QPushButton *Btn_RePoints;
    QPushButton *Btn_ColorTest;
    QPushButton *Btn_HSIcomplete;
    ImageLabelDrawI *Lab_ShowIdata;
    ImageLabelColor *Lab_ColorData;
    HSIslider *Sld_H_Low;
    HSIslider *Sld_H_High;
    HSIslider *Sld_S_Low;
    HSIslider *Sld_S_High;
    HSIslider *Sld_I_Low;
    HSIslider *Sld_I_High;
    QLabel *Lab_H_Low;
    QLabel *Lab_H_High;
    QLabel *Lab_S_Low;
    QLabel *Lab_S_High;
    QLabel *Lab_I_Low;
    QLabel *Lab_I_High;
    QWidget *tab_3;
    QGroupBox *groupBox_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *Sel_SelfAttack;
    QRadioButton *Sel_OppAttack;
    QGroupBox *groupBox_3;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Sel_LeftGround;
    QRadioButton *Sel_RightGround;
    QGroupBox *groupBox_4;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QRadioButton *Sel_GameMode1;
    QRadioButton *Sel_GameMode0;
    QRadioButton *Sel_GameMode2;
    QRadioButton *Sel_GameMode3;
    QRadioButton *Sel_GameMode4;
    QRadioButton *Sel_GameMode5;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *Sel_BackInit;
    QRadioButton *Sel_StartGame;
    QGroupBox *groupBox_6;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *Sel_InitVar;
    QRadioButton *Sel_ContiVar;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Btn_ToStart;
    QPushButton *Btn_ToStop;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1800, 1000);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"  border-radius: 6px;\n"
"  border: 1.5px solid #B0B0B0;\n"
"  font: 12pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"  margin-top: 12px;\n"
"}\n"
"QGroupBox::title {\n"
"  subcontrol-origin: margin;\n"
"  subcontrol-position: top left;\n"
"  left: 8px;\n"
"  padding: 2px 0 7px 0;\n"
"  color: #343434;\n"
"  font: 12pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"  font-weight: normal;\n"
"}\n"
"QPushButton {\n"
"  font: 11pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"  min-width: 88px; min-height: 36px;\n"
"  margin:4px;\n"
"  border-radius: 4.5px;\n"
"  border:1px solid #B5B5B5;\n"
"  background-color:#f6f6f6;\n"
"  color:#262b37;\n"
"}\n"
"QPushButton:hover{background-color:#e9e9ef;}\n"
"QTabWidget::pane { border-radius:6px; border:1.3px solid #bbb; }\n"
"QTabBar::tab {\n"
"  height:32px; min-width:80px;\n"
"  padding:8px 18px;\n"
"  font:11pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"  background:#f8f8f8;\n"
"  margin:4px;\n"
"  border-radiu"
                        "s:6px 6px 0 0;\n"
"}\n"
"QTabBar::tab:selected {background:#d4e2ef;}\n"
"QLabel {font:11pt '\345\276\256\350\275\257\351\233\205\351\273\221';}\n"
""));
        Lab_Image_P = new QLabel(centralwidget);
        Lab_Image_P->setObjectName(QString::fromUtf8("Lab_Image_P"));
        Lab_Image_P->setGeometry(QRect(10, 650, 480, 300));
        Lab_Image_P->setBaseSize(QSize(0, 0));
        Lab_Image_P->setFrameShape(QFrame::Panel);
        Lab_Image_C = new ImageLabelControl(centralwidget);
        Lab_Image_C->setObjectName(QString::fromUtf8("Lab_Image_C"));
        Lab_Image_C->setGeometry(QRect(10, 10, 960, 600));
        Lab_Image_C->setBaseSize(QSize(0, 0));
        Lab_Image_C->setFrameShape(QFrame::Panel);
        Lab_Image_C->setFrameShadow(QFrame::Plain);
        Lab_Image_C->setLineWidth(1);
        Lab_FPS1_Process = new QLabel(centralwidget);
        Lab_FPS1_Process->setObjectName(QString::fromUtf8("Lab_FPS1_Process"));
        Lab_FPS1_Process->setGeometry(QRect(820, 20, 130, 25));
        Lab_FPS1_Process->setStyleSheet(QString::fromUtf8("QLabel#Lab_FPS1_Process {\n"
"     color: red;\n"
"     background-color: transparent;\n"
"     font: bold 10pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"     }"));
        Lab_FPS1_Process->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        Lab_FPS2_Capture = new QLabel(centralwidget);
        Lab_FPS2_Capture->setObjectName(QString::fromUtf8("Lab_FPS2_Capture"));
        Lab_FPS2_Capture->setGeometry(QRect(820, 45, 130, 25));
        Lab_FPS2_Capture->setStyleSheet(QString::fromUtf8("QLabel#Lab_FPS2_Capture {\n"
"     color: red;\n"
"     background-color: transparent;\n"
"     font: bold 10pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"     }"));
        Lab_FPS2_Capture->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(530, 650, 441, 301));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(60);
        gridLayout->setVerticalSpacing(30);
        gridLayout->setContentsMargins(30, 0, 30, 0);
        Btn_Save = new QPushButton(gridLayoutWidget);
        Btn_Save->setObjectName(QString::fromUtf8("Btn_Save"));

        gridLayout->addWidget(Btn_Save, 0, 0, 1, 1);

        Btn_Load = new QPushButton(gridLayoutWidget);
        Btn_Load->setObjectName(QString::fromUtf8("Btn_Load"));

        gridLayout->addWidget(Btn_Load, 0, 1, 1, 1);

        Btn_Open = new QPushButton(gridLayoutWidget);
        Btn_Open->setObjectName(QString::fromUtf8("Btn_Open"));

        gridLayout->addWidget(Btn_Open, 1, 0, 1, 1);

        Btn_Close = new QPushButton(gridLayoutWidget);
        Btn_Close->setObjectName(QString::fromUtf8("Btn_Close"));

        gridLayout->addWidget(Btn_Close, 2, 0, 1, 1);

        Btn_Start = new QPushButton(gridLayoutWidget);
        Btn_Start->setObjectName(QString::fromUtf8("Btn_Start"));

        gridLayout->addWidget(Btn_Start, 1, 1, 1, 1);

        Btn_Quit = new QPushButton(gridLayoutWidget);
        Btn_Quit->setObjectName(QString::fromUtf8("Btn_Quit"));

        gridLayout->addWidget(Btn_Quit, 2, 1, 1, 1);

        Lab_StatusText = new QTextEdit(gridLayoutWidget);
        Lab_StatusText->setObjectName(QString::fromUtf8("Lab_StatusText"));
        Lab_StatusText->setStyleSheet(QString::fromUtf8("QTextEdit#Lab_StatusText {\n"
"         border: 1px solid #D0D0D0;\n"
"         border-radius: 4px;\n"
"         padding: 4px 8px;\n"
"         color: #2c3e50;\n"
"         background-color: #fefefe;\n"
"         font: 11pt '\345\276\256\350\275\257\351\233\205\351\273\221';\n"
"        }"));
        Lab_StatusText->setReadOnly(true);
        Lab_StatusText->setLineWrapMode(QTextEdit::WidgetWidth);
        Lab_StatusText->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        gridLayout->addWidget(Lab_StatusText, 3, 0, 1, 2);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1010, 10, 781, 941));
        QFont font1;
        font1.setPointSize(12);
        tabWidget->setFont(font1);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        gridLayoutWidget_2 = new QWidget(tab_1);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(60, 60, 361, 311));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Btn_PointLeft = new QPushButton(gridLayoutWidget_2);
        Btn_PointLeft->setObjectName(QString::fromUtf8("Btn_PointLeft"));

        gridLayout_2->addWidget(Btn_PointLeft, 1, 0, 1, 1);

        Btn_PointRight = new QPushButton(gridLayoutWidget_2);
        Btn_PointRight->setObjectName(QString::fromUtf8("Btn_PointRight"));

        gridLayout_2->addWidget(Btn_PointRight, 1, 2, 1, 1);

        Btn_PointUp = new QPushButton(gridLayoutWidget_2);
        Btn_PointUp->setObjectName(QString::fromUtf8("Btn_PointUp"));

        gridLayout_2->addWidget(Btn_PointUp, 0, 1, 1, 1);

        Btn_PointDown = new QPushButton(gridLayoutWidget_2);
        Btn_PointDown->setObjectName(QString::fromUtf8("Btn_PointDown"));

        gridLayout_2->addWidget(Btn_PointDown, 2, 1, 1, 1);

        verticalLayoutWidget = new QWidget(tab_1);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(550, 60, 171, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Btn_PointRecord = new QPushButton(verticalLayoutWidget);
        Btn_PointRecord->setObjectName(QString::fromUtf8("Btn_PointRecord"));

        verticalLayout->addWidget(Btn_PointRecord);

        Btn_PointDelone = new QPushButton(verticalLayoutWidget);
        Btn_PointDelone->setObjectName(QString::fromUtf8("Btn_PointDelone"));

        verticalLayout->addWidget(Btn_PointDelone);

        Btn_PointDelall = new QPushButton(verticalLayoutWidget);
        Btn_PointDelall->setObjectName(QString::fromUtf8("Btn_PointDelall"));

        verticalLayout->addWidget(Btn_PointDelall);

        Btn_PointCalib = new QPushButton(verticalLayoutWidget);
        Btn_PointCalib->setObjectName(QString::fromUtf8("Btn_PointCalib"));

        verticalLayout->addWidget(Btn_PointCalib);

        Lab_PointSel = new QLabel(tab_1);
        Lab_PointSel->setObjectName(QString::fromUtf8("Lab_PointSel"));
        Lab_PointSel->setGeometry(QRect(240, 490, 300, 300));
        Lab_PointSel->setFrameShape(QFrame::Panel);
        Lab_PointSel->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        Lab_ColorEnlarge = new ImageLabelEnlarge(tab_2);
        Lab_ColorEnlarge->setObjectName(QString::fromUtf8("Lab_ColorEnlarge"));
        Lab_ColorEnlarge->setGeometry(QRect(240, 70, 300, 300));
        Lab_ColorEnlarge->setFrameShape(QFrame::Panel);
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 20, 161, 451));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 30, 141, 411));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 0, 0);
        Sel_Team = new QRadioButton(verticalLayoutWidget_2);
        Sel_Team->setObjectName(QString::fromUtf8("Sel_Team"));

        verticalLayout_2->addWidget(Sel_Team);

        Sel_Mem1 = new QRadioButton(verticalLayoutWidget_2);
        Sel_Mem1->setObjectName(QString::fromUtf8("Sel_Mem1"));

        verticalLayout_2->addWidget(Sel_Mem1);

        Sel_Mem2 = new QRadioButton(verticalLayoutWidget_2);
        Sel_Mem2->setObjectName(QString::fromUtf8("Sel_Mem2"));

        verticalLayout_2->addWidget(Sel_Mem2);

        Sel_Mem3 = new QRadioButton(verticalLayoutWidget_2);
        Sel_Mem3->setObjectName(QString::fromUtf8("Sel_Mem3"));

        verticalLayout_2->addWidget(Sel_Mem3);

        Sel_Mem4 = new QRadioButton(verticalLayoutWidget_2);
        Sel_Mem4->setObjectName(QString::fromUtf8("Sel_Mem4"));

        verticalLayout_2->addWidget(Sel_Mem4);

        Sel_Mem5 = new QRadioButton(verticalLayoutWidget_2);
        Sel_Mem5->setObjectName(QString::fromUtf8("Sel_Mem5"));

        verticalLayout_2->addWidget(Sel_Mem5);

        Sel_Ball = new QRadioButton(verticalLayoutWidget_2);
        Sel_Ball->setObjectName(QString::fromUtf8("Sel_Ball"));

        verticalLayout_2->addWidget(Sel_Ball);

        Sel_Opp = new QRadioButton(verticalLayoutWidget_2);
        Sel_Opp->setObjectName(QString::fromUtf8("Sel_Opp"));

        verticalLayout_2->addWidget(Sel_Opp);

        verticalLayoutWidget_3 = new QWidget(tab_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(580, 70, 161, 301));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Btn_Sampling = new QPushButton(verticalLayoutWidget_3);
        Btn_Sampling->setObjectName(QString::fromUtf8("Btn_Sampling"));

        verticalLayout_3->addWidget(Btn_Sampling);

        Btn_RePoints = new QPushButton(verticalLayoutWidget_3);
        Btn_RePoints->setObjectName(QString::fromUtf8("Btn_RePoints"));

        verticalLayout_3->addWidget(Btn_RePoints);

        Btn_ColorTest = new QPushButton(verticalLayoutWidget_3);
        Btn_ColorTest->setObjectName(QString::fromUtf8("Btn_ColorTest"));

        verticalLayout_3->addWidget(Btn_ColorTest);

        Btn_HSIcomplete = new QPushButton(verticalLayoutWidget_3);
        Btn_HSIcomplete->setObjectName(QString::fromUtf8("Btn_HSIcomplete"));

        verticalLayout_3->addWidget(Btn_HSIcomplete);

        Lab_ShowIdata = new ImageLabelDrawI(tab_2);
        Lab_ShowIdata->setObjectName(QString::fromUtf8("Lab_ShowIdata"));
        Lab_ShowIdata->setGeometry(QRect(40, 750, 308, 62));
        Lab_ShowIdata->setFrameShape(QFrame::Panel);
        Lab_ColorData = new ImageLabelColor(tab_2);
        Lab_ColorData->setObjectName(QString::fromUtf8("Lab_ColorData"));
        Lab_ColorData->setGeometry(QRect(40, 510, 200, 200));
        Lab_ColorData->setFrameShape(QFrame::Panel);
        Sld_H_Low = new HSIslider(tab_2);
        Sld_H_Low->setObjectName(QString::fromUtf8("Sld_H_Low"));
        Sld_H_Low->setGeometry(QRect(520, 470, 220, 40));
        Sld_H_High = new HSIslider(tab_2);
        Sld_H_High->setObjectName(QString::fromUtf8("Sld_H_High"));
        Sld_H_High->setGeometry(QRect(520, 530, 220, 40));
        Sld_S_Low = new HSIslider(tab_2);
        Sld_S_Low->setObjectName(QString::fromUtf8("Sld_S_Low"));
        Sld_S_Low->setGeometry(QRect(520, 590, 220, 40));
        Sld_S_High = new HSIslider(tab_2);
        Sld_S_High->setObjectName(QString::fromUtf8("Sld_S_High"));
        Sld_S_High->setGeometry(QRect(520, 650, 220, 40));
        Sld_I_Low = new HSIslider(tab_2);
        Sld_I_Low->setObjectName(QString::fromUtf8("Sld_I_Low"));
        Sld_I_Low->setGeometry(QRect(520, 710, 220, 40));
        Sld_I_High = new HSIslider(tab_2);
        Sld_I_High->setObjectName(QString::fromUtf8("Sld_I_High"));
        Sld_I_High->setGeometry(QRect(520, 770, 220, 40));
        Lab_H_Low = new QLabel(tab_2);
        Lab_H_Low->setObjectName(QString::fromUtf8("Lab_H_Low"));
        Lab_H_Low->setGeometry(QRect(430, 470, 67, 40));
        Lab_H_Low->setAlignment(Qt::AlignCenter);
        Lab_H_High = new QLabel(tab_2);
        Lab_H_High->setObjectName(QString::fromUtf8("Lab_H_High"));
        Lab_H_High->setGeometry(QRect(430, 530, 67, 40));
        Lab_H_High->setAlignment(Qt::AlignCenter);
        Lab_S_Low = new QLabel(tab_2);
        Lab_S_Low->setObjectName(QString::fromUtf8("Lab_S_Low"));
        Lab_S_Low->setGeometry(QRect(430, 590, 67, 40));
        Lab_S_Low->setAlignment(Qt::AlignCenter);
        Lab_S_High = new QLabel(tab_2);
        Lab_S_High->setObjectName(QString::fromUtf8("Lab_S_High"));
        Lab_S_High->setGeometry(QRect(430, 650, 67, 40));
        Lab_S_High->setAlignment(Qt::AlignCenter);
        Lab_I_Low = new QLabel(tab_2);
        Lab_I_Low->setObjectName(QString::fromUtf8("Lab_I_Low"));
        Lab_I_Low->setGeometry(QRect(430, 710, 67, 40));
        Lab_I_Low->setAlignment(Qt::AlignCenter);
        Lab_I_High = new QLabel(tab_2);
        Lab_I_High->setObjectName(QString::fromUtf8("Lab_I_High"));
        Lab_I_High->setGeometry(QRect(430, 770, 67, 40));
        Lab_I_High->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(80, 20, 621, 101));
        horizontalLayoutWidget = new QWidget(groupBox_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 30, 601, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(100, 0, 0, 0);
        Sel_SelfAttack = new QRadioButton(horizontalLayoutWidget);
        Sel_SelfAttack->setObjectName(QString::fromUtf8("Sel_SelfAttack"));

        horizontalLayout->addWidget(Sel_SelfAttack);

        Sel_OppAttack = new QRadioButton(horizontalLayoutWidget);
        Sel_OppAttack->setObjectName(QString::fromUtf8("Sel_OppAttack"));

        horizontalLayout->addWidget(Sel_OppAttack);

        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(80, 150, 621, 101));
        horizontalLayoutWidget_2 = new QWidget(groupBox_3);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 30, 601, 61));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(100, 0, 0, 0);
        Sel_LeftGround = new QRadioButton(horizontalLayoutWidget_2);
        Sel_LeftGround->setObjectName(QString::fromUtf8("Sel_LeftGround"));

        horizontalLayout_2->addWidget(Sel_LeftGround);

        Sel_RightGround = new QRadioButton(horizontalLayoutWidget_2);
        Sel_RightGround->setObjectName(QString::fromUtf8("Sel_RightGround"));

        horizontalLayout_2->addWidget(Sel_RightGround);

        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(80, 280, 621, 181));
        gridLayoutWidget_3 = new QWidget(groupBox_4);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 30, 601, 141));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(60, 0, 0, 0);
        Sel_GameMode1 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode1->setObjectName(QString::fromUtf8("Sel_GameMode1"));

        gridLayout_3->addWidget(Sel_GameMode1, 0, 1, 1, 1);

        Sel_GameMode0 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode0->setObjectName(QString::fromUtf8("Sel_GameMode0"));

        gridLayout_3->addWidget(Sel_GameMode0, 0, 0, 1, 1);

        Sel_GameMode2 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode2->setObjectName(QString::fromUtf8("Sel_GameMode2"));

        gridLayout_3->addWidget(Sel_GameMode2, 0, 2, 1, 1);

        Sel_GameMode3 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode3->setObjectName(QString::fromUtf8("Sel_GameMode3"));

        gridLayout_3->addWidget(Sel_GameMode3, 1, 0, 1, 1);

        Sel_GameMode4 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode4->setObjectName(QString::fromUtf8("Sel_GameMode4"));

        gridLayout_3->addWidget(Sel_GameMode4, 1, 1, 1, 1);

        Sel_GameMode5 = new QRadioButton(gridLayoutWidget_3);
        Sel_GameMode5->setObjectName(QString::fromUtf8("Sel_GameMode5"));

        gridLayout_3->addWidget(Sel_GameMode5, 1, 2, 1, 1);

        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(80, 490, 621, 101));
        horizontalLayoutWidget_3 = new QWidget(groupBox_5);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(9, 30, 601, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(100, 0, 0, 0);
        Sel_BackInit = new QRadioButton(horizontalLayoutWidget_3);
        Sel_BackInit->setObjectName(QString::fromUtf8("Sel_BackInit"));

        horizontalLayout_3->addWidget(Sel_BackInit);

        Sel_StartGame = new QRadioButton(horizontalLayoutWidget_3);
        Sel_StartGame->setObjectName(QString::fromUtf8("Sel_StartGame"));

        horizontalLayout_3->addWidget(Sel_StartGame);

        groupBox_6 = new QGroupBox(tab_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(80, 620, 621, 101));
        horizontalLayoutWidget_4 = new QWidget(groupBox_6);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 30, 601, 61));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(100, 0, 0, 0);
        Sel_InitVar = new QRadioButton(horizontalLayoutWidget_4);
        Sel_InitVar->setObjectName(QString::fromUtf8("Sel_InitVar"));

        horizontalLayout_4->addWidget(Sel_InitVar);

        Sel_ContiVar = new QRadioButton(horizontalLayoutWidget_4);
        Sel_ContiVar->setObjectName(QString::fromUtf8("Sel_ContiVar"));

        horizontalLayout_4->addWidget(Sel_ContiVar);

        horizontalLayoutWidget_5 = new QWidget(tab_3);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(80, 770, 621, 91));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(100);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(25, 0, 25, 0);
        Btn_ToStart = new QPushButton(horizontalLayoutWidget_5);
        Btn_ToStart->setObjectName(QString::fromUtf8("Btn_ToStart"));

        horizontalLayout_5->addWidget(Btn_ToStart);

        Btn_ToStop = new QPushButton(horizontalLayoutWidget_5);
        Btn_ToStop->setObjectName(QString::fromUtf8("Btn_ToStop"));

        horizontalLayout_5->addWidget(Btn_ToStop);

        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Lab_Image_P->setText(QString());
        Lab_Image_C->setText(QString());
        Lab_FPS1_Process->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\233\276\345\203\217\345\244\204\347\220\206...", nullptr));
        Lab_FPS2_Capture->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\345\233\276\345\203\217\351\207\207\351\233\206...", nullptr));
        Btn_Save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        Btn_Load->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275", nullptr));
        Btn_Open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        Btn_Close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        Btn_Start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        Btn_Quit->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        Lab_StatusText->setPlainText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\347\212\266\346\200\201\357\274\232\345\276\205\345\221\275", nullptr));
        Btn_PointLeft->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        Btn_PointRight->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        Btn_PointUp->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        Btn_PointDown->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        Btn_PointRecord->setText(QCoreApplication::translate("MainWindow", "\350\256\260\345\275\225\350\257\245\347\202\271", nullptr));
        Btn_PointDelone->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200\344\270\200\347\202\271", nullptr));
        Btn_PointDelall->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\346\222\244\351\224\200", nullptr));
        Btn_PointCalib->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\240\207\345\256\232", nullptr));
        Lab_PointSel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("MainWindow", "\346\240\207\345\256\232", nullptr));
        Lab_ColorEnlarge->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Object", nullptr));
        Sel_Team->setText(QCoreApplication::translate("MainWindow", "TEAM", nullptr));
        Sel_Mem1->setText(QCoreApplication::translate("MainWindow", "MEM1", nullptr));
        Sel_Mem2->setText(QCoreApplication::translate("MainWindow", "MEM2", nullptr));
        Sel_Mem3->setText(QCoreApplication::translate("MainWindow", "MEM3", nullptr));
        Sel_Mem4->setText(QCoreApplication::translate("MainWindow", "MEM4", nullptr));
        Sel_Mem5->setText(QCoreApplication::translate("MainWindow", "MEM5", nullptr));
        Sel_Ball->setText(QCoreApplication::translate("MainWindow", "BALL", nullptr));
        Sel_Opp->setText(QCoreApplication::translate("MainWindow", "OPP", nullptr));
        Btn_Sampling->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267", nullptr));
        Btn_RePoints->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\345\217\226\347\202\271", nullptr));
        Btn_ColorTest->setText(QCoreApplication::translate("MainWindow", "\351\242\234\350\211\262\346\265\213\350\257\225", nullptr));
        Btn_HSIcomplete->setText(QCoreApplication::translate("MainWindow", "\345\256\214\346\210\220\347\241\256\345\256\232", nullptr));
        Lab_ShowIdata->setText(QString());
        Lab_ColorData->setText(QString());
        Lab_H_Low->setText(QCoreApplication::translate("MainWindow", "H_L", nullptr));
        Lab_H_High->setText(QCoreApplication::translate("MainWindow", "H_H", nullptr));
        Lab_S_Low->setText(QCoreApplication::translate("MainWindow", "S_L", nullptr));
        Lab_S_High->setText(QCoreApplication::translate("MainWindow", "S_H", nullptr));
        Lab_I_Low->setText(QCoreApplication::translate("MainWindow", "I_L", nullptr));
        Lab_I_High->setText(QCoreApplication::translate("MainWindow", "I_H", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\351\207\207\350\211\262", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\347\220\203\346\226\271", nullptr));
        Sel_SelfAttack->setText(QCoreApplication::translate("MainWindow", "\346\210\221\346\226\271\345\274\200\347\220\203", nullptr));
        Sel_OppAttack->setText(QCoreApplication::translate("MainWindow", "\345\257\271\346\226\271\345\274\200\347\220\203", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\215\212\345\234\272\351\200\211\346\213\251", nullptr));
        Sel_LeftGround->setText(QCoreApplication::translate("MainWindow", "\345\267\246\345\215\212\345\234\272", nullptr));
        Sel_RightGround->setText(QCoreApplication::translate("MainWindow", "\345\217\263\345\215\212\345\234\272", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\257\224\350\265\233\346\250\241\345\274\217", nullptr));
        Sel_GameMode1->setText(QCoreApplication::translate("MainWindow", "\347\202\271\347\220\203", nullptr));
        Sel_GameMode0->setText(QCoreApplication::translate("MainWindow", "\346\231\256\351\200\232", nullptr));
        Sel_GameMode2->setText(QCoreApplication::translate("MainWindow", "\351\227\250\347\220\203", nullptr));
        Sel_GameMode3->setText(QCoreApplication::translate("MainWindow", "\344\273\273\346\204\217\347\220\203", nullptr));
        Sel_GameMode4->setText(QCoreApplication::translate("MainWindow", "\344\272\211\347\220\203", nullptr));
        Sel_GameMode5->setText(QCoreApplication::translate("MainWindow", "\346\224\266\350\275\246", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\250\241\345\274\217", nullptr));
        Sel_BackInit->setText(QCoreApplication::translate("MainWindow", "\345\275\222\344\275\215", nullptr));
        Sel_StartGame->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\257\224\350\265\233", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\345\217\230\351\207\217\351\207\215\345\244\215\346\250\241\345\274\217", nullptr));
        Sel_InitVar->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226", nullptr));
        Sel_ContiVar->setText(QCoreApplication::translate("MainWindow", "\347\273\247\347\273\255\344\275\277\347\224\250", nullptr));
        Btn_ToStart->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        Btn_ToStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\346\257\224\350\265\233", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
