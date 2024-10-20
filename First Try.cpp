#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const string gFileName = "OldClients.txt";

struct stClient
{
    string AccountNumber;
    string PinCode;
    string FullName;
    string PhoneNumber;
    double BalanceAmount;
    bool MarkedForDelete = false;
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

bool IsAccountNumberUsed(string AccountNumber, vector<stClient> Clients)
{
    for (stClient &Client : Clients)
    {
        if (Client.AccountNumber == AccountNumber)
            return true;
    }
    return false;
}

string ReadOldAccountNumber(string Message,vector <stClient> vClients)
{

    string AccountNumber;
    cout << Message << endl;   
    cin >> AccountNumber;
    while (!IsAccountNumberUsed(AccountNumber,vClients))
    {
        cout << "Pls Input An Existing Account Number!\n";
        cin >> AccountNumber;
    }
    return AccountNumber;
}

string Tabs(int NumOfTabs)
{
    string Tabs= "";
    for (int i = 0; i < NumOfTabs; i++)
        Tabs += "    ";
    return Tabs;
}

void DisplayMenu()
{
    cout << "********************************" << endl;
    cout << Tabs(2) << "Main Screen" << endl;
    cout << "********************************" << endl;
    cout << Tabs(1) << "[1] Show Clients List." << endl;
    cout << Tabs(1) << "[2] Add New Client." << endl;
    cout << Tabs(1) << "[3] Delete Client." << endl;
    cout << Tabs(1) << "[4] Update Client Info." << endl;
    cout << Tabs(1) << "[5] Find Client." << endl;
    cout << Tabs(1) << "[6] Transactions." << endl;
    cout << Tabs(1) << "[7] Exit." << endl;
    cout << "********************************" << endl;
}

void DisplayHeader(string HeaderText)
{
    cout << "********************************" << endl;
    cout << Tabs(2) << HeaderText << endl;
    cout << "********************************" << endl;
}

void DisplayTransMenu()
{
    cout << "********************************" << endl;
    cout << Tabs(2) << "Transactions Screen" << endl;
    cout << "********************************" << endl;
    cout << Tabs(1) << "[1] Deposit." << endl;
    cout << Tabs(1) << "[2] Withdraw." << endl;
    cout << Tabs(1) << "[3] Total Balances." << endl;
    cout << Tabs(1) << "[4] Back to Main Screen." << endl;
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

string RecordToLine(stClient Client, string Seperator = "#//#")
{
    string Line = "";
    Line += Client.AccountNumber + Seperator;
    Line += Client.PinCode + Seperator;
    Line += Client.FullName + Seperator;
    Line += Client.PhoneNumber + Seperator;
    Line += to_string(Client.BalanceAmount);
    return Line;
}

stClient LineToRecord(string Line, string Seperator = "#//#")
{
    stClient Client;
    vector<string> vData = SplitToWords(Line, Seperator);
    Client.AccountNumber = vData[0];
    Client.PinCode = vData[1];
    Client.FullName = vData[2];
    Client.PhoneNumber = vData[3];
    Client.BalanceAmount = stof(vData[4]);
    return Client;
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

void AddNewClient(stClient Client, string FileName)
{
    cout << "New Client Added \n\n";
    string ClientLine = RecordToLine(Client);
    SaveRecordToFile(ClientLine, FileName);
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
            TempClient = LineToRecord(Line);
            Clients.push_back(TempClient);
        }
        File.close();
    }
    return Clients;
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

void ShowBalancesList(vector <stClient> vClients)
{
    cout << "\n\t\t\t\t\Balances List (" << vClients.size() << ") Client(s).";
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

bool FindByAccountNumber(string AccountNumber, stClient& Client, vector<stClient> Clients)
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
                File << RecordToLine(TempClient) << endl;
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
            SaveClientsFromVector(vClients, gFileName);
            vClients = LoadClientsFromFile(gFileName);
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

            SaveClientsFromVector(vClients, gFileName);
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

void WaitForKeyPress() {
    system("pause");  
}

void DeleteClient(vector <stClient>& vClients)
{
	stClient Client;
    DisplayHeader("Delete Screen");
    string AccountNumber = ReadNewAccountNumber("Pls Input Account Number");
    DeleteClientFromFile(AccountNumber, vClients);
}

void UpdateClientInfo(vector <stClient>& vClients)
{
    stClient Client;
    cout << "********************************" << endl;
    cout << Tabs(2) << "Update Client Info Screen" << endl;
    cout << "********************************" << endl;
    string AccountNumber = ReadNewAccountNumber("Pls Input Account Number");
    EditClientFromFile(AccountNumber, vClients);
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

void AddToBalance(vector <stClient>& vClients, string AccountNumber, double Amount)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
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
        cout << "\nBalance Added successfully, New Balance = " << Client.BalanceAmount << endl;
    }
    SaveClientsFromVector(vClients, gFileName);
}

void Withdraw(vector <stClient> &vClients)
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
        AddToBalance(vClients, AccountNumber, Amount* -1);
        cout << "\nBalance Added successfully, New Balance = " << Client.BalanceAmount << endl;
    }
    SaveClientsFromVector(vClients, gFileName);
}

int main()
{
    while (true) {
        vector <stClient> vClients = LoadClientsFromFile(gFileName);
        bool InTrans = true;
        system("cls");
        DisplayMenu();
        int choice = GetChoice("Choose what do you want to do [1 to 7]?",1,7);
        switch (choice) {
        case 1:
            system("cls");
            ShowClientsList(vClients);
            WaitForKeyPress();
            break;
        case 2:
            system("cls");
            AddClients(gFileName,vClients);
            break;
        case 3:
            system("cls");
            DeleteClient(vClients);
			WaitForKeyPress();
        	break;
        case 4:
            system("cls");
            UpdateClientInfo(vClients);
            WaitForKeyPress();
        	break;
        case 5:
            system("cls");
            FindClient(vClients);
            WaitForKeyPress();
            break;
        case 6:
            system("cls");
            while (InTrans)
            {
                system("cls");
                DisplayTransMenu();
                vClients = LoadClientsFromFile(gFileName);
                int TransChoice = GetChoice("Choose what do you want to do [1 to 4]?", 1, 4);
                switch (TransChoice)
                {
                case 1:
                    system("cls");
                    Deposit(vClients);
                    WaitForKeyPress();
                    break;
                case 2:
                    system("cls");
                    Withdraw(vClients);
                    WaitForKeyPress();
                    break;
                case 3:
                    system("cls");
                    ShowBalancesList(vClients);
                    WaitForKeyPress();
                    break;
                case 4:
                    InTrans = false;
                }
            }
            break;
        case 7:
            system("cls");
            cout << "Exiting. Goodbye! \n\n";
            WaitForKeyPress();
            return 0;
        }
    }

}
