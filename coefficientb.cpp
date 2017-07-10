#include "coefficientb.h"
#include <iostream>

CoefficientB::CoefficientB()
    :n(0),
     t(0)
{

}

CoefficientB::CoefficientB(const MatrixXd &coefB, const VectorXd &coefl)
    :n(coefB.rows()),
     t(coefB.cols()),
     B(coefB),
     l(coefl)
{

}

CoefficientB::CoefficientB(const MatrixXd &coefB, const VectorXd &coefl, const VectorXd &inital_X0)
    :n(coefB.rows()),
     t(coefB.cols()),
     B(coefB),
     l(coefl)
{
    X0 = inital_X0;
}



CoefficientB::CoefficientB(const CoefficientB &rhs)
{
    assignment(rhs);
}

CoefficientB& CoefficientB::operator =(const CoefficientB &rhs){
    assignment(rhs);
    return *this;
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

void CoefficientB::assignment(const CoefficientB &rhs)
{
    this->n     = rhs.n;
    this->t     = rhs.t;
    this->B     = rhs.B;
    this->l     = rhs.l;
    this->X0    = rhs.X0;
}
