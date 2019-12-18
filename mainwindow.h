#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include "mygraphicsview.h"
#include "artificialneuralsystems.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QColor getColor();
    void drawCircle(QPoint point);
    void drawNormalizedCircle(QPoint point,int label);
    void normalization();
    double xMean,yMean,xDeviation,yDeviation;
    QPoint *normalizePoint;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPen *pen;
    QBrush *brush;

    QVector<QPoint> pointsVector;
    QVector<QString> colors;
    QVector<QColor> colorVector;
    QVector<int> labelVector;

    int colorAmount;
    double inputPoints[];
private slots:
    void addPoint(QPoint point);
    void on_Hesapla_clicked();


    void on_multicategory_toggled(bool checked);

};

#endif // MAINWINDOW_H
