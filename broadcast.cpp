#include "broadcast.h"

#include <iostream>
#include <fstream>
using namespace std;

Broadcast::Broadcast(const string &navFile)
{
   fstream fs(navFile);
   if(!fs)  { cout << navFile << " opening failed! " << endl;}

   else{
       while(!fs.eof()){
           string strline;
           getline(fs,strline);
           parseNavHead(strline);

       }

       fs.close();
   }
}

void Broadcast::parseNavHead(const string &strline)
{
    string lable = strline.substr(60);

    if(string::npos != lable.find("DELTA-UTC: A0,A1,T,W")) cout << " gps week" << endl;

    if(string::npos != lable.find("END OF HEADER")) cout << " reached the end of navigation header !" << endl;

  //      "DELTA-UTC: A0,A1,T,W":







}
