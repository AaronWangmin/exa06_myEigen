#ifndef SSP_H
#define SSP_H

#include "gpshead.h"
#include "epochrecordFactory.h"
#include "broadcast.h"
#include "positionsat.h"
#include "coefficientb.h"
#include "weightobservation.h"
#include "adjustparameter.h"

class SSP
{
public:
    SSP();

    SSP(Vector4d              &posClockRec0,
        const epochRecord_t   &epochRecord,
        const Broadcast       &brdc);

private:

    void BL(Matrix<double,Dynamic,4>    &B,
            VectorXd                    &L,
            const Vector4d              &posClockRec0,
            const epochRecord_t         &epochRecord,
            const Broadcast             &brdc);

    int oneBL(RowVector4d       &b,
              double            &oneL,
              const double      tr,
              const string      prn,
              const double      pd,
              const Broadcast   &brdc,
              const Vector4d    &posClockRec0);

};

#endif // SSP_H
