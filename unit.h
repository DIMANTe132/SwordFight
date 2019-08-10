#ifndef UNIT_H
#define UNIT_H
#include <QPixmap>
#include <QString>
#include <QProgressBar>
#include <QGraphicsObject>
#include <QGraphicsDropShadowEffect>

#include "move.h"

class Unit :public QGraphicsObject, public Move
{
    Q_OBJECT
public:
    QPoint coord;//Координаты юнита
    int health;//Здоровье юнита
    int max_health;//Максимальное здоровье юнита
    int demage;//Урон юнита
    int id_unit;//id юнита
    int max_count_steps;//Количество клеток за ход
    int count_steps;//Количество оставшихся клеток за ход
    int choose_count_steps;//длина выбранного пути

    QPixmap *image;//Картинка юнита


    bool choose_unit;//выбран ли юнит

    explicit Unit(QPoint point,MyGraphicsScene *scene, QString id_unit,QObject *parent = 0);


private:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void hit();

};

#endif // UNIT_H
