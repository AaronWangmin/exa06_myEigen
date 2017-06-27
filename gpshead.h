#ifndef GPSHEAD
#define GPSHEAD

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <math.h>
using namespace std;

/* constants -----------------------------------------------------------------*/
const static double C       = 299792458; 		    // 光速
const static double PI      = 3.141592653589793;    // 圆周率
const static double GM      = 3.986004415E+14;      // 地球引力常数
const static double OMEGA_E = 7.2921151467E-5;      // 地球自转角速度

const static double gpst0[]={1980,1, 6,0,0,0}; /* gps time reference */


struct gtime_t{
    time_t time;                // times expressed by standard time_t
    double sec;                 // fraction of second under 1s

    gtime_t();
    gtime_t(const gtime_t &rhs);// ? needed a operator= ?
};


struct eph_t{                   // GPS broadcast ephemeris type,based on rinex2.11,(34 variable)   

    // data record
    int prn;                    // first line of nav records
    double toc;
    double af0,af1,af2;
    double iode,Crs,Deln,M0;    // broadcast orbit-1
    double Cuc,e,Cus,sqrtA;     // broadcast orbit-2
    double toe;                 // broadcast orbit-3
    double Cic,OMG0,Cis;
    double i0,Crc,omg,OMGd;     // broadcast orbit-4
    double iDOT,code,week,flag; // broadcast orbit-5,  toes(in rtklib.h) ?
    double sva,svh,tgd,iodc;    // broadcast orbit-6
    double ttr;                 // broadcast orbit-7
    double fit;
    double reserved,reserved01;

    eph_t();                    // ? needed ?
    eph_t(const eph_t &rhs);    // ? needed ?
    eph_t& operator=(const eph_t &rhs);
    //~eph_t();                 // ? needed ?

private:
    void assigment(const eph_t &rhs);
};



extern double extractDouble(const string& str,int pos,int npos);        // ? extern
extern void strSplit(const string& s,
                     vector<string>& v,const string& c);                // bad work!!!
extern int str2time(const string& str,int pos,int npos,gtime_t& t);
extern double timeDiff(gtime_t t1, gtime_t t2);
extern gtime_t epoch2time(const double *ep);
extern gtime_t gpst2time(int week, double sec);



#endif // GPSHEAD

