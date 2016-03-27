/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QToolBox *tb_automode;
    QWidget *page_4;
    QComboBox *cb_portkrxo;
    QPushButton *pb_openportkrxo;
    QPushButton *pb_closeportkrxo;
    QPushButton *pushButton_4;
    QPushButton *pushButton_7;
    QSpinBox *spinBox;
    QLineEdit *le_countkrxo;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *le_krxoammiak;
    QLineEdit *le_krxodioksser;
    QLineEdit *le_krxochlor;
    QLineEdit *le_krxodioksazota;
    QLineEdit *le_krxodoza;
    QLabel *lbl_krxoammiak;
    QLabel *lbl_krxodioksser;
    QLabel *lbl_krxochlor;
    QLabel *lbl_krxodioksazota;
    QLabel *lbl_krxodoza;
    QLineEdit *le_krxolatit;
    QLabel *lbl_krxolatit;
    QLineEdit *le_krxolong;
    QLabel *lbl_krxolong;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroupBDHKConnect;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(760, 770);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(760, 760));
        MainWindow->setMaximumSize(QSize(760, 790));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(106, 104, 100, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        MainWindow->setPalette(palette);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("logo_spectr.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(800, 940));
        centralWidget->setMouseTracking(false);
        centralWidget->setAcceptDrops(false);
        centralWidget->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setEnabled(true);
        frame->setGeometry(QRect(-5, -2, 770, 800));
        frame->setMinimumSize(QSize(0, 720));
        frame->setMaximumSize(QSize(770, 800));
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QStringLiteral(""));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        tb_automode = new QToolBox(frame);
        tb_automode->setObjectName(QStringLiteral("tb_automode"));
        tb_automode->setEnabled(true);
        tb_automode->setGeometry(QRect(4, 2, 762, 751));
        tb_automode->setMaximumSize(QSize(800, 790));
        tb_automode->setAutoFillBackground(false);
        tb_automode->setStyleSheet(QStringLiteral("background-image: url(:/BackMainWindow.jpg);"));
        tb_automode->setLineWidth(1);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 762, 724));
        cb_portkrxo = new QComboBox(page_4);
        cb_portkrxo->setObjectName(QStringLiteral("cb_portkrxo"));
        cb_portkrxo->setGeometry(QRect(134, 30, 100, 25));
        cb_portkrxo->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        cb_portkrxo->setMaxVisibleItems(5);
        cb_portkrxo->setMaxCount(100);
        pb_openportkrxo = new QPushButton(page_4);
        pb_openportkrxo->setObjectName(QStringLiteral("pb_openportkrxo"));
        pb_openportkrxo->setGeometry(QRect(240, 30, 100, 25));
        pb_openportkrxo->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        pb_closeportkrxo = new QPushButton(page_4);
        pb_closeportkrxo->setObjectName(QStringLiteral("pb_closeportkrxo"));
        pb_closeportkrxo->setGeometry(QRect(344, 30, 100, 25));
        pb_closeportkrxo->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        pushButton_4 = new QPushButton(page_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(448, 30, 100, 25));
        pushButton_4->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        pushButton_7 = new QPushButton(page_4);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(552, 30, 100, 25));
        pushButton_7->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        spinBox = new QSpinBox(page_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(284, 84, 100, 25));
        spinBox->setCursor(QCursor(Qt::PointingHandCursor));
        spinBox->setAlignment(Qt::AlignCenter);
        spinBox->setProperty("showGroupSeparator", QVariant(false));
        spinBox->setMinimum(1);
        spinBox->setMaximum(20);
        spinBox->setDisplayIntegerBase(10);
        le_countkrxo = new QLineEdit(page_4);
        le_countkrxo->setObjectName(QStringLiteral("le_countkrxo"));
        le_countkrxo->setGeometry(QRect(390, 84, 100, 25));
        le_countkrxo->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_countkrxo->setAlignment(Qt::AlignCenter);
        le_countkrxo->setReadOnly(true);
        label_7 = new QLabel(page_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(302, 64, 71, 16));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);
        label_7->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(394, 64, 93, 16));
        label_8->setFont(font1);
        label_8->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(150, 10, 71, 16));
        label_9->setFont(font1);
        label_9->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        le_krxoammiak = new QLineEdit(page_4);
        le_krxoammiak->setObjectName(QStringLiteral("le_krxoammiak"));
        le_krxoammiak->setGeometry(QRect(190, 220, 100, 25));
        le_krxoammiak->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxoammiak->setAlignment(Qt::AlignCenter);
        le_krxoammiak->setReadOnly(true);
        le_krxodioksser = new QLineEdit(page_4);
        le_krxodioksser->setObjectName(QStringLiteral("le_krxodioksser"));
        le_krxodioksser->setGeometry(QRect(190, 280, 100, 25));
        le_krxodioksser->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxodioksser->setAlignment(Qt::AlignCenter);
        le_krxodioksser->setReadOnly(true);
        le_krxochlor = new QLineEdit(page_4);
        le_krxochlor->setObjectName(QStringLiteral("le_krxochlor"));
        le_krxochlor->setGeometry(QRect(460, 220, 100, 25));
        le_krxochlor->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxochlor->setAlignment(Qt::AlignCenter);
        le_krxochlor->setReadOnly(true);
        le_krxodioksazota = new QLineEdit(page_4);
        le_krxodioksazota->setObjectName(QStringLiteral("le_krxodioksazota"));
        le_krxodioksazota->setGeometry(QRect(460, 280, 100, 25));
        le_krxodioksazota->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxodioksazota->setAlignment(Qt::AlignCenter);
        le_krxodioksazota->setReadOnly(true);
        le_krxodoza = new QLineEdit(page_4);
        le_krxodoza->setObjectName(QStringLiteral("le_krxodoza"));
        le_krxodoza->setGeometry(QRect(322, 350, 100, 25));
        le_krxodoza->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxodoza->setAlignment(Qt::AlignCenter);
        le_krxodoza->setReadOnly(true);
        lbl_krxoammiak = new QLabel(page_4);
        lbl_krxoammiak->setObjectName(QStringLiteral("lbl_krxoammiak"));
        lbl_krxoammiak->setGeometry(QRect(212, 200, 93, 16));
        lbl_krxoammiak->setFont(font1);
        lbl_krxoammiak->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        lbl_krxodioksser = new QLabel(page_4);
        lbl_krxodioksser->setObjectName(QStringLiteral("lbl_krxodioksser"));
        lbl_krxodioksser->setGeometry(QRect(198, 260, 93, 16));
        lbl_krxodioksser->setFont(font1);
        lbl_krxodioksser->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        lbl_krxochlor = new QLabel(page_4);
        lbl_krxochlor->setObjectName(QStringLiteral("lbl_krxochlor"));
        lbl_krxochlor->setGeometry(QRect(494, 200, 93, 16));
        lbl_krxochlor->setFont(font1);
        lbl_krxochlor->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        lbl_krxodioksazota = new QLabel(page_4);
        lbl_krxodioksazota->setObjectName(QStringLiteral("lbl_krxodioksazota"));
        lbl_krxodioksazota->setGeometry(QRect(466, 258, 93, 16));
        lbl_krxodioksazota->setFont(font1);
        lbl_krxodioksazota->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        lbl_krxodoza = new QLabel(page_4);
        lbl_krxodoza->setObjectName(QStringLiteral("lbl_krxodoza"));
        lbl_krxodoza->setGeometry(QRect(324, 330, 96, 13));
        lbl_krxodoza->setFont(font1);
        lbl_krxodoza->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        le_krxolatit = new QLineEdit(page_4);
        le_krxolatit->setObjectName(QStringLiteral("le_krxolatit"));
        le_krxolatit->setGeometry(QRect(260, 420, 100, 25));
        le_krxolatit->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxolatit->setAlignment(Qt::AlignCenter);
        le_krxolatit->setReadOnly(true);
        lbl_krxolatit = new QLabel(page_4);
        lbl_krxolatit->setObjectName(QStringLiteral("lbl_krxolatit"));
        lbl_krxolatit->setGeometry(QRect(286, 400, 45, 13));
        lbl_krxolatit->setFont(font1);
        lbl_krxolatit->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        le_krxolong = new QLineEdit(page_4);
        le_krxolong->setObjectName(QStringLiteral("le_krxolong"));
        le_krxolong->setGeometry(QRect(385, 420, 100, 25));
        le_krxolong->setStyleSheet(QStringLiteral("background-image: url(:/);"));
        le_krxolong->setAlignment(Qt::AlignCenter);
        le_krxolong->setReadOnly(true);
        lbl_krxolong = new QLabel(page_4);
        lbl_krxolong->setObjectName(QStringLiteral("lbl_krxolong"));
        lbl_krxolong->setGeometry(QRect(410, 400, 51, 13));
        lbl_krxolong->setFont(font1);
        lbl_krxolong->setStyleSheet(QLatin1String("background-image: url(:/);\n"
"color: rgb(255, 255, 255);"));
        tb_automode->addItem(page_4, QString::fromUtf8("\320\221\320\240 \320\220\320\241\320\232\320\240\320\245\320\236"));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush2(QColor(59, 59, 59, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush3(QColor(127, 127, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush3);
        QBrush brush4(QColor(170, 170, 170, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush4);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush5);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
        statusBar->setPalette(palette1);
        statusBar->setStyleSheet(QStringLiteral("background-color: rgb(59, 59, 59);"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tb_automode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202 \320\220\320\241\320\232\320\240\320\245\320\236 | \320\222\320\235\320\230\320\230 \"\320\241\320\237\320\225\320\232\320\242\320\240\"", 0));
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pb_openportkrxo->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        pb_closeportkrxo->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\267\320\260\320\277\320\270\321\201\320\265\320\271", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217", 0));
        label_7->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\221\320\232", 0));
        label_8->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\267\320\260\320\277\320\270\321\201\320\265\320\271", 0));
        label_9->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 COM", 0));
        lbl_krxoammiak->setText(QApplication::translate("MainWindow", "\320\220\320\274\320\274\320\270\320\260\320\272", 0));
        lbl_krxodioksser->setText(QApplication::translate("MainWindow", "\320\224\320\270\320\276\320\272\321\201\320\270\320\264 \321\201\320\265\321\200\321\213", 0));
        lbl_krxochlor->setText(QApplication::translate("MainWindow", "\320\245\320\273\320\276\321\200", 0));
        lbl_krxodioksazota->setText(QApplication::translate("MainWindow", "\320\224\320\270\320\276\320\272\321\201\320\270\320\264 \320\260\320\267\320\276\321\202\320\260", 0));
        lbl_krxodoza->setText(QApplication::translate("MainWindow", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214 \320\264\320\276\320\267\321\213", 0));
        lbl_krxolatit->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260", 0));
        lbl_krxolong->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260", 0));
        tb_automode->setItemText(tb_automode->indexOf(page_4), QApplication::translate("MainWindow", "\320\221\320\240 \320\220\320\241\320\232\320\240\320\245\320\236", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
