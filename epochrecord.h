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

    double  getEpoch() const;
    int     getCountPrnLines() const;
    int     getCountSat() const;
    const   vector<string>& getPrnList() const;

    void    parseHeader(const string &strLine);
    void    parseBody(const vector<string> &strLine,int countLineOneSat);

private:
    double                  epoch;                // ? The member should be a struct?
    int                     flagEpoch;
    int                     countSat;
    vector<string>          prnList;              // edit! seperat G and num(G 02).
    bool                    firstLine;            // Is the first line (prn)?
    int                     countPrnLines;        // the count of  prn lines
    double                  clockOffsetRev;
    vector<satObsValue_t>   satObsValueList;

    void assigment(const EpochRecord &rhs);
    void extractPrn(vector<string> &prnList,const string &strLine);

};

#endif // OBSBLOCK_H
