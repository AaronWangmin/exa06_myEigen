#ifndef BROADCAST_H
#define BROADCAST_H

/**
 * @brief The Broadcast class
 *
 * Broadcast ephemeris,based on rinex2.11
 *
 */

#include <string>
#include <vector>
using namespace std;

#include "gpshead.h"

class Broadcast
{
public:
//    Broadcast();                              // ? needed ?
    Broadcast(const string &navFile);           // from the rinex file.

    eph_t getEph(double givenTime) const;       // added..., ? return a struct data?


private:
    vector<eph_t> ephRecord;                    // ? vector default initialization ?

    int parseNavHead(const string &strline);   // added...
    void parseNavData(const vector<string> &strEph,
                       eph_t &eph);             // parse one record of the NavData.? return a struct data?

};

#endif // BROADCAST_H
