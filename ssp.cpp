#include "ssp.h"

SSP::SSP()
{

}

SSP::SSP(const EpochRecord &epochRecord, const Broadcast &brdc,Vector3d posRec0)
{
    oneBL(epochRecord,brdc,posRec0);
}

void SSP::oneBL(const EpochRecord &epochRecord,const Broadcast &brdc, Vector3d posRec0)
{
    double tr = epochRecord.getEpoch();     // the moment of receiver observation
    double sp = 0.075;                      // the time of light spend, = 22500/c

    const vector<satObsValue_t> &satObsList =  epochRecord.getSatObsValueList();
//    Matrix<double,epochRecord.getCountSat(),4> B;
//    Matrix<double,epochRecord.getCountSat(),1> l;

    vector<satObsValue_t>::const_iterator it;
    for(it = satObsList.begin();it != satObsList.end();it++){
        satObsValue_t satObsValue;                              // a satellite observation process.
        satObsValue = *it;

        RowVector4d b;
        double l;
        while(1){
            double ts = tr - sp;

            int prn = std::stoi((satObsValue.prn).substr(1,2));

            PositionSat posat;
            posat.calculateFromBroadcast(ts,prn,brdc);
            double delta_ts = posat.getDeltaTs();

            Vector3d temp = posRec0 - posat.getPositionSat();
            double d = sqrt((temp.array().square()).matrix().sum());
            double sp2 = d/C;
            if(abs(sp2-sp) <= 1E-11){
                b << (temp/d).transpose(),1;

                double pd = satObsValue.obsValue.at(0);     // pd value process.
                l = pd - d + delta_ts * C;

                break;
            }
            sp = sp2;
        }
    }
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

