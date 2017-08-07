#include "broadcast.h"

#include <iostream>
#include <fstream>
using namespace std;

Broadcast::Broadcast()
{

}

Broadcast::Broadcast(const string &navFile)
{
   fstream fs(navFile);
   if(!fs)  { cout << navFile << " opening failed! " << endl;}

   else{
       string strline;
       while(!fs.eof()){                                // parse the Nav header.
           getline(fs,strline);
           if( -1 == parseNavHead(strline)) break;
       }

       while(!fs.eof()){
           vector<string> strEph;                       // extract one ephemeris record from 8 lines.
           for(int i = 0; i < 8; i++){
               getline(fs,strline);
               strEph.push_back(strline);
           }
           eph_t eph;
           parseNavData(strEph,eph);                    // parse the Nav data record.
           ephRecord.push_back(eph);                    // added a Nav data record to a vector.
       }

       fs.close();
   }
}

const vector<eph_t>& Broadcast::getEphRecord() const
{
    return ephRecord;
}

void Broadcast::setEphRecord(const vector<eph_t> &newEphRecord)
{
    ephRecord = newEphRecord;
}

int Broadcast::parseNavHead(const string &strline)
{
    // need to add a struct of navHead_t to store the NavHead......

    string lable = strline.substr(60);

    if     (string::npos != lable.find("DELTA-UTC: A0,A1,T,W")) cout << " gps week" << endl;

    else if(string::npos != lable.find("END OF HEADER")) return -1;

}

void Broadcast::parseNavData(const vector<string> &strEph, eph_t &eph)
{
        // the 1th line of ephemeris record.
        string temp = strEph.at(0);
        eph.prn               = std::stoi( temp.substr(0,2));

        gtime_t gtime;
        str2time(temp,3,19,gtime);
        eph.toc               = gtime.time + gtime.sec;         // ! posible erro!

        eph.af0               = extractDouble(temp,22,19);
        eph.af1               = extractDouble(temp,41,19);
        eph.af2               = extractDouble(temp,60,19);

        // the 2th line
        temp = strEph.at(1);
        eph.iode               = extractDouble(temp,3,19);
        eph.Crs                = extractDouble(temp,22,19);
        eph.Deln               = extractDouble(temp,41,19);
        eph.M0                 = extractDouble(temp,60,19);

        // the 3th line
        temp = strEph.at(2);
        eph.Cuc               = extractDouble(temp,3,19);
        eph.e                 = extractDouble(temp,22,19);
        eph.Cus               = extractDouble(temp,41,19);
        eph.sqrtA             = extractDouble(temp,60,19);

        // the 4th line
        temp = strEph.at(3);
        eph.toe               = extractDouble(temp,3,19);       // seconds of week. ! posible erro!
        eph.Cic               = extractDouble(temp,22,19);
        eph.OMG0              = extractDouble(temp,41,19);
        eph.Cis               = extractDouble(temp,60,19);

        // the 5th line
        temp = strEph.at(4);
        eph.i0                = extractDouble(temp,3,19);
        eph.Crc               = extractDouble(temp,22,19);
        eph.omg               = extractDouble(temp,41,19);
        eph.OMGd              = extractDouble(temp,60,19);

        // the 6th line
        temp = strEph.at(5);
        eph.iDOT              = extractDouble(temp,3,19);
        eph.code              = extractDouble(temp,22,19);
        eph.week              = extractDouble(temp,41,19);
        eph.flag              = extractDouble(temp,60,19);

//        gtime_t toeTemp(gpst2time(eph.week,sec));
//        eph.toe               = toeTemp.time + toeTemp.sec;

        // the 7th line
        temp = strEph.at(6);
        eph.sva               = extractDouble(temp,3,19);
        eph.svh               = extractDouble(temp,22,19);
        eph.tgd               = extractDouble(temp,41,19);
        eph.iodc              = extractDouble(temp,60,19);

        // the 8th line
        temp = strEph.at(7);
        eph.ttr               = extractDouble(temp,3,19);       // ! posible erro!
        eph.fit               = extractDouble(temp,22,19);
        eph.reserved          = extractDouble(temp,41,19);
        eph.reserved01        = extractDouble(temp,60,19);
}

