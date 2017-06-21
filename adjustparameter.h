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

    VectorXd getX() const;              // get the values of :X, D_XX
    MatrixXd getD_XX() const;

    void printResult() const;

private:
    int n,t;
    double sigma0;                      // σ0,x,X,N,W,V,L,sigma_XX
    VectorXd x,X;
    MatrixXd N,W,V,L,sigma_XX;

    //    double getSigma02() const;           // get the values of : (σ0)^2,x,N,W,V,L
    //    VectorXd get_x() const;
    //    MatrixXd getN() const;
    //    MatrixXd getW() const;
    //    MatrixXd getV() const;
    //    MatrixXd getL() const;

};

#endif // ADJUSTPARAMETER_H
