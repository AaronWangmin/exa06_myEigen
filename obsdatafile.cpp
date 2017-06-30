#include "obsdatafile.h"

#include <fstream>

ObsDataFile::ObsDataFile()
{

}

void ObsDataFile::fromObsFile(const string &obsFile)
{
    fstream fs(obsFile);
    if(!fs)  { cout << obsFile << " opening failed! " << endl;}

    else{
        string strline;
        while(!fs.eof()){                                // parse the Obs header.
            getline(fs,strline);
            if( -1 == obsHeader.parseObsHeader(strline)) break; // end of header
        }

        int countLineObsValue = 1;       // computer the line count of Observation value by observation types.
        if(5 >= obsHeader.getCountObsTypes()){

        }
        if(5 <  obsHeader.getCountObsTypes() && 10 >= obsHeader.getCountObsTypes()){
            countLineObsValue = 2;
        }
        if(10 <  obsHeader.getCountObsTypes()){
            cout << " the count of observation types more than 10! " << endl;
        }


        while(!fs.eof()){
            getline(fs,strline);
            EpochRecord *epochRec = new EpochRecord;
            if(0 == epochRec->getPrnContinue()){
               epochRec->parseHeader(strline);
            }
                         // parse the 1th line of the header of epoch record.

            if(1 == epochRec->getPrnContinue()){        // parse the 2th line of the header of epoch record.
               epochRec->parseHeader(strline);
               epochRec->setPrnContinue(0);

            }

            if(0 == epochRec->getPrnContinue()){          // have finished to read the header of epoch record,
                                                         // extract one ephoch record from N lines.
               vector<string> strecord;
               for(int i = 0; i < epochRec->getCountSat() *countLineObsValue; i++){
                   getline(fs,strline);
                   strecord.push_back(strline);
               }


            }

            delete epochRec;


//            for(int i = 0; i < 8; i++){
//                getline(fs,strline);
//                strEph.push_back(strline);
//            }
/*            eph_t eph;
            parseNavData(strEph,eph);                    // parse the Nav data record.
            ephRecord.push_back(eph);  */                  // added a Nav data record to a vector.
        }

        fs.close();
    }

}

