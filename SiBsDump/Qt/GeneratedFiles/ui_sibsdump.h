/********************************************************************************
** Form generated from reading UI file 'sibsdump.ui'
**
** Created: Tue 7. May 21:28:20 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIBSDUMP_H
#define UI_SIBSDUMP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_SiBsDumpClass
{
public:

    void setupUi(QDialog *SiBsDumpClass)
    {
        if (SiBsDumpClass->objectName().isEmpty())
            SiBsDumpClass->setObjectName(QString::fromUtf8("SiBsDumpClass"));
        SiBsDumpClass->resize(600, 400);

        retranslateUi(SiBsDumpClass);

        QMetaObject::connectSlotsByName(SiBsDumpClass);
    } // setupUi

    void retranslateUi(QDialog *SiBsDumpClass)
    {
        SiBsDumpClass->setWindowTitle(QApplication::translate("SiBsDumpClass", "SiBsDump", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SiBsDumpClass: public Ui_SiBsDumpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIBSDUMP_H
