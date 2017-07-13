#include <QCoreApplication>

#include "Eigen/Dense"
using namespace Eigen;

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

   /**
    * test:: c++
    */
//   string sNum = "3F-3 ";
//   stringstream ss(sNum);
//   double num;
//   if(ss >> num){
//     cout << num << endl;
//   }else{
//     cout << -1 << endl;
//   }
//   cout << endl;

   //    vector<string> v;
   //    strSplit(v,"  aa bb    ccc     ddd a",' ');

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


/**
 * test: Eigen...
 */

//    MatrixXd t1;
//    t1.setRandom(4,4);
//    cout << t1 << endl<< endl;
//    cout << t1.transpose() << endl << endl;
//    cout << t1.adjoint()<< endl;
//    cout << 7*pow(10,-5) << endl;
//    cout << 7E-5 << endl;

//    Vector4d posClockRec0(1,2,3,4);
//    Vector3d posSat(5,10,14);
//    Vector3d temp = posClockRec0.head(3) - posSat;
//    double d = sqrt((temp.array().square()).matrix().sum());
//    RowVector4d b;
//    b << (temp/d).transpose(),1;
//    cout << endl << d << endl;
//    cout << endl << posClockRec0 << endl;
//    cout << endl << posSat << endl;
//    cout << endl << temp << endl;
//    cout << endl << b << endl;

//    cout << endl;



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

//    int i = 4;
//    MatrixXd m1(i,i);
//    RowVector4d r1;
//    r1 << 1,2,3,4;
//    m1.row(0) = r1;
//    cout << r1 << endl;
//    cout << m1 << endl;

//    RowVector3f n;
//    n << 100,100,100;
//    cout << n << endl;
//    MatrixXf m(3,3);
//        m<< 1,2,3,
//            4,5,6,
//            7,8,9;
//        cout<<"Here is the matrix m:"<<endl<<m<<endl;
//        cout<<"2nd Row:"<<m.row(1)<<endl;
//        m.col(2) += 3*m.col(0);
//        m.row(2) = n;
//        m.row(2) += n;
//        cout<<"After adding 3 times the first column into third column,the matrix m is:\n";
//        cout<<m<<endl;


/**
 *   test: WeightObservation...
 */

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

/**
 *   test: date to GPS TIME
 */
//      string temp = " 1 14 12  9  0  0  0.0-0";
//      gtime_t gtime;
//      str2time(temp,3,19,gtime);
//      double t = gtime.time + gtime.sec;
//      cout << t << endl;

/**
 *   test: position sat
 */

//    Broadcast brdc("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/brdc3430.14n");
    Broadcast brdc("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/brdc1730.16n");

//    PositionSat posat;
//    posat.calculateFromBroadcast(1418083200,4,brdc);
//    cout << endl << posat.getPositionSat() << endl;

    ObsDataFile obsfile;
//    obsfile.fromObsFile("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/lhaz3430.14o");
    obsfile.fromObsFile("D:/exam_cs106/code_aaron_cs106/exa06_myEigen/scch1730.16o");


    Vector4d posRec0(0,0,0,0);
    SSP ssp(posRec0,obsfile.getObsDataRecord().at(1),brdc);

   return a.exec();
}

