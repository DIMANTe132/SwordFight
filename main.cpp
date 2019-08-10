#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>

//#include "player.h"
//#include "map.h"
//#include "unit.h"
#include "mygraphicsscene.h"
#include "game.h"
#include "choose_count_players.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = MainWindow::GetInstance();
    w->showFullScreen();

    QGraphicsView *view_2 = w->GetInstanceGraphicsView(2);
    view_2->setGeometry(QRect(0,w->height()-200, 200, 201));
    QPushButton *button_1 = w->GetInstanceButton(1);
    button_1->setGeometry(w->width()-300,0,300,50);
    button_1->setText("ВЫЙТИ");
    QPushButton *button_2 = w->GetInstanceButton(2);
    button_2->setGeometry(w->width()-300,button_1->height(),300,50);
    button_2->setText("ХОД СЛЕДУЮЩЕГО ИГРОКА");


    Game *game = Game::GetInstance();
    game->game_play = true;//перенести все остальное в инициализацию Game
    game->map.scene = new MyGraphicsScene;
    game->map.scene->scene = game->map.scene;
    game->map.drow_map();

    Game::connect(button_2, SIGNAL(clicked()), game, SLOT(next_player()));

    Choose_count_players *wind = new Choose_count_players(w);

//    game->addPlayer("First", "01", 1);
//    game->addPlayer("Second", "01", 2);
//    game->addPlayer("Third", "01", 3);
//    game->addPlayer("Fourth", "01", 4);




    return a.exec();
}
