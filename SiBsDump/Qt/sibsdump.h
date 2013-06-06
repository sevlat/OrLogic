#ifndef SIBSDUMP_H
#define SIBSDUMP_H

#include <QtGui/QDialog>
#include "ui_sibsdump.h"

class SiBsDump : public QDialog
{
    Q_OBJECT

public:
    SiBsDump(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~SiBsDump();

private:
    Ui::SiBsDumpClass ui;
};

#endif // SIBSDUMP_H
