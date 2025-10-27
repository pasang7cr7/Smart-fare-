#include "admin.h"
#include "card.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


using namespace std;


bool adminLogin()
{
    string username, password;
    int attempts = 3;

    while(attempts > 0)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if(username == "admin" && password == "admin123")
        {
            cout << "Login Successful!" << endl;
            return true;
        }
        else
        {
            attempts--;
            cout << "Incorrect ID and password! ";
            if(attempts > 0)
            {
                cout << "You have " << attempts << " attempt(s) left." << endl;
            }
            else
            {
                cout << "No attempts left!" << endl;
            }
        }
    }

    return false;
}


void adminMenu()
{
    if(!adminLogin())
    {
        return;
    }
    int choice;
    while(true){
        cout<<"\n-----ADMIN PANEL-----"<<endl;
        cout<<"1. View all Cards\n2. Search Card by Id\n3. View all Ride\n4. Update Card Balance\n5. Remove/Block Card\n6. Exit Admin Panel\nEnter choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
        //View all Cards
        viewAllCards();
        break;
        case 2:
        //Search Card by ID
        break;
        case 3:
        //View all Ride
        break;
        case 4:
        //Update card Balance
        break;
        case 5:
        //Remove or block card
        break;
        case 6:
        //exit admin panel;
        cout<<"Admin Panel Terminated! going back to main menu! ";
        return;
        

        
        default:
            cout<<"Invalid choice";
            return;
        }

    }
}

void viewAllCards()
{
    ifstream readfrom("card.txt");
    if(!readfrom)
    {
        cout<<"Unable to open file! ";
        return;
    }

   string line;
    bool found = false;
    Card currentCard;

    // Find the card
    while(getline(readfrom, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');

        Card c(id, name, type, stod(balanceStr), expiry);
        c.display();
    }
    readfrom.close();
    
}