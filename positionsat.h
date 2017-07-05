#ifndef POSITIONSAT_H
#define POSITIONSAT_H

#include "gpshead.h"
#include "broadcast.h"


class PositionSat
{
public:
    PositionSat();
    PositionSat(const PositionSat &rhs);
    PositionSat& operator= (const PositionSat &rhs);

    void calculateFromBroadcast(double timeSat,int prn,const Broadcast& brdc);

    const Vector3d& getPositionSat() const;

private:

    Vector3d positionSat;
    double delta_ts;

    eph_t searchClosestEph(double timeSat,int prn,const Broadcast& brdc) const;  // ? return eph_t&(local variable)
    // ?  int searchClosestEph(eph_t& eph,double timeSat, const Broadcast& brdc) const; // 0:ok, -1:false

    void assignment(const PositionSat &rhs);
};

#endif // POSITIONSAT_H
