#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Main_Menu.h"

using namespace std;

int User::Login()
{
    vector<User>User_vr;
    fstream file_users;
    string login, pass, line, part, tmp_check;
    int user_logged, len, part_nr, part_int;
    User user_local;

    file_users.open("Users.txt",ios::in);
    while(getline(file_users,line))
    {
        part_nr = 1;

        len = line.length();
        for (int i=0;i<len;i++)
        {
            tmp_check = line[i];
            if (tmp_check == "|")
            {
                switch(part_nr)
                {
                case 1:
                    part_int = atoi(part.c_str());
                    user_local.id = part_int;
                    break;
                case 2:
                    user_local.login = part;
                    break;
                case 3:
                    user_local.pass = part;
                    break;
                default:
                    cout << "Read_User_DB-ERROR: incorrect part_nr\n";
                    break;
                }
                if (part_nr == 3)
                {
                    User_vr.push_back(user_local);
                }
                part_nr++;
                part.clear();
            }
            else
            {
                part.push_back(line[i]);
            }
        }   //End for
    }   //End while

    file_users.close();

    cout << "Podaj login: \n";
    cin >> login;

    for (vector<User>::iterator itr_users = User_vr.begin();
    itr_users != User_vr.end();++itr_users)
    {
        if ((*itr_users).login == login)
        {
            cout << "Podaj haslo: \n";
            cin >> pass;

            if ((*itr_users).pass == pass)
            {
                cout << "Welcome " << login << endl;
                return (*itr_users).id;
            }
            else
            {
                cout << "Bledne haslo \n";
                return 0;
            }
        }
        else
        {
            if (itr_users+1 == User_vr.end())
            {
                cout << "Brak uzytkownika: " << login << endl;
                return 0;
            }
        }
    }
}
