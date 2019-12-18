#include "neuron.h"
#include <random>
Neuron::Neuron()
{

}

int Neuron::sign(double net)
{
    if(net>=0)
        return 1;
    else
        return -1;

}

double Neuron::sigmoid(double net){
    return (2/(exp(-net)+1.0)) - 1.0;
}

double Neuron::derivativeOfSigmoid(double net)
{
    double fnet=sigmoid(net);
    return (1.0-(fnet*fnet))*0.5;
}

double Neuron::calculateNet()
{
    double net;
    for(int i=0;i<inputDimension;i++){
        net+=inputs[i]*weights[i];
    }
    return net;
}

double Neuron::calculateNetfromThStep(int step)
{
    double net;

    for(int i=0;i<inputDimension;i++)
        {
            net += weights[i]*inputs[step*inputDimension+i];
        }

    return net;

}

void Neuron::setInputDimension(int amount)
{
    inputDimension=amount;
}

void Neuron::setInputs(double *inputArray)
{
    inputs=inputArray;
}

void Neuron::setInputs(double *x, double *y)
{
    xInputs=x;
    yInputs=y;
}

void Neuron::setWeights(double *weightArray)
{
    weights=weightArray;
}

void Neuron::updateWeights(double c,double diff,int step)
{
    for (int i=0;i<inputDimension;i++)
    {
        weights[i] = weights[i] +  c*(diff)*inputs[step*inputDimension+i];
    }

}

void Neuron::updateWeightsDelta(double c,double diff,double derivation, int step)
{
    for (int i=0;i<inputDimension;i++)
    {
        weights[i] = weights[i] +  c*diff*derivation*inputs[step*inputDimension+i];


    }
}



void Neuron::setLabels(int *labelArray)
{
    labels=labelArray;
}


void Neuron::setRandomWeights()
{
    weights = new double[inputDimension];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1.0);
    for (int i=0;i<inputDimension;i++)
    {
        weights[i] = dis(gen);
    }
}

double *Neuron::getWeights()
{
    return weights;
}
