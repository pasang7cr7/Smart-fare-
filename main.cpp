#include<iostream>
#include<string>
#include "TIME.h" // Corrected header file name
#include "card.h"
#include "utils.h"
#include "admin.h"

using namespace std;

int main()
{
    cout<<"==================================="<<endl;
    cout<<"||                               ||"<<endl;
    cout<<"||     SMART FARE SYSTEM         ||"<<endl;
    cout<<"||                               ||"<<endl;
    cout<<"==================================="<<endl;
    cout<<"Welcome to the Smart Fare System!"<<endl;
    cout<<"Your reliable transportation companion."<<endl<<endl;

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
        cin>>choice;

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
               

                case 8:
                {
                    cout << "Current date: " << getcurrentdate() << endl;
                    break;
                }
                case 9:
                {
                    string val;
                    cout<<"Enter a number: ";
                    cin>>val;
                    if(isNumber(val))
                    {
                        cout<<val<<" is a valid number."<<endl;
                    }
                    else
                    {
                        cout<<val<<" is not a valid number."<<endl;
                    }
                    break;
                }
                case 10:
                {
                    cout << "Current date: " << dateWithTime() << endl;
                    break;
                }

            default:
                cout<<"==================================="<<endl;
                cout<<"||     INVALID CHOICE!          ||"<<endl;
                cout<<"==================================="<<endl;
                cout<<"Please select a valid option (1-7)."<<endl;
           
        }
         
    }

    return 0;
}