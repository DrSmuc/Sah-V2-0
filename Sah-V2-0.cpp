#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<string.h>
using namespace std;

void naslov()
{
    cout << "      :::::           ########            |||             |||      " << endl;
    cout << "   ///    \\\\\\        ##########           |||             |||      " << endl;
    cout << "   ###              ///      \\\\\\          |||             |||      " << endl;
    cout << "   ###             ///        \\\\\\         |||             |||      " << endl;
    cout << "   ###            ///          \\\\\\        |||)))))))))))))|||      " << endl;
    cout << "     \\\\\\         ///@@@@@@@@@@@@\\\\\\       |||(((((((((((((|||      " << endl;
    cout << "       ###      ///@@@@@@@@@@@@@@\\\\\\      |||             |||      " << endl;
    cout << "       ###     ///                \\\\\\     |||             |||      " << endl;
    cout << "       ###    ///                  \\\\\\    |||             |||      " << endl;
    cout << "\\\\\\   ///    ///                    \\\\\\   |||             |||      " << endl;
    cout << "  ::::      ///                      \\\\\\  |||             |||      " << endl;
    cout << "" << endl;
}

struct user
{
    char ime[51];
    short int win = 0;
    short int los = 0;
};

void new_user(user* a, int& br_user)
{
    system("cls");
    cout << "Ime novog igraca:" << endl;
    cin.ignore();
    cin.getline(a[br_user].ime, 51);
    br_user++;
}
bool poIme(user a, user b) { return (strcmp(a.ime, b.ime)>0) ? true : false; }
bool poWin(user a, user b) { return (a.win < b.win) ? true : false; }
bool poLos(user a, user b) { return (a.los < b.los) ? true : false; }

void pause()
{
    cout << endl << "Pritisnite enter za nastavak...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

int main()
{
    int br_user;
    user a[50];

    fstream users;
    users.open("users.bin", ios::in | ios::binary);
    users.read((char*)&br_user, sizeof(br_user));
    users.read((char*)&a, sizeof(user) * br_user);
    users.close();
    sort(a, a + br_user, poIme);

    int izbor;

    while (1)
    {
        system("cls");
        naslov();
        cout << "1. nova igra" << endl;
        cout << "2. match history" << endl;
        cout << "3. user menagment" << endl;
        cout << "4. leaderboard" << endl;
        cout << "5. pravila" << endl;
        cout << "6. izlaz" << endl;
        cout << "vas odabir: ";
        cin >> izbor;

        if (izbor == 1)
        {
            string player1, player2;

            while (1)
            {
                int izbor_user1, izbor_user2;
                while (1) {
                    system("cls");
                    cout << "Odabir P1:" << endl;
                    int i;
                    for (i = 0; i < br_user; i++)
                        cout << i + 1 << ". " << a[i].ime << endl;
                    cout << ++i << ". " << "Anonim" << endl;
                    cout << ++i << ". " << "New user" << endl << "vas izbor: ";
                    cin >> izbor_user1;
                    izbor_user1--;
                    if (izbor_user1 == i - 1)
                    {
                        new_user(a, br_user);
                        player1 = a[br_user - 1].ime;
                        sort(a, a + br_user, poIme);
                        break;
                    }
                    else if (izbor_user1 == i - 2)
                    {
                        player1 = "Anonim";
                        break;
                    }
                    else if (izbor_user1 < 0 || izbor_user1 >= i)
                        cout << endl << "Krivi unos!" << endl;
                    else
                    {
                        player1 = a[izbor_user1].ime;
                        break;
                    }
                    pause();
                }

                while (1) {
                    system("cls");
                    cout << "Odabir P2:" << endl;
                    int i;
                    for (i = 0; i < br_user; i++)
                    {
                        if (a[i].ime == player1)
                        {
                            cout << "\033[34m" << i + 1 << ". " << a[i].ime << "  P1" << endl;
                            cout << "\033[37m";
                        }
                        else
                            cout << i + 1 << ". " << a[i].ime << endl;
                    }
                    cout << ++i << ". " << "Anonim" << endl;
                    cout << ++i << ". " << "New user" << endl << "vas izbor: ";
                    cin >> izbor_user2;
                    izbor_user2--;
                    if (izbor_user2 == izbor_user1 && izbor_user1 < i - 2) {
                        cout << "Ne moze biti isti igrac!" << endl;
                        pause();
                    }
                    else if (izbor_user2 == i - 1)
                    {
                        new_user(a, br_user);
                        player2 = a[br_user - 1].ime;
                        sort(a, a + br_user, poIme);
                        break;
                    }
                    else if (izbor_user2 == i - 2) {
                        if (player1 == "Anonim")
                        {
                            player1 = "Anonim 1";
                            player2 = "Anonim 2";
                        }
                        else
                            player2 = "Anonim";
                        break;
                    }
                    else
                    {
                        player2 = a[izbor_user2].ime;
                        break;
                    }
                }

                system("cls");
                cout << "\033[34m" << "P1  " << player1 << endl;
                cout << "\033[31m" << "P2  " << player2 << endl << endl;
                cout << "\033[37m" << "Continue [1]" << endl << "Change [0]" << endl;
                cin >> izbor_user1;
                if (izbor_user1 == 1)
                    break;
            }

        }

        else if (izbor == 2)
        {

        }

        else if (izbor == 3)
        {
            //user menager

            int menager_izbor;
            while (1)
            {
                system("cls");
                for (int i = 0; i < br_user; i++)
                {
                    cout << a[i].ime << "\t\t" << a[i].win << "\t\t" << a[i].los << endl;
                }
                cout << endl;
                cout << "1. sortiraj" << endl;
                cout << "2. dodaj" << endl;
                cout << "3. izbrisi" << endl;
                cout << "4. promijeni" << endl;
                cout << "5. izlaz" << endl;
                cout << "Izbor: ";
                cin >> menager_izbor;

                if (menager_izbor == 1)
                {
                    while (1)
                    {
                        system("cls");
                        cout << "1. po imenu" << endl;
                        cout << "2. po pobjedama" << endl;
                        cout << "3. po porazima" << endl;
                        cout << "4. povratak" << endl;
                        cin >> menager_izbor;

                        switch (menager_izbor)
                        {
                        case 1:
                            sort(a, a + br_user, poIme);
                            break;
                        case 2:
                            sort(a, a + br_user, poWin);
                            break;
                        case 3:
                            sort(a, a + br_user, poLos);
                            break;
                        case 4:
                            cout << "Povratak!" << endl;
                            pause();
                            break;
                        default:
                            cout << "Krivi unos!" << endl;
                            pause();
                        }
                    }
                }
                else if (menager_izbor == 2)
                    new_user(a, br_user);
                /*else if (menager_izbor == 3)
                {
                    char brisati[51];
                    cout << "Koga zelite izbrisati:" << endl;
                    cin.ignore();
                    cin.getline(brisati, 51);
                    remove_if(a, a + br_user, a->ime==brisati);
                }*/
            }
        }

        else if (izbor == 4)
        {

        }

        else if (izbor == 5)
        {

        }

        else if (izbor == 6)
        {
            cout << "Izlaz iz programa!" << endl;
            break;
        }

        else
        {

        }
    }

    return 0;
}

