#include <iostream>
#include<fstream>
#include <string>
#include<cstdlib>
#include <algorithm>
using namespace std;
struct                                // struct array
{
    string name;
    float hours;
    float price;
    float tax;
    float gross;
    float net;
}
employ[10];
double total;
//read file
void rfile()
{
    int i;
    ifstream re;
    re.open("emp.txt");
    for (i = 0; i <= 10; i++)
    {
        re >> employ[i].name;
        re >> employ[i].hours;
        re >> employ[i].price;
    }
    re.close();
}
int size_of_struct(int &n)            //calculate size of struct .. passing number on (n)
{
    rfile();// to call function
    n = -1;
    for (int i = 0; i <= 10; i++)
        if (employ[i].price>0)       // when price is >0 then  n=n+1
            n++;
    return n;
}

void add()                          // function add Employee
{
    rfile();
    int n;
    size_of_struct(n);
    ofstream wr;
    wr.open("emp.txt", ios::app);
    cout << "Name  :  ";
    getline(cin, employ[0].name);
    wr << employ[0].name << endl;     // save in file
    cout << "Hours of month : ";
    cin >> employ[0].hours;
    while (1)                // handling if user input mistake or errors
    {
        if (cin.fail() || employ[0].hours <= 0 || employ[0].hours >= 720)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input Try again : ";
            cin >> employ[0].hours;
            continue;
        }
        break;
    }
    wr << employ[0].hours << endl;
    cout << "price in hours : ";
    cin >> employ[0].price;
    while (1)                                // handling if user input mistake or errors
    {
        if (cin.fail() || employ[0].price <= 0)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input  Try again : ";
            cin >> employ[0].price;
            continue;
        }

        break;
    }
    wr << employ[0].price << endl;
    cout << endl;

}

void tax()                     //calculate  tax
{
    int n;
    size_of_struct(n);
    for (int i = 0; i <= n; i++)
    {
        if (employ[i].gross< 0.00)
            employ[i].tax = 0;
        else if (employ[i].gross < 15000)
            employ[i].tax = 0.15 * employ[i].gross;
        else if (employ[i].gross < 30000)
            employ[i].tax = (employ[i].gross - 15000.00) * 0.16 + 2250.00;
        else if (employ[i].gross < 50000)
            employ[i].tax = (employ[i].gross - 30000.00) * 0.18 + 4650.00;
        else if (employ[i].gross < 80000)
            employ[i].tax = (employ[i].gross - 50000.00) * 0.20 + 8250.00;
        else if (employ[i].gross <= 150000)
            employ[i].tax = (employ[i].gross - 80000.00) * 0.25 + 14250.00;
        else
            employ[i].tax = 0;
    }
}

void compute()//calculate the gross and Nat salary and total salary of company
{
    rfile();
    int n;
    size_of_struct(n);
    float maxm = 0;
    float minm = employ[n].net;
    char c;
    cout << "\nG- Gross \n" << "N- Net salary \n" << "T- Total \n" << "X- Max\n" << "I- Min\n";
    cout << "Enter your choice >> ";
    cin >> c;
    cin.clear();
    cin.ignore(100, '\n');
    if (c == 'G' || c == 'g')                       //calculate gross ...gross = hours * price
    {
        for (int k = 0; k <= 10; k++)
            employ[k].gross = employ[k].hours*employ[k].price;
    }
    else if (c == 'N' || c == 'n')                  //calculate Net salary ...Net = gross + (gross*0.52)-tax
    {
        tax();
        for (int i = 0; i <= 10; i++)
            employ[i].net = employ[i].gross + (employ[i].gross*0.52) - employ[i].tax;
    }
    else if (c == 'T' || c == 't')                 //calculate total
    {
        for (int i = 0; i <= 10; i++)
            total += employ[i].net;

        cout << "\nTotal is : " << total << " $" << endl;
    }
    else if (c == 'X' || c == 'x')                  //calculate max salary
    {
        for (int x = 0; x<10; x++)
            if (employ[x].net>maxm)
            {
                maxm = employ[x].net;
            }
        for (int a = 0; a<10; a++)
            if (maxm == employ[a].net)
            {
                cout << " Name : " << employ[a].name << endl;
                cout << "gross : " << employ[a].gross << endl;
                cout << "tax : " << employ[a].tax << endl;
                cout << "Net salary : " << employ[a].net << endl;
                break;
            }
    }
    else if (c == 'i' || c == 'I') //calculate min salary
    {
        for (int s = 0; s<n; s++)
            if (employ[s].net < minm)
            {
                minm = employ[s].net;
            }
        for (int p = 0; p<10; p++)
            if (minm == employ[p].net)
            {
                cout << " Name : " << employ[p].name << endl;
                cout << "gross : " << employ[p].gross << endl;
                cout << "tax : " << employ[p].tax << endl;
                cout << "Net salary : " << employ[p].net << endl;
                break;
            }

    }
    else
        cout << "Please try again !!! \n";

}
void print_all()  // print all Employees and sort struct
{
    int n;
    size_of_struct(n);
    string temp_name;
    float temp,temp_hours,temp_price,temp_gross,temp_tax;
    for(int j=0; j<=n; j++) // sort struct array
    {
        for(int s=0; s<n; s++)
        {

            if(employ[j].net>employ[s].net)
            {
                temp=employ[j].net;            //sort net salary
                employ[j].net=employ[s].net;           // swap
                employ[s].net=temp;

                temp_name=employ[j].name;      // sort name
                employ[j].name=employ[s].name;        // swap
                employ[s].name=temp_name;

                temp_hours=employ[j].hours;     // sort hours
                employ[j].hours=employ[s].hours;      // swap
                employ[s].hours=temp_hours;

                temp_price=employ[j].price; // sort price
                employ[j].price=employ[s].price;     // swap
                employ[s].price=temp_price;

                temp_gross=employ[j].gross; //sort gross
                employ[j].gross=employ[s].gross;    // swap
                employ[s].gross=temp_gross;

                temp_tax=employ[j].tax; // sort tax
                employ[j].tax=employ[s].tax;      // swap
                employ[s].tax=temp_tax;

            }
        }
    }

    for (int i = 0; i<=n; i++)
    {
        cout << i + 1 << "- Name : " << employ[i].name << endl;
        cout << "hours : " << employ[i].hours << endl;
        cout << "price : " << employ[i].price << " $" << endl;
        cout << "gross : " << employ[i].gross << " $" << endl;
        cout << "tax : " << employ[i].tax << " $" << endl;
        cout << "Net salary : " << employ[i].net << " $" << endl;
    }
}
void print_one()
{
    int n;
    size_of_struct(n);
    for (int j = 0; j <= n; j++)// print name of all Employee
        cout << j + 1 << "- Name : " << employ[j].name << "  ";
    cout << endl;
    int num;
    cout << "Enter number of Employee to print : ";
    cin >> num;
    while (1)
    {
        if (cin.fail() || num <= 0)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Wrong input  Try again : ";
            cin >> num;
            continue;
        }

        break;
    }
    cout << num << "- Name : " << employ[num - 1].name << endl;
    cout << "gross : " << employ[num - 1].gross << endl;
    cout << "tax : " << employ[num - 1].tax << endl;
    cout << "Net salary : " << employ[num - 1].net << endl;
}
void print() // function to choose print all Employee or print one Employee
{
    int n;
    size_of_struct(n);
    int c;
    cout << "1- print all Employee data \n" << "2- print one Employee data \n";
    cin >> c;
    while (1)
    {

        if (cin.fail() || c <= 0)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Wrong input  Try again : ";
            cin >> c;
            continue;
        }

        break;

    }
    if (c == 1)       //case 1
        print_all();
    else if (c == 2)
        print_one();//case 2
    else
        cout << "Please try again Enter 1 or 2 \n";

}
void delet()//function delete one Employee
{
    int n;
    size_of_struct(n);
    int i, d;
    for (i = 0; i <= n; i++)
        cout << i + 1 << "- Name : " << employ[i].name << "    ";
    cout << endl;
    cout << "Enter number of Employees : ";
    cin >> d;
    while (1)
    {

        if (cin.fail() || d <= 0)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Worng input  Try again : ";
            cin >> d;
            continue;
        }

        break;
    }
    d -= 1;// d=d-1 because array start from 0
    for (int j = d; j <= n; j++)
    {
        employ[j].name = employ[j + 1].name;
        employ[j].hours = employ[j + 1].hours;
        employ[j].price = employ[j + 1].price;

    }
    ofstream temp;//make new text file
    temp.open("temp.txt");// temp to can  save all Employee not deleted
    {
        for (int a = 0; a<n; a++)
        {
            temp << employ[a].name << endl;
            temp << employ[a].hours << endl;
            temp << employ[a].price << endl;
        }
    }
    temp.close();
    remove("emp.txt");             // remove old file
    rename("temp.txt", "emp.txt");//rename temp  to emp text  to can read again

}
int main()
{
    char c;
    cout << "       ***************************        \n";
    cout << "******  welcome  to system payroll **********\n ";
    do
    {
        cout << "*************************************\n";
        cout << "A- Add Employee \n" << "P- Print Employees Data \n" << "C- compute \n";
        cout << "D- delete Employees \n";
        cout << "Q- Exit \n";
        cout << "Enter your choice >> ";
        cin >> c;
        cin.ignore(256, '\n');
        cin.clear();
        switch (c)
        {
        case 'A':
        case 'a':
            add();
            break;
        case 'P':
        case 'p':
            print();
            break;
        case 'C':
        case 'c':
            compute();
            break;
        case 'D':
        case 'd':
            delet();
            break;
        case 'Q':
        case 'q':
            exit(0);
            break;
        default:
            cout << "Please try again !!! \n";
        }

    }
    while (c != 'Q' || c != 'q');    // Exit

    return 0;
}
