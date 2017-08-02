#include "dgps.h"

DGPS::DGPS()
{

}

DGPS::DGPS(Vector4d                           &posClockRec0,
           epochRecord_t                      &epochRecord,
           const vector<pseudoCorretions_t>   &pseudoCorretionsList,
           const Broadcast                    &brdc)
{
    vector<satObsValue_t>& gpsObsList = epochRecord.gpsSatObsList;
    vector<satObsValue_t>::iterator it;

    for(it = gpsObsList.begin(); it != gpsObsList.end(); it++){

        vector<pseudoCorretions_t>::const_iterator it_pseuCorr;

        for(it_pseuCorr = pseudoCorretionsList.begin();
            it_pseuCorr != pseudoCorretionsList.end(); it_pseuCorr++){

            if( (*it).prn == (*it_pseuCorr).prn ){      // 计算 并更新伪距
                double newPseudo = (*it).obsValue.at(0) - (*it_pseuCorr).value;
                (*it).obsValue.at(0) = newPseudo;
            }
        }

        //add...         如果在伪距改正值列表中没有找到这颗卫星，则删除这个卫星


    }

    SSP ssp(posClockRec0,epochRecord,brdc);
    cout << "dgps..." << endl;
    cout << posClockRec0 << endl << endl;

}