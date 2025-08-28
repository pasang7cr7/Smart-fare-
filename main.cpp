#include<iostream>


using namespace std;

int main()
{
    cout<<"-----------------------------------"<<endl;
    cout<<"|   Welcome to Smart Fare system   |"<<endl;
    cout<<"-----------------------------------"<<endl;

    int choice;

    

    while(1)
    {
        cout << "1. Register Card\n2. Top-up Card\n3. Start Ride\n4. Show Card Ride History\n5. Admin Panel\n6. Exit\nChoice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                // Register Card
                break;
            case 2:
                // Top-up Card
                break;
            case 3:
                // Start Ride
                break;
            case 4:
                // Show Card Ride History
                break;
            case 5:
                // Admin Panel
                break;
            case 6:
                cout << "Thank you for using the Smart Card System!\n";
                return 0;
            default:
                cout<<"Invalid choice! Please try again."<<endl;
           
        }
         
    }

    return 0;
}