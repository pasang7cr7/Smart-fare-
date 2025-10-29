#include "admin.h"
#include "card.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>


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
    system("cls");
    int choice;
    while(true){
        
        cout<<"\n-----ADMIN PANEL-----"<<endl;
        cout<<"1. View all Cards\n2. Search Card by Id\n3. View all Ride\n4. Update Card Balance\n5. Remove/Block Card\n6. Unblock Card\n7. Exit Admin Panel\nEnter choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
        //View all Cards
        viewAllCards();
        break;
        case 2:
        //Search Card by ID
        cardDetails();
        break;
        case 3:
        //View all Ride
        viewAllRideHistory();
        break;
        case 4:
        //Update card Balance
        rechargeCardByAdmin();
        break;
        case 5:
        //Remove or block card
        blockCard();
        break;
        case 6:
        //unblock
        unBlockCard();

        break;
        case 7:
        //exit admin panel;
        cout<<"Admin Panel Terminated! going back to main menu!\n";
        system("cls");
        return;
        

        
        default:
            cout<<"Invalid choice";
            return;
        }

    }
}

void viewAllCards()
{
    ifstream readfrom("card.csv");
    if(!readfrom)
    {
        cout<<"\nNO Cards Found! \n";
        return;
    }

            string line;
        bool found = false;
        Card currentCard;

    // Find the card
         cout<<"\n==================================="<<endl;
         cout<<"||       CARD DETAILS            ||"<<endl;
         cout<<"==================================="<<endl;
    while(getline(readfrom, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry,status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');


        Card c(id, name, type, atof(balanceStr.c_str()), expiry, status);

        c.display();
    }




    readfrom.close();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

}

void rechargeCardByAdmin()
{
    string searchID;
    cout << "\nEnter card ID: ";
    cin >> searchID;

    ifstream searchfrom("card.csv");
    if(!searchfrom)
    {
        cout << "Error opening file." << endl;
        return;
    }

    ofstream temp("temp.csv");

    string line;
    bool found = false;
    Card currentCard;

    while(getline(searchfrom, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');

        double balance = atof(balanceStr.c_str());

        if(id == searchID)
        {
            currentCard = Card(id, name, type, balance, expiry);
            found = true;

            cout << "\nCard found. Details:" << endl << endl;
            currentCard.display();
            cout << endl;

            double amt;
            cout << "Enter amount to topUP: ";
            cin >> amt;

             currentCard.balance += amt;
             cout << "Top-up successful! ";
             cout << "New Balance: " << currentCard.balance << endl;



            // Write the updated card to temp
            temp << currentCard.cardID << "," << currentCard.name << ","
                 << currentCard.cardType << "," << currentCard.balance << ","
                 << currentCard.expiryDate <<"," <<currentCard.status<<endl;
        }
        else
        {
            // Write the original line for non-matching cards
            temp << line << "\n";
        }
    }

    temp.close();
    searchfrom.close();

    remove("card.csv");
    rename("temp.csv", "card.csv");

    if(!found)
    {
        cout << "Card ID not found." << endl;
        return;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void blockCard()
{
    string idBlock;
    cout<<"Enter Id to Block: ";
    cin>>idBlock;

    ifstream readfrom("card.csv");
    ofstream temp("temp.csv");
    string line;
    bool found = false;

    while(getline(readfrom,line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');

        if(getline(ss, status, ','))
        status = "active";

        if(id==idBlock)
        {
            status = "blocked";
            found = true;
        }

        temp<<id<<","<<name<<","<<type<<","<<balanceStr<<","<<expiry<<","<<status<<endl;

    }
    readfrom.close();
    temp.close();
    remove("card.csv");
    rename("temp.csv", "card.csv");

    if(found)
    {
        cout<<"Card Blocked!";

    }
    else{
        cout<<"Card ID not found!";
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

}
void unBlockCard()
{
    string idBlock;
    cout<<"Enter Id to UnBlock: ";
    cin>>idBlock;

    ifstream readfrom("card.csv");
    ofstream temp("temp.csv");
    string line;
    bool found = false;

    while(getline(readfrom,line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');

        if(getline(ss, status, ','))
        status = "active";

        if(id==idBlock)
        {
            status = "active";
            found = true;
        }

        temp<<id<<","<<name<<","<<type<<","<<balanceStr<<","<<expiry<<","<<status<<endl;

    }
    readfrom.close();
    temp.close();
    remove("card.csv");
    rename("temp.csv", "card.csv");

    if(found)
    {
        cout<<"Card UNBlocked!";

    }
    else{
        cout<<"Card ID not found!";
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

}

void viewAllRideHistory()
{
    ifstream fin("Ride_History.csv");

    if(!fin)
    {
        cout<<"NO rides found!";
        return;
    }

    cout<<"\n==================================="<<endl;
         cout<<"||       RIDE HISTORY            ||"<<endl;
         cout<<"==================================="<<endl;

            string line;
            bool found = false;

         while(getline(fin,line))
         {
            stringstream ss(line);
        string id, name, type, balanceStr, expiry, status,startStop,endStop,fareStr,date,time;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, startStop, ',');
        getline(ss, endStop, ',');
        getline(ss, fareStr, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        
                    cout << "Card ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Type: " << type << endl;
            cout << "Route: " << startStop << " -> " << endStop << endl;
            cout << "Fare: Rs. " << fareStr << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "===================================" << endl;
         }

         fin.close();

         cout<<"\nPress Enter to continue....";
         cin.ignore();
         cin.get();
    
}