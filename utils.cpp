#include "utils.h"
#include "card.h"
#include<iostream>
#include <string>
#include<vector>
#include<cmath>


using namespace std;

bool  isNumber(const string& str )
{
    if(str.empty()) return false;

    int point = 0;

    for(char c : str)
    {
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

// bool isValidCardType(const string & type)
// {
//     string lowertype = type;
//     transform(lowertype.begin(), lowertype.end(), lowertype.begin(), ::tolower);

//     return (lowertype == "normal" || lowertype == "student" || lowertype == "senior");
// }



double calculateFare(const string& cardType, const string& start, const string& end)
{
    vector<string> stops = {
        "kalanki",
        "balkhu",
        "Ekantakuna",
        "Satdobato",
        "Gwarko",
        "Koteshwor",
        "tinkune",
        "Sinamangal",
        "Gaushala",
        "Chabahil",
        "Sukedhara",
        "Maharajgunj",
        "balaju"
    };
    int startindex = -1;
    int endindex = -1;

    for(int i=0; i<stops.size(); i++)
    {
        if(stops[i] == start)
        {
            startindex = i;
        }
        if(stops[i] == end)
        {
            endindex = i;
        }
    }

    if(startindex == -1 || endindex == -1 || startindex >= endindex)
    {
        cout << "Invalid start or end stop." << endl;
        return 0; // Indicate an error
    }
    int numStops = abs(endindex - startindex);

    cout<<"Number of stops: "<<numStops<<endl;

    double farePerStop = 5.0;
    double baseFare = numStops * farePerStop;
    double finalFare = baseFare;

   

    if(cardType == "student")
    {
        finalFare = baseFare * 0.5;
    }
    else if(cardType == "elder citizen")
    {
        finalFare = baseFare * 0.3;
    }

    cout<<"your fare is: "<<finalFare<<endl;
    return finalFare;
}


