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

    const   Vector3d& getPositionSat() const;
    double  getDeltaTs() const;
    bool    getUsable() const;

    void calculateFromBroadcast(double timeSat,int prn,const Broadcast& brdc);



private:
    Vector3d    positionSat;
    double      delta_ts;            // 卫星钟差
    bool        usable;

    int searchClosestEph(eph_t& eph,
                           double timeSat,int prn,const Broadcast& brdc) const;

    void assignment(const PositionSat &rhs);
};

#endif // POSITIONSAT_H
