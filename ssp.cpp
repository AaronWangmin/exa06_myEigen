#include "ssp.h"

SSP::SSP()
{

}

SSP::SSP(const EpochRecord &epochRecord, const Broadcast &brdc)
{

}

void SSP::oneBL(const EpochRecord &epochRecord,const Broadcast &brdc, Vector3d posRec0)
{
    double tr = epochRecord.getEpoch();     // the moment of receiver observation
    double sp = 0.075;                      // the spended time, = 22500/c
    double ts = tr - sp;


    posRec0 << 0,0,0;


    PositionSat posat;
//    posat.calculateFromBroadcast(ts,


}

//const eph_t& SSP::usableEpoch(double timeRec,const string prn, const Broadcast &brdc)
//{
//    vector<eph_t>::const_iterator it;
//    for(it = brdc.getEphRecord().begin();it != brdc.getEphRecord().end();it++){
//        int satID = static_cast<int>( prn.substr(1,2));
//        if(satID == (*it).prn && abs(timeRec - (*it).toe ) <= 3600){        // maybe error! toe? toc?
//            return *it;
//        }
//    }
//}

