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

    eph_t getEph(double givenTime) const;       // added...


private:
    vector<eph_t> ephRecord;    // ? vector default initialization ?

    void parseNavHead(const string &strline);   // only one(gps week) now. added...

};

#endif // BROADCAST_H
