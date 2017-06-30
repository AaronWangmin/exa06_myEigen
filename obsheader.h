#ifndef OBSHEADER_H
#define OBSHEADER_H

#include "gpshead.h"

/**
 * @brief The ObsHeader class
 *
 * GNSS Observation Data Record -- Header Section, based on rinex2.11
 */
class ObsHeader
{
public:
    ObsHeader();                        // ? needed? all data from file.
    ObsHeader(const ObsHeader &rhs);
    ObsHeader& operator=(const ObsHeader &rhs);

    int parseObsHeader(const string &strLine);

//    void setTagObsTypes(int tag);
//    void setObsTypes(const vector<string> &newObsTypes);

private:
    int countObsTypes;
    int tagObsTypes;        // countObsTypes <= 9, tagObsTypes = 0;
                            // countObsTypes > 9,  tagObsTypes = 1, need to read contiune line
    vector<string> obsTypes;
    double leapSeconds;
    // added other members....
    // obsTypes_t obsTypesInfo;

    void assigment(const ObsHeader &rhs);
    void extractObsTypes(vector<string>& obsTypes,const string& strline) const;

};

#endif // OBSHEADER_H
