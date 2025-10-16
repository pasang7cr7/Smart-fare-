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

     Card(string id, string nm, string type, double bal, string exp)
        : cardID(id), name(nm), cardType(type), balance(bal), expiryDate(exp) {}

        Card() : balance(0.0)
        {

        }

        //function tro display card details

        void display()
        {
         cout<<endl;   
            cout << "Card Details:\n";
        cout << "Card ID: " << cardID << endl;         // Prints card ID
        cout << "Name: " << name << endl;              // Prints cardholder's name
        cout << "Type: " << cardType << endl;          // Prints card type
        cout << "Balance: " << balance << endl;        // Prints card balance
        cout << "Expiry: " << expiryDate << endl;    
        }
};

void registerCard(); // Declare the function so main.cpp knows about it
void startride();
void topupCard();


#endif
