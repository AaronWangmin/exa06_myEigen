#ifndef OBSDATAFILE_H
#define OBSDATAFILE_H

#include "obsheader.h"
#include "epochrecord.h"

/**
 * @brief The ObsDataFile class
 * GNSS Observation Data File, based on rinex2.11
 */
class ObsDataFile
{
public:
    ObsDataFile();

    const vector<EpochRecord>& getObsDataRecord() const;

    void fromObsFile(const string& obsFile);

private:
    ObsHeader obsHeader;
    vector<EpochRecord> obsDataRecord;
    int calculateLinesPrn(int countSat) const;          // the lines of epoch record header.
};

#endif // OBSDATAFILE_H
