#ifndef MAP_H
#define MAP_H


#include <QPointF>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "mygraphicsscene.h"
#include "drow.h"

class Map : public Drow//Класс карты
{
public:
    int width;//Количество клеток в ширину
    int height;//Количество клеток в высоту

    int **map;

    MyGraphicsScene *scene;//Главная сцена

    void drow_map();//функция рисования карты
public slots:
};

#endif // MAP_H
