#ifndef ARTIFICIALNEURALSYSTEMS_H
#define ARTIFICIALNEURALSYSTEMS_H

#include <neuron.h>
#include <utility>


class ArtificialNeuralSystems
{
public:
    ArtificialNeuralSystems();
    std::pair <double,double> SingleLayerPerceptron(int dimension,  double inputPoints[], int *d,int size);
    std::pair <double,double> Delta(int dimension,  double inputPoints[], int *d,int size);
    void MultiPerceptron(int dimension,int classSize, double inputPoints[]);
    void MultiPerceptronWithDeltaRule(int dimension,int classSize, double inputPoints[]);
private:
     Neuron *neuron;
};

#endif // ARTIFICIALNEURALSYSTEMS_H
