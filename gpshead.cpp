#include "gpshead.h"

gtime_t::gtime_t()
    :time(0),
     sec(0)
{

}

gtime_t::gtime_t(time_t t, double s)
    :time(t),
     sec(s)
{

}


gtime_t::gtime_t(const gtime_t &rhs)
{
    this->time   = rhs.time;
    this->sec    = rhs.sec;
}

eph_t::eph_t()
    :prn(0),toc(0),
     af0(0),af1(0),af2(0),
     iode(0),Crs(0),Deln(0),M0(0),
     Cuc(0),e(0),Cus(0),sqrtA(0),
     toe(0),
     Cic(0),OMG0(0),Cis(0),
     i0(0),Crc(0),omg(0),OMGd(0),
     iDOT(0),code(0),week(0),flag(0),
     sva(0),svh(0),tgd(0),iodc(0),
     ttr(0),
     fit(0),
     reserved(0),reserved01(0)
{

}

eph_t::eph_t(const eph_t &rhs)
{    
   eph_t::assigment(rhs);
}

eph_t& eph_t::operator =(const eph_t &rhs)
{
    eph_t::assigment(rhs);
    return *this;
}

void eph_t::assigment(const eph_t &rhs)
{
    this->af0           = rhs.af0;
    this->af1           = rhs.af1;
    this->af2           = rhs.af2;
    this->Cic           = rhs.Cic;
    this->Cis           = rhs.Cis;
    this->code          = rhs.code;
    this->Crc           = rhs.Crc;
    this->Crs           = rhs.Crs;
    this->Cuc           = rhs.Cuc;
    this->Cus           = rhs.Cus;
    this->Deln          = rhs.Deln;
    this->e             = rhs.e;
    this->fit           = rhs.fit;
    this->flag          = rhs.flag;
    this->i0            = rhs.i0;
    this->iDOT          = rhs.iDOT;
    this->iodc          = rhs.iodc;
    this->iode          = rhs.iode;
    this->M0            = rhs.M0;
    this->omg           = rhs.omg;
    this->OMG0          = rhs.OMG0;
    this->OMGd          = rhs.OMGd;
    this->prn           = rhs.prn;
    this->reserved      = rhs.reserved;
    this->reserved01    = rhs.reserved01;
    this->sqrtA         = rhs.sqrtA;
    this->sva           = rhs.sva;
    this->svh           = rhs.svh;
    this->tgd           = rhs.tgd;
    this->toc           = rhs.toc;
    this->toe           = rhs.toe;
    this->ttr           = rhs.ttr;
    this->week          = rhs.week;
}

obsDesc_t::obsDesc_t()
    :obsDescType(OBS_DESC_TYPE::C),
     obsDescBand(OBS_DESC_BAND::L1)
{

}

obsDesc_t::obsDesc_t(const obsDesc_t &rhs)
{
    assigment(rhs);
}

obsDesc_t& obsDesc_t::operator =(const obsDesc_t &rhs){
    assigment(rhs);
    return *this;
}

void obsDesc_t::assigment(const obsDesc_t &rhs)
{
    this->obsDescType = rhs.obsDescType;
    this->obsDescBand = rhs.obsDescBand;
}

obsTypes_t::obsTypes_t()
    :sysType(SYS_CODE::N),
     countObsTypes(0)
{

}

obsTypes_t::obsTypes_t(const obsTypes_t &rhs)
{
    assigment(rhs);
}

obsTypes_t& obsTypes_t::operator =(const obsTypes_t &rhs)
{
    assigment(rhs);
    return *this;
}

void obsTypes_t::assigment(const obsTypes_t &rhs)
{
    this->sysType       = rhs.sysType;
    this->countObsTypes = rhs.countObsTypes;
    this->obsDesclist   = rhs.obsDesclist;
}

satObsValue_t::satObsValue_t()
{

}

satObsValue_t::satObsValue_t(const satObsValue_t &rhs)
{
    assigment(rhs);
}

satObsValue_t& satObsValue_t::operator =(const satObsValue_t &rhs)
{
    assigment(rhs);
    return *this;
}

void satObsValue_t::assigment(const satObsValue_t &rhs)
{
    this->prn      = rhs.prn;
    this->obsValue = rhs.obsValue;
}

epochRecord_t::epochRecord_t()
    :epoch(0),
     flagEpoch(0),
     countSat(0),
     clockOffsetRev(0)
{

}

epochRecord_t::epochRecord_t(const epochRecord_t &rhs)
{
    assigment(rhs);
}

epochRecord_t& epochRecord_t::operator =(const epochRecord_t &rhs)
{
    assigment(rhs);
    return *this;
}

void epochRecord_t::assigment(const epochRecord_t &rhs)
{
    this->epoch                 = rhs.epoch;
    this->flagEpoch             = rhs.flagEpoch;
    this->countSat              = rhs.countSat;
    this->prnList               = rhs.prnList;
    this->clockOffsetRev        = rhs.clockOffsetRev;
    this->gpsSatObsList         = rhs.gpsSatObsList;
    this->glonassSatObsList     = rhs.glonassSatObsList;
}

pseudoCorretions_t::pseudoCorretions_t()
    :epochTime(0),
     value(0)
{

}

pseudoCorretions_t::pseudoCorretions_t(const pseudoCorretions_t &rhs)
{
    assigment(rhs);
}

pseudoCorretions_t& pseudoCorretions_t::operator= (const pseudoCorretions_t &rhs)
{
    assigment(rhs);
    return *this;
}

void pseudoCorretions_t::assigment(const pseudoCorretions_t &rhs)
{
    this->epochTime = rhs.epochTime;
    this->prn       = rhs.prn;
    this->value     = rhs.value;
}


/**
 * @brief extractDouble,
 * extract a double from string included 'D' in rinex file.
 * @param str       I   string()
 * @param pos       I   substring position and width
 * @param npos
 * @return          O   double, -1:fail.
 */
extern double extractDouble(const string &str,int pos, int npos)
{
    if (pos < 0||(int)str.length() < pos) return -1;

    string temp = str.substr(pos,npos);
    if(string::npos != temp.find('D')){
       temp.replace(15,1,"E");
    }

    stringstream sin(temp);
    double d;
    if(sin >> d) return d;
    else         return -1;

//    return std::stod(temp);
}

/* string to time --------------------------------------------------------------
* convert substring in string to gtime_t struct
* args   : string &str        I   string ("... yyyy mm dd hh mm ss ...")
*          int    pos,npos    I   substring position and width
*          gtime_t *t         O   gtime_t struct
* return : status (0:ok,0>:error)
*-----------------------------------------------------------------------------*/
extern int str2time(const string& str,int pos,int npos,gtime_t& t)
{
    string temp = str.substr(pos,npos);
    if (pos < 0||(int)str.length() < pos) return -1;

    double ep[6];
    if (sscanf(temp.c_str(),"%lf %lf %lf %lf %lf %lf",ep,ep+1,ep+2,ep+3,ep+4,ep+5)<6)
        return -1;
    if (ep[0]<100.0) ep[0]+=ep[0]<80.0?2000.0:1900.0;
    t = epoch2time(ep);
    return 0;
}

/* split a string -------------------------------------------------------------
* split string to serveral substring by pattern
* args   : string &str        I   string ("  aa bb    cc  ")
*          char   c           I   char (' ')
*                 v           O   string ("aa","bb","cc")
*-----------------------------------------------------------------------------*/
extern void strSplit(vector<string>& strlist,const string& str, const char c)
{
    string::const_iterator it;
    for(it = str.begin(); it != str.end(); ){
        string::const_iterator head;

        for( ; it != str.end();++it){              // 查找第一个 不等于 分割符的字符。
            char temp = *it;
            if( temp != c ){
                head = it;
                break;
            }
        }

        if(it == str.end()){
            break;
        }

        string result;
        for( ; it != str.end();++it){           // 查找第一个 等于 分割符的字符。
            char temp = *it;
            if(temp == c)   break;

            result += temp;
        }

        strlist.push_back(result);
    }
}

extern void extractDoubleList(vector<double>& doubleList,const string& str,int pos, int npos)
{
    string::const_iterator it;
    for(it = str.begin(); it != str.end(); it += npos){
        double temp = extractDouble(str,pos,npos);
        doubleList.push_back(temp);

        pos += npos;
    }
}

/* convert calendar day/time to time -------------------------------------------
* convert calendar day/time to gtime_t struct
* args   : double *ep       I   day/time {year,month,day,hour,min,sec}
* return : gtime_t struct
* notes  : proper in 1970-2037 or 1970-2099 (64bit time_t)
*-----------------------------------------------------------------------------*/
extern gtime_t epoch2time(const double *ep)
{
    const int doy[]={1,32,60,91,121,152,182,213,244,274,305,335};
    gtime_t time;
    int days,sec,year=(int)ep[0],mon=(int)ep[1],day=(int)ep[2];

    if (year<1970||2099<year||mon<1||12<mon) return time;

    /* leap year if year%4==0 in 1901-2099 */
    days=(year-1970)*365+(year-1969)/4+doy[mon-1]+day-2+(year%4==0&&mon>=3?1:0);
    sec=(int)floor(ep[5]);
    time.time=(time_t)days*86400+(int)ep[3]*3600+(int)ep[4]*60+sec;
    time.sec=ep[5]-sec;
    return time;
}

extern double timeDiff(gtime_t t1, gtime_t t2)
{
    return difftime(t1.time,t2.time) + t1.sec - t2.sec;
}

/* gps time to time ------------------------------------------------------------
* convert week and tow in gps time to gtime_t struct
* args   : int    week      I   week number in gps time
*          double sec       I   time of week in gps time (s)
* return : gtime_t struct
*-----------------------------------------------------------------------------*/
extern gtime_t gpst2time(int week, double sec)
{
    gtime_t t = epoch2time(gpst0);
    if (sec<-1E9||1E9<sec) sec=0.0;
    t.time += 86400*7*week + (int)sec;
    t.sec = sec - (int)sec;
    return t;
}
extern double time2gpst(gtime_t t, int &week){
    gtime_t t0=epoch2time(gpst0);
    time_t sec=t.time-t0.time;
    int w=(int)(sec/(86400*7));

//    if (week) *week=w;
    week=w;
    return (double)(sec-w*86400*7)+t.sec;
}

extern double distance2Points(const Vector3d &point1, const Vector3d &point2)
{
    Vector3d temp = point1 - point2;
    return sqrt((temp.array().square()).matrix().sum());
}
