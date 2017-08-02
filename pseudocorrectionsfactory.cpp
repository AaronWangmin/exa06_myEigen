#include "pseudocorrectionsfactory.h"

PseudoCorrectionsFactory::PseudoCorrectionsFactory()
    :epochTime(0)
{

}

/**
 * @brief PseudoCorrectionsFactory::correctionsFrom
 *
 * 以历元为单元，计算伪改正数
 *
 * @param epochRecord
 * @param posClockRec0
 * @param brdc
 */
void PseudoCorrectionsFactory::correctionsFrom(const epochRecord_t &epochRecord,
                                               const Vector4d      &posClockRec0,
                                               const Broadcast     &brdc)
{

    const vector<satObsValue_t>& gpsObsList = epochRecord.gpsSatObsList;
    vector<satObsValue_t>::const_iterator it;

    for(it = gpsObsList.begin(); it != gpsObsList.end(); it++){
        pseudoCorretions_t deltaPseu;
        deltaPseu.epochTime = epochRecord.epoch;
        deltaPseu.prn       = (*it).prn;

        double timeRec = epochRecord.epoch;
        int        prn = std::stoi((*it).prn.substr(1,2));
        PositionSat posat;
        posat.fromBroadcast(timeRec,prn,brdc,posClockRec0);
        double distance = distance2Points(posat.getPositionSat(),posClockRec0.head(3));

        deltaPseu.value = distance - (*it).obsValue.at(0);
        pseudoCorretionsList.push_back(deltaPseu);
    }
}

const vector<pseudoCorretions_t>& PseudoCorrectionsFactory::listPseudoCorrections() const
{
    return pseudoCorretionsList;
}

