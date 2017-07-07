#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "weightobservation.h"
#include "coefficientb.h"
#include "adjustparameter.h"
#include "broadcast.h"
#include "positionsat.h"
#include "obsdatafile.h"
#include "ssp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    // test: Eigen...
//    MatrixXd t1;
//    t1.setRandom(4,4);
//    cout << t1 << endl<< endl;
//    cout << t1.transpose() << endl << endl;
//    cout << t1.adjoint()<< endl;

//    Vector3d v1(1,2,3), v2(4,6,8);
//    Vector3d temp = v2 - v1;
//    double d = sqrt((temp.array().square()).matrix().sum());
//    RowVector4d b;
//    b << (temp/d).transpose(),1;
//    cout << v1 << endl;
//    cout << v2 << endl;
//    cout << temp << endl;
//    cout << d << endl;
//    cout << b << endl;

    Vector4d v3,v4;
    v3 << 1,2,3,4;
    cout << v3 << endl;
    v4(v3,5,6,7,8);
    cout << v4 << endl;



//    // test: WeightObservation...
//    WeightObservation w1(10);
//    cout << w1.getWeight() << endl;

//    VectorXd weight(5);
//    weight << 1,2,3,4,5;
//    WeightObservation w2(5,weight);
//    cout << w2.getWeight() << endl;

//    MatrixXd B(6,3);
//    B << 1,0,0,
//        -1,0,0,
//        -1,1,0,
//         0,1,-1,
//         0,0,1,
//         0,0,1;
//    cout << B << endl;
//    VectorXd l(6);
//    l << 0,-6,0,3,0,-9;
//    cout << l << endl;
//    CoefficientB coefB(B,l);
//    coefB.printBL();

//    VectorXd p(6);
//    p << 1,1,2,1,2,2;
//    WeightObservation weight1(6,p);
//    AdjustParameter adj(coefB,weight1);
//    adj.printResult();

    Broadcast brdc("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/brdc1730.16n");

//    PositionSat posat;
////    posat.calculateFromBroadcast(1,1466467200,brdt);
////    cout << endl << posat.getPositionSat() << endl;

////    vector<string> v;
////    strSplit(v,"  aa bb    ccc     ddd a",' ');

//    vector<double> span;
//    for(int i = 0; i < 12 ; i++){
//        span.push_back(1466467200 + i*7200);
//        posat.calculateFromBroadcast(2,span.back(),brdt);
//        cout << posat.getPositionSat() << endl << endl;
//    }

//    double d2 = 0.0000000000000000000000000000000000000000000000000000000001;
//    string d1 = "0.190200000000e+04";
//    cout << std::stod(d1) << endl;
//    cout << d2 << endl;


    ObsDataFile obsfile;
    obsfile.fromObsFile("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/scch1730.16o");

    Vector3d posRec0(0,0,0);
    SSP ssp(obsfile.getObsDataRecord().at(1),brdc,posRec0);



    return a.exec();
}
