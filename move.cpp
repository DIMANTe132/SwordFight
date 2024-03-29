#include "move.h"
#include <QPen>
#include <QList>
#include <QPoint>
#include <QGraphicsLineItem>
#include <QGraphicsDropShadowEffect>

#include <QList>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QTimer>
#include <QThread>

#include "unit.h"
#include "game.h"
#include "graphicsellipseitem.h"

bool Move::next_cell(MyGraphicsScene *scene, QPoint first_coord, QPoint second_coord,const int width_map, const int height_map/*, int **array*/, int count_steps)
{
    Game *game = Game::GetInstance();
    if(!game->map.map) return false;
    int ax = first_coord.x()/scene->size_items, ay = first_coord.y()/scene->size_items,
        bx = second_coord.x()/scene->size_items, by = second_coord.y()/scene->size_items;
//    int ax = 1, ay = 1 , bx = 1, by = 5;
    const int W = width_map;//ширина поля
    const int H = height_map;//высота поля
    const int WALL = -1;
    const int BLANK = -2;
    const int ENEMY = -3;

    int px[W*H],py[W*H];//координаты ячеек, входящих в путь
    for (int j=0;j<W*H;j++) {
        px[j]=py[j]=0;
    }
    int len;//длина пути
    int grid[width_map][height_map];
//    int **grid;
//    grid = new int*[width_map];
//    for (int i=0;i<width_map;i++)
//        grid[i] = new int[height_map];

    for(int i=0;i<width_map;i++)
        for(int j=0;j<height_map;j++)
            grid[i][j] = game->map.map[j][i];
    grid[0][0] = ENEMY;
    grid[0][width_map-1] = ENEMY;
    grid[width_map-1][0] = ENEMY;
    grid[width_map-1][width_map-1] = ENEMY;

    if(grid[by][bx] == ENEMY)
        grid[by][bx]=BLANK;
    int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
    int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
    int d, x, y, k;
    bool stop;

    if (grid[ay][ax] == WALL || grid[by][bx] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена

    // распространение волны
    d = 0;
    grid[ay][ax] = 0;            // стартовая ячейка помечена 0
    do {
    stop = true;               // предполагаем, что все свободные клетки уже помечены
    for ( y = 0; y < H; ++y )
      for ( x = 0; x < W; ++x )
        if ( grid[y][x] == d )                         // ячейка (x, y) помечена числом d
        {
          for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
          {
             int iy=y + dy[k], ix = x + dx[k];
             if ( iy >= 0 && iy < H && ix >= 0 && ix < W &&
                  grid[iy][ix] == BLANK)
             {
                stop = false;              // найдены непомеченные клетки
                grid[iy][ix] = d + 1;      // распространяем волну
             }
          }
        }
    d++;
    } while ( !stop && grid[by][bx] == BLANK);

    if (grid[by][bx] == BLANK) return false;  // путь не найден

    // восстановление пути
    len = grid[by][bx]+1;            // длина кратчайшего пути из (ax, ay) в (bx, by)
    x = bx;
    y = by;
    d = len;
    while ( d > 0 )
    {
    px[d] = x;
    py[d] = y;                   // записываем ячейку (x, y) в путь
    d--;
    for (k = 0; k < 4; ++k)
    {
       int iy=y + dy[k], ix = x + dx[k];
       if ( iy >= 0 && iy < H && ix >= 0 && ix < W &&
            grid[iy][ix] == d)
      {
          x = x + dx[k];
          y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
          break;
      }
    }
    }
    px[0] = ax;
    py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути

//    way_x = px;
//    way_y = py;

    way_x = new int[len];
    way_y = new int[len];
    for (int i=0;i<len;i++)
    {
        way_x[i] = px[i];
        way_y[i] = py[i];
    }

    draw_way(scene, len, px, py, count_steps);
    scene->way_drow = true;
    steps = len;

    return true;
}

void Move::draw_way(MyGraphicsScene *scene, int length, int *coord_x, int *coord_y, int count_steps)
{
    QPen pen;
    pen.setStyle(Qt::DashLine);
//        pen.setCapStyle(Qt::RoundCap);
    pen.setColor(Qt::green);
    pen.setWidth(5);
    qreal space = 5;
    pen.setDashOffset(space);

    for (int i=0;i<length-1;i++)
    {
        if(count_steps<=0)
            pen.setColor(Qt::red);

        QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
        bodyShadow->setBlurRadius(9.0);
        bodyShadow->setColor(QColor(0, 0, 0, 160));
        bodyShadow->setYOffset(-2.0);
        bodyShadow->setXOffset(5.0);

        QGraphicsLineItem *line = scene->addLine(coord_x[i]*scene->size_items+scene->size_items/2,
                                                 coord_y[i]*scene->size_items+scene->size_items/2,
                                                 coord_x[i+1]*scene->size_items+scene->size_items/2,
                                                 coord_y[i+1]*scene->size_items+scene->size_items/2, pen);

        if(i==length-2)
        {
            QPen ellips_pen;
            if(count_steps>0)
                ellips_pen.setColor(Qt::green);
            else
                ellips_pen.setColor(Qt::red);
            ellips_pen.setWidth(5);

            QGraphicsEllipseItem *ellips = scene->addEllipse(coord_x[i+1]*scene->size_items+scene->size_items/2-scene->size_items/16,
                                                             coord_y[i+1]*scene->size_items+scene->size_items/2-scene->size_items/16,
                                                             scene->size_items/8,scene->size_items/8, ellips_pen, Qt::red);
            ellips->setGraphicsEffect(bodyShadow);
            ellips->setActive(false);
            scene->line_group.append(ellips);
        }
        line->setGraphicsEffect(bodyShadow);
        line->setActive(false);
        scene->line_group.append(line);

        count_steps--;
    }
}

void Move::movement(MyGraphicsScene *scene, int count_steps, QString type_move)
{
    int max_steps;

    max_steps = count_steps+1;
    if(steps<=count_steps)
        max_steps = steps;

    if((type_move == "attack unit" || type_move == "ally" || type_move == "attack castle") && count_steps>=steps)
        max_steps--;

    if(way_x!=nullptr && way_y != nullptr)
    {
        QTimeLine *timer = new QTimeLine(/*850*max_steps*/100);
        timer->setCurveShape(QTimeLine::LinearCurve);
        QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timer);
        Unit *unit = dynamic_cast<Unit*>(scene->itemAt(way_x[0]*scene->size_items, way_y[0]*scene->size_items,QTransform()));
        std::cout<<way_x[0]*scene->size_items<<"  | "<<way_y[0]*scene->size_items<<std::endl;
        if(type_move == "move")
            unit->count_steps-=max_steps;
        else if(type_move == "ally")
            unit->count_steps-=max_steps-1;
        else
            unit->count_steps = 0;
        animation->setItem(unit);
        animation->setTimeLine(timer);

        QTimer *tim = new QTimer;
        for (int i = 0; i < max_steps; ++i)
        {
            animation->setPosAt(i/ float(max_steps+1), QPointF(way_x[i]*scene->size_items, way_y[i]*scene->size_items));
            unit->coord = QPoint(way_x[i]*scene->size_items, way_y[i]*scene->size_items);
            scene->coord_first = unit->coord;
//            if(i<max_steps-1)
//                tim->singleShot((i+1)*10,scene, SLOT(delete_first_line()));
        }
        tim->singleShot(0,scene, SLOT(disenable_scene()));
        tim->singleShot(100, scene, SLOT(delete_all_line()));
        tim->singleShot(100,scene, SLOT(enable_scene()));
        tim->singleShot(100,tim, SLOT(stop()));
        if(type_move == "attack unit")
        {
            Unit *attack_unit = dynamic_cast<Unit*>(scene->itemAt(way_x[max_steps]*scene->size_items, way_y[max_steps]*scene->size_items,QTransform()));
            tim->singleShot(100,attack_unit,SLOT(hit()));
        }
        else if(type_move == "attack castle")
        {
            Castle *attack_castle = dynamic_cast<Castle*>(scene->itemAt(way_x[max_steps]*scene->size_items, way_y[max_steps]*scene->size_items,QTransform()));
            tim->singleShot(100,attack_castle,SLOT(hit()));
        }
        timer->start();
        Game *game = Game::GetInstance();
        game->map.map[way_x[0]][way_y[0]] = -2;
        game->map.map[way_x[max_steps-1]][way_y[max_steps-1]] = -3;
        way_x = way_y =0;
    }
}
