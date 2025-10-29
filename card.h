#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<string>

using namespace std;

class Card{
    public:
    string cardID;
    string name;
    string cardType;
    double balance;
    string expiryDate;
    string status;

     Card(string id, string nm, string type, double bal, string exp, string st = "active")
        : cardID(id), name(nm), cardType(type), balance(bal), expiryDate(exp), status(st)  {}

        Card() : balance(0.0), status("active")
        {
                
        }

        //function to display card details

        void display()
        {
         cout<<endl;
         
        cout << "Card ID: " << cardID << endl;         // Prints card ID
        cout << "Name: " << name << endl;              // Prints cardholder's name
        cout << "Type: " << cardType << endl;          // Prints card type
        cout << "Balance: Rs. " << balance << endl;        // Prints card balance
        cout << "Expiry: " << expiryDate << endl;
        cout << "Status: " << status << endl;
        cout<<"==================================="<<endl;
        }

        
};

void registerCard(); // Declare the function so main.cpp knows about it
void startride();
void topupCard();
void cardDetails();


#endif
