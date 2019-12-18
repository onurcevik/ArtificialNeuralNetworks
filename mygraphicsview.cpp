#include "mygraphicsview.h"
#define ORIGINX 400 // WIDTH/2
#define ORIGINY 300 // HEIGHT/2

MyGraphicsView::MyGraphicsView(QWidget *parent): QGraphicsView (parent){

}
void MyGraphicsView::mousePressEvent(QMouseEvent *ev)
{
    neuronPoint = ev->pos();
    neuronPoint=centerOriginPoint(neuronPoint);
    qDebug()<<neuronPoint;
    QGraphicsView::mousePressEvent(ev);

    emit mouseClicked(neuronPoint);
}

QPoint MyGraphicsView::centerOriginPoint(QPoint clickedPoint)
{
    QPoint originPoint(ORIGINX,ORIGINY); // ORIGINX: WIDTH/2 , ORIGINY: HEIGHT/2
    clickedPoint.setX(clickedPoint.x()-ORIGINX);
    clickedPoint.setY(ORIGINY-clickedPoint.y());
    return clickedPoint;
}
