#include "obsdatafile.h"

#include <fstream>

ObsDataFile::ObsDataFile()
{

}

const vector<EpochRecord>& ObsDataFile::getObsDataRecord() const
{
    return obsDataRecord;
}

void ObsDataFile::fromObsFile(const string &obsFile)
{
    fstream fs(obsFile);
    if(!fs)  { cout << obsFile << " opening failed! " << endl;}

    else{
        vector<string> strBlock;
        string strline;

        // extract the Obs header.
        while(!fs.eof()){
            getline(fs,strline);
            strBlock.push_back(strline);

            if( string::npos != strline.substr(60).find("END OF HEADER")) break; // end of header
        }

        ObsHeader obsHeader;
        obsHeader.parseObsHeader(strBlock);

        // parse the Obs data bady.
        while(!fs.eof()){

            //extract a header of one epoch record
            strBlock.clear();

            getline(fs,strline);
            strBlock.push_back(strline);

            int countSat = extractDouble(strline,29,3);
            for(int i = 1; i < calculateLinesPrn(countSat); i++){
                getline(fs,strline);
                strBlock.push_back(strline);
            }

            EpochRecord epochRec;
            epochRec.parseHeader(strBlock);

            //extract a body of one epoch record
            strBlock.clear();
            for(int i = 0; i < countSat * obsHeader.calculateLinesObsValue(); i++){
                getline(fs,strline);
                strBlock.push_back(strline);
            }

            epochRec.parseBody(strBlock,obsHeader.calculateLinesObsValue());

            obsDataRecord.push_back(epochRec);           // added a epoch record  to a vector.
        }

        fs.close();
    }
}

int ObsDataFile::calculateLinesPrn(int countSat) const
{
    if                       (12 >= countSat)   return 1;

    else if(12 <  countSat && 24 >= countSat)   return 2;

    else{
        cout << " the count of sat more than 24! " << endl;
    }
}

