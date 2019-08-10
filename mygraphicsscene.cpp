#include "mygraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <iostream>
#include <QTransform>
#include <QObject>

#include <QGraphicsEffect>

#include <QFile>
#include <QTextStream>
#include <QPainter>
#include "unit.h"
#include "castle.h"

#include <QGraphicsItem>

#include "mainwindow.h"
#include "buy_units.h"
#include "game.h"



void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Game *game = Game::GetInstance();
    if(game->game_play)
    {
        if (event->button() == Qt::LeftButton)
        {
            coord_first = event->scenePos();
            if(!chooseUnit())
            {
                for (int i=0;i<game->list_players.length();i++)
                {
                    game->list_players[i]->refreshUnits();
                }

                unit_inst = 0;
                delete_way();
            }
        }
        else if  (event->button() == Qt::RightButton && event->scenePos().x()>0 &&
                  event->scenePos().y() > 0 && event->scenePos().x() < this->width() && event->scenePos().y()<this->height())
        {
            coord_second = event->scenePos();
            if(coord_second.x() < this->width() && coord_second.y() < this->height())
            {
//                Unit *new_unit = dynamic_cast<Unit*>(this->itemAt(coord_second,QTransform()));
                if(unit_inst)
                {
                    Unit *unit = dynamic_cast<Unit*>(unit_inst);

                    delete_way();

                    unit->next_cell(this,QPoint(coord_first.x(),coord_first.y()), QPoint(coord_second.x(),coord_second.y()),
                                    game->map.width,game->map.height, unit->count_steps);
                }
            }
        }
//        this->update(0,0,width(), height());
    }
}
void MyGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Game *game = Game::GetInstance();
    if(game->game_play)
    {
        if(mouseEvent->button() == Qt::RightButton)
        {
            Unit *unit = dynamic_cast<Unit*>(unit_inst);
        //попробовать сделать через проверку на то что в клутке в game->map.map[][]
            if(unit->count_steps>0)
            {
                if(game->map.map[(int)mouseEvent->scenePos().x()/game->map.scene->size_items]
                                [(int)mouseEvent->scenePos().y()/game->map.scene->size_items] != -3)
                {
                    unit->movement(game->map.scene, unit->count_steps);
                }
                else
                {
                    int index_player = index_move_player();

                    Castle *attack_castle = dynamic_cast<Castle*>(game->map.scene->itemAt(mouseEvent->scenePos(), QTransform()));
                    if(attack_castle)
                    {
                        if(game->list_players[index_player]->castle == attack_castle)
                        {
                            unit->movement(game->map.scene, unit->count_steps, "ally");
                            return;
                        }
                        else
                            unit->movement(game->map.scene, unit->count_steps, "attack castle");
                        return;
                    }
                    Unit *attack_unit = dynamic_cast<Unit*>(game->map.scene->itemAt(mouseEvent->scenePos(), QTransform()));

                }


            }
        }
    }
}

bool MyGraphicsScene::chooseUnit()
{
//    Unit *unit = dynamic_cast<Unit*>(scene->itemAt(coord_first,QTransform()));
    Game *game = Game::GetInstance();

    if(game->map.map[(int)coord_first.x()/game->map.scene->size_items][(int)coord_first.y()/game->map.scene->size_items] != -3)
        return false;

//    Unit *unit = dynamic_cast<Unit*>(scene->itemAt(QPointF((int)coord_first.x()/game->map.scene->size_items*game->map.scene->size_items,
//                                                           (int)coord_first.y()/game->map.scene->size_items*game->map.scene->size_items), QTransform()));

    Unit *unit = dynamic_cast<Unit*>(scene->itemAt(coord_first,QTransform()));

    bool index = false;
    for (int i=0;i<game->list_players.length();i++)
    {
        if(game->list_players[i]->list_units.indexOf(unit)>=0)
            if(game->list_players[i]->move)
                index = true;
    }
    if(unit && index)
    {
        if(unit!=unit_inst && unit_inst)
        {
            delete_way();

            QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
            bodyShadow->setBlurRadius(9.0);
            bodyShadow->setColor(QColor(0, 0, 0, 160));
            bodyShadow->setYOffset(-2.0);
            bodyShadow->setXOffset(5.0);

            Unit *old_unit = dynamic_cast<Unit*>(unit_inst);
            old_unit->choose_unit = false;
            delete old_unit->graphicsEffect();
            old_unit->setGraphicsEffect(bodyShadow);
        }
        QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
        bodyShadow->setBlurRadius(10.0);
        bodyShadow->setColor(Qt::yellow);
        bodyShadow->setOffset(0.0);
        unit->setGraphicsEffect(bodyShadow);
        unit->choose_unit = true;
        unit_inst = unit;
        return true;
    }
    Castle *castle = dynamic_cast<Castle*>(scene->itemAt(coord_first, QTransform()));
    if(castle)
    {
        delete_way();

        int index_player = index_move_player();

        if(game->list_players[index_player]->castle == castle)
        {
            game->list_players[index_player]->refreshUnits();
            chooseCastle(castle);
            return true;
        }
        else return false;
    }
    else return false;
}
bool MyGraphicsScene::chooseCastle(QGraphicsObject *castle)
{
    Castle *new_castle = static_cast<Castle*>(castle);

    delete_way();

    Buy_units *nol = new Buy_units();

}

void MyGraphicsScene::delete_first_line()
{
    delete line_group[0];
    line_group.removeAt(0);
}

void MyGraphicsScene::delete_all_line()
{
    if(line_group.length()!=0)
    {
        for(int i=0;i<line_group.length();i++)
            delete line_group[i];
        line_group.clear();
    }
}

void MyGraphicsScene::enable_scene()
{
    MainWindow *win = MainWindow::GetInstance();
    QGraphicsView *viev = win->GetInstanceGraphicsView(1);
    viev->setEnabled(true);
}

void MyGraphicsScene::disenable_scene()
{
    MainWindow *win = MainWindow::GetInstance();
    QGraphicsView *viev = win->GetInstanceGraphicsView(1);
    viev->setEnabled(false);
}

void MyGraphicsScene::delete_unit_inst()
{
    unit_inst = 0;
}

void MyGraphicsScene::delete_way()
{
    if(this->way_drow)
    {
        for (int i=0;i<line_group.length();i++)
            delete this->line_group[i];
        this->line_group.clear();
        this->way_drow = false;
    }
}

int MyGraphicsScene::index_move_player()
{
    Game *game = Game::GetInstance();
    for (int i=0;i<game->list_players.length();i++)
        if(game->list_players[i]->move)
            return  i;
}
