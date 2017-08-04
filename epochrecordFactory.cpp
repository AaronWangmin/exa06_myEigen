#include "epochrecordFactory.h"

EpochRecordFactory::EpochRecordFactory()
{

}

EpochRecordFactory::EpochRecordFactory(const EpochRecordFactory &rhs)
{
    assigment(rhs);
}

EpochRecordFactory& EpochRecordFactory::operator =(const EpochRecordFactory &rhs)
{
    assigment(rhs);
    return *this;
}

const epochRecord_t& EpochRecordFactory::getEpochRecord() const
{
    return epochRecord;
}

void EpochRecordFactory::parseHeader(const vector<string> &strBlock)
{
    string strLine = strBlock.at(0);

    gtime_t gtime;
    str2time(strLine,0,26,gtime);
    epochRecord.epoch               = gtime.time + gtime.sec;

    epochRecord.flagEpoch           = extractDouble(strLine,28,1);

    epochRecord.countSat            = extractDouble(strLine,29,3);

    vector<string>::const_iterator it;
    for(it = strBlock.begin(); it != strBlock.end(); it++){
        vector<string> tempPrn;
        extractPrn(tempPrn,*it);

        epochRecord.prnList.insert(epochRecord.prnList.end(),tempPrn.begin(),tempPrn.end());
    }
}

void EpochRecordFactory::parseBody(const vector<string> &strBlock,int linesObsValue)
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

        oneSatObs.prn = epochRecord.prnList.at(iSat);
        iSat++;

        if(string::npos != oneSatObs.prn.find("G")){
            epochRecord.gpsSatObsList.push_back(oneSatObs);
        }else if(string::npos != oneSatObs.prn.find("R")){
            epochRecord.glonassSatObsList.push_back(oneSatObs);
        }else{
            // add...
            // beidou...
        }
    }
}

void EpochRecordFactory::extractPrn(vector<string> &prnList, const string &strLine)
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
void EpochRecordFactory::parseOneSatObs(vector<double> &oneSatObs, const vector<string> &strBlock)
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
void EpochRecordFactory::parseOneLineObs(vector<double> &obsList, const string &strLine)
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

void EpochRecordFactory::assigment(const EpochRecordFactory &rhs)
{
    this->epochRecord       = rhs.epochRecord;
}
