#include "coefficientb.h"
#include <iostream>

CoefficientB::CoefficientB(const MatrixXd &coefB, const VectorXd &coefl)
    :n(coefB.rows()),
     t(coefB.cols()),
     B(coefB),
     l(coefl),
     X0(MatrixXd::Zero(coefB.cols(),1))
{

}

const MatrixXd& CoefficientB::getB() const
{
    return B;
}

const VectorXd& CoefficientB::getl() const
{
    return l;
}

const VectorXd& CoefficientB::getX0() const
{
    return X0;
}

void CoefficientB::printBL() const
{
    std::cout << "   Error equation: B   " << std::endl;
    std::cout << B << std::endl;
    std::cout << "   Error equation: l   " << std::endl;
    std::cout << l << std::endl;
}
