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

    const   Vector3d& getPositionSat()  const;
    double  getDeltaTs()                const;
    bool    getUsable()                 const;

    int     fromBroadcast(double           timeRec,
                          int              prn,
                          const            Broadcast& brdc,
                          const Vector4d   &posClockRec0);

private:
    Vector3d    positionSat;
    double      delta_ts;            // 卫星钟差
    bool        usable;

    int calculateFromBroadcast(double timeSat,int prn,const Broadcast& brdc);

    int searchClosestEph(eph_t& eph,
                           double timeSat,int prn,const Broadcast& brdc) const;

    void assignment(const PositionSat &rhs);
};

#endif // POSITIONSAT_H
