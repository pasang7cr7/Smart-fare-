#include<iostream>
#include<string>
#include "TIME.h" // Corrected header file name
#include "card.h"
#include "utils.h"
#include "admin.h"

using namespace std;

int main()
{
    cout<<"-----------------------------------"<<endl;
    cout<<"|   Welcome to Smart Fare system   |"<<endl;
    cout<<"-----------------------------------"<<endl;

    int choice;

    

    while(1)
    {
        cout<<endl<<"-----Main Menu-----";
        cout << "\n1. Register Card\n2. Top-up Card\n3. Start Ride\n4. Card Details\n5. Ride History\n6. Admin Panel\n7. Show card details\n8. get time\n9. validation\n\nChoice: ";
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
                cout << "Thank you for using the Smart Card System!\n";
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
                cout<<"Invalid choice! Please try again."<<endl;
           
        }
         
    }

    return 0;
}