#ifndef DGPS_H
#define DGPS_H

#include "ssp.h"
#include "pseudocorrectionsfactory.h"

class DGPS
{
public:
    DGPS();
    DGPS(Vector4d                           &posClockRec0,
         epochRecord_t                      &epochRecord,
         const vector<pseudoCorretions_t>   &pseudoCorretionsList,
         const Broadcast                    &brdc);
};

#endif // DGPS_H
