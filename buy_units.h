#ifndef BUY_UNITS_H
#define BUY_UNITS_H
#include <QWidget>
#include "mainwindow.h"
#include <iostream>

class Buy_units : public QWidget
{
    Q_OBJECT
public:
    QWidget *window;
    explicit Buy_units(QWidget *perant = 0);

public slots:
    void buy_unit(int id_unit);
    void close_window();
};

#endif // BUY_UNITS_H
