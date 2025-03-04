#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>

#include <QPoint>
#include <QDebug>
#include <QLabel>


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent = nullptr);

protected:


    void mousePressEvent(QMouseEvent *ev);
    //void paintEvent();
    //void mouseReleaseEvent(QMouseEvent *ev);
    //void mouseMoveEvent(QMouseEvent *ev);


signals:
    void mouseClicked(QPoint point);


private:
    QPoint centerOriginPoint(QPoint clickedPoint);
    QPoint neuronPoint;
};

#endif // MYGRAPHICSVIEW_H
