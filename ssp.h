#ifndef SSP_H
#define SSP_H

#include "gpshead.h"
#include "epochrecord.h"
#include "broadcast.h"
#include "positionsat.h"

class SSP
{
public:
    SSP();
    SSP(const EpochRecord &epochRecord,const Broadcast &brdc,Vector3d posRec0);

private:
    void oneBL(const EpochRecord &epochRecord,const Broadcast &brdc, Vector3d posRec0);
};

#endif // SSP_H
