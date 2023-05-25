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

            char  figure[13], stupac_pretvarac[8];
            int ploca[8][8], krajigre = 0, rosada_b1 = 1, rosada_b2 = 1, rosada_c1 = 1, rosada_c2 = 1, pozicija_ck_i = 0, pozicija_bk_i = 7, pozicija_bk_j = 4, pozicija_ck_j = 4;
            cout << "Upisite ime bijeli: \n" << endl;;
            

            cout << "\n\nFigure: \n\nB - BIJELA FIGURA \nC - CRNA FIGURA \nP - PJESACI \nT - TOP \nS - SKAKAC \nL - LOVAC \nQ - KRALJICA \nK - KRALJ\n\n" << endl;

            cout << "\nPomicanje figura:\n\nZa pomicanje figura upisite koordinate \npolja figure koju hocete pomaknuti te potom mjesta gdje je zelite pomaknuti.\nPrvo upisite stupac a potom redak.\n\n\n" << endl;


            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    ploca[i][j] = 13;

            figure[0] = 'P';
            figure[1] = 'P';
            figure[2] = 'T';
            figure[3] = 'T';
            figure[4] = 'S';
            figure[5] = 'S';
            figure[6] = 'L';
            figure[7] = 'L';
            figure[8] = 'Q';
            figure[9] = 'Q';
            figure[10] = 'K';
            figure[11] = 'K';


            ploca[0][0] = 3;
            ploca[0][1] = 5;
            ploca[0][2] = 7;
            ploca[0][3] = 9;
            ploca[0][4] = 11;
            ploca[0][5] = 7;
            ploca[0][6] = 5;
            ploca[0][7] = 3;
            ploca[7][0] = 2;
            ploca[7][1] = 4;
            ploca[7][2] = 6;
            ploca[7][3] = 8;
            ploca[7][4] = 10;
            ploca[7][5] = 6;
            ploca[7][6] = 4;
            ploca[7][7] = 2;

            for (int i = 0; i < 8; i++)
                for (char j = 'A'; j < 'I'; j++)
                    stupac_pretvarac[i] = j;

            for (int j = 0; j < 8; j++)
                ploca[1][j] = 1;
            for (int j = 0; j < 8; j++)
                ploca[6][j] = 0;

            int pb = 0;

            for (int i = 'a'; i < 'i'; i++)
            {
                stupac_pretvarac[pb] = i;
                pb++;
            }

            int napotezu = 1;

            while (1)
            {
                int unos_reda_pomak, unos_stupca_pocetni, reset = 1, unos_stupca_pomak, unos_reda_pocetni, red_pocetni, red_pomak, bsah_dd = 0, bsah_dl = 0, bsah_gl = 0, bsah_gd = 0, bsah_g = 0, bsah_desno = 0, bsah_d = 0, bsah_l = 0, bsah_pijun = 0, bsah_konj = 0, csah_dd = 0, csah_dl = 0, csah_gl = 0, csah_gd = 0, csah_g = 0, csah_desno = 0, csah_d = 0, csah_l = 0, csah_pijun = 0, csah_konj = 0;
                char stupac_pocetni, stupac_pomak, zamjena_figure;

                if (napotezu % 2 != 0)
                {
                    for (int t = 8, i = 0; i < 8; i++)
                    {
                        cout << "|";
                        for (int j = 0; j < 8; j++)
                        {
                            int t = ploca[i][j];
                            if (t % 2 == 0 && t != 13 && t != 14 && t != 15)
                            {
                                cout << "B";
                                cout << figure[t] << "|";
                            }
                            if (t % 2 != 0 && t != 13 && t != 14 && t != 15)
                            {
                                cout << "C";
                                cout << figure[t] << "|";
                            }
                            if (t == 13 || t == 14 || t == 15)
                                cout << "  |";
                        }
                        cout << " " << t << endl;
                        t--;
                    }
                    cout << " ";
                    for (char i = 'A'; i < 'I'; i++)
                    {
                        cout << i << "  ";
                    }
                    cout << endl << endl;
                }

                else
                {
                    for (int t = 1, i = 7; i >= 0; i--)
                    {
                        cout << "|";
                        for (int j = 7; j >= 0; j--)
                        {
                            int t = ploca[i][j];
                            if (t % 2 == 0 && t != 13 && t != 14 && t != 15)
                            {
                                cout << "B";
                                cout << figure[t] << "|";
                            }
                            if (t % 2 != 0 && t != 13 && t != 14 && t != 15)
                            {
                                cout << "C";
                                cout << figure[t] << "|";
                            }
                            if (t == 13 || t == 14 || t == 15)
                                cout << "  |";
                        }
                        cout << " " << t << endl;
                        t++;
                    }
                    for (char i = 'H'; i >= 'A'; i--)
                    {
                        cout << "  " << i;
                    }
                    cout << endl << endl;
                }


                if (napotezu % 2 != 0)
                    cout << player1 << endl;
                else
                    cout << player2 << endl;
                cout << "Upisite polje figure koju zelite pomaknuti:\n" << endl;
                cin >> stupac_pocetni >> red_pocetni;
                cout << "Upisite polje gdje zelite pomaknuti figuru:\n" << endl;
                cin >> stupac_pomak >> red_pomak;

                unos_reda_pocetni = 8 - red_pocetni;

                for (int i = 0; i < 8; i++)
                    if (stupac_pocetni == stupac_pretvarac[i])
                        unos_stupca_pocetni = i;


                unos_reda_pomak = 8 - red_pomak;

                for (int i = 0; i < 8; i++)
                    if (stupac_pomak == stupac_pretvarac[i])
                        unos_stupca_pomak = i;

                if (ploca[unos_reda_pocetni][unos_stupca_pocetni] % 2 != napotezu % 2 && (ploca[unos_reda_pomak][unos_stupca_pomak] % 2 == napotezu % 2 || ploca[unos_reda_pomak][unos_stupca_pomak] == 13))//nesto tu
                {
                    switch (ploca[unos_reda_pocetni][unos_stupca_pocetni])
                    {
                    case 0:
                        //crni pijun
                        if (unos_reda_pomak == unos_reda_pocetni - 1 && unos_stupca_pocetni == unos_stupca_pomak)
                            reset = 0;
                        if (unos_reda_pocetni == 6 && unos_reda_pomak == unos_reda_pocetni - 2 && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            reset = 0;
                        }
                        if ((ploca[unos_reda_pomak][unos_stupca_pomak] == 15 || ploca[unos_reda_pomak][unos_stupca_pomak] != 13) && unos_reda_pomak + 1 == unos_reda_pocetni && (unos_stupca_pomak + 1 == unos_stupca_pocetni || unos_stupca_pomak - 1 == unos_stupca_pocetni))
                            reset = 0;
                        break;
                    case 1:
                        //bijeli pijun
                        if (unos_reda_pomak == unos_reda_pocetni + 1 && unos_stupca_pocetni == unos_stupca_pomak)
                            reset = 0;
                        if (unos_reda_pocetni == 1 && unos_reda_pomak == unos_reda_pocetni + 2 && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            reset = 0;
                        }
                        if ((ploca[unos_reda_pomak][unos_stupca_pomak] == 14 || ploca[unos_reda_pomak][unos_stupca_pomak] != 13) && unos_reda_pomak - 1 == unos_reda_pocetni && (unos_stupca_pomak + 1 == unos_stupca_pocetni || unos_stupca_pomak - 1 == unos_stupca_pocetni))
                            reset = 0;
                        break;
                    case 2:
                        //crni top
                        if (unos_stupca_pocetni == 0)
                            rosada_b1 = 0;
                        if (unos_stupca_pocetni == 7)
                            rosada_b2 = 0;
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13 && ploca[unos_reda_pocetni][i] != 14 && ploca[unos_reda_pocetni][i] != 15)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni - 1; i > unos_stupca_pomak; i--)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13 && ploca[unos_reda_pocetni][i] != 14 && ploca[unos_reda_pocetni][i] != 15)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1; i > unos_reda_pomak; i--)
                            {
                                if (ploca[i][unos_stupca_pomak] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[i][unos_reda_pomak] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 3:
                        //bijeli top
                        if (unos_stupca_pocetni == 0)
                            rosada_c1 = 0;
                        if (unos_stupca_pocetni == 7)
                            rosada_c2 = 0;
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[i][unos_stupca_pomak] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni - 1; i > unos_stupca_pomak; i--)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13 && ploca[unos_reda_pocetni][i] != 14 && ploca[unos_reda_pocetni][i] != 15)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1; i > unos_reda_pomak; i--)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 4:
                        //crni skakac
                        if (unos_reda_pomak == unos_reda_pocetni - 2 && unos_stupca_pomak == unos_stupca_pocetni - 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 2 && unos_stupca_pomak == unos_stupca_pocetni + 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 1 && unos_stupca_pomak == unos_stupca_pocetni - 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 1 && unos_stupca_pomak == unos_stupca_pocetni + 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 1 && unos_stupca_pomak == unos_stupca_pocetni - 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 1 && unos_stupca_pomak == unos_stupca_pocetni + 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 2 && unos_stupca_pomak == unos_stupca_pocetni - 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 2 && unos_stupca_pomak == unos_stupca_pocetni + 1)
                            reset = 0;
                        break;
                    case 5:
                        //bijeli skakac
                        if (unos_reda_pomak == unos_reda_pocetni - 2 && unos_stupca_pomak == unos_stupca_pocetni - 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 2 && unos_stupca_pomak == unos_stupca_pocetni + 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 1 && unos_stupca_pomak == unos_stupca_pocetni - 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni - 1 && unos_stupca_pomak == unos_stupca_pocetni + 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 1 && unos_stupca_pomak == unos_stupca_pocetni - 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 1 && unos_stupca_pomak == unos_stupca_pocetni + 2)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 2 && unos_stupca_pomak == unos_stupca_pocetni - 1)
                            reset = 0;
                        if (unos_reda_pomak == unos_reda_pocetni + 2 && unos_stupca_pomak == unos_stupca_pocetni + 1)
                            reset = 0;
                        break;
                    case 6:
                        //crni lovac
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni<unos_reda_pomak && unos_stupca_pocetni>unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni - 1; i < unos_reda_pomak; i++, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni + 1; i > unos_reda_pomak; i--, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni - 1; i > unos_reda_pomak; i--, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 7:
                        //bijeli lovac
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni - 1; i < unos_reda_pomak; i--, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni + 1; i > unos_reda_pomak; i--, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni - 1; i > unos_reda_pomak; i--, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 8:
                        //crna queen
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni<unos_reda_pomak && unos_stupca_pocetni>unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni - 1; i < unos_reda_pomak; i++, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni + 1; i > unos_reda_pomak; i--, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni - 1; i > unos_reda_pomak; i--, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni - 1; i > unos_stupca_pomak; i--)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1; i >= unos_reda_pomak; i--)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)//gsgsgsdgsdg
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1; i < unos_reda_pomak - 1; i++)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 9:
                        //bijela queen
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            if (unos_reda_pocetni - unos_stupca_pocetni == unos_reda_pomak - unos_stupca_pomak)
                            {
                                reset = 1;
                                break;
                            }
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni<unos_reda_pomak && unos_stupca_pocetni>unos_stupca_pomak)
                        {
                            if (unos_reda_pocetni - unos_stupca_pocetni == unos_reda_pomak - unos_stupca_pomak)
                            {
                                reset = 1;
                                break;
                            }
                            for (int i = unos_reda_pocetni + 1, j = unos_stupca_pocetni - 1; i < unos_reda_pomak; i++, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            if (unos_reda_pocetni - unos_stupca_pocetni == unos_reda_pomak - unos_stupca_pomak)
                            {
                                reset = 1;
                                break;
                            }
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni + 1; i > unos_reda_pomak; i--, j++)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            if (unos_reda_pocetni - unos_stupca_pocetni == unos_reda_pomak - unos_stupca_pomak)
                            {
                                reset = 1;
                                break;
                            }
                            for (int i = unos_reda_pocetni - 1, j = unos_stupca_pocetni - 1; i > unos_reda_pomak; i--, j--)
                            {
                                if (ploca[i][j] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni < unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni == unos_reda_pomak && unos_stupca_pocetni > unos_stupca_pomak)
                        {
                            for (int i = unos_stupca_pocetni - 1; i > unos_stupca_pomak; i--)
                            {
                                if (ploca[unos_reda_pocetni][i] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni > unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni - 1; i >= unos_reda_pomak; i--)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)//reerwerwere
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        if (unos_reda_pocetni < unos_reda_pomak && unos_stupca_pocetni == unos_stupca_pomak)
                        {
                            for (int i = unos_reda_pocetni + 1; i < unos_reda_pomak; i++)
                            {
                                if (ploca[i][unos_stupca_pocetni] != 13)
                                {
                                    reset = 1;
                                    break;
                                }
                                else
                                    reset = 0;
                            }
                        }
                        break;
                    case 10:
                        //crni kralj
                        if ((unos_stupca_pomak == unos_stupca_pocetni + 1 || unos_stupca_pomak == unos_stupca_pocetni - 1 || unos_stupca_pomak == unos_stupca_pocetni) && (unos_reda_pomak == unos_reda_pocetni + 1 || unos_reda_pomak == unos_reda_pocetni - 1 || unos_reda_pomak == unos_reda_pocetni) && (unos_reda_pocetni != unos_reda_pomak || unos_stupca_pomak != unos_stupca_pocetni))
                        {
                            reset = 0;
                            rosada_b1 = 0;
                            rosada_b2 = 0;
                        }
                        if (rosada_b1 == 1 && unos_reda_pomak == 7 && unos_stupca_pomak == 1 && ploca[7][3] == 13 && ploca[7][2] == 13 && ploca[7][1] == 13)
                        {
                            rosada_b1 = 2;
                            rosada_b2 = 0;
                            reset = 0;
                        }
                        if (rosada_b2 == 1 && unos_reda_pomak == 7 && unos_stupca_pomak == 6 && ploca[7][5] == 13 && ploca[7][6] == 13)
                        {
                            rosada_c2 = 2;
                            rosada_c1 = 0;
                            reset = 0;
                        }
                        if (reset == 0)
                        {
                            pozicija_bk_i = unos_reda_pomak;
                            pozicija_bk_j = unos_stupca_pomak;
                        }
                        break;
                    case 11:
                        //bijeli kralj
                        if ((unos_stupca_pomak == unos_stupca_pocetni + 1 || unos_stupca_pomak == unos_stupca_pocetni - 1 || unos_stupca_pomak == unos_stupca_pocetni) && (unos_reda_pomak == unos_reda_pocetni + 1 || unos_reda_pomak == unos_reda_pocetni - 1 || unos_reda_pomak == unos_reda_pocetni) && (unos_reda_pocetni != unos_reda_pomak || unos_stupca_pomak != unos_stupca_pocetni))
                        {
                            reset = 0;
                            rosada_c1 = 0;
                            rosada_c2 = 0;
                        }
                        if (rosada_c1 == 1 && unos_reda_pomak == 0 && unos_stupca_pomak == 1 && ploca[0][3] == 13 && ploca[0][2] == 13 && ploca[0][1] == 13)
                        {
                            rosada_c1 = 2;
                            rosada_c2 = 0;
                            reset = 0;
                        }
                        if (rosada_c2 == 1 && unos_reda_pomak == 0 && unos_stupca_pomak == 6 && ploca[0][5] == 13 && ploca[0][6] == 13)
                        {
                            rosada_c2 = 2;
                            rosada_c1 = 0;
                            reset = 0;
                        }
                        if (reset == 0)
                        {
                            pozicija_ck_i = unos_reda_pomak;
                            pozicija_ck_j = unos_stupca_pomak;
                        }
                        break;
                    default:
                    {
                        break;
                    }
                    }
                }

                if (reset == 0)
                {

                    if (ploca[unos_reda_pomak][unos_stupca_pomak] == 10 || ploca[unos_reda_pomak][unos_stupca_pomak] == 11)
                        krajigre = 1;

                    if (rosada_b1 == 2)
                    {
                        ploca[7][1] = 10;
                        ploca[7][2] = 2;
                        ploca[7][0] = 13;
                        ploca[7][4] = 13;
                        rosada_b1 = 0;
                        rosada_b2 = 0;
                        rosada_c1 = 0;
                        rosada_c2 = 0;
                    }
                    else if (rosada_b2 == 2)
                    {
                        ploca[7][6] = 10;
                        ploca[7][5] = 2;
                        ploca[7][7] = 13;
                        ploca[7][4] = 13;
                        rosada_b1 = 0;
                        rosada_b2 = 0;
                        rosada_c1 = 0;
                        rosada_c2 = 0;
                    }
                    else if (rosada_c1 == 2)
                    {
                        ploca[0][1] = 11;
                        ploca[0][2] = 3;
                        ploca[0][0] = 13;
                        ploca[0][4] = 13;
                        rosada_b1 = 0;
                        rosada_b2 = 0;
                        rosada_c1 = 0;
                        rosada_c2 = 0;
                    }
                    else if (rosada_c2 == 2)
                    {
                        ploca[7][6] = 10;
                        ploca[7][5] = 2;
                        ploca[7][7] = 13;
                        ploca[7][4] = 13;
                        rosada_b1 = 0;
                        rosada_b2 = 0;
                        rosada_c1 = 0;
                        rosada_c2 = 0;
                    }
                    else
                    {
                        ploca[unos_reda_pomak][unos_stupca_pomak] = ploca[unos_reda_pocetni][unos_stupca_pocetni];
                        ploca[unos_reda_pocetni][unos_stupca_pocetni] = 13;
                    }

                    while (1)
                    {
                        if (unos_reda_pomak == 0 && ploca[unos_reda_pomak][unos_stupca_pomak] == 0)
                        {
                            char zamjena_figure;
                            cout << "Upisite oznaku figure koju zelite uzeti:\n" << endl;
                            cin >> zamjena_figure;
                            switch (zamjena_figure)
                            {
                            case 'T':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 2;
                                break;
                            case 'S':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 4;
                                break;
                            case 'L':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 6;
                                break;
                            case 'Q':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 8;
                                break;
                            default:
                                cout << "krivi unos.\nPonovite unos." << endl;
                            }
                            if (ploca[unos_reda_pomak][unos_stupca_pomak] != 0)
                                break;
                        }
                        else
                            break;
                    }
                    while (1)
                    {
                        if (unos_reda_pomak == 7 && ploca[unos_reda_pomak][unos_stupca_pomak] == 1)
                        {
                            char zamjena_figure;
                            cout << "Upisite oznaku figure koju zelite uzeti:\n" << endl;
                            cin >> zamjena_figure;
                            switch (zamjena_figure)
                            {
                            case 'T':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 3;
                                break;
                            case 'S':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 5;
                                break;
                            case 'L':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 7;
                                break;
                            case 'Q':
                                ploca[unos_reda_pomak][unos_stupca_pomak] = 9;
                                break;
                            default:
                                cout << "krivi unos.\nPonovite unos." << endl;
                            }
                            if (ploca[unos_reda_pomak][unos_stupca_pomak] != 1)
                                break;
                        }
                        else
                            break;
                    }

                    if (napotezu % 2 != 0)
                    {
                        for (int t = 8, i = 0; i < 8; i++)
                        {
                            cout << "|";
                            for (int j = 0; j < 8; j++)
                            {
                                int t = ploca[i][j];
                                if (t % 2 == 0 && t != 13 && t != 14 && t != 15)
                                {
                                    cout << "B";
                                    cout << figure[t] << "|";
                                }
                                if (t % 2 != 0 && t != 13 && t != 14 && t != 15)
                                {
                                    cout << "C";
                                    cout << figure[t] << "|";
                                }
                                if (t == 13 || t == 14 || t == 15)
                                    cout << "  |";
                            }
                            cout << " " << t << endl;
                            t--;
                        }
                        for (char i = 'A'; i < 'I'; i++)
                        {
                            cout << "  " << i;
                        }
                        cout << endl << endl;
                    }

                    else
                    {
                        for (int t = 1, i = 7; i >= 0; i--)
                        {
                            cout << "|";
                            for (int j = 7; j >= 0; j--)
                            {
                                int t = ploca[i][j];
                                if (t % 2 == 0 && t != 13 && t != 14 && t != 15)
                                {
                                    cout << "B";
                                    cout << figure[t] << "|";
                                }
                                if (t % 2 != 0 && t != 13 && t != 14 && t != 15)
                                {
                                    cout << "C";
                                    cout << figure[t] << "|";
                                }
                                if (t == 13 || t == 14 || t == 15)
                                    cout << "  |";
                            }
                            cout << " " << t << endl;
                            t++;
                        }
                        for (char i = 'H'; i >= 'A'; i--)
                        {
                            cout << " " << i;
                        }
                        cout << endl << endl;
                    }
                    napotezu++;
                }
                else
                    cout << "Krivi unos\nPonovite unos.\n\n" << endl;


                if (krajigre == 1)
                {
                    if (napotezu % 2 == 1)
                        cout << "Bijeli je pobjednik!!" << endl;
                    else
                        cout << "Crni je pobjednik!!" << endl;
                    return 0;
                }
                //provjera saha za bijelog

                for (int i = pozicija_bk_i + 1, j = pozicija_bk_j + 1; i < 8 && j < 8; i++, j++)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 9 || ploca[i][j] == 7))
                    {
                        bsah_dd = 1;
                        break;
                    }
                    else
                        bsah_dd = 0;
                }

                for (int i = pozicija_bk_i + 1, j = pozicija_bk_j - 1; i<8 && j>-1; i++, j--)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 9 || ploca[i][j] == 7))
                    {
                        bsah_dl = 1;
                        break;
                    }
                    else
                        bsah_dl = 0;
                }


                for (int i = pozicija_bk_i - 2, j = pozicija_bk_j + 2; i > -1 && j < 8; i--, j++)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 9 || ploca[i][j] == 7))
                    {
                        bsah_gd = 1;
                        break;
                    }
                    else
                        bsah_gd = 0;
                }

                for (int i = pozicija_bk_i - 2, j = pozicija_bk_j - 2; i > -1 && j > -1; i--, j--)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 9 || ploca[i][j] == 7))
                    {
                        bsah_gl = 1;
                        break;
                    }
                    else
                        bsah_gl = 0;
                }

                for (int i = pozicija_bk_i + 1; i < 8; i++)
                {
                    if (ploca[i][pozicija_bk_j] != 13 && (ploca[i][pozicija_bk_j] == 3 || ploca[i][pozicija_bk_j] == 9))
                    {
                        bsah_d = 1;
                        break;
                    }
                    else
                        bsah_d = 0;
                }

                for (int i = pozicija_bk_i - 1; i > -1; i--)
                {
                    if (ploca[i][pozicija_bk_j] != 13 && (ploca[i][pozicija_bk_j] == 3 || ploca[i][pozicija_bk_j] == 9))
                    {
                        bsah_g = 1;
                        break;
                    }
                    else
                        bsah_g = 0;
                }

                for (int j = pozicija_bk_j + 1; j < 8; j++)
                {
                    if (ploca[pozicija_bk_i][j] != 13 && (ploca[pozicija_bk_i][j] == 3 || ploca[pozicija_bk_i][j] == 9))
                    {
                        bsah_desno = 1;
                        break;
                    }
                    else
                        bsah_desno = 0;
                }

                for (int j = pozicija_bk_j - 1; j > -1; j--)
                {
                    if (ploca[pozicija_bk_i][j] != 13 && (ploca[pozicija_bk_i][j] == 3 || ploca[pozicija_bk_i][j] == 9))
                    {
                        bsah_l = 1;
                        break;
                    }
                    else
                        bsah_l = 0;
                }

                while (1)
                {
                    if (ploca[pozicija_bk_i + 2][pozicija_bk_j + 1] == 4 && pozicija_bk_i + 2 >= 0 && pozicija_bk_i + 2 < 8 && pozicija_bk_j + 1 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i + 2][pozicija_bk_j - 1] == 4 && pozicija_bk_i + 2 >= 0 && pozicija_bk_i + 2 < 8 && pozicija_bk_j - 1 >= 0 && pozicija_bk_j - 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i + 1][pozicija_bk_j + 2] == 4 && pozicija_bk_i + 1 >= 0 && pozicija_bk_i + 1 < 8 && pozicija_bk_j + 2 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i + 1][pozicija_bk_j - 2] == 4 && pozicija_bk_i + 1 >= 0 && pozicija_bk_i + 1 < 8 && pozicija_bk_j - 2 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i - 2][pozicija_bk_j + 1] == 4 && pozicija_bk_i - 2 >= 0 && pozicija_bk_i - 1 < 8 && pozicija_bk_j + 1 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i - 2][pozicija_bk_j - 1] == 4 && pozicija_bk_i - 2 >= 0 && pozicija_bk_i - 1 < 8 && pozicija_bk_j - 1 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i - 1][pozicija_bk_j + 2] == 4 && pozicija_bk_i - 1 >= 0 && pozicija_bk_i - 2 < 8 && pozicija_bk_j + 2 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    if (ploca[pozicija_bk_i - 1][pozicija_bk_j - 2] == 4 && pozicija_bk_i - 1 >= 0 && pozicija_bk_i - 2 < 8 && pozicija_bk_j - 2 >= 0 && pozicija_bk_j + 1 < 8)
                        bsah_konj = 1;
                    break;
                }

                if (ploca[pozicija_bk_i - 1][pozicija_bk_j - 1] == 1 || ploca[pozicija_bk_i - 1][pozicija_bk_j + 1] == 1 || ploca[pozicija_bk_i - 1][pozicija_bk_j - 1] == 9 || ploca[pozicija_bk_i + 1][pozicija_bk_j - 1] == 9)
                    bsah_pijun = 1;

                if (bsah_dd == 1 || bsah_dl == 1 || bsah_gl == 1 || bsah_gd == 1 || bsah_g == 1 || bsah_desno == 1 || bsah_d == 1 || bsah_l == 1 || bsah_konj == 1 || bsah_pijun == 1)
                    printf("\nSAH NA BIJELOG!!!\n");


                for (int i = pozicija_ck_i + 1, j = pozicija_ck_j + 1; i < 8 && j < 8; i++, j++)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 8 || ploca[i][j] == 6))
                    {
                        csah_dd = 1;
                        break;
                    }
                    else
                        csah_dd = 0;
                }

                for (int i = pozicija_ck_i + 1, j = pozicija_ck_j - 1; i<8 && j>-1; i++, j--)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 8 || ploca[i][j] == 6))
                    {
                        csah_dl = 1;
                        break;
                    }
                    else
                        csah_dl = 0;
                }


                for (int i = pozicija_ck_i - 2, j = pozicija_ck_j + 2; i > -1 && j < 8; i--, j++)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 8 || ploca[i][j] == 6))
                    {
                        csah_gd = 1;
                        break;
                    }
                    else
                        csah_gd = 0;
                }

                for (int i = pozicija_ck_i - 2, j = pozicija_ck_j - 2; i > -1 && j > -1; i--, j--)
                {
                    if (ploca[i][j] != 13 && (ploca[i][j] == 8 || ploca[i][j] == 6))
                    {
                        csah_gl = 1;
                        break;
                    }
                    else
                        csah_gl = 0;
                }

                for (int i = pozicija_ck_i + 1; i < 8; i++)
                {
                    if (ploca[i][pozicija_ck_j] != 13 && (ploca[i][pozicija_ck_j] == 2 || ploca[i][pozicija_ck_j] == 8))
                    {
                        csah_d = 1;
                        break;
                    }
                    else
                        csah_d = 0;
                }

                for (int i = pozicija_ck_i - 1; i > -1; i--)
                {
                    if (ploca[i][pozicija_ck_j] != 13 && (ploca[i][pozicija_ck_j] == 2 || ploca[i][pozicija_ck_j] == 8))
                    {
                        csah_g = 1;
                        break;
                    }
                    else
                        csah_g = 0;
                }

                for (int j = pozicija_ck_j + 1; j < 8; j++)
                {
                    if (ploca[pozicija_ck_i][j] != 13 && (ploca[pozicija_ck_i][j] == 2 || ploca[pozicija_ck_i][j] == 8))
                    {
                        csah_desno = 1;
                        break;
                    }
                    else
                        csah_desno = 0;
                }

                for (int j = pozicija_ck_j - 1; j > -1; j--)
                {
                    if (ploca[pozicija_ck_i][j] != 13 && (ploca[pozicija_ck_i][j] == 2 || ploca[pozicija_ck_i][j] == 8))
                    {
                        csah_l = 1;
                        break;
                    }
                    else
                        csah_l = 0;
                }

                while (1)
                {
                    if (ploca[pozicija_ck_i + 2][pozicija_ck_j + 1] == 4 && pozicija_ck_i + 2 >= 0 && pozicija_ck_i + 2 < 8 && pozicija_ck_j + 1 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i + 2][pozicija_ck_j - 1] == 4 && pozicija_ck_i + 2 >= 0 && pozicija_ck_i + 2 < 8 && pozicija_ck_j - 1 >= 0 && pozicija_ck_j - 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i + 1][pozicija_ck_j + 2] == 4 && pozicija_ck_i + 1 >= 0 && pozicija_ck_i + 1 < 8 && pozicija_ck_j + 2 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i + 1][pozicija_ck_j - 2] == 4 && pozicija_ck_i + 1 >= 0 && pozicija_ck_i + 1 < 8 && pozicija_ck_j - 2 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i - 2][pozicija_ck_j + 1] == 4 && pozicija_ck_i - 2 >= 0 && pozicija_ck_i - 1 < 8 && pozicija_ck_j + 1 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i - 2][pozicija_ck_j - 1] == 4 && pozicija_ck_i - 2 >= 0 && pozicija_ck_i - 1 < 8 && pozicija_ck_j - 1 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i - 1][pozicija_ck_j + 2] == 4 && pozicija_ck_i - 1 >= 0 && pozicija_ck_i - 2 < 8 && pozicija_ck_j + 2 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    if (ploca[pozicija_ck_i - 1][pozicija_ck_j - 2] == 4 && pozicija_ck_i - 1 >= 0 && pozicija_ck_i - 2 < 8 && pozicija_ck_j - 2 >= 0 && pozicija_ck_j + 1 < 8)
                        csah_konj = 1;
                    break;
                }

                if (ploca[pozicija_ck_i + 1][pozicija_ck_j - 1] == 0 || ploca[pozicija_ck_i + 1][pozicija_ck_j + 1] == 0 || ploca[pozicija_bk_i + 1][pozicija_bk_j - 1] == 8 || ploca[pozicija_bk_i + 1][pozicija_bk_j + 1] == 8)
                    csah_pijun = 1;

                if (csah_dd == 1 || csah_dl == 1 || csah_gl == 1 || csah_gd == 1 || csah_g == 1 || csah_desno == 1 || csah_d == 1 || csah_l == 1 || csah_konj == 1 || csah_pijun == 1)
                    cout << "\nSAH NA CRNOG!!!\n" << endl;

            }

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
            //pravila
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

