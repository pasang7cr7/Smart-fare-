#include<ctime>
#include<string>
#include<iostream>
using namespace std;

std:: string getcurrentdate()
{
   
    time_t now = std::time(0);
    tm* ltm = std::localtime(&now);
    char datestr[11];
    sprintf(datestr,"%04d-%02d-%02d",1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday); 

    cout<<datestr<<endl;
    return std::string(datestr);
}