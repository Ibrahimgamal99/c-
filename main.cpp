#include <iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<windows.h>
#include<conio.h>
using namespace std;
#define s 9
string file;
int col = 0, row = 0,num;
struct stack
{
    int arr[10][2];
    int i;
};
stack st;
void menu();
struct node
{
    int data;
    node*right, *down;
};
node*head = NULL, *cr, *pr, *pd, *con;
//void Interface/////////////////////////////
void append(int d);
void setcolor(unsigned short color) ;                //The function that you'll use to
void display();
void chang(int r, int c, int n);
void load(string name);
void save(string name);
bool checkcol(int col, int num);
bool checkrow(int row, int num);
bool checkbox(int row, int col, int value);
bool ok (int row,int col,int num);
bool solve();
void createSudoku();
void newgame();
void play();
void menu();
//////////////////////////////////////////////8
void append(int d)
{

    cr = new node;
    cr->data = d;
    if (col == s)
    {
        col = 0;
        con = pd;
        pd->down = cr;
        pd = pd->down;
        pr = pd;
        con = con->right;
        row++;
    }
    if (head == NULL)
    {
        head = cr;
        pd = cr;
        pr = cr;
    }
    else
    {
        pr->right = cr;
        pr = pr->right;
        cr->right = NULL;
        cr->down = NULL;
        if (row>0 && col>0)
        {
            con->down = cr;
            con = con->right;
        }
    }
    col++;
}
void setcolor(unsigned short color)                 //The function that you'll use to
{
    //set the colour
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
void display()
{
    int i = 0;
    int j = 0;
    node*dp = head, *rp;
    setcolor(8);
    cout << "----------------------------";
    cout << endl;
    while (dp != NULL)
    {
        rp = dp;
        j = 0;
        while (rp != NULL)
        {
            if (j == 0)             //desien
            {
                setcolor(12);
                cout << "| ";
                setcolor(10);
            }
            //setcolor(1);
            cout << rp->data << " ";
            if (j == 2 || j == 5 || j == 8)
            {
                setcolor(12);
                cout << " | ";
                setcolor(10);
            }
            rp = rp->right;
            j++;
        }
        if (i == 2 || i == 5 || i == 8)
        {
            setcolor(8);
            cout << endl << "----------------------------";
            setcolor(15);

        }
        cout << endl;
        dp = dp->down;
        i++;

    }
}
void chang(int r, int c, int n)
{
    node*dp = head, *rp;
    for (int i = 0; i<r; i++)
        dp = dp->down;
    rp = dp;
    for (int j = 0; j<c; j++)
        rp = rp->right;
    cr = rp;
    cr->data = n;
}
void load()
{
    int x;
    ifstream f;
    f.open("data.txt");      //open of file to save asma2 elnase kolha
    while (!f.eof())
    {
        f >> file;
        cout << file << endl;
    }
    f.close();
    cout << "Enter file name to load  : ";
    cin >> file;
    ifstream r;
    r.open(file.c_str());        // hutb3 el2sm elenta da5alto
    while (!r.eof())
    {
        r >> x;
        append(x);             //7ot el x fe elinked list
    }
    r.close();
}
void save(string name)
{
    node*dp = head, *rp;
    ofstream fd;
    fd.open("data.txt", ios::app);
    fd << name << endl;
    fd.close();
    ofstream sv;
    sv.open(name.c_str());
    while (dp != NULL)
    {
        rp = dp;
        while (rp != NULL)
        {
            if (rp->right == NULL)
                sv << rp->data;
            else
                sv << rp->data << " ";
            rp = rp->right;
        }
        if (dp->down != NULL)
            sv << endl;
        dp = dp->down;
    }
    sv.close();
}
bool checkcol(int col, int num)
{
    node*dp = head, *rp;
    rp = dp;
    for (int j = 0; j<col; j++)
        rp = rp->right;
    dp = rp;
    for (int i = 0; i<s; i++)
    {
        if (dp->data == num)
            return false;
        dp = dp->down;

    }
    return true;
}
bool checkrow(int row, int num)
{
    node*dp = head, *rp;
    rp = dp;
    for (int j = 0; j<row; j++)
        dp = dp->down;
    rp = dp;
    for (int i = 0; i<s; i++)
    {
        if (rp->data == num)
            return false;
        rp = rp->right;

    }
    return true;
}
bool cheakbox(int row, int col, int value)
{
    node*dp = head, *rp;

    int r = 0;
    int c = 0;
    if (row >= 0 && row <= 2)
        r = 0;
    else if (row >= 3 && row <= 5)
        r = 3;
    else if (row >= 6 && row <= 8)
        r = 6;
    if (col >= 0 && col <= 2)
        c = 0;
    else if (col >= 3 && col <= 5)
        c = 3;
    else if (col >= 6 && col <= 8)
        c = 6;

    dp = head;
    for (int i = 0; i < r; i++)
        dp = dp->down;
    for (int i = 0; i < 3; i++)
    {
        rp = dp;
        for (int j = 0; j< c; j++)
            rp = rp->right;
        for (int i = 0; i < 3; i++)
        {
            if (rp->data == value)
                return false;
            rp = rp->right;
        }
        dp = dp->down;
    }
    return true;
}
bool ok(int row, int col, int num)
{
    return checkrow(row, num) && checkcol(col, num) && cheakbox(row, col, num);
}
bool zero(int &row, int &col)
{
    node*dp = head, *rp;
    for (row = 0; row<s; row++)
    {
        rp = dp;
        for (col = 0; col<s; col++)
        {
            if (rp->data == 0)
                return false;
            rp = rp->right;
        }
        dp = dp->down;
    }
    return true;
}
bool solve()
{
    int row, col;
    if (zero(row, col))
        return true;
    for (int num = 1; num<10; num++)
    {
        if (ok(row, col, num))
        {
            chang(row, col, num);
            if (solve())
                return true;
            chang(row, col, 0);
        }
    }
    return false;
}
void createSudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            append(0);
        }
    }
}
void newgame()
{
    createSudoku();
    int cnt = 20, i;
    cout << "Enter the level \n1-easy\n2-mid\n3-hard \n";
    cin >> i;
    if (i == 1)
        i = 30;
    else if (i == 2)
        i = 42;
    else if (i == 3)
        i = 55;
    else
    {
        cout << "Error Entry \n";
        exit(0);
    }
    srand(time(NULL));
    while (cnt--)
    {
        int row = rand() % 9, col = rand() % 9, value = rand() % 9;
        if (ok(row, col, value))
        {
            chang(row, col, value);
        }
    }
    if (solve())
    {
        srand(time(NULL));
        while (i--)
        {
            int row = rand() % 9, col = rand() % 9;
            chang(row, col, 0);
        }
    }
}
void redo(int row,int col)
{
    st.i++;
    st.arr[st.i][0]= row;
    st.arr[st.i][1]=col;
}
void undo(int &row,int &col)
{
    st.i--;
    row= st.arr[st.i][0];
    col=st.arr[st.i][1];
}
int cont=0;
void play()
{
    char c = 0;
    string name;
    int row, col, num,r,co,v;
    while (1)
    {
        display();
        do
        {
            cout << "Enter row : ";
            cin >> row;
        }
        while (row > 9);
        row--;
        do
        {
            cout << "Enter colum : ";
            cin >> col;

        }
        while (col > 9);
        col--;
        do
        {
            cout << "Enter number : ";
            cin >> num;
        }
        while (num > 9);
        if (ok(row, col, num))
        {
            chang(row, col, num);
            redo(row,col);
        }
        else
            play();
        display();
        cout << "'c' to solve to continue or 's' to save or 'e' to exit or 'u' to undo or : ";
        cin >> c;
        if (c == 'c' || c == 'C')
        {
            if (solve() == true)
                display();
            else
                cout << "No solution exists";
            break;
        }
        else if (c == 's' || c == 'S')
        {
            cout << "Enter name of game : ";
            cin >> name;
            save(name);
            break;
        }
        else if (c == 'y' || c == 'Y')
            continue;
        else if (c == 'u' || c == 'U')
        {
            undo(r,co);
            chang(r,co,0);
            cout<<r<<"  "<<co<<endl;
            getch();
        }
        else if (c =='e'||c =='E')
            break;
        system("cls");
        cont++;
    }
}
void menu()
{
    char c;
    int i = 0;
    system("cls");
    cout << "N- for new game\nL- for load game\nE- key for exit\n";
    cin >> c;
    if (c == 'l' || c == 'L')
    {
        load();
        play();
    }
    else if (c == 'n' || c == 'N')
    {
        newgame();
        play();
    }
    else
        exit(0);

}
int main()
{
    setcolor(15);
    menu();
    return 0;
}
