#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void Login();
void MainManuScreen();

static const string FileName = "..\\Bank system\\clients data file.txt";
static const string SEPERATOR = "#//#";

enum enMainMenuScreen{enQuickWithdraw=1, enNormalWithdarw, enDeposit, enCheckBalance, enLogout};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string phone;
    double Balance=0;
};

static stClient CurrentClient;

void ShowScreenTitle(string title)
{
    system("cls");
    cout << "\n===========================================\n";
    cout << "\t\t" << title;
    cout << "\n===========================================\n";
}

void GoBackToMenuScreen()
{
    cout << "\nPress any key to go back to main menu...";
    system("pause>0");
    MainManuScreen();
}

// Read information

stClient ReadAccountNumberAndPinCode(stClient& client)
{

    cout << "Enter Account Number? ";
    getline(cin >> ws, client.AccountNumber);
    cout << "Enter PinCode? ";
    getline(cin >> ws, client.PinCode);

    return client;
}

int ReadNumberToDepositOrWithdraw()
{
    int number;

    cout << "ATM don\'t accept tens or twentys ";
    cin >> number;

    while (number <= 0 || number % 50 != 0)
    {
        cout << "ATM don\'t accept tens or twentys ";
        cin >> number;
    }

    return number;
}

vector<string>SplitLine(string line,string Seperator)
{
    short pos = 0;
    string word;
    vector<string>vClient;

    while ((pos=line.find(Seperator))!=string::npos)
    {
        word = line.substr(0, pos);
        vClient.push_back(word);
        line.erase(0, pos + Seperator.length());
    }

    if (!line.empty())
    {
        vClient.push_back(line);
    }

    return vClient;
}

stClient ConvertLineStringToRecord(string line)
{
    vector<string>vClient = SplitLine(line, SEPERATOR);
    stClient client;

    client.AccountNumber = vClient[0];
    client.PinCode = vClient[1];
    client.Name = vClient[2];
    client.phone = vClient[3];
    client.Balance = stod(vClient[4]);

    return client;
}

string ConvertRecordToStringLine(stClient Client, string Seperator)
{
    string line = "";

    line += Client.AccountNumber + Seperator;
    line += Client.PinCode + Seperator;
    line += Client.Name + Seperator;
    line += Client.phone + Seperator;
    line += to_string(Client.Balance);

    return line;

}

// Files

vector<stClient>LoadClientDataFromFile()
{
    vector<stClient>vClients;
    fstream ClientFileData;

    ClientFileData.open(FileName, ios::in);  //Read Only
    if (ClientFileData.is_open())
    {
        string line;
        while (getline(ClientFileData, line))
            vClients.push_back(ConvertLineStringToRecord(line));
        ClientFileData.close();
    }

    return vClients;
}

void SaveClientData(vector<stClient> vClients)
{
    fstream ClientFileData;

    ClientFileData.open(FileName, ios::out);    //Update
    if (ClientFileData.is_open())
    {
        for (stClient &client : vClients)
        {
            ClientFileData << ConvertRecordToStringLine(client, SEPERATOR) << endl;
        }
        ClientFileData.close();
    }
}

// Find Client By Account Number And PinCode

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode)
{
    vector<stClient> vClients = LoadClientDataFromFile();
    for (stClient &client : vClients)
    {
        if (client.AccountNumber == AccountNumber && client.PinCode==PinCode)
        {
            CurrentClient = client;
            return true;
        }
    }
    return false;
}

vector<stClient> UpdateClientData()
{
    vector<stClient> vClients = LoadClientDataFromFile();

    for (stClient& client : vClients)
    {
        if (client.AccountNumber == CurrentClient.AccountNumber)
        {
            client.Balance = CurrentClient.Balance;
            break;
        }
    }
    return vClients;
}

// Withdraw

bool DoThisTransaction()
{
    char answer;

    cout << "Do you sure you want perform this transacation? yes(y) no(n)? ";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        return true;
    }

    return false;
}

void QuickWithdrawMenu()
{
    cout << right << setw(10) << "[1] 50" << setw(10) << "[2] 100\n";
    cout << setw(10) << "[3] 200" << setw(10) << "[4] 300\n";
    cout << setw(10) << "[5] 500" << setw(10) << "[6] 1000\n";
    cout << setw(10) << "[7] 2000" << setw(10) << "[8] 3000\n";
    cout << setw(10) << "[9]Exit\n";
    cout <<"===========================================\n";
}

void WirhdrawByNumber(double number)
{
    if (CurrentClient.Balance>=number)
    {
        CurrentClient.Balance -= number;
        SaveClientData(UpdateClientData());
        cout << "Done successfully. New balance is: " << CurrentClient.Balance<<endl;
    }
    else
    {
        cout << "This amount exceeds your balance, make anther choice \n";
    }
}

void PerformQuickWithdraw(short answer)
{
    switch (answer)
    {
    case 1:
        WirhdrawByNumber(50);
        break;
    case 2:
        WirhdrawByNumber(100);
        break;
    case 3:
        WirhdrawByNumber(200);
        break;
    case 4:
        WirhdrawByNumber(300);
        break;
    case 5:
        WirhdrawByNumber(500);
        break;
    case 6:
        WirhdrawByNumber(1000);
        break;
    case 7:
        WirhdrawByNumber(2000);
        break;
    case 8:
        WirhdrawByNumber(3000);
        break;
    case 9:
        return;
        break;

    default:
        break;
    }
}

void QuickWithdrawScreen()
{
    short answer;
    char ch;

    QuickWithdrawMenu();
    cout << "Your Balance is: " << CurrentClient.Balance << endl;
    cout << "Choose what to withdraw from [1 to 8]? and [9] to exit: ";
    cin >> answer;

    while (answer < 1 || answer >9)
    {
        cout << "Invaild number!\n";
        cout << "Choose what to withdraw from [1 to 8]? and [9] to exit: ";
        cin >> answer;
    }


    if (DoThisTransaction())
    {
        PerformQuickWithdraw(answer);
    }
}

void NormalWithdrawScreen()
{
    int WithdrawAmount = ReadNumberToDepositOrWithdraw();

    if (DoThisTransaction)
    {
        WirhdrawByNumber(WithdrawAmount);
    }
}

void DepositScreen()
{
    int DepositAmount = ReadNumberToDepositOrWithdraw();

    if (DoThisTransaction)
    {
        CurrentClient.Balance += DepositAmount;
        SaveClientData(UpdateClientData());
        cout << "Done successfully. New balance is: " << CurrentClient.Balance << endl;
    }
}

void CheckBalanceScreen()
{
    cout << "Your Balance is: " << CurrentClient.Balance << endl;
}


enMainMenuScreen ReadChoiceOfMenu()
{
    short number;
    cout << "Choose what you want to do? [1 to 5]? ";
    cin >> number;
    return (enMainMenuScreen)number;
}

void PerfomMainMenu(enMainMenuScreen choice)
{
    switch (choice)
    {
    case enMainMenuScreen::enQuickWithdraw:
        ShowScreenTitle("Quick Withdraw Screen");
        QuickWithdrawScreen();
        GoBackToMenuScreen();
        break;
    case enMainMenuScreen::enNormalWithdarw:
        ShowScreenTitle("Normal Withdraw Screen");
        NormalWithdrawScreen();
        GoBackToMenuScreen();
        break;
    case enMainMenuScreen::enDeposit:
        ShowScreenTitle("Deposit Screen");
        DepositScreen();
        GoBackToMenuScreen();
        break;
    case enMainMenuScreen::enCheckBalance:
        ShowScreenTitle("Check Balance Screen");
        CheckBalanceScreen();
        GoBackToMenuScreen();
        break;
    case enMainMenuScreen::enLogout:
        Login();
        break;

    default:
        break;
    }
}

void MainManuScreen()
{
    ShowScreenTitle("ATM Main Menu Screen");

    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance..\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";

    PerfomMainMenu(ReadChoiceOfMenu());
}

// Login

void Login()
{
    bool LoginIsFail = false;
    stClient client;
    do
    {
        ShowScreenTitle("Login Screen");

        if (LoginIsFail)
        {
            cout << "Invalid Account Nymber or PinCode!\n";
        }

        ReadAccountNumberAndPinCode(client);
        LoginIsFail = !FindClientByAccountNumberAndPinCode(client.AccountNumber, client.PinCode);
    } while (LoginIsFail);
    MainManuScreen();
}

int main()
{
    Login();
}
