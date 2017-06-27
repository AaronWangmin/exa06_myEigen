#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "weightobservation.h"
#include "coefficientb.h"
#include "adjustparameter.h"
#include "broadcast.h"
#include "positionsat.h"

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

    Broadcast brdt("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/brdc1730.16n");

    PositionSat posat;
//    posat.calculateFromBroadcast(1,1466467200,brdt);
//    cout << endl << posat.getPositionSat() << endl;

    vector<double> span;
     for(int i = 0; i < 12 ; i++){
         span.push_back(1466467200 + i*7200);
         posat.calculateFromBroadcast(2,span.back(),brdt);
         cout << posat.getPositionSat() << endl << endl;
    }








    return a.exec();
}
