#ifndef MINIMAP_H
#define MINIMAP_H

#include <QGraphicsObject>
#include "drow.h"

class MiniMap : public Drow
{
public:
    QGraphicsScene *scene;
    int **map_array;
    int width, height;
    explicit MiniMap(QObject *parent = 0);
};

#endif // MINIMAP_H
