#include <QCoreApplication>

#include <iostream>
#include "weightobservation.h"
#include "coefficientb.h"
#include "adjustparameter.h"
using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // test: Eigen...
    MatrixXd t1;
    t1.setRandom(4,4);
    cout << t1 << endl<< endl;
    cout << t1.transpose() << endl << endl;
    cout << t1.adjoint()<< endl;

    // test: WeightObservation...
    WeightObservation w1(10);
    cout << w1.getWeight() << endl;

    VectorXd weight(5);
    weight << 1,2,3,4,5;
    WeightObservation w2(5,weight);
    cout << w2.getWeight() << endl;   

    MatrixXd B(6,3);
    B << 1,0,0,
        -1,0,0,
        -1,1,0,
         0,1,-1,
         0,0,1,
         0,0,1;
    cout << B << endl;
    VectorXd l(6);
    l << 0,-6,0,3,0,-9;
    cout << l << endl;
    CoefficientB coefB(B,l);
    coefB.printBL();

    VectorXd p(6);
    p << 1,1,2,1,2,2;
    WeightObservation weight1(6,p);
    AdjustParameter adj(coefB,weight1);    
    adj.printResult();


    return a.exec();
}
