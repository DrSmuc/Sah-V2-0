#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

struct user
{
    char ime[51];
    short int win = 0;
    short int los = 0;
    short int drw = 0;
};

struct rep
{
    char player1[51];
    char player2[51];
    char winner[51];
};

int main()
{
    int br=4;
    user a[50];
    rep b[5];
    strcpy(a[0].ime, "Gulis");
    strcpy(a[1].ime, "Cacic");
    strcpy(a[2].ime, "Zlaja");
    strcpy(a[3].ime, "Hledik");
    for (int i=0;i<4;i++)
    {
        a[i].win=0;
        a[i].los=0;
        a[i].drw=0;
    }
    for (int i=0;i<4;i++)
    {
        strcpy(b[i].player1, "Empty");
        strcpy(b[i].player2, "Empty");
        strcpy(b[i].winner, "Empty");
    }
    fstream file;
    file.open("data/users.bin", ios::out|ios::binary);
    file.write((char*)&br, sizeof(br));
    file.write((char*)&a, sizeof(user)*4);
    file.close();

    file.open("data/replays/list.bin", ios::out|ios::binary);
    file.write((char*)&b, sizeof(rep)*5);
    file.close();
}
