#ifndef ADJUSTPARAMETER_H
#define ADJUSTPARAMETER_H

/**
 * @brief The AdjustParameter class
 *
 *  L = B X + d
 *
 *  V = B x - l
 *
 *
 */

#include "weightobservation.h"
#include "coefficientb.h"

class AdjustParameter
{
public:
    AdjustParameter(const CoefficientB &coefficient, const WeightObservation &weight);

    const VectorXd& getX() const;              // get the values of :X, D_XX
    const VectorXd& getx() const;

    void printResult() const;

private:
    int n,t;
    double sigma0;                      // σ0,x,X,N,W,V,L,sigma_XX
    VectorXd x,X;
    MatrixXd N,W,V,L,sigma_XX;
};

#endif // ADJUSTPARAMETER_H
