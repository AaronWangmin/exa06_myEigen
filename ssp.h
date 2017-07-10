#ifndef SSP_H
#define SSP_H

#include "gpshead.h"
#include "epochrecord.h"
#include "broadcast.h"
#include "positionsat.h"
#include "coefficientb.h"
#include "weightobservation.h"
#include "adjustparameter.h"

class SSP
{
public:
    SSP();
    SSP(Vector4d &posClockRec0,const EpochRecord &epochRecord,const Broadcast &brdc);

private:
    void oneBL(MatrixXd &B,MatrixXd &L,const EpochRecord &epochRecord,const Broadcast &brdc,const Vector4d &posClockRec0);
};

#endif // SSP_H
