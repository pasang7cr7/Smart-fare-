#ifndef UTILS_H
#define UTILS_H

#include<string>

using namespace std;

bool isNumber(const string& str );  //for valid number input

bool isValidCardType(const string& type); //for valid card type

//double calculateFare(const string& cardType, double distance); //fare calculation based on card type and distance   

double calculateFare(const string& cardType, int distance); //fare calculation based on card type and distance

void saveRideHistory(const string& cardID, const string& name, const string& cardType , const string& startStop, const string& endStop, double fare );

void viewRideHistory(const string& cardID);

#endif


