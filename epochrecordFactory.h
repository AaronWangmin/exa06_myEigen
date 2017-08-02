#ifndef EPOCHRECORDFACTORY_H
#define EPOCHRECORDFACTORY_H

#include "gpshead.h"

/**
 * @brief The EpochRecord class
 *
 * ? better name: ephoch record
 */
class EpochRecordFactory
{
public:
    EpochRecordFactory();
    EpochRecordFactory(const EpochRecordFactory &rhs);
    EpochRecordFactory& operator=(const EpochRecordFactory &rhs);

    const epochRecord_t&            getEpochRecord()        const;
    void                            setEpochRecord()        const;

    void    parseHeader(const vector<string> &strBlock);
    void    parseBody(const vector<string> &strLine,int linesObsValue);


private:
    epochRecord_t epochRecord;

    void assigment(const EpochRecordFactory &rhs);
    void extractPrn(vector<string> &prnList,const string &strLine);

    void parseOneSatObs(vector<double> &oneSatObs,const vector<string> &strBlock);
    void parseOneLineObs(vector<double> &obsLine,const string &strLine);

};

#endif // OBSBLOCK_H
