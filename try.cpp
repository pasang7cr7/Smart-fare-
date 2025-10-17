#include<iostream>
#include<cctype>

using namespace std;

int main()
{
char input;
string password;
while(true)
{
    cout<<"Enter Password: ";
    cin>>password;

    if(password == "213")
    {
        cout<<"correct Password";
        
    }
    else
    {
        cout<<"Do you want to try again?\nEnter Y or N: ";
        cin>>input;
        input = toupper(input);
        if(input == 'Y')
        {
            cout<<"ok try again!";
        }
        
        else if(input == 'N')
        {
            cout<<"exiting progrma! ";
            return 0;
        }
    }

}
cin.get();
return 0;
}
