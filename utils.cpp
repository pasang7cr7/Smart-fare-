#include "utils.h"
#include "card.h"
#include<iostream>
#include <string>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include "time.h"


using namespace std;

bool  isNumber(const string& str )
{
    if(str.empty()) return false;

    int point = 0;

    for(size_t i = 0; i < str.length(); ++i)
    {
        char c = str[i];
        if(c == '.')
        {
            point++;
            if(point > 1) return false;

        }
        else if(!isdigit(c))
        {
            return false;
        }
    }

    return true;
}






double calculateFare(const string& cardType, int distance)
{
    if (distance <= 0)
    {
        cout << "Invalid distance entered.\n";
        return 0;
    }

    cout << "Number of stops: " << distance << endl;

    double farePerStop = 5.0; // Rs. 5 per stop
    double baseFare = distance * farePerStop;
    double finalFare = baseFare;

    // Apply discounts
    if (cardType == "student")
    {
        finalFare = baseFare * 0.5; // 50% discount
    }
    else if (cardType == "Elder Citizen" || cardType == "elder citizen")
    {
        finalFare = baseFare * 0.3; // 70% discount (30% pay)
    }

    cout << "Your fare is: Rs. " << finalFare << endl;
    return finalFare;
}

void saveRideHistory(const string& cardID, const string& name, const string& cardType , const string& startStop, const string& endStop, double fare )
{
    ofstream writeto("Ride_History.csv", ios::app);
    if(!writeto)
    {
        cout<<"Unable to opem file! ";
        return;
    }

    string dateTime = dateWithTime();

    writeto<<cardID<<","<<name<<","<<cardType<<","<<startStop<<","<<endStop<< 
    ","<<fare<<","<<dateTime<<endl;

    writeto.close();
    cout<<"Ride History saved! ";

}

void viewRideHistory(const string& cardID)
{
    ifstream readfrom("Ride_History.csv");
    if(!readfrom)
    {
        cout<<"Unable to open file! ";
        return;
    }
    string line;
    bool found = false;
    cout<<"\n------Ride History for Card ID: "<<cardID<<"------\n";

    while(getline(readfrom, line))
    {
        stringstream ss(line);
        string id, name, type, startStop, endStop, farestr, date,time;

        getline(ss, id , ',');
        getline(ss, name , ',');
        getline(ss, startStop , ',');
        getline(ss, endStop, ',');
        getline(ss, farestr, ',');
        getline(ss,date, ',');
        getline(ss,time, ',');

        if(id == cardID)
        {
            found = true;
            cout<< "Ride: "<<startStop<<" -> "<<endStop<<", Fare: Rs. "<<farestr << ", Date: "<<date<<time<<endl;
        }



    }
     if(!found)
        {
            cout<<"No ride for this card found! "<<endl;

        }
        readfrom.close();
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

}
