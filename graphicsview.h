#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include "mygraphicsscene.h"

class GraphicsView : public QGraphicsView
{
public:
    explicit GraphicsView(QWidget *parent = 0);
private:
    QGraphicsView *View;
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent* event);
};

#endif // GRAPHICSVIEW_H
