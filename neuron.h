#ifndef NEURON_H
#define NEURON_H


class Neuron
{
public:
    Neuron();
    int sign(double net);
    double sigmoid(double net);
    double derivativeOfSigmoid(double net);
    double calculateNet();
    double calculateNetfromThStep(int step);
    void setInputDimension(int dimension);
    void setInputs(double* inputArray);
    void setInputs(double* x, double* y);
    void setWeights(double* weightArray);
    void updateWeights(double c,double diff,int step);
    void updateWeightsDelta(double c,double diff,double derivation, int step);
    void setLabels(int* labelArray);
    double *getWeights();

    void setRandomWeights();


private:
    int inputDimension;
    int *labels;
    double* inputs, *xInputs,*yInputs;
    double* outputs;
    double* weights;



};

#endif // NEURON_H
