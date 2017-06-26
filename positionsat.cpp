#include "positionsat.h"

PositionSat::PositionSat()
{

}



const Vector3d& PositionSat::getPositionSat() const
{
    return positionSat;
}

void PositionSat::calculateFromBroadcast(double givenTime, const Broadcast &brdc)
{
    eph_t eph(searchClosestEph(givenTime,brdc));

    double delta_ts = eph.



}

/**
 * @brief PositionSat::searchClosestEph
 * @param eph           O       eph_t
 * @param givenTime     I       double
 * @param brdc          I       Broadcast
 * @return 0:ok, -1:false
 */
eph_t& PositionSat::searchClosestEph(double givenTime, const Broadcast &brdc) const
{
    vector<eph_t> ephRecord = brdc.getEphRecord();
    for(int i = 0; i < ephRecord.size(); i++){
        double gpst = ephRecord.at(i).toe + ephRecord.at(i).week *7 *24 *3600;
        if(givenTime - gpst > 3600)
        {
            i++;
        }else if(givenTime - gpst <= 3600){
            return ephRecord.at(i);
        }
    }
    cout << " no eph !" << endl;
}


