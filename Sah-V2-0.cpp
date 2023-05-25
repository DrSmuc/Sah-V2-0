#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<string.h>
#include<Windows.h>
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
    short int drw = 0;
};

void pause() //hvala profesore :)
{
    cout << endl << "Pritisnite enter za nastavak...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

void new_user(user* a, int& br_user)
{
    bool ponoviti;
    do
    {
        ponoviti = false;
        system("cls");
        cout << "Ime novog igraca:" << endl;
        cin.ignore();
        cin.getline(a[br_user].ime, 51);
        for (int i = 0; i < br_user; i++)
        {
            if (strcmp(a[br_user].ime, a[i].ime) == 0)
            {
                cout << "Ime vec postoji, izaberite drugo!" << endl;
                ponoviti = true;
                pause();
            }
        }
    } while (ponoviti);
    br_user++;
}

void remove_user(user* a, int& br_user, char *name)
{
    for (int i = 0; i < br_user; i++)
    {
        if (strcmp(a[i].ime, name) == 0)
        {
            for (int j = i; j < br_user - 1; j++)
            {
                a[j] = a[j + 1];
            }
            return;
        }
    }
}

bool poIme(user a, user b) { return (strcmp(a.ime, b.ime)<0) ? true : false; }
bool poWin(user a, user b) { return (a.win > b.win) ? true : false; }
bool poLos(user a, user b) { return (a.los > b.los) ? true : false; }
bool poDrw(user a, user b) { return (a.drw > b.drw) ? true : false; }

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

            //stari kod
            SetConsoleOutputCP(65001);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            char q[] = "\xE2\x99\x94 ";
            SetConsoleTextAttribute(hConsole, 16);
            cout << q;
            SetConsoleTextAttribute(hConsole, 15);
            pause();

        }

        else if (izbor == 2)
        {
            //prvo treba alg. za citanje 
        }

        else if (izbor == 3)
        {
            //user menager

            int menager_izbor;
            while (1)
            {
                system("cls");
                cout << "Ime\twin\tloss\tdraw" << endl;
                cout << "====================================" << endl;
                for (int i = 0; i < br_user; i++)
                    cout << a[i].ime << "\t" << a[i].win << "\t" << a[i].los << "\t" << a[i].drw << endl;
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
                        cout << "4. po izjednacenjima" << endl;
                        cout << "5. povratak" << endl;
                        cin >> menager_izbor;

                        if (menager_izbor == 1)
                        {
                            sort(a, a + br_user, poIme);
                            break;
                        }
                        else if (menager_izbor == 2)
                        {
                            sort(a, a + br_user, poWin);
                            break;
                        }
                        else if (menager_izbor == 3)
                        {
                            sort(a, a + br_user, poLos);
                            break;
                        }
                        else if (menager_izbor == 4)
                        {
                            sort(a, a + br_user, poDrw);
                            break;
                        }
                        else if (menager_izbor == 5)
                        {
                            cout << "Povratak!" << endl;
                            pause();
                            break;
                        }
                        else
                        {
                            cout << "Krivi unos!" << endl;
                            pause();
                        }
                    }
                }
                else if (menager_izbor == 2)
                    new_user(a, br_user);
                else if (menager_izbor == 3)
                {
                    char brisati[51];
                    cout << endl << "Koga zelite izbrisati:" << endl;
                    cin.ignore();
                    cin.getline(brisati, 51);
                    remove_user(a, br_user, brisati);
                    br_user--;
                }
                else if (menager_izbor == 4)
                {
                    char promijeniti[51];
                    int i_promjena;
                    bool ponoviti;

                    do
                    {
                        ponoviti = true;
                        cout << endl << "Koje ime zelite promijeniti:" << endl;
                        cin.ignore();
                        cin.getline(promijeniti, 51);
                        for (int i = 0; i < br_user; i++)
                        {
                            if (strcmp(a[i].ime, promijeniti) == 0)
                            {
                                i_promjena = i;
                                ponoviti = false;
                                break;
                            }
                        }
                    } while (ponoviti);

                    do
                    {
                        system("cls");
                        cout << a[i_promjena].ime << "\t" << a[i_promjena].win << "\t" << a[i_promjena].los << "\t" << a[i_promjena].drw << endl;
                        ponoviti = false;
                        cout << endl << "Upisite novo ime:" << endl;
                        cin.getline(a[i_promjena].ime, 51);
                        for (int i = 0; i < br_user; i++)
                        {
                            if (strcmp(a[br_user].ime, a[i].ime) == 0 && i != i_promjena)
                            {
                                cout << "Ime vec postoji, izaberite drugo!" << endl;
                                ponoviti = true;
                                pause();
                            }
                        }
                    } while (ponoviti);

                    cout << endl << "Novi broj pobjeda:" << endl;
                    cin >> a[i_promjena].win;
                    cout << endl << "Novi broj poraza:" << endl;
                    cin >> a[i_promjena].los;
                    cout << endl << "Novi broj izjednacenja:" << endl;
                    cin >> a[i_promjena].drw;
                }
                else if (menager_izbor == 5)
                {
                    cout << "Povratak!" << endl;
                    pause();
                    break;
                }
                else
                {
                    cout << "Krivi unos!" << endl;
                    pause();
                }
            }
        }

        else if (izbor == 4)
        {
            system("cls");
            sort(a, a + br_user, poWin);
            cout << "Ime\t|   pobjede\t|     porazi\t|   izjednacenja" << endl;
            cout << "=============================================================" << endl;
            for (int i = 0; i < br_user; i++)
                cout << a[i].ime << "\t|\t" << a[i].win << "\t|\t" << a[i].los << "\t|\t" << a[i].drw << endl;
            cout << endl;
            pause();
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

    users.open("users.bin", ios::out | ios::binary);
    users.write((char*)&br_user, sizeof(br_user));
    users.write((char*)&a, sizeof(user)* br_user);
    users.close();

    return 0;
}

