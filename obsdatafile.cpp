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

        while(!fs.eof()){       // parse the Obs data bady.

            EpochRecord epochRec;
            for(int i = 0; i < epochRec.getCountPrnLines(); i++){       // parse the epoch record header
                getline(fs,strline);
                epochRec.parseHeader(strline);
            }

            vector<string> strBlock;                    // extract one epoch record from n lines.
            for(int i = 0; i < epochRec.getCountSat() * obsHeader.calculateLinesObsValue(); i++){
                getline(fs,strline);
                strBlock.push_back(strline);
            }

            epochRec.parseBody(strBlock,obsHeader.calculateLinesObsValue());

            obsDataRecord.push_back(epochRec);           // added a epoch record  to a vector.
        }

        fs.close();
    }

}

