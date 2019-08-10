#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include "game.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
}

MainWindow* MainWindow::mainInstance = 0;

MainWindow* MainWindow::GetInstance(QWidget *parent)
{
    if(!mainInstance)
        mainInstance = new MainWindow(parent);

    return mainInstance;
}

QGraphicsView* MainWindow::GetInstanceGraphicsView(int number)
{
    if(number == 2)
        return ui->graphicsView_2;
}

QPushButton* MainWindow::GetInstanceButton(int number)
{
    switch (number)
    {
        case 1:
        return ui->pushButton;
        case 2:
        return  ui->pushButton_2;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

