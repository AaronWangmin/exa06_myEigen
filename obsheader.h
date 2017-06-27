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

    int parseObsHeader(const string &strTemp);

private:
    string lable;
    int countObsTypes;
    vector<string> obsTypes;
    double leapSeconds;
    // added other members....

    void assigment(const ObsHeader &rhs);

};

#endif // OBSHEADER_H
