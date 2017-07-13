#include "ssp.h"

SSP::SSP()
{

}

SSP::SSP(Vector4d &posRec0,const EpochRecord &epochRecord, const Broadcast &brdc)
{
    while(1){
        MatrixXd B;
        MatrixXd L;
        BL(B,L,posRec0,epochRecord,brdc);

        CoefficientB coeB(B,L,posRec0);
        WeightObservation w(epochRecord.getGPSObsList().size());

        AdjustParameter adjust(coeB,w);
        posRec0 = adjust.getX();
        if((adjust.getx().head(3)).cwiseAbs().maxCoeff() <= 0.001 &&
           (adjust.getx().tail(1)).cwiseAbs().maxCoeff() <= C * (1E-7)){
        //    adjust.printResult();
            break;
        }
    }
}
/**
 * @brief SSP::BL
 *
 * 一个观测历元的所有伪距的误差方程系数的计算。
 *
 * @param B             O, 误差方程系数，4列（X,X,X,1）
 * @param L             O, 误差议程常数项，1列
 * @param posClockRec0  I, 接收机的坐标、及钟差，初始值为 0.
 * @param epochRecord   I
 * @param brdc          I
 *
 */
void SSP::BL(MatrixXd &B,MatrixXd &L,
             const Vector4d &posClockRec0,
             const EpochRecord &epochRecord,const Broadcast &brdc)
{
    const vector<satObsValue_t> &satObsList =  epochRecord.getGPSObsList();     // 一组 gps 观测值的处理

    // 第 i颗卫星，误差方差系数、及常数项的计算
    int index = 0;
    B.resize(satObsList.size(),4);
    L.resize(satObsList.size(),1);

    vector<satObsValue_t>::const_iterator it;
    for(it = satObsList.begin();it != satObsList.end();it++){
        double tr = epochRecord.getEpoch() + posClockRec0(3)/C ;      // the moment of receiver observation.
        RowVector4d b;
        double oneL;

        // 如果 oneBL 计算的结果有效，进行如下操作
        if(0 == oneBL(b, oneL, tr, (*it).prn, (*it).obsValue.at(0), brdc,posClockRec0)){
            B.row(index) = b;
            L(index) = oneL;
            ++index;
        }
    }
}

/**
 * @brief SSP::oneBL
 *
 * 一个伪距观测值 的误差方程系数的计算。
 *
 * @param b             O
 * @param oneL          O
 * @param tr            I
 * @param prn           I
 * @param pd            I
 * @param brdc          I
 * @param posClockRec0  I
 * @return 0:ok, -1:false
 */
int SSP::oneBL(RowVector4d &b,double &oneL,
                   const double tr, const string prn,const double pd,
                   const Broadcast &brdc,const Vector4d &posClockRec0)
{
    double sp = 0.075;
    while(1){
        double  ts = tr - sp;
        int     iPrn = std::stoi(prn.substr(1,2));

        PositionSat posat;
        posat.calculateFromBroadcast(ts,iPrn,brdc);
        if(!posat.getUsable()){                // 如果卫星位置不可用，无法计算 b oneL,退出函数。
            return -1;
        }

        Vector3d temp = posClockRec0.head(3) - posat.getPositionSat();
        double d = sqrt((temp.array().square()).matrix().sum());
        double sp2 = d/C;
        if(abs(sp2-sp) <= 1E-11){
            b << (temp/d).transpose(),1;             // 误差方程系统 b 的计算(一个伪距观测值)

//            oneL = pd - d - posClockRec0(3);         // 误差方程常数项 L 的计算(一个伪距观测值)
            oneL = pd - d + posat.getDeltaTs() * C;

            return 0;
        }
        sp = sp2;
    }
}
