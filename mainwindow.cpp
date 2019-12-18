#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QtDebug>
#include <utility>

#include <QGraphicsEllipseItem>

#define CLASSAMOUNT 4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->scale(1, -1);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->show();
    ui->graphicsView->setFrameStyle(0);
    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setSceneRect(0,0,800,600);

    pen = new QPen();
    brush = new QBrush(Qt::red);
    //Draw X and Y lines on the coordinate system
    scene->addLine(400,0,400,600,QPen(QBrush(Qt::black),1));
    scene->addLine(0,300,800,300,QPen(QBrush(Qt::black),1));

    QObject::connect(ui->graphicsView, SIGNAL(mouseClicked(QPoint)),
                     this, SLOT(addPoint(QPoint)));

    ui->Blue->setEnabled(false);
    ui->Gray->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::drawCircle(QPoint point)
{
    //Add ellipse to the given QPoint
    QColor color = getColor();
    pen->setColor(color);
    brush->setColor(color);
    QGraphicsEllipseItem *i = scene->addEllipse(0,0,5,5,*pen,*brush);

    //Translate originx to the original point
    point.setX(point.x()+400);
    point.setY(-1*point.y()+300);
    i->setPos(point);

}

void MainWindow::drawNormalizedCircle(QPoint point, int label)
{
    QColor color;

    if(label==1){
        color = Qt::red;
    }
    else if(label==-1){
        color = Qt::green;
    }

    pen->setColor(color);
    brush->setColor(color);
    QGraphicsEllipseItem *i = scene->addEllipse(0,0,7,7,*pen,*brush);

    //Translate originx to the original point
    point.setX(point.x()+400);
    point.setY(-1*point.y()+300);
    i->setPos(point);

}


void MainWindow::addPoint(QPoint point)
{
    //Draw the circle and save the point to the pointsVector
    drawCircle(point);
    pointsVector.push_back(point);
    //TODO:SADECE RED YA DA GREEN SECILEBILIYOR DURUMA GORE AYARLA
    if(ui->Red->isChecked()){
        labelVector.push_back(1);
        }
    if(ui->Green->isChecked()){
        labelVector.push_back(-1);

        }

    for(int i=0;i<colors.size();i++)
    {
        if(colors.at(i) == getColor().name()) return;
    }
    colors.push_back(getColor().name());
    qDebug()<<colors;
}


void MainWindow::on_Hesapla_clicked()
{

    //Normalized
    if(ui->normalize->isChecked()){
        normalization();
        scene->clear();
        scene->addLine(400,0,400,600,QPen(QBrush(Qt::black),3));
        scene->addLine(0,300,800,300,QPen(QBrush(Qt::black),3));

            inputPoints[pointsVector.size()*3];
            for(int i=0;i<pointsVector.size()*3;i+=3){
                inputPoints[i]=(pointsVector.at(i/3).x() - xMean) / xDeviation;
                inputPoints[i+1] = (pointsVector.at(i/3).y() - yMean) / yDeviation;
                inputPoints[i+2] = -1;
                normalizePoint = new QPoint(inputPoints[i]*100,inputPoints[i+1]*100);
                drawNormalizedCircle(*normalizePoint,labelVector.at(i/3));
            }
    }
    //Non-Normalized
    else{
            inputPoints[pointsVector.size()*3];
        for(int i=0;i<pointsVector.size()*3;i+=3){
            inputPoints[i]=pointsVector.at(i/3).x();
            inputPoints[i+1] =pointsVector.at(i/3).y();
            inputPoints[i+2] = -1;
        }

    }


    int* d = labelVector.data();
    int dimension=3;//x y bias

    ArtificialNeuralSystems system;

    if(ui->comboBox->currentText()=="SingleLayerPerceptron")
    {
        std::pair <double,double> p;
        p = system.SingleLayerPerceptron(dimension,inputPoints,d,pointsVector.size());
        QLineF line;
        line.setLine(0,(300+p.first*-1),800,(300+p.second*-1));
        scene->addLine(line);
    }

    else if(ui->comboBox->currentText()=="Delta"){
        std::pair <double,double> p;
        p = system.Delta(dimension,inputPoints,d,pointsVector.size());
        QLineF line;
        line.setLine(0,(300+p.first*-1),800,(300+p.second*-1));
        scene->addLine(line);

    }

    else if(ui->comboBox->currentText()=="MultiPerceptron"){
        int amount=colors.size();
    }

}


void MainWindow::normalization()
{
    xMean = yMean = xDeviation = yDeviation = 0;
    int size = pointsVector.size();
    for (int i=0; i<size;i++)
    {
        xMean += pointsVector.at(i).x();
        yMean += pointsVector.at(i).y();
    }
    xMean = xMean/size;
    yMean = yMean/size;

    for (int i=0; i<size;i++)
    {
        xDeviation += pow(pointsVector.at(i).x() - xMean, 2);
        yDeviation += pow(pointsVector.at(i).y() - yMean, 2);
    }
    xDeviation = sqrt(xDeviation/(size-1));
    yDeviation = sqrt(yDeviation/(size-1));
}



QColor MainWindow::getColor()
{
    if(ui->Red->isChecked())
    {return Qt::red;}

    else if(ui->Blue->isChecked())
    {return Qt::blue;}

    else if(ui->Green->isChecked())
    {return Qt::green;}

    else if(ui->Gray->isChecked())
    {return Qt::gray;}

    else return Qt::black;
}



void MainWindow::on_multicategory_toggled(bool checked)
{
    ui->Blue->setEnabled(checked);
    ui->Gray->setEnabled(checked);
}
