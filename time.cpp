#include<ctime>
#include<string>
#include<iostream>
using namespace std;

string getcurrentdate()
{
   
    time_t now = std::time(0);
    tm* ltm = std::localtime(&now);
    char datestr[11];
    sprintf(datestr,"%04d-%02d-%02d",1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday); 

    cout<<datestr<<endl;
    return std::string(datestr);
}

string dateWithTime()
{
      time_t now = std::time(0);
    tm* ltm = localtime(&now);
    char datestr[20];
    sprintf(datestr,"%04d-%02d-%02d, %02d:%02d:%02d",1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec); 

    cout<<datestr<<endl;
    return string(datestr);
}