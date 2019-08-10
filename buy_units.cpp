#include "buy_units.h"
#include "mainwindow.h"
#include "game.h"
#include <QMessageBox>

#include <iostream>

Buy_units::Buy_units(QWidget *parent) : QWidget (parent)
{
    MainWindow *win = MainWindow::GetInstance();
    win->setEnabled(false);

    window = new QWidget(parent);
    window->setFixedSize(QSize(500,500));
    window->setWindowFlag(Qt::ToolTip);


    QPushButton *melle_first = new QPushButton();
    melle_first->setMinimumSize(QSize(200,200));
//    melle_first->setStyleSheet("border-image:url(10.png)");
    melle_first->setText("First");
    connect(melle_first, &QPushButton::clicked, [this, melle_first](){this->buy_unit(1);});

    QPushButton *melle_second = new QPushButton();
    melle_second->setMinimumSize(melle_first->minimumSize());
    melle_second->setText("Second");
    connect(melle_second, &QPushButton::clicked, [this, melle_first](){this->buy_unit(2);});

    QPushButton *range_first = new QPushButton();
    range_first->setMinimumSize(melle_first->minimumSize());
    range_first->setText("Third");
    connect(range_first, &QPushButton::clicked, [this, melle_first](){this->buy_unit(3);});
    QPushButton *range_second = new QPushButton();
    range_second->setMinimumSize(melle_first->minimumSize());
    range_second->setText("Forth");
    connect(range_second, &QPushButton::clicked, [this, melle_first](){this->buy_unit(4);});
    QPushButton *exit_button = new QPushButton();
    exit_button->setText("ВЫХОД!");
    connect(exit_button, SIGNAL(clicked()), this, SLOT(close_window()));


    QVBoxLayout *main_layout = new QVBoxLayout;
    QHBoxLayout *firs_line = new QHBoxLayout;
    QHBoxLayout *second_line = new QHBoxLayout;

    firs_line->addWidget(melle_first);
    firs_line->addWidget(melle_second);
    second_line->addWidget(range_first);
    second_line->addWidget(range_second);
    main_layout->addLayout(firs_line);
    main_layout->addLayout(second_line);
    main_layout->addWidget(exit_button);


//    Game *game = Game::GetInstance();

    window->setLayout(main_layout);
    window->show();

}

void Buy_units::buy_unit(int id_unit)
{
    Game *game = Game::GetInstance();
    int index_player;
    int max_cost;
    switch (id_unit)
    {
        case 1:
            max_cost=150;
        break;
        case 2:
            max_cost=250;
        break;
        case 3:
            max_cost=100;
        break;
        case 4:
            max_cost=150;
        break;
    }
    for (int i=0;i<game->list_players.length();i++)
        if(game->list_players[i]->move)
        {
            if(game->list_players[i]->count_money>=max_cost && game->list_players[i]->list_units.length()<10)
            {
                int x,y;
                switch (i)
                {
                    case 0:
                    x = game->list_players[0]->castle->pos().x()+game->map.scene->size_items;
                    y = game->list_players[0]->castle->pos().y();
                    break;
                    case 1:
                    x = game->list_players[1]->castle->pos().x()-game->map.scene->size_items;
                    y = game->list_players[1]->castle->pos().y();
                    break;
                    case 2:
                    x = game->list_players[2]->castle->pos().x()-game->map.scene->size_items;
                    y = game->list_players[2]->castle->pos().y();
                    break;
                    case 3:
                    x = game->list_players[3]->castle->pos().x()+game->map.scene->size_items;
                    y = game->list_players[3]->castle->pos().y();
                    break;
                }
                    if(game->map.map[x/game->map.scene->size_items][y/game->map.scene->size_items]==-2)
                        game->list_players[i]->addUnit(x,y,QString::number(10+id_unit),game->map.scene);
                    else
                    {
//                        MainWindow *win = MainWindow::GetInstance();
                        QMessageBox::warning(this->window,"","Место спавна занято", QMessageBox::Ok);
                    }
            }
        }

    MainWindow *win = MainWindow::GetInstance();
    win->setEnabled(true);
}


void Buy_units::close_window()
{
    MainWindow *win = MainWindow::GetInstance();
    win->setEnabled(true);
    this->window->close();
    delete this;
}
