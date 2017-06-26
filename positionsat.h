#ifndef POSITIONSAT_H
#define POSITIONSAT_H

#include "gpshead.h"
#include "broadcast.h"


class PositionSat
{
public:
    PositionSat();

    void calculateFromBroadcast(double givenTime, const Broadcast& brdc);

    const Vector3d& getPositionSat() const;

private:

    Vector3d positionSat;

    eph_t& searchClosestEph(double givenTime, const Broadcast& brdc) const;
    // ?  int searchClosestEph(eph_t& eph,double givenTime, const Broadcast& brdc) const; // 0:ok, -1:false
};

#endif // POSITIONSAT_H
