#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std; 
struct stclient
{
    string accountnumber;
    string pincode;
    string name;
    string phonenum;
    double accountbalance = 0.0;
    bool deletemark = false;
};
enum enatmoptions {
    quickdw = 1, normalw = 2, deposit = 3, checkbalance = 4, logout = 5
};
void Login();
void  ShowMainMenu();
stclient currentclient;
void  gobackmainmenu()
{
    cout << "press any key to go back to main menu ..";
    system("pause>0");
    ShowMainMenu();

}
vector<string> split(string st, string del)
{
    vector <string> v_string;
    short pos = 0;
    string newst;
    while ((pos = st.find(del)) != string::npos)
    {
        newst = st.substr(0, pos);
        if (newst != "")
            v_string.push_back(newst);


        st.erase(0, pos + del.length());


    }
    if (st != "")
        v_string.push_back(st);


    return v_string;
}
stclient convertlinetorecords(string line, string del)
{
    stclient client;
    vector <string>v_string;
    v_string = split(line, "%/%/%");
    client.accountnumber = v_string.at(0);
    client.pincode = v_string.at(1);
    client.name = v_string.at(2);
    client.phonenum = v_string.at(3);
    client.accountbalance = stod(v_string.at(4));

    return client;




}
string convertrecodstoline(stclient c, string del = "%/%/%")
{
    string newst = "";
    newst += c.accountnumber + del;
    newst += c.pincode + del;
    newst += c.name + del;
    newst += c.phonenum + del;
    newst += to_string(c.accountbalance);
    return newst;

}
void saveclientsdatatofile(string filename, vector <stclient>& vclient)
{
    fstream MyFile;
    MyFile.open(filename, ios::out);
    string dataline;

    if (MyFile.is_open())
    {
        for (stclient& c : vclient)
        {
            if (c.deletemark == false)
            {
                dataline = convertrecodstoline(c);
                MyFile << dataline << endl;

            }
        }
    }
    MyFile.close();
}
vector <stclient>loadclientsdatafromfile(string FileName)
{
    vector <stclient> vclient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stclient client;
        while (getline(MyFile, Line))
        {
            client = convertlinetorecords(Line, "%/%/%");
            vclient.push_back(client);

        }
        MyFile.close();
    }
    return vclient;
}
bool FindUserByaccountnumberAndpincode(string accountnumber, string pincode, stclient& c)
{

    vector <stclient> vclient = loadclientsdatafromfile("users.txt");

    for (stclient U : vclient)
    {

        if (U.accountnumber == accountnumber && U.pincode == pincode)
        {
            c = U;
            return true;
        }

    }
    return false;

}
bool  LoadUserInfo(string accountnumber, string pincode)
{

    if (FindUserByaccountnumberAndpincode(accountnumber, pincode, currentclient))
        return true;
    else
        return false;

}
void   drawalancescreen()
{
    cout << "=============================================================" << endl;
    cout << "                         BALANCE SCREEN                        " << endl;
    cout << "=============================================================" << endl;


}

void balancescreen()
{
    system("cls");
    drawalancescreen();
    cout << " your balance is = " << currentclient.accountbalance << endl;
    gobackmainmenu();

}
void   drawdepositscreen()
{
    cout << "=============================================================" << endl;
    cout << "                        DEPOSIT SCREEN                       " << endl;
    cout << "=============================================================" << endl;


}
void depositscreen()
{
    system("cls");
    vector <stclient > vclient = loadclientsdatafromfile("users.txt");
    double amounttodeposit = 0;
    char ans = 'n';
   
    drawdepositscreen();
    do {
        cout << "please enter positive amount to deposit ";
        cin >> amounttodeposit;

    } while (amounttodeposit < 0 );
    cout << "are you sure to perform this trinsaction ? y/n ";
    cin >> ans;
    if (tolower(ans) == 'y')
    {
        currentclient.accountbalance += amounttodeposit;

    }
    saveclientsdatatofile("users.txt", vclient);
    cout << "done successfully your balance now ";
    cout << currentclient.accountbalance << endl;
    gobackmainmenu();

}
void   drawnormalwscreen()
{
    cout << "=============================================================" << endl;
    cout << "                 NORMAL WITHDRAW SCREEN                       " << endl;
    cout << "=============================================================" << endl;


}
void   normwithscreen()
{
    system("cls");
    drawnormalwscreen();
    vector <stclient > vclient = loadclientsdatafromfile("users.txt");
    int ammountnormalwithdraw = 0;
    char ans = 'n';

    do {
        cout << "please enter an amount multiaple of 5 ";
        cin >> ammountnormalwithdraw;
       

    } while (ammountnormalwithdraw %5!=0);
    if (ammountnormalwithdraw > currentclient.accountbalance)
    {
        cout << "the ammount exeded your balance make anoher choice " << endl;
        cout << "press any key to continue ...";
        system("pause>0");
        normwithscreen();

    }
    cout << "are you sure to perform this trinsaction ? y/n ";
    cin >> ans;
    if (tolower(ans) == 'y')
    {
        currentclient.accountbalance -= ammountnormalwithdraw;
       

    }
    saveclientsdatatofile("users.txt", vclient);
    cout << "done successfully your balance now ";
    cout << currentclient.accountbalance << endl;
    gobackmainmenu();

}
int  performwithchoices(short choice)
{
   
    if (choice == 9)
    {
        ShowMainMenu();
       
    }
      
    switch (choice)
    {
    case 1:
    {
        return 20;
        break;
    }
    case 2:
    {
        return 50;
        break;
    }
    case 3:
    {
        return 100;
        break;
    }
    case 4:
    {
        return 200;
        break;
    }
    case 5:
    {
        return 400;
        break;
    }
    case 6:
    {
        return 600;
        break;
    }
    case 7:
    {
        return 800;
        break;
    }
    case 8:
    {
        return 1000;
        break;
    }
    defult :
    return 0;

    }


}
void   drawquickwscreen()
{
   
    cout << "=============================================================" << endl;
    cout << "                 Quick WITHDRAW SCREEN                       " << endl;
    cout << "=============================================================" << endl;
    cout << "[1] 20             [2] 50" << endl;
    cout << "[3] 100            [4] 200" << endl;
    cout << "[5] 400            [6] 600" << endl;
    cout << "[7] 800            [8] 1000" << endl;
    cout << "[9] EXIT" << endl;
    cout << "your balance is" << currentclient.accountbalance << endl;
    cout << endl;

   

}
void  quichwithscreen()
{
    system("cls");
    drawquickwscreen();
    vector <stclient > vclient = loadclientsdatafromfile("users.txt");
    char ans = 'n';
    short choice = 0;
    int ammount = 0;
    while (choice < 1 || choice >9)
    {
        cout << "chose what to do from [1] to [9]?";
        cin >> choice;
    }
  
   ammount= performwithchoices(choice);
   
       
        if (ammount > currentclient.accountbalance)
        {
            cout << "the ammount exeded your balance make anoher choice " << endl;
            cout << "press any key to continue ...";
            system("pause>0");
            quichwithscreen();

        }
   
    cout << "are you sure to perform this trinsaction ? y/n ";
    cin >> ans;
    if (tolower(ans) == 'y')
    {
        currentclient.accountbalance -= ammount;


    }
    saveclientsdatatofile("users.txt", vclient);
    cout << "done successfully your balance now ";
    cout << currentclient.accountbalance << endl;
    gobackmainmenu();

}
void performmenuoptions(enatmoptions option)
{
    switch (option)
    {
    case quickdw:
    {
        quichwithscreen();
        break;
    }
    case normalw:
    {
        normwithscreen();
        break;

    }
    case deposit:
    {
        depositscreen();
        break;

    }
    case checkbalance:
    {
        balancescreen();
        break;

    }
    case logout:
    {
        Login();
        break;

    }

    }

}
short readmenuoption()
{
    short ans = 0;
    do {
        cout << "enter option [ 1 - 5 ] ??";
        cin >> ans;
    } while (ans > 5 || ans <= 0);
    return ans;
}
void  ShowMainMenu()
{
    system("cls");
    cout << "--------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "\t   ATM  Main Menu Screen    " << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "\t[1] Quick Withdraw " << endl;
    cout << "\t[2] Normal Withdraw " << endl;
    cout << "\t[3] Deposit " << endl;
    cout << "\t[4] Check Balance " << endl;
    cout << "\t[5] Logout " << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------" << endl;

    performmenuoptions((enatmoptions)readmenuoption());


}
void adddatatofile(string filename, string data)
{
    fstream MyFile;
    MyFile.open(filename, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << data << endl;

        MyFile.close();
    }

}
void Login()
{
    system("cls");
    bool LoginFaild = false;

    string accountnumber, pincode;
    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaid Username/Password!\n";
        }

        cout << "Enter AccountNumber? ";
        cin >> accountnumber;

        cout << "Enter Pincode? ";
        cin >> pincode;

        LoginFaild = !LoadUserInfo(accountnumber, pincode);

    } while (LoginFaild);

    ShowMainMenu();

}

int main()
{
    Login();

   


}

