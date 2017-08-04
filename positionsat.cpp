#include "positionsat.h"

PositionSat::PositionSat()
    :delta_ts(0),
     usable(1)
{

}

PositionSat::PositionSat(const PositionSat &rhs)
{
    assignment(rhs);
}

PositionSat& PositionSat::operator = (const PositionSat &rhs)
{
    assignment(rhs);
    return *this;
}



const Vector3d& PositionSat::getPositionSat() const
{
    return positionSat;
}

double PositionSat::getDeltaTs() const
{
    return delta_ts;
}

bool PositionSat::getUsable() const
{
    return usable;
}

/**
 * @brief PositionSat::fromBroadcast
 *
 * 计算卫星的位置：以接收机的时间为参考
 *
 * @param timeRec
 * @param prn
 * @param brdc
 * @return
 */
int PositionSat::fromBroadcast(double           timeRec,
                               int              prn,
                               const            Broadcast& brdc,
                               const Vector4d   &posClockRec0)
{
    double sp = 0.075;
    while(1){
        double  ts = timeRec + posClockRec0(3)/C - sp;
        if( -1 == calculateFromBroadcast(ts,prn,brdc)) return -1;       // 若计算失败，函数返回；

        double d = distance2Points(posClockRec0.head(3) ,positionSat);
        double sp2 = d/C;
        if(abs(sp2-sp) <= 1E-11){
            return 0;
        }
        sp = sp2;
    }
}

/**
 * @brief PositionSat::calculateFromBroadcast
 *
 *  计算卫星的位置：以卫星的时间为参考；
 *
 *  卫星位置计算时，toe 以 GPS秒为参考进行计算；
 *
 *
 * @param timeSat
 * @param prn
 * @param brdc
 */
int PositionSat::calculateFromBroadcast(double timeSat,int prn,const Broadcast &brdc)
{
    eph_t eph;
    if(0 != searchClosestEph(eph,timeSat,prn,brdc)){
       usable = false;
       return -1;
    }

    // transfer the double to gpst(week, seconds)
    gtime_t tSat((int)timeSat,timeSat - (int)timeSat );
    int weekSat;
    double secondsSat = time2gpst(tSat, weekSat);   

    // 计算卫星发射时刻与参考时刻的差,以GPS秒进行计算
    double tk =  secondsSat - eph.toe;
    if     (tk >  302400)     tk = 302400 - 604800;
    else if(tk < -302400)     tk = 302400 + 604800;
    else                      tk = tk;

    // 计算卫星平近点角 Mk
    double A  = pow(eph.sqrtA,2);       // 卫星轨道长半轴
    double n0 = sqrt(GM/ pow(A,3));     // 计算平角速度
    double n  = n0 + eph.Deln;          // 改正平角速度
    double Mk = eph.M0 + n *tk;         // 平近点角

    // 迭代法计算偏近角点 Ek,最后取值为 vEk.back()    
    vector<double> vEk;
    vEk.push_back(Mk);
    while(1){
        vEk.push_back(Mk + eph.e * sin(vEk.back()));
        double the2th = *(vEk.end()-2);     // 获得倒数第二个元素
        if( abs(the2th - vEk.back()) < 1.0E-12)    break;
    }
    double Ek = vEk.back();

    // 真近角点
    double cos_vk = (cos(Ek) - eph.e) /(1 - eph.e *cos(Ek));
    double sin_vk = sqrt(1 - pow(eph.e,2)) *sin(Ek) /(1 - eph.e *cos(Ek));
    double vk     = atan2(sin_vk,cos_vk);

    // 计算纬度参数, （升交距角）
    double fk = vk + eph.omg;

    // 周期改正项
    double delta_uk = eph.Cus * sin(2*fk) + eph.Cuc * cos(2*fk);
    double delta_rk = eph.Crs * sin(2*fk) + eph.Crc * cos(2*fk);
    double delta_ik = eph.Cis * sin(2*fk) + eph.Cic * cos(2*fk);

    double uk = fk + delta_uk;
    double rk = A *( 1 - eph.e*cos(Ek) ) + delta_rk;
    double ik = eph.i0 + delta_ik;

    // 计算卫星在其轨道面内的坐标
    double xk = rk * cos(uk);
    double yk = rk * sin(uk);
    double zk = 0;

    //
    double OMEGA_K = eph.OMG0 + ( eph.OMGd - OMEGA_E ) * tk - OMEGA_E * eph.toe;

    // 计算卫星在ECEF(WGS84)下的坐标
    double Xk = xk * cos(OMEGA_K) - yk * cos(ik) *sin(OMEGA_K);
    double Yk = xk * sin(OMEGA_K) + yk * cos(ik) *cos(OMEGA_K);
    double Zk = yk * sin(ik);

    positionSat << Xk,Yk,Zk;

    // gps clock diff
    delta_ts = eph.af0 +
               eph.af1 *(secondsSat - eph.toe) +
               eph.af2 *pow((secondsSat - eph.toe),2) +
               F * eph.e * eph.sqrtA * sin(Ek) - eph.tgd;     // 相对论效应改正

    return 0;
}

/**
 * @brief PositionSat::searchClosestEph
 * @param eph           O       eph_t
 * @param timeSat       I       double
 * @param brdc          I       Broadcast
 * @return 0:ok, -1:false
 */
int PositionSat::searchClosestEph(eph_t& eph,
                                  double timeSat,int prn,const Broadcast &brdc) const
{
    const vector<eph_t> &ephRecord = brdc.getEphRecord();
    for(int i = 0; i < ephRecord.size(); i++){
        const eph_t &ephTemp = ephRecord.at(i);
        if(prn == ephTemp.prn && abs(timeSat - ephTemp.toc) <= 3600)
        {
            eph = ephTemp;
            return 0;
        }
    }

    cout << " sat prn: " << prn << " no eph !" << endl;
    return -1;
}

void PositionSat::assignment(const PositionSat &rhs)
{
    this->positionSat    = rhs.positionSat;
    this->delta_ts       = rhs.delta_ts;
    this->usable         = rhs.usable;
}

