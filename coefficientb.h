#ifndef COEFFICIENTB_H
#define COEFFICIENTB_H

#include <Eigen/Dense>
using namespace Eigen;

class CoefficientB
{
public:
    CoefficientB(const MatrixXd &coefB,const VectorXd &coefl);

    MatrixXd getB() const;      // get coefficient Matrix B
    VectorXd getl() const;      // get const Vector l
    VectorXd getX0() const;     // get X0

    void printBL() const;

private:
    int n,t;
    MatrixXd B;
    VectorXd l;
    VectorXd X0;
};

#endif // COEFFICIENTB_H
