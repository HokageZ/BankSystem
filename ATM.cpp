#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Header.h"

using namespace std;
using namespace Header;

void PrintATMMenu()
{
	DisplayHeader("ATM Main Menu");
    cout << Tabs(1) << "[1] Quick Withdraw." << endl;
    cout << Tabs(1) << "[2] Normal Withdraw." << endl;
    cout << Tabs(1) << "[3] Deposit." << endl;
    cout << Tabs(1) << "[4] Check Balance." << endl;
    cout << Tabs(1) << "[5] Logout." << endl;
    cout << "********************************" << endl;
}

short LoginReturnIndex(vector <stClient> vClients)
{
    stClient InputClient;
    stClient CorrectClient;
    bool DoesClientExist;
    do
    {
        cout << "input Account Number: ";
        cin >> InputClient.AccountNumber;
        cout << "input Password: ";
        cin >> InputClient.Password;

        DoesClientExist = FindByAccountNumber(InputClient.AccountNumber, CorrectClient, vClients);

        if (!DoesClientExist || (InputClient.Password != CorrectClient.Password))
            cout << "Invalid User Name or Password\n\n";
        else
        {
            for (short i = 0; i < vClients.size(); i++) {
                if (vClients[i].AccountNumber == CorrectClient.AccountNumber && vClients[i].Password == CorrectClient.Password)
                    return i;
            }
        }
    } while (!DoesClientExist || (InputClient.Password != CorrectClient.Password));
}

void CheckBalance(stClient CurrentClient)
{
    DisplayHeader("Check Baalance Screen");
	cout << "Your Balance Is: " << CurrentClient.BalanceAmount << endl << endl;
}

bool IsMultipleOf5(int Number)
{
    return Number % 5 == 0;
}

void ATMDeposit(vector <stClient>& vClients, stClient CurrentClient)
{
    double Amount;
    DisplayHeader("Deposit Screen");
    Amount = ReadPositiveNumbers("Pls input Deposit amount: ");

    if (ReadYesOrNo("\nAre u sure u want to perform this Transaction? (y/n): "))
    {
        AddToBalance(vClients, CurrentClient.AccountNumber, Amount);
        SaveClientsFromVector(vClients, gClientsFile);
        cout << "\nBalance Added successfully, New Balance = " << CurrentClient.BalanceAmount + Amount << endl;
    }
}

void NormalWithdraw(vector <stClient> &vClients, stClient CurrentClient)
{
    double Amount;
    DisplayHeader("Normal Withdraw Screen");
    do
    {
        Amount = ReadPositiveNumbers("Pls input a multiple of 5 Withdraw amount: ");
    } while (!IsMultipleOf5(int(Amount)));

    if (ReadYesOrNo("\nAre u sure u want to perform this Transaction? (y/n): "))
    {
        AddToBalance(vClients, CurrentClient.AccountNumber, Amount * -1);
        SaveClientsFromVector(vClients, gClientsFile);
        cout << "\nBalance Withdrew successfully, New Balance = " << CurrentClient.BalanceAmount - Amount << endl;
    }
}

void DisplayQuickWithdrawMenu(int choices[],short NumOfChoices)
{
    for (short i = 1; i <= NumOfChoices; i++)
    {

        if (i % 2 != 0)
        {
            cout << setw(5) << "[" << i << "]" << choices[i - 1];

            if (i == NumOfChoices)
                cout << setw(10) << "[" << i + 1 << "]" << "EXIT" << endl;
        }
        else
        {
            cout << setw(11) << "[" << i << "]" << choices[i - 1] << endl;

            if (i == NumOfChoices)
                cout << setw(5) << "[" << i + 1 << "]" << "EXIT" << endl;
        }
    }
    cout << "********************************" << endl;
}

void QuickWithdraw(vector <stClient>& vClients, stClient CurrentClient, int choices[], short NumOfChoices)
{
    double Amount = 0;
    DisplayHeader("Quick Withdraw Screen");
    DisplayQuickWithdrawMenu(choices, NumOfChoices);
    cout << "Your Balance Is: " << CurrentClient.BalanceAmount << endl;
    short choice = GetChoice("Choose what do you want to do [1 to 9]?", 1, 9);
    
    switch (choice)
    {
    case 1:
        Amount = choices[0];
        break;
    case 2:
        Amount = choices[1];
        break;
    case 3:
        Amount = choices[2];
        break;
    case 4:
        Amount = choices[3];
        break;
    case 5:
        Amount = choices[4];
        break;
    case 6:
        Amount = choices[5];
        break;
    case 7:
        Amount = choices[6];
        break;
    case 8:
        Amount = choices[7];
        break;
    case 9:
        return;
    }

    if (ReadYesOrNo("\nAre u sure u want to perform this Transaction? (y/n): "))
    {
        AddToBalance(vClients, CurrentClient.AccountNumber, Amount * -1);
        SaveClientsFromVector(vClients, gClientsFile);
        cout << "\nBalance Withdrew successfully, New Balance = " << CurrentClient.BalanceAmount - Amount << endl;
    }

}

int main()
{
    vector <stClient> vClients = LoadClientsFromFile(gClientsFile);
    int QuickWithdrawChoices[] = { 20,50,100,200,400,600,800,1000 };
    short QuickWithdrawChoicesLength = 8;
    while (true)
    {
        system("cls");

        short CurrentClientIndex = LoginReturnIndex(vClients);
        bool LoggedIn = true;

        while (LoggedIn)
        {
            vClients = LoadClientsFromFile(gClientsFile);
			stClient CurrentClient = vClients[CurrentClientIndex];
            system("cls");
            PrintATMMenu();

            int choice = GetChoice("Choose what do you want to do [1 to 5]?", 1, 5);
            switch (choice) {
            case 1:
                system("cls");
                QuickWithdraw(vClients, CurrentClient, QuickWithdrawChoices, QuickWithdrawChoicesLength);
                WaitForKeyPress();
                break;
            case 2:
                system("cls");
                NormalWithdraw(vClients, CurrentClient);
                WaitForKeyPress();
                break;
            case 3:
                system("cls");
                ATMDeposit(vClients, CurrentClient);
                WaitForKeyPress();
                break;
            case 4:
                system("cls");
                CheckBalance(CurrentClient);
                WaitForKeyPress();
                break;
            case 5:
                system("cls");
                cout << "Logging Out. Goodbye! \n\n";
                LoggedIn = false;
                WaitForKeyPress();
                break;
            }
        }
    }
}