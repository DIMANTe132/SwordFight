#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "graphicsview.h"
#include "unitsgraphicsscene.h"
#include <QList>

class Game : public QObject
{
    Q_OBJECT
public:
    Map map;
    QList <Player*> list_players;
    GraphicsView *graphicsView;
    UnitsGraphicsScene *graphicsScene;

    bool game_play = false;

    void addPlayer(QString name_player, QString id_image, int number_player);
    static Game* GetInstance();
private:
    static Game *GameInstance;
    void refresh_data_players();

public slots:
    void next_player();

};

#endif // GAME_H
