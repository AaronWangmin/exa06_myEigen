#ifndef PSEUDOCORRECTIONSFACTORY_H
#define PSEUDOCORRECTIONSFACTORY_H

#include "gpshead.h"
#include "epochrecordFactory.h"
#include "broadcast.h"
#include "positionsat.h"


class PseudoCorrectionsFactory
{
public:
    PseudoCorrectionsFactory();

    void correctionsFrom(const epochRecord_t &epochRecord,
                         const Vector4d      &posClockRec0,
                         const Broadcast     &brdc);

    const vector<pseudoCorretions_t>& listPseudoCorrections() const;

private:
    double                     epochTime;
    vector<pseudoCorretions_t> pseudoCorretionsList;

};

#endif // PSEUDOCORRECTIONSFACTORY_H
