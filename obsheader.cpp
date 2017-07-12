#include "obsheader.h"
ObsHeader::ObsHeader()
    :countObsTypes(0),
     leapSeconds(0)         // ? vector<string> obsTypes?
{

}

ObsHeader::ObsHeader(const ObsHeader &rhs)
{
    assigment(rhs);                             // ? is ok ?
}

ObsHeader& ObsHeader::operator =(const ObsHeader &rhs)
{
    assigment(rhs);
    return *this;                               // ? is ok ?
}

void ObsHeader::parseObsHeader(const vector<string> &strBlock){
    vector<string>::const_iterator it;
    for(it = strBlock.begin(); it != strBlock.end(); it++){
        string lable = (*it).substr(60);

        if(string::npos != lable.find("# / TYPES OF OBSERV")){
            countObsTypes = static_cast<int>(extractDouble(*it,0,6));
            vector<string> strBlockLable;
            for(int i = 0; i < calculateLinesObsTypes(); i++){      // extract "# / TYPES OF OBSERV"
                strBlockLable.push_back(*it);
                it++;
            }

            parseObsTypes(strBlockLable);
        }
    }
}

int ObsHeader::calculateLinesObsTypes() const
{

    if                            (9 >= countObsTypes)   return 1;

    else if(9 <  countObsTypes && 18 >= countObsTypes)   return 2;

    else{
        cout << " the count of observation types more than 18! " << endl;
    }
}

int ObsHeader::calculateLinesObsValue() const
{

    if                            (5 >= countObsTypes)   return 1;

    else if(5 <  countObsTypes && 10 >= countObsTypes)   return 2;

    else{
        cout << " the count of observation types more than 10! " << endl;
    }
}

void ObsHeader::assigment(const ObsHeader &rhs)
{
    this->countObsTypes = rhs.countObsTypes;
    this->obsTypes      = rhs.obsTypes;
    this->leapSeconds   = rhs.leapSeconds;
}

void ObsHeader::parseObsTypes(const vector<string> &strBlockLable)
{
    vector<string>::const_iterator it;
    for(it = strBlockLable.begin(); it != strBlockLable.end();it++){
        string temp = (*it).substr(6,54);
        vector<string> obsTypesTemp;
        strSplit(obsTypesTemp,temp,' ');

        obsTypes.insert(obsTypes.end(),obsTypesTemp.begin(),obsTypesTemp.end());
    }
}
