#include "ssp.h"

SSP::SSP()
{

}

SSP::SSP(Vector4d &posRec0,const EpochRecord &epochRecord, const Broadcast &brdc)
{
    while(1){
        MatrixXd B;
        MatrixXd L;
        oneBL(B,L,epochRecord,brdc,posRec0);

        CoefficientB coeB(B,L,posRec0);
        WeightObservation w(epochRecord.getCountSat());

        AdjustParameter adjust(coeB,w);
        posRec0 = adjust.getX();
        if((adjust.getx().head(3)).cwiseAbs().maxCoeff() <= 1){
            adjust.printResult();
            break;
        }

    }

//    cout << "B:" << endl << B <<endl;
//    cout << "L:" << endl << L <<endl;
}
/**
 * @brief SSP::oneBL
 * @param B             O, 误差方程系数，4列（X,X,X,1）
 * @param L             O, 误差议程常数项，1列
 * @param epochRecord   I
 * @param brdc          I
 * @param posClockRec0  I, 接收机的坐标、及钟差，初始值为 0.
 */
void SSP::oneBL(MatrixXd &B,MatrixXd &L,const EpochRecord &epochRecord,const Broadcast &brdc,const Vector4d &posClockRec0)
{    


    const vector<satObsValue_t> &satObsList =  epochRecord.getSatObsValueList();

    // 第 i颗卫星，误差方差系数、及常数项的计算
    int iSat = 0;
    B.resize(epochRecord.getCountSat(),4);
    L.resize(epochRecord.getCountSat(),1);

    vector<satObsValue_t>::const_iterator it;
    for(it = satObsList.begin();it != satObsList.end();it++){
        satObsValue_t satObsValue;                              // a satellite observation list process.
        satObsValue = *it;

        double sp = 0.075;                                            // the time of light spend, = 22500/c
        while(1){
            double tr = epochRecord.getEpoch() + posClockRec0(3)/C ;  // the moment of receiver observation.
            double ts = tr - sp;

            int prn = std::stoi((satObsValue.prn).substr(1,2));

            PositionSat posat;
            posat.calculateFromBroadcast(ts,prn,brdc);
            double delta_ts = posat.getDeltaTs();

            Vector3d temp = posClockRec0.head(3) - posat.getPositionSat();
            double d = sqrt((temp.array().square()).matrix().sum());
            double sp2 = d/C;
            if(abs(sp2-sp) <= 1E-11){
                RowVector4d b;
                b << (temp/d).transpose(),1;                // 误差方程系统 b 的计算(一个卫星)
                B.row(iSat) = b;

                double pd = satObsValue.obsValue.at(0);     // pd value process.
                double oneL = pd - d + delta_ts * C;        // 误差方程常数项 L 的计算(一个卫星)
                L(iSat) = oneL;

                iSat++;

                break;
            }
            sp = sp2;
        }
    }
}
