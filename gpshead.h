#ifndef GPSHEAD
#define GPSHEAD

#include <Eigen/Dense>
using namespace Eigen;

#include <iostream>
#include <string>
#include <sstream>
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

enum class SYS_CODE{          // Satellite system code,based rinex3.03, rinex2.11
    N  = 0,             // noe
    G  = 1,             // GPS
    C  = 2,             // BeiDou
    R  = 4,             // Glonass
    E  = 8,             // Golleo
    S  = 10,            // SBAS
    A  = 16             // ALL
};

enum class OBS_DESC_TYPE{          // Observation descript: TYPE,based rinex3.03, rinex2.11
    C   = 0,            // Code/ Pseudorange
    L   = 1,            // Phrase
    D   = 2,            // Doppler
    S   = 4,            // Raw signal strength(carrier to noise radio)
    I   = 8,            // Ionosphere phase delay
    X   = 10            // Receiver channel number
};

enum class OBS_DESC_BAND{          // Observation descript: BAND,based rinex3.03, rinex2.11
    L1  = 1,            // L1(GPS,QZSS,SBAS),G1(GLO),E1(GAL)
    L2  = 2,            // L2(GPS,QZSS),G2(GLO),B1(BDS)
    L5  = 5,            // L5(GPS,QZSS,SBAS),E5a(GAL),L5(IRNSS)
    E6  = 6,            // E6(GAL),LEX(QZSS),B3(BDS)
    B2  = 7,            // E5b(GAL),B2(BDS)
    E5  = 8,            // E5a+b(GAL)
    S   = 9,            // (IRNSS)
    A   = 0             // ALL
};

enum class OBS_DESC_ATTRIBUTE{     // Observation descript: Attribute,based rinex3.03, rinex2.11
    // added...
};



struct gtime_t{
    time_t time;                // times expressed by standard time_t
    double sec;                 // fraction of second under 1s

    gtime_t();
    gtime_t(time_t t,double s);
    gtime_t(const gtime_t &rhs);// ? needed a operator= ?
};


struct eph_t{                   // GPS broadcast ephemeris type,based on rinex2.11,(34 variable)   

    // data record
    int prn;                    // first line of nav records
    double toc;                 // from time_t(0), "16  6 21  0  0  0.0"
    double af0,af1,af2;
    double iode,Crs,Deln,M0;    // broadcast orbit-1
    double Cuc,e,Cus,sqrtA;     // broadcast orbit-2
    double toe;                 // broadcast orbit-3,  seconds of gps week(toe)
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

struct obsDesc_t{
    OBS_DESC_TYPE obsDescType;
    OBS_DESC_BAND obsDescBand;
//    OBS_DESC_ATTRIBUTE obsDescAtti;       // added... (based on rinex3.11)

    obsDesc_t();
    obsDesc_t(const obsDesc_t &rhs);
    obsDesc_t& operator=(const obsDesc_t &rhs);

private:
    void assigment(const obsDesc_t &rhs);
};

struct obsTypes_t{              // SYS/#/OBSTYPES, based rinex3.03,can be used to rinex2.11
    SYS_CODE sysType;
    int countObsTypes;
    vector<obsDesc_t> obsDesclist;

    obsTypes_t();
    obsTypes_t(const obsTypes_t &rhs);
    obsTypes_t& operator=(const obsTypes_t &rhs);

private:
    void assigment(const obsTypes_t &rhs);

};

struct satObsValue_t{               //
    string prn;
    vector<double> obsValue;        // ? should be update by key-value(L1:21170728.140)

    satObsValue_t();
    satObsValue_t(const satObsValue_t &rhs);
    satObsValue_t& operator=(const satObsValue_t &rhs);

private:
    void assigment(const satObsValue_t &rhs);
};


extern double extractDouble(const string& str,int pos,int npos);        // ? extern
extern void strSplit(vector<string>& strlist,const string& str,char c);
extern void extractDoubleList(vector<double>& doubleList,const string& str,int pos, int npos);
extern int str2time(const string& str,int pos,int npos,gtime_t& t);
extern double timeDiff(gtime_t t1, gtime_t t2);
extern gtime_t epoch2time(const double *ep);
extern gtime_t gpst2time(int week, double sec);
extern double  time2gpst(gtime_t t, int &week);



#endif // GPSHEAD

