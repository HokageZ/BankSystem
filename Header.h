#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const string gClientsFile = "Clients.txt";
const string gUsersFile = "Users.txt";

namespace Header {
    struct stClient
    {
        string AccountNumber;
        string Password;
        string PinCode;
        string FullName;
        string PhoneNumber;
        double BalanceAmount = 0;
        bool MarkedForDelete = false;
    };

    struct stUser
    {
        string UserName;
        string Password;
        short Permissions = 0;
        bool MarkedForDelete = false;
    };

    enum ePermissions
    {
        pFullAccess = -1, pShowClientList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32
    };

    int GetChoice(string Message, int from, int to)
    {
        int choice;
        cout << Message << endl;
        do
        {
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Pls Input a Numerical Value!\n";
            }
            else if (choice > to || choice < from)
                cout << "Pls Input a Number between " << from << " and " << to << endl;

        } while (choice > to || choice < from);
        return choice;
    }

    bool ReadYesOrNo(string Message = "")
    {
        char YesOrNo;
        cout << Message;
        cin >> YesOrNo;
        if (tolower(YesOrNo) == 'y')
            return true;
        else
            return false;
    }

    double ReadPositiveNumbers(string Message) {
        double Number = 0;
        do {
            cout << Message;
            cin >> Number;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Pls Input a Numerical Value!\n";
            }
            else if (Number < 0)
                cout << "Pls Input a Positive Value!\n";
        } while (Number < 0);
        return Number;
    }

    string ReadNewAccountNumber(string Message)
    {
        string AccountNumber;
        cout << Message << endl;
        cin >> AccountNumber;
        return AccountNumber;
    }

    string ReadNewUserName(string Message)
    {
        string UserName;
        cout << Message << endl;
        cin >> UserName;
        return UserName;
    }

    bool IsAccountNumberUsed(string AccountNumber, vector<stClient> Clients)
    {
        for (stClient& Client : Clients)
        {
            if (Client.AccountNumber == AccountNumber)
                return true;
        }
        return false;
    }

    bool IsUserNameUsed(string UserName, vector<stUser> vUsers)
    {
        for (stUser& User : vUsers)
        {
            if (User.UserName == UserName)
                return true;
        }
        return false;
    }

    string ReadOldAccountNumber(string Message, vector <stClient> vClients)
    {

        string AccountNumber;
        cout << Message << endl;
        cin >> AccountNumber;
        while (!IsAccountNumberUsed(AccountNumber, vClients))
        {
            cout << "Pls Input An Existing Account Number!\n";
            cin >> AccountNumber;
        }
        return AccountNumber;
    }

    string ReadOldUserName(string Message, vector <stUser> vUsers)
    {

        string UserName;
        cout << Message << endl;
        cin >> UserName;
        while (!IsUserNameUsed(UserName, vUsers))
        {
            cout << "Pls Input An Existing User Name!\n";
            cin >> UserName;
        }
        return UserName;
    }

    string Tabs(int NumOfTabs)
    {
        string Tabs = "";
        for (int i = 0; i < NumOfTabs; i++)
            Tabs += "    ";
        return Tabs;
    }

    void DisplayHeader(string HeaderText)
    {
        cout << "********************************" << endl;
        cout << Tabs(2) << HeaderText << endl;
        cout << "********************************" << endl;
    }

    void DisplayMainMenu()
    {
        DisplayHeader("Main Screen");
        cout << Tabs(1) << "[1] Show Clients List." << endl;
        cout << Tabs(1) << "[2] Add New Client." << endl;
        cout << Tabs(1) << "[3] Delete Client." << endl;
        cout << Tabs(1) << "[4] Update Client Info." << endl;
        cout << Tabs(1) << "[5] Find Client." << endl;
        cout << Tabs(1) << "[6] Transactions." << endl;
        cout << Tabs(1) << "[7] Manage Users." << endl;
        cout << Tabs(1) << "[8] Logout." << endl;
        cout << "********************************" << endl;
    }

    void DisplayTransMenu()
    {
        DisplayHeader("Transactions Screen");
        cout << Tabs(1) << "[1] Deposit." << endl;
        cout << Tabs(1) << "[2] Withdraw." << endl;
        cout << Tabs(1) << "[3] Total Balances." << endl;
        cout << Tabs(1) << "[4] Back to Main Screen." << endl;
        cout << "********************************" << endl;
    }

    void DisplayManageUsersMenu()
    {
        DisplayHeader("Users Screen");
        cout << Tabs(1) << "[1] List Users." << endl;
        cout << Tabs(1) << "[2] Add New User." << endl;
        cout << Tabs(1) << "[3] Delete User." << endl;
        cout << Tabs(1) << "[4] Update User." << endl;
        cout << Tabs(1) << "[5] Find User." << endl;
        cout << Tabs(1) << "[6] Main Menue." << endl;
        cout << "********************************" << endl;
    }

    vector <string> SplitToWords(string SourceString, string delimeter = " ")
    {
        vector <string> vWords;
        short pos = 0;
        string sWord;
        while ((pos = SourceString.find(delimeter)) != std::string::npos)
        {
            sWord = SourceString.substr(0, pos);
            if (!sWord.empty())
            {
                vWords.push_back(sWord);
            }
            SourceString.erase(0, pos + delimeter.length());
        }
        if (!SourceString.empty())
        {
            vWords.push_back(SourceString);
        }
        return vWords;
    }

    stClient ReadNewClient(stClient NewClient, vector <stClient> vClients)
    {
        do
        {
            cout << "Enter Account Number : ";
            getline(cin >> ws, NewClient.AccountNumber);
            if (IsAccountNumberUsed(NewClient.AccountNumber, vClients))
                cout << "Account Number is Already Used\n";
        } while (IsAccountNumberUsed(NewClient.AccountNumber, vClients));

        cout << "Enter Pin Code       : ";
        getline(cin, NewClient.PinCode);
        cout << "Enter Full Name      : ";
        getline(cin, NewClient.FullName);
        cout << "Enter Phone Number   : ";
        getline(cin, NewClient.PhoneNumber);
        cout << "Enter Balance Amount : ";
        cin >> NewClient.BalanceAmount;
        cout << endl << endl;
        cin.ignore();
        return NewClient;
    }

    stUser ReadNewUser(stUser NewUser, vector <stUser> vUser)
    {
        do
        {
            cout << "Enter User Name : ";
            getline(cin >> ws, NewUser.UserName);
            if (IsUserNameUsed(NewUser.UserName, vUser))
                cout << "User Name is Already Used\n";
        } while (IsUserNameUsed(NewUser.UserName, vUser));

        cout << "Enter Password       : ";
        getline(cin, NewUser.Password);


        if (ReadYesOrNo("Do you want to give full access? (y/n) "))
            NewUser.Permissions = ePermissions::pFullAccess;
        else
        {
            cout << "Do you want to give access to (y/n):  \n\n";
            if (ReadYesOrNo("Show Client List ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pShowClientList;
            if (ReadYesOrNo("Add New Client ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pAddClient;
            if (ReadYesOrNo("Delete Client ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pDeleteClient;
            if (ReadYesOrNo("Update Client ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pUpdateClient;
            if (ReadYesOrNo("Find Client ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pFindClient;
            if (ReadYesOrNo("Transactions ?"))
                NewUser.Permissions = NewUser.Permissions | ePermissions::pTransactions;
        }

        cout << "User Added Successfully" << endl;
        return NewUser;
    }

    void SaveRecordToFile(string Record, string FileName)
    {
        fstream File;
        File.open(FileName, ios::out | ios::app);
        if (File.is_open())
        {
            File << Record << endl;
            File.close();
        }
    }

    string ClientRecordToLine(stClient Client, string Seperator = "#//#")
    {
        string Line = "";
        Line += Client.AccountNumber + Seperator;
		Line += Client.Password + Seperator;
        Line += Client.PinCode + Seperator;
        Line += Client.FullName + Seperator;
        Line += Client.PhoneNumber + Seperator;
        Line += to_string(Client.BalanceAmount);
        return Line;
    }

    stClient ClientLineToRecord(string Line, string Seperator = "#//#")
    {
        stClient Client;
        vector<string> vData = SplitToWords(Line, Seperator);
        Client.AccountNumber = vData[0];
		Client.Password = vData[1];
        Client.PinCode = vData[2];
        Client.FullName = vData[3];
        Client.PhoneNumber = vData[4];
        Client.BalanceAmount = stof(vData[5]);
        return Client;
    }

    string UserRecordToLine(stUser User, string Seperator = "#//#")
    {
        string Line = "";
        Line += User.UserName + Seperator;
        Line += User.Password + Seperator;
        Line += to_string(User.Permissions);
        return Line;
    }

    stUser UserLineToRecord(string Line, string Seperator = "#//#")
    {
        stUser User;
        vector<string> vData = SplitToWords(Line, Seperator);
        User.UserName = vData[0];
        User.Password = vData[1];
        User.Permissions = stof(vData[2]);
        return User;
    }

    void PrintClientCard(stClient Client)
    {

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(40) << left << Client.FullName;
        cout << "| " << setw(12) << left << Client.PhoneNumber;
        cout << "| " << setw(12) << left << Client.BalanceAmount;
        cout << endl;
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    void PrintUserCard(stUser User)
    {

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(40) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(40) << left << User.Permissions;
        cout << endl;
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    void AddNewClient(stClient Client, string FileName)
    {
        cout << "New Client Added \n\n";
        SaveRecordToFile(ClientRecordToLine(Client), FileName);
    }

    void AddNewUser(stUser User, string FileName)
    {
        cout << "New User Added \n\n";
        SaveRecordToFile(UserRecordToLine(User), FileName);
    }

    void AddClients(string FileName, vector <stClient> vClients)
    {
        stClient Client;
        char YesOrNo;
        do
        {
            AddNewClient(ReadNewClient(Client, vClients), FileName);
            cout << "Do U want 2 add more (y/n)? ";
            cin >> YesOrNo;
        } while (toupper(YesOrNo) == 'Y');
    }

    void AddUsers(string FileName, vector <stUser> vUsers)
    {
        stUser User;
        char YesOrNo;
        do
        {
            AddNewUser(ReadNewUser(User, vUsers), FileName);
            cout << "Do U want 2 add more (y/n)? ";
            cin >> YesOrNo;
        } while (toupper(YesOrNo) == 'Y');
    }

    vector<stClient> LoadClientsFromFile(string FileName)
    {
        fstream File;
        vector <stClient> Clients;
        File.open(FileName, ios::in);
        if (File.is_open())
        {
            string Line = "";
            stClient TempClient;
            while (getline(File, Line))
            {
                TempClient = ClientLineToRecord(Line);
                Clients.push_back(TempClient);
            }
            File.close();
        }
        return Clients;
    }

    vector<stUser> LoadUsersFromFile(string FileName)
    {
        fstream File;
        vector <stUser> Users;
        File.open(FileName, ios::in);
        if (File.is_open())
        {
            string Line = "";
            stUser TempUser;
            while (getline(File, Line))
            {
                TempUser = UserLineToRecord(Line);
                Users.push_back(TempUser);
            }
            File.close();
        }
        return Users;
    }

    void ShowClientsList(vector <stClient> vClients)
    {
        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        for (stClient Client : vClients)
        {
            cout << "| " << setw(15) << left << Client.AccountNumber;
            cout << "| " << setw(10) << left << Client.PinCode;
            cout << "| " << setw(40) << left << Client.FullName;
            cout << "| " << setw(12) << left << Client.PhoneNumber;
            cout << "| " << setw(12) << left << Client.BalanceAmount;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    void ShowUsersList(vector <stUser> vUsers)
    {
        cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(40) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        for (stUser User : vUsers)
        {
            cout << "| " << setw(15) << left << User.UserName;
            cout << "| " << setw(10) << left << User.Password;
            cout << "| " << setw(40) << left << User.Permissions;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    void ShowBalancesList(vector <stClient> vClients)
    {
        cout << "\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        for (stClient Client : vClients)
        {
            cout << "| " << setw(15) << left << Client.AccountNumber;
            cout << "| " << setw(40) << left << Client.FullName;
            cout << "| " << setw(12) << left << Client.BalanceAmount;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    bool FindByAccountNumber(string AccountNumber, stClient &Client, vector<stClient> Clients)
    {
        for (int i = 0; i < Clients.size(); i++)
        {
            if (Clients[i].AccountNumber == AccountNumber)
            {
                Client = Clients[i];
                return true;
            }
        }
        return false;
    }

    bool FindByUserName(string UserName, stUser& User, vector<stUser> vUsers)
    {
        for (int i = 0; i < vUsers.size(); i++)
        {
            if (vUsers[i].UserName == UserName)
            {
                User = vUsers[i];
                return true;
            }
        }
        return false;
    }

    bool MarkClientForDelete(string AccountNumber, vector <stClient>& vClients)
    {
        for (int i = 0; i < vClients.size(); i++)
        {
            if (vClients[i].AccountNumber == AccountNumber)
            {
                vClients[i].MarkedForDelete = true;
                return true;
            }
        }
        return false;
    }

    bool MarkUserForDelete(string UserName, vector <stUser>& vUsers)
    {
        for (int i = 0; i < vUsers.size(); i++)
        {
            if (vUsers[i].UserName == UserName)
            {
                vUsers[i].MarkedForDelete = true;
                return true;
            }
        }
        return false;
    }

    void SaveClientsFromVector(vector <stClient>& vClients, string FileName)
    {
        fstream File;
        File.open(FileName, ios::out);
        if (File.is_open())
        {
            for (stClient TempClient : vClients)
            {
                if (!TempClient.MarkedForDelete)
                {
                    File << ClientRecordToLine(TempClient) << endl;
                }
            }

        }
        File.close();
    }

    bool DeleteClientFromFile(string AccountNumber, vector <stClient>& vClients)
    {
        char Answer = 'n';
        stClient TempClient;
        if (FindByAccountNumber(AccountNumber, TempClient, vClients))
        {
            PrintClientCard(TempClient);
            cout << "\nDo u Really want to Delete this client? (y/n)" << endl;
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                MarkClientForDelete(AccountNumber, vClients);
                SaveClientsFromVector(vClients, gClientsFile);
                vClients = LoadClientsFromFile(gClientsFile);
                cout << "Client deleted\n";
                return true;
            }
        }
        else
        {
            cout << "Account Number (" << AccountNumber << ") was not found\n";
        }
        return false;
    }

    void SaveUsersFromVector(vector <stUser>& vUsers, string FileName)
    {
        fstream File;
        File.open(FileName, ios::out);
        if (File.is_open())
        {
            for (stUser TempUser : vUsers)
            {
                if (!TempUser.MarkedForDelete)
                {
                    File << UserRecordToLine(TempUser) << endl;
                }
            }

        }
        File.close();
    }

    bool DeleteUserFromFile(string UserName, vector <stUser>& vUsers)
    {
        char Answer = 'n';
        stUser TempUser;
        if (FindByUserName(UserName, TempUser, vUsers))
        {
            PrintUserCard(TempUser);
            cout << "\nDo u Really want to Delete this User? (y/n)" << endl;
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                MarkUserForDelete(UserName, vUsers);
                SaveUsersFromVector(vUsers, gUsersFile);
                vUsers = LoadUsersFromFile(gUsersFile);
                cout << "Userf deleted\n";
                return true;
            }
        }
        else
        {
            cout << "User Name (" << UserName << ") was not found\n";
        }
        return false;
    }

    stClient EditClientRecord(string AccountNumber)
    {
        stClient Client;
        Client.AccountNumber = AccountNumber;
        cout << "Enter Pin Code       : ";
        getline(cin >> ws, Client.PinCode);
        cout << "Enter Full Name      : ";
        getline(cin, Client.FullName);
        cout << "Enter Phone Number   : ";
        getline(cin, Client.PhoneNumber);
        cout << "Enter Balance Amount : ";
        cin >> Client.BalanceAmount;
        cout << endl << endl;
        cin.ignore();
        return Client;
    }

    stUser EditUserRecord(string UserName)
    {
        stUser User;
        User.UserName = UserName;
        cout << "Enter Password : ";
        getline(cin >> ws, User.Password);

        if (ReadYesOrNo("Do you want to give full access? (y/n) "))
            User.Permissions = ePermissions::pFullAccess;
        else
        {
            cout << "Do you want to give access to (y/n):  \n\n";
            if (ReadYesOrNo("Show Client List ?"))
                User.Permissions = User.Permissions | ePermissions::pShowClientList;
            if (ReadYesOrNo("Add New Client ?"))
                User.Permissions = User.Permissions | ePermissions::pAddClient;
            if (ReadYesOrNo("Delete Client ?"))
                User.Permissions = User.Permissions | ePermissions::pDeleteClient;
            if (ReadYesOrNo("Update Client ?"))
                User.Permissions = User.Permissions | ePermissions::pUpdateClient;
            if (ReadYesOrNo("Find Client ?"))
                User.Permissions = User.Permissions | ePermissions::pFindClient;
            if (ReadYesOrNo("Transactions ?"))
                User.Permissions = User.Permissions | ePermissions::pTransactions;
        }
        return User;
    }

    bool EditClientFromFile(string AccountNumber, vector <stClient>& vClients)
    {
        char Answer = 'n';
        stClient TempClient;
        if (FindByAccountNumber(AccountNumber, TempClient, vClients))
        {
            PrintClientCard(TempClient);
            cout << "\nDo u Really want to Edit this client? (y/n)" << endl;
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                for (stClient& C : vClients)
                {
                    if (C.AccountNumber == AccountNumber)
                    {
                        C = EditClientRecord(AccountNumber);
                        break;
                    }
                }

                SaveClientsFromVector(vClients, gClientsFile);
                cout << "Client Edited\n";
                return true;
            }
        }
        else
        {
            cout << "Account Number (" << AccountNumber << ") was not found";
        }
        return false;
    }

    bool EditUserFromFile(string UserName, vector <stUser>& vUsers)
    {
        char Answer = 'n';
        stUser TempUser;
        if (FindByUserName(UserName, TempUser, vUsers))
        {
            PrintUserCard(TempUser);
            cout << "\nDo u Really want to Edit this user? (y/n)" << endl;
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                for (stUser& User : vUsers)
                {
                    if (User.UserName == UserName)
                    {
                        User = EditUserRecord(UserName);
                        break;
                    }
                }

                SaveUsersFromVector(vUsers, gUsersFile);
                cout << "Client Edited\n";
                return true;
            }
        }
        else
        {
            cout << "User Name (" << UserName << ") was not found";
        }
        return false;
    }

    void WaitForKeyPress() {
        system("pause");
    }

    bool CheckPermission(stUser User, ePermissions Permission)
    {
        if (User.Permissions == ePermissions::pFullAccess)
            return true;
        return ((Permission & User.Permissions) == Permission);
    }

    void DeleteClient(vector <stClient>& vClients)
    {
        stClient Client;
        DisplayHeader("Delete Screen");
        string AccountNumber = ReadNewAccountNumber("Pls Input Account Number");
        DeleteClientFromFile(AccountNumber, vClients);
    }

    void DeleteUser(vector <stUser>& vUsers)
    {
        stUser User;
        DisplayHeader("Delete Screen");
        string UserName = ReadNewUserName("Pls Input User Name: ");
        DeleteUserFromFile(UserName, vUsers);
    }

    void UpdateClientInfo(vector <stClient>& vClients)
    {
        stClient Client;
        DisplayHeader("Update Info Screen");
        string AccountNumber = ReadNewAccountNumber("Pls Input Account Number");
        EditClientFromFile(AccountNumber, vClients);
    }

    void UpdateUserInfo(vector <stUser>& vUsers)
    {
        stUser User;
        DisplayHeader("Update Info Screen");
        string UserName = ReadNewUserName("Pls Input User Name: ");
        EditUserFromFile(UserName, vUsers);
    }

    void FindClient(vector <stClient> vClients)
    {
        stClient Client;
        string AccountNumber = ReadNewAccountNumber("Pls Input Account Number");
        if (FindByAccountNumber(AccountNumber, Client, vClients))
            PrintClientCard(Client);
        else
            cout << "Client Wasn't found";
    }

    void FindUser(vector <stUser> vUsers)
    {
        stUser User;
        string UserName = ReadNewUserName("Pls Input User Name: ");
        if (FindByUserName(UserName, User, vUsers))
            PrintUserCard(User);
        else
            cout << "User Wasn't found";
    }

    void AddToBalance(vector <stClient>& vClients, string AccountNumber, double Amount)
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                if ((C.BalanceAmount + Amount) < 0)
                {
                    cout << "The Amount exceeds ur balance, Pls Change The Amount"; 
                    break;
                }
                C.BalanceAmount += Amount;
                break;
            }
        }
    }

    void Deposit(vector <stClient>& vClients)
    {
        stClient Client;
        char Answer = 'n';
        DisplayHeader("Deposit Screen");
        string AccountNumber = ReadOldAccountNumber("Pls input Account Number: ", vClients);
        cout << "The Following Are the Client details: \n";
        FindByAccountNumber(AccountNumber, Client, vClients);
        PrintClientCard(Client);
        double Amount = ReadPositiveNumbers("Pls input Deposit Amount: ");
        cout << "Are u sure u want to perform this Transaction? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            AddToBalance(vClients, AccountNumber, Amount);
            SaveClientsFromVector(vClients, gClientsFile);
            cout << "\nBalance Added successfully, New Balance = " << Client.BalanceAmount + Amount << endl;
        }
    }

    void Withdraw(vector <stClient>& vClients)
    {
        stClient Client;
        char Answer = 'n';
        DisplayHeader("Withdraw Screen");
        string AccountNumber = ReadOldAccountNumber("Pls input Account Number: ", vClients);
        cout << "The Following Are the Client details: \n";
        FindByAccountNumber(AccountNumber, Client, vClients);
        PrintClientCard(Client);
        double Amount = ReadPositiveNumbers("Pls input Withdraw Amount: ");
        cout << "Are u sure u want to perform this Transaction? (y/n): ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            AddToBalance(vClients, AccountNumber, Amount * -1);
            SaveClientsFromVector(vClients, gClientsFile);
            cout << "\nBalance Withdrew successfully, New Balance = " << Client.BalanceAmount - Amount << endl;
        }
    }

    stUser Login(vector <stUser> vUsers)
    {
        stUser InputUser;
        stUser CorrectUser;
        bool DoesUserExist;
        do
        {
            cout << "input User Name: ";
            cin >> InputUser.UserName;
            cout << "input Password: ";
            cin >> InputUser.Password;

            DoesUserExist = FindByUserName(InputUser.UserName, CorrectUser, vUsers);

            if (!DoesUserExist || (InputUser.Password != CorrectUser.Password))
                cout << "Invalid User Name or Password\n\n";
            else
                return CorrectUser;
        } while (!DoesUserExist || (InputUser.Password != CorrectUser.Password));
    }

}