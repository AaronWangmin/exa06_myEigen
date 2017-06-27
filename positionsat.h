#ifndef POSITIONSAT_H
#define POSITIONSAT_H

#include "gpshead.h"
#include "broadcast.h"


class PositionSat
{
public:
    PositionSat();

    void calculateFromBroadcast(int prn,double givenTime, const Broadcast& brdc);

    const Vector3d& getPositionSat() const;

private:

    Vector3d positionSat;

    eph_t searchClosestEph(int prn,double givenTime, const Broadcast& brdc) const;  // ? return eph_t&(local variable)
    // ?  int searchClosestEph(eph_t& eph,double givenTime, const Broadcast& brdc) const; // 0:ok, -1:false
};

#endif // POSITIONSAT_H
