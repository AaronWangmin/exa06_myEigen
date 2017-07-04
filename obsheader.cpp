#include "obsheader.h"
ObsHeader::ObsHeader()
    :countObsTypes(0),
     firstLine(1),
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

int ObsHeader::calculateLinesObsTypes() const
{

    if                       (9 >= countObsTypes)   return 1;

    if(9 <  countObsTypes && 18 >= countObsTypes)   return 2;

    if(18 <  countObsTypes){
        cout << " the count of observation types more than 19! " << endl;
    }
}

int ObsHeader::calculateLinesObsValue() const
{

    if(5 >= countObsTypes)                          return 1;

    if(5 <  countObsTypes && 10 >= countObsTypes)   return 2;

    if(10 <  countObsTypes){
        cout << " the count of observation types more than 10! " << endl;
    }
}

/**
 * @brief ObsHeader::parseObsHeader
 * @param strTemp
 * @return 0:ok, -1:false
 */
int ObsHeader::parseObsHeader(const string &strLine)     // ? needed initializaton list?
{
    string lable = strLine.substr(60);

    if(string::npos != lable.find("# / TYPES OF OBSERV")){
        countObsTypes = static_cast<int>(extractDouble(strLine,0,6));

        extractObsTypes(obsTypes,strLine);
        firstLine = 0;

        if(18 < countObsTypes){
            cout << "the count of observation types is bigger than 18!" << endl;
        }

        return 0;
    }

    // read the continued line of "# / TYPES OF OBSERV"
    if(string::npos != lable.find("                 ") && 0 == firstLine){
        vector<string> obsTypesLine2;
        extractObsTypes(obsTypesLine2,strLine);
        obsTypes.insert(obsTypes.end(),obsTypesLine2.begin(),obsTypesLine2.end());
    }

        // added other lalbes...
    if(string::npos != lable.find("LEAP SECONDS")){
        leapSeconds = static_cast<int>(extractDouble(strLine,0,6));

        return 0;
    }

    if(string::npos != lable.find("END OF HEADER")) return -1;

    return 0;
}


void ObsHeader::assigment(const ObsHeader &rhs)
{
    this->countObsTypes = rhs.countObsTypes;
    this->obsTypes      = rhs.obsTypes;
    this->firstLine     = rhs.firstLine;
    this->leapSeconds   = rhs.leapSeconds;
}

/**
 * @brief ObsHeader::extractObsTypes
 * @param strTemp
 * @return 0:ok, -1:false
 */
void ObsHeader::extractObsTypes(vector<string> &obsTypes, const string &strline) const
{
    string temp = strline.substr(6,54);
    strSplit(obsTypes,temp,' ');
}

//void ObsHeader::setTagObsTypes(int tag)
//{
//    tagObsTypes = tag;
//}

//void ObsHeader::setObsTypes(const vector<string> &newObsTypes)
//{
//    obsTypes(newObsTypes);
//}
