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

    void parseObsHeader(const vector<string> &strBlock);

    int calculateLinesObsTypes() const;
    int calculateLinesObsValue() const;         // calculate lines of observation value in epochRecord.

private:
    int countObsTypes;
    vector<string> obsTypes;
    double leapSeconds;  

    void assigment(const ObsHeader &rhs);

    void parseObsTypes(const vector<string> &strBlockLable);
};

#endif // OBSHEADER_H
