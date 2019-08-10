#include "castle.h"
#include "game.h"
#include <QPoint>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QString>

Castle::Castle(MyGraphicsScene *scene, QPoint coord_castle, QString id_image,QObject *parent):
     QGraphicsObject ()
{
    spawnPos = coord_castle;
    health = max_health = 1000;
    image_id = id_image;
    Game *game = Game::GetInstance();
    game->map.map[coord_castle.x()/game->map.scene->size_items][coord_castle.y()/game->map.scene->size_items] = -3;

    QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
    bodyShadow->setBlurRadius(9.0);
    bodyShadow->setColor(QColor(0, 0, 0, 160));
    bodyShadow->setOffset(4.0);
    this->setGraphicsEffect(bodyShadow);
    this->setZValue(2);

    scene->addItem(this);
    this->setEnabled(false);
    this->setPos(coord_castle);
}

QRectF Castle::boundingRect() const
{
    Game *game = Game::GetInstance();
    return QRectF(-10,-10,game->map.scene->size_items+10,game->map.scene->size_items+10);
}

void Castle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Game *game = Game::GetInstance();
    QPixmap pixmap = QPixmap("../Game/"+image_id+".png").scaled(game->map.scene->size_items,game->map.scene->size_items);
    painter->drawPixmap(0,0,pixmap);
    painter->setPen(Qt::NoPen);
    for (int i=0;i<game->list_players.length();i++)
    {
        if(game->list_players[i]->castle == this)
            if(game->list_players[i]->move)
                painter->setBrush(Qt::green);
            else
                painter->setBrush(Qt::red);
    }
    painter->drawRect(10,0,((game->map.scene->size_items-20)*health/max_health), 5);
}
void Castle::hit()
{
    Game *game = Game::GetInstance();
    int index_player, index_attack_unit;
    for (int i=0;i<game->list_players.length();i++)
    {
        if(game->list_players[i]->move)
        {
            index_player = i;
            break;
        }
    }
    for (int i=0;i<game->list_players[index_player]->list_units.length();i++)
    {
        if(game->list_players[index_player]->list_units[i]->choose_unit)
        {
            index_attack_unit = i;
            break;
        }
    }
    health-=game->list_players[index_player]->list_units[index_attack_unit]->demage;
    if(health<=0)
    {
        for (int i=0;i<game->list_players.length();i++)
            if(game->list_players[i]->castle == this)
            {
                delete this;
                game->list_players[i]->castle = 0;
                break;
            }
    }
    else
        this->update(0,0,game->map.scene->size_items,game->map.scene->size_items);
}
