#include "card.h"
#include "utils.h"
#include<iostream>
#include<fstream>
#include <cstdlib>
#include "time.h"
#include<string>
#include <cstdio> // Add this at the top for sscanf and sprintf
#include<sstream>
#include<vector>

using namespace std;


//funtion to create id
int getNextCard()
{
    ifstream fin("card.txt");
    string line, lastId = "2082000";
    while(getline(fin, line))
    {
        size_t pos = line.find(',');
        if(pos != string::npos)
        {
            lastId = line.substr(0, pos);
        }
    }

    fin.close();
   
   return atoi(lastId.c_str()) + 1; 
}



//function to register new card

void registerCard()
{
    string name, cardType, expiryDate;
    double balance;
    int choicecard, age =0;
    int cardID = getNextCard();

    cout <<"\nEnter name: ";
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    getline(cin, name);

     cout << "\nSelect card type:\n1. Normal\n2. Student\n3. Elder Citizen\nChoice: ";
     cin >> choicecard;

     if(choicecard == 1)
     {
        cardType = "normal";
     }
     else if(choicecard == 2)
    {
        string codeInput;
        cout<<"Enter your student code: ";
        cin>>codeInput;

        if(codeInput.substr(0,3) == "kac" && codeInput.length() > 3)
        {
            cardType = "student";
            cout << "Student validation successful." << endl;
        }
        else
        {
          cout << "\nInvalid student keyword or roll number. Registration failed.\n";
            return;
         }

    }
    else if(choicecard == 3)
    {
        cout<<"Enter your age: ";
        cin>>age;

        if(age >=60)
        {
            cardType = "Ender Citizen";
            cout<<"\nAge validation successful."<<endl;
        }
        else
        {
            cout<<"\nAge must be 60 or above for Elder Citizen card. Registration failed.\n";
            return;
        }
    }
    else{
        cout<<"\nInvalid card type choice. Registration failed.\n";
        return;
    }

    
    // expiry date calculation
    string regDate = getcurrentdate(); // e.g., "2025-10-11"

    // Extract year, month, day using sscanf
    int year, month, day;
    sscanf(regDate.c_str(), "%d-%d-%d", &year, &month, &day);

    // Add one year for expiry
    year += 1;

    // Build expiry date string using sprintf
    char expiryStr[11];
    sprintf(expiryStr, "%04d-%02d-%02d", year, month, day);
    expiryDate = expiryStr;


    // Convert cardID to string using sprintf
    char cardIDstr[10];
    sprintf(cardIDstr, "%d", cardID);

    // Create Card object with collected details
    Card newCard(cardIDstr, name, cardType, balance, expiryDate);

     // Save card details to file
    ofstream fout("card.txt", ios::app); // Opens file in append mode
    fout << newCard.cardID << "," << newCard.name << "," << newCard.cardType << "," << newCard.balance << "," << newCard.expiryDate << endl;
    fout.close(); // Closes the file

    cout << "\nCard registered successfully!\n"; // Success message
    newCard.display(); // Show card details
}

void startride()
{
    string searchID;
    cout<<"\nEnter your card ID: ";
    cin>>searchID;

    ifstream searchfrom("card.txt");
    if(!searchfrom)
    {
        cout<<"Error opening file."<<endl;
        return;
    }

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

        if(id == searchID)
    {
        currentCard = Card(id, name,type ,stod(balanceStr), expiry);
        found = true;
        break;
    }
    }
    searchfrom.close();

    if(!found)
    {
        cout<<"Card ID not found."<<endl;
        return;
    }

    cout<<"\nCard found. Details:"<<endl<<endl;
    currentCard.display();
    cout<<endl;


    //now start ride process

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
    
    cout<<"Available stops:\n";
    for(int i = 0; i<stops.size();i++)
    {
        cout<<i+1<<" "<<stops[i]<<endl;


    }

    int startind, endind;
    cout<<"\n Enter starting point: ";
    cin>>startind;

    

    cout<<"\n Enter ending stop: ";
    cin>>endind;

    if(startind<1 || endind<1 || startind > stops.size() || endind > stops.size())
    {
        cout<<"\nInvalid starting or ending stops! ";
        return;
    }

    string startStop = stops[startind-1];
    string endStop = stops[endind-1];

    double fare = calculateFare(currentCard.cardType, startStop, endStop);

    if(currentCard.balance<fare || currentCard.balance == 0)
    {
        cout<<"\nYou dont have sufficient balance! Please recharge first! ";
        return;
    }

    if(fare = 0)
    {
        cout<<"\n Invalid ride details, ride cancelled! \n";
        return;
    }
    cout<<"\n Fare for this ride is: Rs, "<<fare<<endl;
}


void topupCard()
{
     string searchID;
    cout<<"\nEnter your card ID: ";
    cin>>searchID;

    ifstream searchfrom("card.txt");
    if(!searchfrom)
    {
        cout<<"Error opening file."<<endl;
        return;
    }

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

        if(id == searchID)
    {
        currentCard = Card(id, name,type ,stod(balanceStr), expiry);
        found = true;
        break;
    }
    }
    searchfrom.close();

    if(!found)
    {
        cout<<"Card ID not found."<<endl;
        return;
    }

    cout<<"\nCard found. Details:"<<endl<<endl;
    currentCard.display();
    cout<<endl;

    double amt;

    cout<<"Enter amount to topUP: ";
    cin>>amt;

    

}