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
            ObsHeader obsHeader;
            if( -1 == obsHeader.parseObsHeader(strline)) break;
        }

        while(!fs.eof()){
            vector<string> strEph;                       // extract one ephemeris record from 8 lines.
            for(int i = 0; i < 8; i++){
                getline(fs,strline);
                strEph.push_back(strline);
            }
            eph_t eph;
            parseNavData(strEph,eph);                    // parse the Nav data record.
            ephRecord.push_back(eph);                    // added a Nav data record to a vector.
        }

        fs.close();
    }

}

