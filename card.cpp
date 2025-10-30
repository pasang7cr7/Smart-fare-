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
    ifstream fin("card.csv");
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
    string name, cardType, expiryDate,status;
    double balance = 0.0;
    int choicecard, age =0;
    int cardID = getNextCard();

    cout<<"==================================="<<endl;
    cout<<"||     CARD REGISTRATION         ||"<<endl;
    cout<<"==================================="<<endl;
    cout <<"Enter your full name: ";
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    getline(cin, name);

     cout << "\n==================================="<<endl;
     cout << "Select card type:"<<endl;
     cout << "1. Normal"<<endl;
     cout << "2. Student"<<endl;
     cout << "3. Elder Citizen"<<endl;
     cout << "==================================="<<endl;
     cout << "Enter your choice (1-3): ";
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
    ofstream fout("card.csv", ios::app); // Opens file in append mode
    fout << newCard.cardID << "," << newCard.name << "," << newCard.cardType << "," << newCard.balance << "," << newCard.expiryDate <<","<<newCard.status<< endl;
    fout.close(); // Closes the file

    cout << "\n==================================="<<endl;
    cout << "Card registered successfully!"<<endl;
    cout << "==================================="<<endl;
    newCard.display(); // Show card details
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}



void startride()
{
    string searchID;
    cout << "\nEnter your card ID: ";
    cin >> searchID;

    ifstream fin("card.csv");
    if(!fin)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;
    Card currentCard;

    // Find the card
    while(getline(fin, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry,status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');
        

        if(id == searchID)
        {
            currentCard = Card(id, name, type, stod(balanceStr), expiry,status);
            found = true;

            if(currentCard.status == "blocked")
            {
                cout<<"You Can't start ride! Your card is blocked!"<<endl;
                cout<<"Contact to customer care!\nContact: 9841222122\nEmail:Fakecustomercare@pmail.com\n";
                return;
            }

            break;
        }
       
    }
    fin.close();

    if(!found)
    {
        cout << "Card ID not found." << endl;
        return;
    }

    cout << "\nCard found. Details:\n" << endl;
    currentCard.display();
    cout << endl;

    // Stops
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
    cout<<"\nEnter starting stop: ";
    cin>>startind;

    

    cout<<"Enter ending stop: ";
    cin>>endind;

    if(startind<1 || endind<1 || startind > stops.size() || endind > stops.size())
    {
        cout<<"\nInvalid starting or ending stops! ";
        return;
    }

    
    string startStop = stops[startind-1];
    string endStop = stops[endind-1];

   

   
    
int distance = abs(endind - startind);
if(distance == 0)
{
    cout<<"Starting and ending stops can't be same! ";
    return;
}

double fare = calculateFare(currentCard.cardType, distance);

 if(currentCard.balance<fare || currentCard.balance == 0)
    {
        cout<<"\nYou dont have sufficient balance! Please recharge first! \n";
        return;
    }

    if(fare == 0)
    {
        cout<<"\nInvalid ride details, ride cancelled! \n";
        return;
    }

    // Deduct fare
    currentCard.balance -= fare;
    cout << "\nRide started! Rs. " << fare << " deducted. Remaining balance: Rs. " 
         << currentCard.balance << endl;

         saveRideHistory(currentCard.cardID, currentCard.name, currentCard.cardType, startStop, endStop, fare);

    // Update card.txt safely
    ifstream fin2("card.csv");
    ofstream temp("temp.csv");
    string line2;

    while(getline(fin2, line2))
    {
        stringstream ss(line2);
        string id, name, type, balanceStr, expiry,status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');

        double balance = stod(balanceStr);

        if(id == currentCard.cardID)
        {
            temp << currentCard.cardID << "," << currentCard.name << "," 
                 << currentCard.cardType << "," << currentCard.balance << "," 
                 << currentCard.expiryDate <<","<<currentCard.status<<endl;
        }
        else
        {
            temp << id << "," << name << "," << type << "," << balance << "," << expiry << "\n";
        }
    }

    fin2.close();
    temp.close();

    remove("card.csv");
    rename("temp.csv", "card.csv");

    cout << "\nCard updated successfully!\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}


void topupCard()
{
    string searchID;
    cout << "\nEnter your card ID: ";
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
        string id, name, type, balanceStr, expiry,status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');


        double balance = stod(balanceStr);

       

        if(id == searchID)
        {
            currentCard = Card(id, name, type, balance, expiry,status);
            found = true;

            cout << "\nCard found. Details:" << endl << endl;
            currentCard.display();
            cout << endl;

            if(currentCard.status == "blocked")
            {
                cout<<"You Can't topUP! Your card is blocked!"<<endl;
                cout<<"Contact to customer care!\nContact: 9841222122\nEmail:Fakecustomercare@pmail.com\n";
                return;
            }

            double amt;
            cout << "Enter amount to topUP: ";
            cin >> amt;

            string password;
            char ch;
            while(true)
            {
                cout << "\nEnter Password: ";
                cin >> password;

                if(password == "kacbit")
                {
                    currentCard.balance += amt;
                    cout << "Top-up successful! ";
                    cout << "New Balance: " << currentCard.balance << endl;
                    break;
                }
                else
                {
                    cout << "Incorrect password!" << endl;
                    cout<<"Do you want to try again? type Y or N: ";
                    cin>>ch;
                    ch = toupper(ch);
                    if(ch == 'Y')
                    {
                        cout<<"Try again! ";
                    }
                    else if(ch == 'N')
                    {
                        cout<<"\nok!";
                        return;
                    }
                    else{
                        cout<<"\ninvalid selection! ";
                        return;
                    }
                }
            }

            // Write the updated card to temp
            temp << currentCard.cardID << "," << currentCard.name << "," 
                 << currentCard.cardType << "," << currentCard.balance << "," 
                 << currentCard.expiryDate <<","<< currentCard.status<<endl;
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
}

void cardDetails()
{
     string searchID;
    cout << "\nEnter your card ID: ";
    cin >> searchID;

    ifstream fin("card.csv");
    if(!fin)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;
    Card currentCard;

    // Find the card
    while(getline(fin, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry,status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');

        if(id == searchID)
        {
            currentCard = Card(id, name, type, stod(balanceStr), expiry,status);
            found = true;
            break;
        }
    }
    fin.close();

    if(!found)
    {
        cout << "Card ID not found." << endl;
        return;
    }

    cout << "\nCard found." << endl;
    currentCard.display();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}


