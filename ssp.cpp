#include "ssp.h"

SSP::SSP()
{

}

SSP::SSP(Vector4d &posRec0,const epochRecord_t &epochRecord, const Broadcast &brdc)
{
    if(0 != epochRecord.flagEpoch){
        cout << " the epoch record is not available !" << endl;
        return;
    }

    while(1){
        Matrix<double,Dynamic,4> B;
        VectorXd L;
        BL(B,L,posRec0,epochRecord,brdc);

        CoefficientB coeB(B,L,posRec0);
        WeightObservation w(B.rows());

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
void SSP::BL(Matrix<double,Dynamic,4> &B,VectorXd &L,
             const Vector4d &posClockRec0,
             const epochRecord_t &epochRecord,const Broadcast &brdc)
{
    const vector<satObsValue_t> &satObsList =  epochRecord.gpsSatObsList;     // 一组 gps 观测值的处理

    // 第 i颗卫星，误差方差系数、及常数项的计算
    vector<RowVector4d> vB;
    vector<double> vL;

    vector<satObsValue_t>::const_iterator it;
    for(it = satObsList.begin();it != satObsList.end();it++){
        double tr = epochRecord.epoch + posClockRec0(3)/C ;      // the moment of receiver observation.
        RowVector4d b;
        double oneL;

        // 如果 oneBL 计算的结果有效，进行如下操作
        if(0 == oneBL(b, oneL, tr, (*it).prn, (*it).obsValue.at(0), brdc,posClockRec0)){
            vB.push_back(b);
            vL.push_back(oneL);
        }
    }

    B.resize(vL.size(),4);
    L.resize(vL.size(),1);
    for(unsigned int i = 0; i < vL.size(); i++){
        B.row(i) = vB.at(i);
        L(i) = vL.at(i);
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
    PositionSat posat;
    int         iPrn = std::stoi(prn.substr(1,2));

    if( -1 == posat.fromBroadcast(tr,iPrn,brdc,posClockRec0)) return -1;

    Vector3d temp = posClockRec0.head(3) - posat.getPositionSat();
    double d = distance2Points(posClockRec0.head(3),posat.getPositionSat());
    b << (temp/d).transpose(),1;             // 误差方程系统 b 的计算(一个伪距观测值)

    oneL = pd - d + posat.getDeltaTs() * C;

    return 0;
}
