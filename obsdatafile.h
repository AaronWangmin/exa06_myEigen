#ifndef OBSDATAFILE_H
#define OBSDATAFILE_H

#include "obsheader.h"

/**
 * @brief The ObsDataFile class
 * GNSS Observation Data File, based on rinex2.11
 */
class ObsDataFile
{
public:
    ObsDataFile();

    void fromObsFile(const string& obsFile);

private:
    ObsHeader obsHeader;
//    ObsDataRecord;

};

#endif // OBSDATAFILE_H
