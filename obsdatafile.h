#ifndef OBSDATAFILE_H
#define OBSDATAFILE_H

#include "obsheader.h"
#include "epochrecordFactory.h"

/**
 * @brief The ObsDataFile class
 * GNSS Observation Data File, based on rinex2.11
 */
class ObsDataFile
{
public:
    ObsDataFile();

    const vector<epochRecord_t>&  getObsDataRecord()           const;
    void                          fromObsFile(const string& obsFile);

private:
    ObsHeader             obsHeader;
    vector<epochRecord_t> obsDataRecord;

private:
    int calculateLinesPrn(int countSat) const;  // the lines of epoch record header.
};

#endif // OBSDATAFILE_H
