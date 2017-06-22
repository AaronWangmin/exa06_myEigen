#ifndef GPSHEAD
#define GPSHEAD

struct eph_t{                   // GPS broadcast ephemeris type,based on rinex2.11

    // head
    int week;

    // data record
    int sat;
    double toc;
    double af0,af1,af2;
    double iode,Crs,Deln,M0;    // broadcast orbit-1
    double Cuc,e,Cus,A;         // broadcast orbit-2
    double toe;                 // broadcast orbit-3
    double Cic,OMG0,Cis;
    double i0,Crc,omg,OMGd;     // broadcast orbit-4
    double iDOT,code,toes,flag; // broadcast orbit-5
    double sva,svh,tgd,iodc;    // broadcast orbit-6
    double ttr;                 // broadcast orbit-7
    double fit;
    double reserved,reserved01;

    eph_t();                    // ? needed ?
    eph_t(const &eph_t);        // ? needed ?
    //~eph_t();                 // ? needed ?
};


#endif // GPSHEAD

