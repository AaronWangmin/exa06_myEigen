#include "EpochRecord.h"

EpochRecord::EpochRecord()
    :epoch(0),
     flagEpoch(0),
     countSat(0),
     prnContinue(0),
     clockOffsetRev(0)
{

}

EpochRecord::EpochRecord(const EpochRecord &rhs)
{
    assigment(rhs);
}

EpochRecord& EpochRecord::operator =(const EpochRecord &rhs)
{
    assigment(rhs);
    return *this;
}

bool EpochRecord::getPrnContinue() const
{
    return prnContinue;
}

void EpochRecord::setPrnContinue(bool b)
{
    prnContinue = b;
}

int EpochRecord::getCountSat() const
{
    return countSat;
}

/**
 * @brief EpochRecord::parseHeader
 * @param strLine
 * @return 0:ok, -1:false
 */
int EpochRecord::parseHeader(const string &strLine)
{
    if(0 == prnContinue){       // read the first line of the epoch record header.
        gtime_t gtime;
        str2time(strLine,0,26,gtime);
        epoch               = gtime.time + gtime.sec;         // ! posible erro!

        flagEpoch           = extractDouble(strLine,28,1);
        countSat            = extractDouble(strLine,29,3);

        extractPrn(prnList,strLine);

        if(12 < countSat && 24 >= countSat){
           prnContinue = 1;
        }
        if(24 < countSat){
           cout << "The count of sat more than 24! " << endl;
        }

        return 0;
    }

    if(1 == prnContinue){       // read the second line of the epoch record header.
        vector<string> addPrn;
        extractPrn(addPrn,strLine);
        prnList.insert(prnList.end(),addPrn.begin(),addPrn.end());
        prnContinue = 0;

        return 0;
    }

    return -1;
}

void EpochRecord::extractPrn(vector<string> &prnList, const string &strLine)
{
    string temp = strLine.substr(32,36);

    string::const_iterator it;
    int pos = 0;
    for(it = temp.begin(); it != temp.end(); it+=3){
        string prn = temp.substr(pos,3);
        prnList.push_back(prn);
        pos += 3;
    }
}

void EpochRecord::assigment(const EpochRecord &rhs)
{
    this->epoch             = rhs.epoch;
    this->flagEpoch         = rhs.flagEpoch;
    this->countSat          = rhs.countSat;
    this->prnList           = rhs.prnList;
    this->prnContinue       = rhs.prnContinue;
    this->clockOffsetRev    = rhs.clockOffsetRev;
    this->epochRecord         = rhs.epochRecord;
}
