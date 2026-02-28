/********************************************************************************
** Form generated from reading UI file 'HSIslider.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSISLIDER_H
#define UI_HSISLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HSIslider
{
public:
    QFormLayout *formLayout;
    QSpinBox *spinBox;
    QScrollBar *horizontalScrollBar;

    void setupUi(QWidget *HSIslider)
    {
        if (HSIslider->objectName().isEmpty())
            HSIslider->setObjectName(QString::fromUtf8("HSIslider"));
        HSIslider->resize(400, 300);
        formLayout = new QFormLayout(HSIslider);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        spinBox = new QSpinBox(HSIslider);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        formLayout->setWidget(0, QFormLayout::LabelRole, spinBox);

        horizontalScrollBar = new QScrollBar(HSIslider);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, horizontalScrollBar);


        retranslateUi(HSIslider);

        QMetaObject::connectSlotsByName(HSIslider);
    } // setupUi

    void retranslateUi(QWidget *HSIslider)
    {
        HSIslider->setWindowTitle(QCoreApplication::translate("HSIslider", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HSIslider: public Ui_HSIslider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSISLIDER_H
