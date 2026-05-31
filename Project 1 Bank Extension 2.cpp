#include <iostream>
#include <iomanip>
#include<fstream>
#include <string>
#include <vector>
using namespace std;

const string ClientFile = "Client.txt";
const string UserFile = "User.txt";
struct stClient
{
    string AccountNumber = "";
    string PinNumber = "";
    string Name = "";
    string PhoneNumber = "";
    int AccountBalance = 0;
    bool isDelete = false;

};

struct stUser {
    string AdminName = "";
    string Passowerd = "";
    int Permission = 0 ;
    bool isDelete = false;
};
vector<stUser>  UploadUsertFromRecord();
vector<stUser> User1 = UploadUsertFromRecord();
int DisplayMainMenue();
bool IsPermisssion(stUser User, int Num);
void ListClientOption(int num , stUser User=User1[0]);

/////////////////////////////////////////////////////////////////////////

vector<string> spliting(string Line, string del="#//#") {
    string s1 = "";
    short pos = 0;
    vector<string> vLine;
    while ((pos = Line.find(del)) != string::npos) {
        s1 = Line.substr(0, pos);
        vLine.push_back(s1);
        Line.erase(0, pos + del.length());

    }
    if (Line != "") {
        vLine.push_back(Line);

    }
    return vLine;

}

stClient ChangeLineToStruct(string Line) {
    stClient Client;
    vector<string> vLine = spliting(Line);
    Client.AccountNumber = vLine[0];
    Client.PinNumber = vLine[1];
    Client.Name = vLine[2];
    Client.PhoneNumber = vLine[3];
    Client.AccountBalance = stoi(vLine[4]);
    return Client;
    
}

vector<stClient>UploadClientFromRecord() {
    fstream  MyFile;
    MyFile.open(ClientFile, ios::in);
    vector<stClient> vsClient;
    if (MyFile.is_open()) {
        string Line = "";
        stClient Client;
        while (getline(MyFile, Line)) {
            Client = ChangeLineToStruct(Line);
            vsClient.push_back(Client);
        }
    }
    MyFile.close();
    return vsClient;
}

//////////////////////////////////////////////////////////////////////////////////////////

string JoinTheRecord(stClient Client, string del ="#//#") {
    string Line = "";
    Line += Client.AccountNumber + del;
    Line += Client.PinNumber + del;
    Line += Client.Name + del;
    Line += Client.PhoneNumber + del;
    Line += to_string(Client.AccountBalance);
    return Line;
}

void UploadToFile(vector<stClient> vsClient) {
    fstream MyFile;
    MyFile.open(ClientFile, ios::out);
    if (MyFile.is_open()) {
        string Line = "";
        for (stClient& Client : vsClient) {
            if (Client.isDelete == false) {
                Line = JoinTheRecord(Client);
                MyFile << Line << endl;
            }
        }
    }
    MyFile.close();



}

/////////////////////////////////////////////////////////////////////////////////////////

//Show Client 

void ClientDisplay(stClient Client) {
    cout << left;
    cout <<"|" << setw(15) << Client.AccountNumber;
    cout <<"|" << setw(10) << Client.PinNumber;
    cout <<"|" << setw(25) << Client.Name;
    cout <<"|" << setw(15) << Client.PhoneNumber;
    cout <<"|" << setw(12) << Client.AccountBalance;

    cout << endl;
}

void ClientDisplayList() {
    vector<stClient> vsClient = UploadClientFromRecord();
    cout << "\t\t\t\tClient (s) No("<<vsClient.size()<<")"<<endl;
    cout << "----------------------------------------------------------------------------------------\n";
    cout << left;
    cout << "|" << setw(15) << "Account Number";
    cout << "|" << setw(10) << "Pin Number";
    cout << "|" << setw(25) << "Name";
    cout << "|" << setw(15) << "Phone Number";
    cout << "|" << setw(12) << "Account Balance";
    cout << "\n----------------------------------------------------------------------------------------\n";
    for (int i = 0;i < vsClient.size();i++) {
        ClientDisplay(vsClient[i]);
    }
    cout << "----------------------------------------------------------------------------------------\n";
}

//////////////////////////////////////////////////////////////////////

//Add New Client

stClient AskToAdd(stClient Client) {
   
    
    cout << "\n\t\tEnter Pin Code :";
    getline(cin>>ws, Client.PinNumber);
    cout << "\t\tEnter Name :";
    getline(cin, Client.Name);
    cout << "\t\tEnter Phone Number :";
    getline(cin, Client.PhoneNumber);
    cout << "\t\tEnter Account Balance :";
    cin>> Client.AccountBalance;
    return Client;
}

bool isExisted(string Acc) {
    vector<stClient>vsClient=UploadClientFromRecord();
    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) return true;
    }
    return false;
}

void AppendToFile(stClient Client) {
    fstream MyFile;
    MyFile.open(ClientFile, ios::app);
    MyFile <<endl<< JoinTheRecord(Client);
}

void AddNewClient() {
    string Acc = "";
    cout << "\n\tEnter Account Nubmber : ";
    cin >> Acc;
    char is = 'y';
    if (isExisted(Acc)) {
        cout << "The Account Number (" << Acc << ") Is Existed\n\n";
    }
    else {
        stClient Client;
        Client.AccountNumber = Acc;
        Client=AskToAdd(Client);
        
        cout << "\nDo You Want To Add To File ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            AppendToFile(Client);
        }
    }
}

void AddNewClientOption() {
    char is = 'Y';

    do {
        system("cls");
        cout << "\n\t\t\tAdd New Client (s) .\n";
        cout << "----------------------------------------------------------";
        AddNewClient();
        cout << "\n\tDo You Want To Add Another Client ? (y/n)";
        cin >> is;
    } while (tolower(is) == 'y');

}

/////////////////////////////////////////////////////////////////////////////////////
//Delete Client 

string AskToDelete() {
    string Acc = "";
    cout << "\n\t\tEnter an Account : ";
    cin >> Acc;
    return Acc;
}

void IsExitedToDelete(string Acc, vector<stClient> & vsClient ) {
  
    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) {
            Client.isDelete = true;
        }
    }
}

void DeletClient() {
    vector<stClient>vsClient = UploadClientFromRecord();
    string Acc = AskToDelete();
    char is = 'y';
  
    if (isExisted(Acc)) {
      
        cout << "\n\t\tDo You Want To Delete ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            IsExitedToDelete(Acc, vsClient);
            UploadToFile(vsClient);
        }
       
    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }
}

void DeleteClientOption() {
    char is = 'y';

    do {

        system("cls");
        cout << "\n\t\t\t Delete Client (s)  ";
        cout << "\n----------------------------------------------------------";
        DeletClient();
        cout << "\n\nDo You Want To Delete Another Account ? (y/n) ";
        cin >> is;
    } while (tolower(is)=='y');
}

//////////////////////////////////////////////////////////////////////////
//Update Client

void IsExitedToUpdate(string Acc, vector<stClient>& vsClient) {

    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) {
           Client= AskToAdd(Client);
           break;
        }
    }
}

void UpdateClient() {
    vector<stClient> vsClient = UploadClientFromRecord();
    string Acc = AskToDelete();
    char is = 'y';
    stClient sClient;
    if (isExisted(Acc)) {
        cout << "\n\t\tDo Want To Update ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            IsExitedToUpdate(Acc, vsClient);
            UploadToFile(vsClient);
        }
       
      
    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }

}

void UpdateClientOption() {
    char is = 'y';
    do {
        system("cls");
        cout << "\n\t\t\t Update Client (s)  ";
        cout << "\n----------------------------------------------------------";
        UpdateClient();
        cout << "\n\nDo You Want To Update Another Client ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

//////////////////////////////////////////////////////////////////////////
//Find Client

void ShowClient(stClient Client) {
    cout << "\t\tAccount Number :" << Client.AccountNumber << endl;
    cout << "\t\tPin Code  :" << Client.PinNumber << endl;
    cout << "\t\tName :" << Client.Name << endl;
    cout << "\t\tPhone :" << Client.PhoneNumber << endl;
    cout << "\t\tAccount Balance :" << Client.AccountBalance << endl;
}

void IsExitedToFind(string Acc, vector<stClient>& vsClient) {

    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) {
            ShowClient(Client);
            break;
        }
    }
}

void FindClient() {
    string Acc = AskToDelete();
    char is = 'y';
    vector<stClient>vsClient = UploadClientFromRecord();
    if (isExisted(Acc)) {
        cout << "\n----------------------------------------------------------\n";
        IsExitedToFind(Acc, vsClient);
        cout << "\----------------------------------------------------------";
        UploadToFile(vsClient);

    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }
}

void FindClientOption() {
    char is = 'y';
    do {
        system("cls");
        cout << "\n\t\t\t Find Client (s)  ";
        cout << "\n----------------------------------------------------------";
        FindClient();
        cout << "\n\nDo You Want To Find Another Client ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

//////////////////////////////////////////////////////////////////////////////////////////
//Transaction 

//Add Money 

void AddMoney(stClient & Client, int Amount ) {
    Client.AccountBalance += Amount;
}

void IsExitedToAddMoney(string Acc, vector<stClient>& vsClient, int Amount) {

    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) {
            AddMoney(Client, Amount);
            break;
        }
    }
}

void AddTransaction() {
    vector<stClient>vsClient = UploadClientFromRecord();
    string Acc = AskToDelete();
    char is = 'y';
    int Amount = 0;
    if (isExisted(Acc)) {
        cout << "\n\t\tEnter An Amount ?  ";
        cin >> Amount;
        cout << "\n\t\tDo Want TO Add The Amount  ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            IsExitedToAddMoney(Acc, vsClient, Amount);
            UploadToFile(vsClient);
        }


    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }
}

void AddMoneyOption() {
    char is = 'y';
    do {
        cout << "\n\t\tDeosite Money ";
        cout << "\n----------------------------------------------------------";
        AddTransaction();
        cout << "\n\nDo You Want To Deposite Again ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

//////////////////////////////////////////////////////////////////////
//Minus Money


void MinusMoney(stClient& Client, int Amount) {
    if (Client.AccountBalance < Amount) {
        cout << "\n\nInvalid Withdraw Number !!!\n";
    }
    else
    {
        Client.AccountBalance -= Amount;
    }
    
}

void IsExitedToMinusMoney(string Acc, vector<stClient>& vsClient, int Amount) {

    for (stClient& Client : vsClient) {
        if (Acc == Client.AccountNumber) {
            MinusMoney(Client, Amount);
            break;
        }
    }
}

void MinusTransaction() {
    vector<stClient>vsClient = UploadClientFromRecord();
    string Acc = AskToDelete();
    char is = 'y';
    int Amount = 0;
    if (isExisted(Acc)) {
        cout << "\n\t\tEnter The Amount ?  ";
        cin >> Amount;
        cout << "\n\t\tDo Want TO Withdraw The Amount  ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            IsExitedToMinusMoney(Acc, vsClient, Amount);
            UploadToFile(vsClient);
        }


    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }
}

void MinusMoneyOption() {
    char is = 'y';
    do {
        system("cls");
        cout << "\n\t\t\t WithDraw Money   ";
        cout << "\n----------------------------------------------------------";
        MinusTransaction();
        cout << "\nDo You Want To Withdraw Another Balance ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

/////////////////////////////////////////////////////////////////////////
//Dispaly Transaction 

void TranDisplay(stClient Client) {
    cout << left;
    cout << "|" << setw(15) << Client.AccountNumber;
 
    cout << "|" << setw(25) << Client.Name;
   
    cout << "|" << setw(12) << Client.AccountBalance;

    cout << endl;
}

void TranDisplayList() {
    vector<stClient> vsClient = UploadClientFromRecord();
    cout << "\t\t Client (s) No(" << vsClient.size() << ")" << endl;
    cout << "----------------------------------------------------------\n";
    cout << left;
    cout << "|" << setw(15) << "Account Number";
  
    cout << "|" << setw(25) << "Name";
 
    cout << "|" << setw(12) << "Account Balance";
    cout << "\n----------------------------------------------------------";
    cout << endl;
    for (int i = 0;i < vsClient.size();i++) {
        TranDisplay(vsClient[i]);
    }
    cout << "----------------------------------------------------------\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Dispaly Transaction 
int displayTransactionMenue() {
    int choice = 0;
    cout << "\t\t[ Transaction  Menue ] ";
    cout << "\n----------------------------------------------------------\n";
    cout << "\t[1] Show Transaction List \n";
    cout << "\t[2] Withdraw Money \n";
    cout << "\t[3] Add Money \n";
    cout << "\t[4] Return To Main Menue";
    cout << "\n----------------------------------------------------------\n";
    cout << "Enter A Number : ";
    cin >> choice;

    return choice;

}

void ListOfTransactionOption(int choice) {
    switch (choice) {
    case 1: {
        system("cls");
        TranDisplayList();
        break;
    }
    case 2: {
        system("cls");
        MinusMoneyOption();
        break;
    }
    case 3: {
        system("cls");
        AddMoneyOption();
        break;
    }
    case 4:
    {
        system("cls");
        ListClientOption(DisplayMainMenue());
        break;
    }
    }
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// User



vector<string> splitingUser(string Line, string del = "#//#") {
    string s1 = "";
    short pos = 0;
    vector<string> vLine;
    while ((pos = Line.find(del)) != string::npos) {
        s1 = Line.substr(0, pos);
        vLine.push_back(s1);
        Line.erase(0, pos + del.length());

    }
    if (Line != "") {
        vLine.push_back(Line);

    }
    return vLine;

}

stUser ChangeLineUserToStruct(string Line) {
    stUser User;
    vector<string> vLine = splitingUser(Line);
    User.AdminName = vLine[0];
    User.Passowerd = vLine[1];
    User.Permission = stoi(vLine[2]);
    return User;


}


vector<stUser>UploadUsertFromRecord() {
    fstream  MyFile;
    MyFile.open(UserFile, ios::in);
    vector<stUser> vsClient;
    if (MyFile.is_open()) {
        string Line = "";
        stUser Client;
        while (getline(MyFile, Line)) {
            Client = ChangeLineUserToStruct(Line);
            vsClient.push_back(Client);
        }
    }
    MyFile.close();
    return vsClient;
}

////////////////////////////////////////////////////////////

string JoinTheUserRecord(stUser Client, string del = "#//#") {
    string Line = "";
    Line += Client.AdminName + del;
    Line += Client.Passowerd + del;
    Line += to_string(Client.Permission);
    return Line;
}

void UploadUserToFile(vector<stUser> vsClient) {
    fstream MyFile;
    MyFile.open(UserFile, ios::out);
    if (MyFile.is_open()) {
        string Line = "";
        for (stUser & Client : vsClient) {
            if (Client.isDelete == false) {
                Line = JoinTheUserRecord(Client);
                MyFile << Line << endl;
            }
        }
    }
    MyFile.close();



}
////////////////////////////////////////////////////////////////////////


//show user

void UserDisplay(stUser Client) {
    cout << left;
    cout << "|" << setw(15) << Client.AdminName;

    cout << "|" << setw(20) << Client.Passowerd;

    cout << "|" << setw(12) << Client.Permission;

    cout << endl;
}

void UserDisplayList() {
    vector<stUser> vsUser = UploadUsertFromRecord();
    cout << "\t\t Client (s) No(" << vsUser.size() << ")" << endl;
    cout << "----------------------------------------------------------\n";
    cout << left;
    cout << "|" << setw(15) << "Name ";

    cout << "|" << setw(20) << "Passowerd ";

    cout << "|" << setw(12) << "Permission";
    cout << "\n----------------------------------------------------------";
    cout << endl;
    for (int i = 0;i < vsUser.size();i++) {
       UserDisplay(vsUser[i]);
    }
    cout << "----------------------------------------------------------\n";
}

//////////////////////////////////////////////////////////////
//Delete User

bool isExistedUser(string Acc) {
    vector<stUser>vsClient = UploadUsertFromRecord();
    for (stUser& Client : vsClient) {
        if (Acc == Client.AdminName) return true;
    }
    return false;
}

string AskToDeleteUserNAme () {
    string Acc = "";
    cout << "Enter Admin Name  :";
    cin >> Acc;
    return Acc;
}

void IsExitedToDeleteUser(string Acc, vector<stUser>& vsClient) {

    for (stUser& Client : vsClient) {
        if (Acc == Client.AdminName) {
            Client.isDelete = true;
        }
    }
}

void DeletUser() {
    vector<stUser>vsClient = UploadUsertFromRecord();
    string Acc = AskToDeleteUserNAme();
    char is = 'y';
    if (Acc == "admin")
    {
        cout << "\nCannot update Super Admin!\n";
        return;
    }
    if (isExistedUser(Acc)) {

        cout << "\nDo You Want To Delete ? (y/n)";
        cin >> is;
        if (tolower(is) == 'y') {
            IsExitedToDeleteUser(Acc, vsClient);
            UploadUserToFile(vsClient);
        }

    }
    else {
        cout << "\nThis Account Dont Exit !!";
    }
}

void DeleteUserOption() {
    char is = 'y';

    do {
        system("cls");
        cout << "\t\tDelete User \n";
        cout << "----------------------------------------------------------\n";
        DeletUser();
        cout << "\n\nDo You Want To Delete Again ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

////////////////////////////////////////////////////////////////////
// Add New User 

void AskPermisssions(stUser& User) {
    char is = 'y';
    cout << "\nDO you Want to Give Access To Show Client ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 1; }
    cout << "\nDO you Want to Give Access To Add Client ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 2; }
    cout << "\nDO you Want to Give Access To Delete Client ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 4; }
    cout << "\nDO you Want to Give Access To Update Client ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 8; }
    cout << "\nDO you Want to Give Access To Find Client ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 16; }
    cout << "\nDO you Want to Give Access To Transaction ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 32; }
    cout << "\nDO you Want to Give Access To Manage User ?  (y/n) ";
    cin >> is;
    if (tolower(is) == 'y') { User.Permission += 64; }

}

stUser AskToAddUser(stUser  Client) {

    cout << "\t\tEnter Password :";
    cin >> Client.Passowerd;

    AskPermisssions(Client);
    return Client;
}

void AppendUserToFile(stUser Client) {
    fstream MyFile;
    MyFile.open(UserFile, ios::app);
    MyFile << JoinTheUserRecord(Client) << endl;
}

void AddNewUser() {
    string Acc = "";
    cout << "\tEnter User Name  ";
    cin >> Acc;
    char is = 'y';
    if (isExistedUser(Acc)) {
        cout << "\t\tThe Admin (" << Acc << ") Is Existed\n\n";
    }
    else {
        stUser Client;
        Client.AdminName = Acc;
        Client = AskToAddUser(Client);

        cout << "\nDo You Want To Add To File ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            AppendUserToFile(Client);
        }
    }
}

void AddNewUserOption() {
    char is = 'Y';

    do {
        system("cls");
        cout << "\t\tAdd New User \n";
        cout << "----------------------------------------------------------\n";
        AddNewUser();
        cout << "\n\nDo You Want To Add More Client ? (y/n)";
        cin >> is;
    } while (tolower(is) == 'y');

}

////////////////////////////////////////////////////////////////////////////
// update user 

void IsUserExitedToUpdate(string Acc, vector<stUser>& vsClient) {

    for (stUser& Client : vsClient) {
        if (Acc == Client.AdminName) {
            Client = AskToAddUser(Client);
            break;
        }
    }
}

void UpdateUser() {
    vector<stUser> vsClient =UploadUsertFromRecord();
    cout << "\tEnter User Name : ";
    string Acc = "";
    cin >> Acc;
    char is = 'y';
    stUser sClient;
    if (Acc == "admin")
    {
        cout << "\nCannot update Super Admin!\n";
        return;
    }
    if (isExistedUser(Acc)) {
        cout << "\n\t\tDo Want To Update ? (y/n) ";
        cin >> is;
        if (tolower(is) == 'y') {
            IsUserExitedToUpdate(Acc, vsClient);
            UploadUserToFile(vsClient);
        }


    }
    else {
        cout << "\nThis Admin Dont Exit !!";
    }

}

void UpdateUserOption() {
    char is = 'y';
    do {
        system("cls");
        cout << "\t\tUpdate User \n";
        cout << "----------------------------------------------------------\n";
        UpdateUser();
        cout << "\n\nDo You Want To Update Another User ? (y/n) ";
        cin >> is;
    } while (tolower(is) == 'y');
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Dispaly User
int displayUserMenue() {
    int choice = 0;
    cout << "\t\t\t[ User Menue ] ";
    cout << "\n----------------------------------------------------------\n";
    cout << "\t\t[1] Show Users List\n";
    cout << "\t\t[2] Add New User \n";
    cout << "\t\t[3] Delete User \n";
    cout << "\t\t[4] Update User \n";
    cout << "\t\t[5] Return To Main Menue ";
    cout << "\n----------------------------------------------------------\n";
    cout << "Choice a Number : ";
    cin >> choice;


    return choice;

}

void ListOfUserOption(int choice) {
    switch (choice) {
    case 1: {
        system("cls");
        UserDisplayList();
        break;
    }
    case 2: {
        system("cls");
        AddNewUserOption();
        break;
    }
    case 3: {
        system("cls");
        DeleteUserOption();
        break;
    }
    case 4:{
        system("cls");
        UpdateUserOption();
        break;
    }
    case 5: {
        system("cls");
        ListClientOption(DisplayMainMenue());
        break;
    }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
// Main Menue 
int DisplayMainMenue() {
    int choice = 0;

    cout << "\t\t\t[ Main Menue ] ";
    cout << "\n----------------------------------------------------------\n";
    cout << "\t\t[1] Show Client List\n";
    cout << "\t\t[2] Add New Client \n";
    cout << "\t\t[3] Delete Client \n";
    cout << "\t\t[4] Update Client \n";
    cout << "\t\t[5] Find Client  \n ";
    cout << "\t\t[6] Transaction \n ";
    cout << "\t\t[7] Mange User \n ";
    cout << "\t\t[8] Logo Out  ";
    cout << "\n----------------------------------------------------------\n";
    cout << "Choice a Number : ";
    cin >> choice;


    return choice;

}

void toContunue() {
    system("pause");
    system("cls");

    ListClientOption(DisplayMainMenue());
}

void toContunueUser() {
    int choice;
    do {
        system("pause");
        system("cls");
        choice = displayUserMenue();

        ListOfUserOption(choice);

    } while (choice != 5);
    
}
void toContunueTrans() {
    int choice;
    do {
            system("pause");

        system("cls");
        choice = displayTransactionMenue();

        ListOfTransactionOption(choice);

    } while (choice != 4);
}
void login();

void ListClientOption(int choice ,stUser User) {
    if (!IsPermisssion(User, choice)) {
        system("cls");
        cout << "\n\t\tYou dont Allowed To Use This !!!!!!!!\n\n\n";
        toContunue();
    }
    else {
    switch (choice) {
    case 1: {
        system("cls");
        ClientDisplayList();
        toContunue();
        break;
    }
    case 2: {
        system("cls");
        AddNewClientOption();
        toContunue();
        break;
    }
    case 3: {
        system("cls");
        DeleteClientOption();
        toContunue();
        break;
    }
    case 4:
    {
        system("cls");
        UpdateClientOption();
        toContunue();
        break;
    }
    case 5: {
        system("cls");
        FindClientOption();
        toContunue();
        break;

    }
    case 6: {
        system("cls");
        ListOfTransactionOption(displayTransactionMenue());
        toContunueTrans();
        break;

    }
    case 7: {
        system("cls");
        ListOfUserOption(displayUserMenue());
        toContunueUser();
        break;
    }
    case 8: {
        system("cls");
        login();
    }
    }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
bool IsPermisssion(stUser User, int Choice)
{
    if (User.Permission == -1)
        return true;
    switch (Choice)
    {
    case 1: return (User.Permission & 1);
    case 2: return (User.Permission & 2);
    case 3: return (User.Permission & 4);
    case 4: return (User.Permission & 8);
    case 5: return (User.Permission & 16);
    case 6: return (User.Permission & 32);
    case 7: return (User.Permission & 64);
    case 8: return true; // Logout
    default: return false;
    }
}
stUser UserData(string Acc) {
    vector<stUser>vsClient = UploadUsertFromRecord();
    for (stUser& Client : vsClient) {
        if (Acc == Client.AdminName) return Client;
    }
}

bool isExistedUserAndpassword(string Acc, string password) {
    vector<stUser>vsClient = UploadUsertFromRecord();
    for (stUser& Client : vsClient) {
        if (Acc == Client.AdminName) {
            if (password == Client.Passowerd) {
                return true;
            }
            else {
                cout << "\nYou Enter Invalid Password !! ";
                return false;
            }
        }

    }
    return false;
}
void login() {

    string name = "";
    string pasword = "";
    do {
        system("cls");
        cout << "\tLogin Page \n";
        cout << "-------------------------------------\n";
        cout << "\tLogin Name : ";
        cin >> name;
        cout << "\tLogin Password : ";
        cin >> pasword;
        if (isExistedUserAndpassword(name, pasword)) {
            system("cls");
            User1[0] = UserData(name);
            ListClientOption(DisplayMainMenue());
        }
        else {
            system("cls");
            cout << "\tLogin Page \n";
            cout << "-------------------------------------\n";
            cout << "You Enter Invalid \n\n";
            system("pause");
        }
    } while (!isExistedUserAndpassword(name, pasword));
}
int main()
{
    login();
}
