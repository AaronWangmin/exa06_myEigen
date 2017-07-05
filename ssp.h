#ifndef SSP_H
#define SSP_H

#include "epochrecord.h"
#include "broadcast.h"
#include "positionsat.h"

class SSP
{
public:
    SSP();
    SSP(const EpochRecord &epochRecord,const Broadcast &brdc);

private:
    void oneBL(const EpochRecord &epochRecord,const Broadcast &brdc, Vector3d posRec0);
};

#endif // SSP_H
