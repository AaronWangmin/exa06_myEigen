#ifndef OBSBLOCK_H
#define OBSBLOCK_H

#include "gpshead.h"

/**
 * @brief The ObsBlock class
 *
 * ? better name: ephoch record
 */
class ObsBlock
{
public:
    ObsBlock();
    ObsBlock(const ObsBlock &rhs);
    ObsBlock& operator=(const ObsBlock &rhs);

private:
    double ephoch;
    int flagEphoc;
    int countSat;
    vector<string> prnList;
    double clockOffsetRev;
    vector<obsat_t> ephochObs;

    void assigment(const ObsBlock &rhs);

    void parseEphochRecordHeader(const string &strLine);

};

#endif // OBSBLOCK_H
