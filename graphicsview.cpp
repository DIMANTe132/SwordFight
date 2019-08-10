#include "graphicsview.h"
#include "mainwindow.h"
GraphicsView::GraphicsView(QWidget *parent):
    QGraphicsView ()
{
    View = new QGraphicsView(parent);
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
}

void GraphicsView::keyPressEvent(QKeyEvent* event)
{
}
