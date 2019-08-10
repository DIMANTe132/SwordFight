#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsItem>
#include <QObject>

#include <iostream>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    int size_items;
    QGraphicsItemGroup *group_line;
    QList <QGraphicsItem*> line_group;
    bool way_drow = false;
    QPointF coord_first; //выбранные первые координаты
private:

    QPointF coord_second;//Вторые координаты
    QGraphicsObject *unit_inst = 0;
//    QGraphicsObject *attack_castle_inst;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * mouseEvent);
    bool chooseUnit();
    bool chooseCastle(QGraphicsObject *castle);
    void delete_way();
    int index_move_player();
private slots:
    void delete_first_line();
    void delete_all_line();
    void enable_scene();
    void disenable_scene();
public slots:
    void delete_unit_inst();
};

#endif // MYGRAPHICSSCENE_H
