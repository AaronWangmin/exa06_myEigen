#include "adjustparameter.h"
#include <iostream>

AdjustParameter::AdjustParameter(const CoefficientB &coefficient, const WeightObservation &weight)
{
    MatrixXd B,P,N,W;
    B = coefficient.getB();
    P = weight.getWeight();
    N = B.transpose() * P * B;

    VectorXd l,X0;
    l = coefficient.getl();
    W = B.transpose() * P * l;
    X0 = coefficient.getX0();

    // result...
    x = N.inverse() * W;
    X = X0 + x;
    V = B * x - l;

    // pricision...
    n = coefficient.getB().rows();
    t = coefficient.getB().cols();
    int r = n-t;
    double sigma02 =( V.transpose() * P * V /r)(0,0);

    MatrixXd D_XX = sigma02 * N.inverse();
    sigma_XX = D_XX.cwiseSqrt();

    sigma0 = sqrt(sigma02);
}



const VectorXd& AdjustParameter::getX() const
{
    return X;
}
const VectorXd& AdjustParameter::getx() const
{
    return x;
}

void AdjustParameter::printResult() const
{
    std::cout << "   Adjustment result: X   " << std::endl;
    std::cout << X << std::endl;

    std::cout << "   Adjustment result: sigma_XX   " << std::endl;
    std::cout << sigma_XX << std::endl;

    std::cout << "   Adjustment result: V   " << std::endl;
    std::cout << V << std::endl;

    std::cout << "   Adjustment result: sigma0   " << std::endl;
    std::cout << sigma0 << std::endl;
}
