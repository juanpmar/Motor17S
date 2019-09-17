/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QLabel *conect;
    QPlainTextEdit *datoss;
    QProgressBar *Progres;
    QLabel *Title;
    QLabel *sign;
    QLabel *tag;
    QLabel *sufPS1;
    QLabel *sufF1;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(403, 337);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(310, 90, 75, 23));
        conect = new QLabel(Widget);
        conect->setObjectName(QString::fromUtf8("conect"));
        conect->setGeometry(QRect(30, 70, 81, 16));
        datoss = new QPlainTextEdit(Widget);
        datoss->setObjectName(QString::fromUtf8("datoss"));
        datoss->setGeometry(QRect(20, 100, 251, 91));
        Progres = new QProgressBar(Widget);
        Progres->setObjectName(QString::fromUtf8("Progres"));
        Progres->setGeometry(QRect(10, 282, 118, 21));
        Progres->setValue(0);
        Title = new QLabel(Widget);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(100, 0, 201, 61));
        QFont font;
        font.setPointSize(14);
        Title->setFont(font);
        sign = new QLabel(Widget);
        sign->setObjectName(QString::fromUtf8("sign"));
        sign->setGeometry(QRect(270, 310, 131, 20));
        tag = new QLabel(Widget);
        tag->setObjectName(QString::fromUtf8("tag"));
        tag->setGeometry(QRect(20, 230, 71, 16));
        sufPS1 = new QLabel(Widget);
        sufPS1->setObjectName(QString::fromUtf8("sufPS1"));
        sufPS1->setGeometry(QRect(140, 290, 47, 13));
        QFont font1;
        font1.setPointSize(11);
        sufPS1->setFont(font1);
        sufF1 = new QLabel(Widget);
        sufF1->setObjectName(QString::fromUtf8("sufF1"));
        sufF1->setGeometry(QRect(140, 250, 47, 13));
        sufF1->setFont(font1);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 250, 31, 20));
        label->setFont(font1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "Abrir", nullptr));
        conect->setText(QCoreApplication::translate("Widget", "No conectado", nullptr));
        Title->setText(QCoreApplication::translate("Widget", "Frecuencimetro Digital", nullptr));
        sign->setText(QCoreApplication::translate("Widget", "@powered by: L.O & J.M", nullptr));
        tag->setText(QCoreApplication::translate("Widget", "Frecuencia ", nullptr));
        sufPS1->setText(QCoreApplication::translate("Widget", "Hz", nullptr));
        sufF1->setText(QCoreApplication::translate("Widget", "Hz", nullptr));
        label->setText(QCoreApplication::translate("Widget", "000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
