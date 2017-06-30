#ifndef EPOCHRECORD_H
#define EPOCHRECORD_H

#include "gpshead.h"

/**
 * @brief The EpochRecord class
 *
 * ? better name: ephoch record
 */
class EpochRecord
{
public:
    EpochRecord();
    EpochRecord(const EpochRecord &rhs);
    EpochRecord& operator=(const EpochRecord &rhs);

    int parseHeader(const string &strLine);

private:
    double                  epoch;
    int                     flagEpoch;
    int                     countSat;
    vector<string>          prnList;
    bool                    prnContinue;        // Is prn continue line ?
    double                  clockOffsetRev;
    vector<epochRecord_t>   epochRecord;

    void assigment(const EpochRecord &rhs);
    void extractPrn(vector<string> &prnList,const string &strLine);

};

#endif // OBSBLOCK_H
