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

    double                          getEpoch()              const;
    int                             getCountSat()           const;
    const vector<string>&           getPrnList()            const;
    const vector<satObsValue_t>&    getSatObsValueList()    const;
    const vector<satObsValue_t>&    getGPSObsList()         const;
    const vector<satObsValue_t>&    getGlonassObsList()     const;

    void    parseHeader(const vector<string> &strBlock);
    void    parseBody(const vector<string> &strLine,int linesObsValue);

private:
    double                  epoch;                // ? The member should be a struct?
    int                     flagEpoch;
    int                     countSat;
    vector<string>          prnList;              // edit! seperat G and num(G 02).
    double                  clockOffsetRev;
    vector<satObsValue_t>   satObsValueList;

    vector<satObsValue_t>   gpsSatObsList;
    vector<satObsValue_t>   glonassSatObsList;

    void assigment(const EpochRecord &rhs);
    void extractPrn(vector<string> &prnList,const string &strLine);

    void parseOneSatObs(vector<double> &oneSatObs,const vector<string> &strBlock);
    void parseOneLineObs(vector<double> &obsLine,const string &strLine);

};

#endif // OBSBLOCK_H
