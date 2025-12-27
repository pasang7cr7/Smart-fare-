
#include "card.h"
#include "utils.h"
#include "admin.h"
#include<iostream>
#include<fstream>
#include <cstdlib>
#include "time.h"
#include<string>
#include <cstdio> // Add this at the top for sscanf and sprintf
#include<sstream>
#include<vector>
#include<limits>
#include <windows.h>

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
    if(name.empty()) {
        cout << "Name cannot be empty. Registration failed.\n";
        return;
    }

     cout << "\n==================================="<<endl;
     cout << "Select card type:"<<endl;
     cout << "1. Normal"<<endl;
     cout << "2. Student"<<endl;
     cout << "3. Elder Citizen"<<endl;
     cout << "==================================="<<endl;
     cout << "Enter your choice (1-3): ";
    while (!(cin >> choicecard) || choicecard < 1 || choicecard > 3) {
        cout << "Invalid input. Please enter a number between 1 and 3: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

     if(choicecard == 1)
     {
        cardType = "normal";
     }
     else if(choicecard == 2)
    {
        string codeInput;
        cout<<"Enter your student code (must start with 'kac' followed by roll number): ";
        cin>>codeInput;

        if(codeInput.substr(0,3) == "kac" && codeInput.length() > 3)
        {
            cardType = "student";
            cout << "Student validation successful." << endl;
        }
        else
        {
          cout << "\nInvalid student code. Must start with 'kac'. Registration failed.\n";
            return;
         }

    }
    else if(choicecard == 3)
    {
        cout<<"Enter your age: ";
        while (!(cin >> age) || age < 0) {
            cout << "Invalid age. Please enter a positive number: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if(age >=60)
        {
            cardType = "elder citizen";
            cout<<"\nAge validation successful."<<endl;
        }
        else
        {
            cout<<"\nAge must be 60 or above for Elder Citizen card. Registration failed.\n";
            return;
        }
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
            // Check if card is expired and update status
            string cardStatus = status;
            if(isCardExpired(expiry))
            {
                cardStatus = "expired";
            }
            else
            {
                cardStatus = "active";
            }
            currentCard = Card(id, name, type, stod(balanceStr), expiry, cardStatus);
            found = true;

            if(currentCard.status == "expired")
            {
                cout<<"Your card has expired! Please renew your card."<<endl;
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

    // Check balance before proceeding
    if(currentCard.balance == 0)
    {
        cout << "You have zero balance. Cannot start ride. Please recharge first!" << endl;
        return;
    }
    else if(currentCard.balance < 100)
    {
        cout << "Warning: You are running out of balance. Please top-up soon." << endl;
    }

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
    cout<<"\nEnter starting stop (1-" << stops.size() << "): ";
    while (!(cin >> startind) || startind < 1 || startind > stops.size()) {
        cout << "Invalid input. Please enter a number between 1 and " << stops.size() << ": ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    cout<<"Enter ending stop (1-" << stops.size() << "): ";
    while (!(cin >> endind) || endind < 1 || endind > stops.size()) {
        cout << "Invalid input. Please enter a number between 1 and " << stops.size() << ": ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

 if(currentCard.balance < fare)
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

    // Loading screen with buffer time
    system("cls");
    printf("Ride started!\n");
    Sleep(2000);
    system("cls");
    printf("Travelling...\n");
    Sleep(3000);
    system("cls");
    printf("After few minutes...\n");
    Sleep(2000);
    system("cls");
    printf("Ride completed!\n");
    Sleep(1000);

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
            temp << id << "," << name << "," << type << "," << balance << "," << expiry << "," << status << "\n";
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
            // Check if card is expired and update status
            string cardStatus = status;
            if(isCardExpired(expiry))
            {
                cardStatus = "expired";
            }
            else
            {
                cardStatus = "active";
            }
            currentCard = Card(id, name, type, balance, expiry, cardStatus);
            found = true;

            cout << "\nCard found. Details:" << endl << endl;
            currentCard.display();
            cout << endl;

            // Expired cards can topup

            double amt;
            cout << "Enter amount to topUP: ";
            cin >> amt;

            
            char ch;
            while(true)
            {
                
            string password = getPassword();

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

    ofstream temp("temp.csv");

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

        double balance = stod(balanceStr);

        if(id == searchID)
        {
            // Check if card is expired and update status
            string cardStatus = status;
            if(isCardExpired(expiry))
            {
                cardStatus = "expired";
            }
            else
            {
                cardStatus = "active";
            }
            currentCard = Card(id, name, type, balance, expiry, cardStatus);
            found = true;

            // Write the updated card to temp if status changed
            if(cardStatus != status)
            {
                temp << currentCard.cardID << "," << currentCard.name << ","
                     << currentCard.cardType << "," << currentCard.balance << ","
                     << currentCard.expiryDate << "," << currentCard.status << endl;
            }
            else
            {
                temp << line << "\n";
            }
        }
        else
        {
            temp << line << "\n";
        }
    }
    fin.close();
    temp.close();

    if(!found)
    {
        cout << "Card ID not found." << endl;
        remove("temp.csv");
        return;
    }

    // Replace the file if status was updated
    if(currentCard.status == "expired")
    {
        remove("card.csv");
        rename("temp.csv", "card.csv");
    }
    else
    {
        remove("temp.csv");
    }

    cout << "\nCard found." << endl;
    currentCard.display();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void renewCard(bool isAdmin = false)
{
    string searchID;
    cout << "\nEnter your card ID to renew: ";
    cin >> searchID;

    ifstream fin("card.csv");
    if(!fin)
    {
        cout << "Error opening file." << endl;
        return;
    }

    ofstream temp("temp.csv");

    string line;
    bool found = false;
    Card currentCard;

    while(getline(fin, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');

        double balance = stod(balanceStr);

        if(id == searchID)
        {
            currentCard = Card(id, name, type, balance, expiry, status);
            found = true;

            cout << "\nCard found. Details:" << endl << endl;
            currentCard.display();
            cout << endl;

            double renewalFee = 100.0;
            if(!isAdmin && currentCard.balance < renewalFee)
            {
                cout << "Insufficient balance! Renewal fee is Rs. " << renewalFee << ". Please top-up your card." << endl;
                temp << line << "\n";
                continue;
            }

            if(!isAdmin)
            {
                // Deduct renewal fee for clients
                currentCard.balance -= renewalFee;
            }

            // Calculate new expiry date (add 1 year)
            string currentDate = getcurrentdate();
            int year, month, day;
            sscanf(currentDate.c_str(), "%d-%d-%d", &year, &month, &day);
            year += 1;
            char newExpiry[11];
            sprintf(newExpiry, "%04d-%02d-%02d", year, month, day);
            currentCard.expiryDate = newExpiry;

            // Reset status to active upon renewal
            currentCard.status = "active";

            if(isAdmin)
            {
                cout << "Card renewed successfully by admin! New expiry date: " << currentCard.expiryDate << endl;
            }
            else
            {
                cout << "Card renewed successfully! Rs. " << renewalFee << " deducted. New expiry date: " << currentCard.expiryDate << ". Remaining balance: Rs. " << currentCard.balance << endl;
            }

            // Write the updated card to temp
            temp << currentCard.cardID << "," << currentCard.name << ","
                 << currentCard.cardType << "," << currentCard.balance << ","
                 << currentCard.expiryDate << "," << currentCard.status << endl;
        }
        else
        {
            // Write the original line for non-matching cards
            temp << line << "\n";
        }
    }

    temp.close();
    fin.close();

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

void manipulateExpiry()
{
    string searchID;
    cout << "\nEnter your card ID to manipulate expiry: ";
    cin >> searchID;

    ifstream fin("card.csv");
    if(!fin)
    {
        cout << "Error opening file." << endl;
        return;
    }

    ofstream temp("temp.csv");

    string line;
    bool found = false;
    Card currentCard;

    while(getline(fin, line))
    {
        stringstream ss(line);
        string id, name, type, balanceStr, expiry, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, balanceStr, ',');
        getline(ss, expiry, ',');
        getline(ss, status, ',');

        double balance = stod(balanceStr);

        if(id == searchID)
        {
            currentCard = Card(id, name, type, balance, expiry, status);
            found = true;

            cout << "\nCard found. Details:" << endl << endl;
            currentCard.display();
            cout << endl;

            cout << "Enter new expiry date (YYYY-MM-DD): ";
            string newExpiry;
            cin >> newExpiry;

            // Validate date format (strict check)
            if(newExpiry.length() != 10 || newExpiry[4] != '-' || newExpiry[7] != '-')
            {
                cout << "Invalid date format! Use YYYY-MM-DD." << endl;
                temp << line << "\n";
                continue;
            }

            // Check if all parts are digits and valid
            string yearStr = newExpiry.substr(0,4);
            string monthStr = newExpiry.substr(5,2);
            string dayStr = newExpiry.substr(8,2);
            if(!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr))
            {
                cout << "Invalid date! Year, month, and day must be numbers." << endl;
                temp << line << "\n";
                continue;
            }

            int year = atoi(yearStr.c_str());
            int month = atoi(monthStr.c_str());
            int day = atoi(dayStr.c_str());

            if(month < 1 || month > 12 || day < 1 || day > 31)
            {
                cout << "Invalid date! Month must be 01-12, day 01-31." << endl;
                temp << line << "\n";
                continue;
            }

            // Check if new expiry is not in the past
            string currentDate = getcurrentdate();
            if(newExpiry < currentDate)
            {
                cout << "Expiry date cannot be in the past!" << endl;
                temp << line << "\n";
                continue;
            }

            currentCard.expiryDate = newExpiry;

            // Update status based on new expiry date
            if(isCardExpired(newExpiry))
            {
                currentCard.status = "expired";
            }
            else
            {
                currentCard.status = "active";
            }

            cout << "Expiry date updated successfully! New expiry date: " << currentCard.expiryDate << endl;

            // Write the updated card to temp
            temp << currentCard.cardID << "," << currentCard.name << ","
                 << currentCard.cardType << "," << currentCard.balance << ","
                 << currentCard.expiryDate << "," << currentCard.status << endl;
        }
        else
        {
            // Write the original line for non-matching cards
            temp << line << "\n";
        }
    }

    temp.close();
    fin.close();

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


