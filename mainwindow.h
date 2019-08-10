#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QgraphicsView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* GetInstance(QWidget* parent = 0);
    QGraphicsView* GetInstanceGraphicsView(int number);
    QPushButton* GetInstanceButton(int number);

    static MainWindow* mainInstance;

//    void question_count_players();

public:
    Ui::MainWindow *ui;


private slots:
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
