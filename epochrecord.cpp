#include "EpochRecord.h"

EpochRecord::EpochRecord()
    :epoch(0),
     flagEpoch(0),
     countSat(0),
     firstLine(1),
     countPrnLines(1),
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

double EpochRecord::getEpoch() const
{
    return epoch;
}

int EpochRecord::getCountPrnLines() const
{
    return countPrnLines;
}

int EpochRecord::getCountSat() const
{
    return countSat;
}

const vector<string>& EpochRecord::getPrnList() const
{
    return prnList;
}

/**
 * @brief EpochRecord::parseHeader
 * @param strLine
 * @return 0:ok, -1:false
 */
void EpochRecord::parseHeader(const string &strLine)
{
    if(1 == firstLine){       // read the first line of the epoch record header.
        gtime_t gtime;
        str2time(strLine,0,26,gtime);
        epoch               = gtime.time + gtime.sec;         // ! posible erro!

        flagEpoch           = extractDouble(strLine,28,1);
        countSat            = extractDouble(strLine,29,3);

        extractPrn(prnList,strLine);
        firstLine = 0;

        if(12 >= countSat){
            countPrnLines = 1;
        }
        if(12 < countSat && 24 >= countSat){
           countPrnLines = 2;
        }
        if(24 < countSat){
           cout << "The count of sat more than 24! " << endl;
        }

        return;
    }

    if(0 == firstLine){       // read the second line of the epoch record header.
        vector<string> addPrn;
        extractPrn(addPrn,strLine);
        prnList.insert(prnList.end(),addPrn.begin(),addPrn.end());             
    }   
}

void EpochRecord::parseBody(const vector<string> &strBlock,int countLineOneSat)
{
    int i = 0;

    vector<string>::const_iterator it;
    for(it = strBlock.begin();it != strBlock.end(); 1){
        satObsValue_t satObsValue;

        for(int j = 0; j < countLineOneSat ; j++){
        //   string tempLine = *it;
           vector<double> tempObsValue;         // one satellite observation (maybe more than 5)
           extractDoubleList(tempObsValue,*it,0,16);
           satObsValue.obsValue.insert(satObsValue.obsValue.end(),
                                       tempObsValue.begin(),tempObsValue.end());
           it++;
        }

        satObsValue.prn = prnList.at(i);
        i++;

        satObsValueList.push_back(satObsValue);
    }
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
    this->firstLine         = rhs.firstLine;
    this->countPrnLines     = rhs.countPrnLines;
    this->clockOffsetRev    = rhs.clockOffsetRev;
    this->satObsValueList   = rhs.satObsValueList;
}
