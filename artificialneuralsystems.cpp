#include "artificialneuralsystems.h"
#include <math.h>
#include <utility>

#include <QDebug>

ArtificialNeuralSystems::ArtificialNeuralSystems()
{

}

std::pair <double,double> ArtificialNeuralSystems::SingleLayerPerceptron(int dimension,  double inputPoints[], int *d,int size)
{ //TODO: CYCLEI PARAMETRE OLARAK VERIP ARTTIR
    neuron= new Neuron();
    neuron->setInputDimension(dimension);
    neuron->setRandomWeights();
    neuron->setInputs(inputPoints);
    neuron->setLabels(d);//Red:1, Green:-1  TODO:MULTIYALER ICIN LABELLLARI AYRI SETLEMEYI UNUTMA
    double c=0.1;
    double net;
    int output;
    double diff;
    bool keepIterating = true;
    while(keepIterating)
    {
        keepIterating=false;

        for(int step=0;step<size;step++){
            net=neuron->calculateNetfromThStep(step);
            output = neuron->sign(net);

            if(output!=d[step]){
                diff=d[step]-output;
                neuron->updateWeights(c,diff,step);
                keepIterating = true;
            }
            net=0;
        }
    }

    double *w = neuron->getWeights();
    double w2 = (w[2]);
    double w1 = (w[1]);
    double w0 = (w[0]);
    double a = (w0*400+w2)/w1;
    double b = (-w0*400+w2)/w1;

    std::pair <double,double> linePoints;
    linePoints.first=a;
    linePoints.second=b;

    return linePoints;
}

std::pair <double,double> ArtificialNeuralSystems::Delta(int dimension,  double inputPoints[], int *d,int size)
{
    neuron= new Neuron();
    neuron->setInputDimension(dimension);
    neuron->setRandomWeights();
    neuron->setInputs(inputPoints);
    neuron->setLabels(d);//Red:1, Green:-1  TODO:MULTIYALER ICIN LABELLLARI AYRI SETLEMEYI UNUTMA
    double net;
    double output;
    double derivation;
    bool keepIterating=true;
    double error;
    double diff;
    double c=0.1;
    while(keepIterating){
        error=0;
        for(int step=0;step<size;step++){
            net=neuron->calculateNetfromThStep(step);
            output =neuron->sigmoid(net);
            derivation=neuron->derivativeOfSigmoid(net);
            diff=d[step]-output;
            error +=( 0.5*pow((diff),2));
            qDebug()<<error;
            neuron->updateWeightsDelta(c,diff,derivation,step);
            net=0;
        }

        if (error <0.5){keepIterating = false;}
    }

    double *w = neuron->getWeights();
    double w2 = (w[2]);
    double w1 = (w[1]);
    double w0 = (w[0]);

    double a = (w0*400+w2)/w1;
    double b = (-w0*400+w2)/w1;

    std::pair <double,double> linePoints;
    linePoints.first=a;
    linePoints.second=b;

    return linePoints;
}

void ArtificialNeuralSystems::MultiPerceptron(int dimension,int classSize, double inputPoints[])
{
    neuron= new Neuron();
    neuron->setInputDimension(dimension);
    neuron->setRandomWeights();
    neuron->setInputs(inputPoints);
    double net;
    double output;
    double derivation;
    bool keepIterating=true;
    double error=100.1;
    double diff;
    double c=0.1;


}

void ArtificialNeuralSystems::MultiPerceptronWithDeltaRule(int dimension,int classSize, double inputPoints[])
{


}
