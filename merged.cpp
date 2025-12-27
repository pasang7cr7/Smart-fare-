#include<iostream>
#include<string>
#include<limits>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstdio>
#include<ctime>

using namespace std;

// Class definition from card.h
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

// Function declarations (from headers)
string getcurrentdate();
string dateWithTime();
bool isNumber(const string& str);
double calculateFare(const string& cardType, int distance);
void saveRideHistory(const string& cardID, const string& name, const string& cardType , const string& startStop, const string& endStop, double fare );
void viewRideHistory(const string& cardID);
void registerCard();
void startride();
void topupCard();
void cardDetails();
bool adminLogin();
void adminMenu();
void viewAllCards();
void viewAllRideHistory();
void rechargeCardByAdmin();
void blockCard();
void unBlockCard();

// Time functions from time.cpp
string getcurrentdate()
{
   
    time_t now = std::time(0);
    tm* ltm = std::localtime(&now);
    char datestr[11];
    sprintf(datestr,"%04d-%02d-%02d",1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday); 

    cout<<datestr<<endl;
    return std::string(datestr);
}

string dateWithTime()
{
      time_t now = std::time(0);
    tm* ltm = localtime(&now);
    char datestr[20];
    sprintf(datestr,"%04d-%02d-%02d, %02d:%02d:%02d",1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec); 

    cout<<datestr<<endl;
    return string(datestr);
}

// Utils functions from utils.cpp
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
      string id, name, type, startStop, endStop, fareStr, dateTime;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, startStop, ',');
        getline(ss, endStop, ',');
        getline(ss, fareStr, ',');
        getline(ss, dateTime, ',');

        if(id == cardID)
        {
            found = true;
            cout<<id<<","<<name<<","<<type<<","<<startStop<<"->"<<endStop<<", Rs:"<<fareStr<<"," <<dateTime<<endl;
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

// Card functions from card.cpp
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

// Admin functions from admin.cpp
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

// Main function from main.cpp
int main()
{
     
    cout<<"==================================="<<endl;
    cout<<"||                               ||"<<endl;
    cout<<"||     SMART FARE SYSTEM         ||"<<endl;
    cout<<"||                               ||"<<endl;
    cout<<"==================================="<<endl;
    cout<<"Welcome to the Smart Fare System!"<<endl;
    cout<<"Your reliable transportation companion."<<endl<<endl;

     cout << "\nPress Enter to continue...";
    cin.ignore();
    

    int choice;

   system("cls");
    while(1)
    {

        cout<<"==================================="<<endl;
        cout<<"||         MAIN MENU             ||"<<endl;
        cout<<"==================================="<<endl;
        cout << "1. Register New Card"<<endl;
        cout << "2. Top-up Card Balance"<<endl;
        cout << "3. Start a Ride"<<endl;
        cout << "4. View Card Details"<<endl;
        cout << "5. View Ride History"<<endl;
        cout << "6. Admin Panel"<<endl;
        cout << "7. Exit System"<<endl;
        cout << "==================================="<<endl;
        cout << "Enter your choice (1-7): ";
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid input. Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch(choice)
        {
            case 1:
                // Register Card
                registerCard();
                break;
            case 2:
                // Top-up Card
                topupCard();
                break;
            case 3:
                // Start Ride
                startride();
                break;
            case 4:
                // Show Card Details
                cardDetails();
                break;
            case 5:
                // Ride History
                {
                    string id;
                cout<<"Enter your card id: ";
                cin>>id;
                viewRideHistory(id);
                break;
                }

            case 6:
                //Admin Panel
                adminMenu();

                break;


                case 7:
                {
                system("cls");
                cout<<"==================================="<<endl;
                cout<<"||                               ||"<<endl;
                cout<<"||     THANK YOU FOR USING       ||"<<endl;
                cout<<"||     SMART FARE SYSTEM         ||"<<endl;
                cout<<"||                               ||"<<endl;
                cout<<"==================================="<<endl;
                cout<<"Goodbye! Have a great day!"<<endl;
                return 0;
                break;
                }


            default:
                // This should not be reached due to validation
                break;

        }
         
    }

    return 0;
}
