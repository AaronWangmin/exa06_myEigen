#ifndef COEFFICIENTB_H
#define COEFFICIENTB_H

#include <Eigen/Dense>
using namespace Eigen;

class CoefficientB
{
public:
    CoefficientB();
    CoefficientB(const MatrixXd &coefB,const VectorXd &coefl);    
    CoefficientB(const CoefficientB &rhs);
    CoefficientB& operator= (const CoefficientB &rhs);


    const MatrixXd& getB() const;      // get coefficient Matrix B
    const VectorXd& getl() const;      // get const Vector l
    const VectorXd& getX0() const;     // get X0

    void printBL() const;

private:
    int n,t;
    MatrixXd B;
    VectorXd l;
    VectorXd X0;

    void assignment(const CoefficientB &rhs);
};

#endif // COEFFICIENTB_H
