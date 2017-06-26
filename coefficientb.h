#ifndef COEFFICIENTB_H
#define COEFFICIENTB_H

#include <Eigen/Dense>
using namespace Eigen;

class CoefficientB
{
public:
    CoefficientB(const MatrixXd &coefB,const VectorXd &coefl);

    const MatrixXd& getB() const;      // get coefficient Matrix B
    const VectorXd& getl() const;      // get const Vector l
    const VectorXd& getX0() const;     // get X0

    void printBL() const;

private:
    int n,t;
    MatrixXd B;
    VectorXd l;
    VectorXd X0;
};

#endif // COEFFICIENTB_H
