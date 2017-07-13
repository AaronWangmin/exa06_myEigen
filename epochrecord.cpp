#include "EpochRecord.h"

EpochRecord::EpochRecord()
    :epoch(0),
     flagEpoch(0),
     countSat(0),
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

int EpochRecord::getCountSat() const
{
    return countSat;
}

const vector<string>& EpochRecord::getPrnList() const
{
    return prnList;
}

//int EpochRecord::getCountPrnLines() const
//{
//    return countPrnLines;
//}

const vector<satObsValue_t>& EpochRecord::getSatObsValueList() const
{
    return satObsValueList;
}

const vector<satObsValue_t>& EpochRecord::getGPSObsList() const
{
    return gpsSatObsList;
}
const vector<satObsValue_t>& EpochRecord::getGlonassObsList() const
{
    return glonassSatObsList;
}

void EpochRecord::parseHeader(const vector<string> &strBlock)
{
    string strLine = strBlock.at(0);

    gtime_t gtime;
    str2time(strLine,0,26,gtime);
    epoch               = gtime.time + gtime.sec;         // ! posible erro!

    flagEpoch           = extractDouble(strLine,28,1);
    countSat            = extractDouble(strLine,29,3);

    vector<string>::const_iterator it;
    for(it = strBlock.begin(); it != strBlock.end(); it++){
        vector<string> tempPrn;
        extractPrn(tempPrn,*it);
        prnList.insert(prnList.end(),tempPrn.begin(),tempPrn.end());
    }
}

void EpochRecord::parseBody(const vector<string> &strBlock,int linesObsValue)
{
    int iSat = 0;
    vector<string>::const_iterator it;
    for(it = strBlock.begin();it != strBlock.end(); 1){

        // extract observations of one sat.
        vector<string> strBlockObsValue;
        for(int i = 0; i < linesObsValue; i++){
            strBlockObsValue.push_back(*it);
            it++;
        }

        satObsValue_t oneSatObs;
        parseOneSatObs(oneSatObs.obsValue,strBlockObsValue);

        oneSatObs.prn = prnList.at(iSat);
        iSat++;

        if(string::npos != oneSatObs.prn.find("G")){
            gpsSatObsList.push_back(oneSatObs);
        }else if(string::npos != oneSatObs.prn.find("R")){
            glonassSatObsList.push_back(oneSatObs);
        }else{
            // add...
            // beidou...
        }
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

/**
 * @brief EpochRecord::parseObsValue
 *
 * 提取一个卫星的观测值，可能多于 1行
 *
 * @param obsValueList
 * @param strBlock
 */
void EpochRecord::parseOneSatObs(vector<double> &oneSatObs, const vector<string> &strBlock)
{
    vector<string>::const_iterator it;
    for(it = strBlock.begin(); it != strBlock.end(); it++){
        vector<double> obsLine;
        parseOneLineObs(obsLine,*it);

        oneSatObs.insert(oneSatObs.end(),obsLine.begin(),obsLine.end());
    }
}

/**
 * @brief EpochRecord::extractObsList
 *
 * 提取一行观测值
 *
 * @param obsList
 * @param strLine
 */
void EpochRecord::parseOneLineObs(vector<double> &obsList, const string &strLine)
{
    string::const_iterator it;
    int pos = 0;
    for(it = strLine.begin(); it != strLine.end() && pos <= strLine.size(); it+=16){
        string temp = strLine.substr(pos,16);
        double value = extractDouble(temp,0,14);
        obsList.push_back(value);

        pos += 16;

        // added the two items:LLI and Signal strength,...
    }
}

void EpochRecord::assigment(const EpochRecord &rhs)
{
    this->epoch             = rhs.epoch;
    this->flagEpoch         = rhs.flagEpoch;
    this->countSat          = rhs.countSat;
    this->prnList           = rhs.prnList;
    this->clockOffsetRev    = rhs.clockOffsetRev;
    this->satObsValueList   = rhs.satObsValueList;
    this->gpsSatObsList     = rhs.gpsSatObsList;
    this->glonassSatObsList = rhs.glonassSatObsList;
}
