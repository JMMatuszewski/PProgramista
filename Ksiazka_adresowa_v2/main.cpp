#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

struct Menu_output
{
    int exit, user;
};

struct User
{
    int id;
    string login;
    string pass;
};

struct Person
{
    int id;
    int user;
    string name;
    string surname;
    string tel;
    string email;
    string address;
};

int Login()
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

void Registration()
{
    vector<User>User_vr;
    User user_local;
    fstream file_users;
    string tmp_check,login,pass,part,line_out,line;
    int len,part_int,part_nr,id_last=1;

    cout << "// REJESTRACJA //\n";

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
    /////////////////////////////////////////////////////////////
    cout << "Podaj login: \n";
    cin >> login;
    for (vector<User>::iterator itr_users = User_vr.begin();
    itr_users != User_vr.end();++itr_users)
    {
        if ((*itr_users).login == login)
        {
            cout << "Taki login juz istnieje \n";
            break;
        }
        if (id_last <= (*itr_users).id)
            id_last = (*itr_users).id + 1;
    }

    cout << "Podaj haslo: \n";
    cin >> pass;


    file_users.open("Users.txt",ios::app);
    line_out.clear();
    //to_string((*itr_person).id)
    line_out += to_string(id_last) + "|";
    line_out += login + "|";
    line_out += pass + "|";
    //cout << line_out << endl;
    file_users << line_out << endl;

    file_users.close();
}

auto Main_Menu()
{
    Menu_output flags;
    flags.exit = 0;
    flags.user = 0;
    int MM_choice = 0;  //Main Menu choice

    for (;;)
    {
        cout << endl;
        cout << "1. Logowanie \n";
        cout << "2. Rejestracja \n";
        cout << "3. Zamknij program \n";
        cin >> MM_choice;

        if (MM_choice == 1)
        {
            flags.user = Login();
            break;
        }
        else if(MM_choice == 2)
        {
            Registration();
            break;
        }
        else if(MM_choice == 3)
        {
            cout << "Zamykanie programu\n";
            flags.exit = 1;
            break;
        }
    }   //End of for
    return flags;
}   //End of Main_Menu

int User_Menu()
{
    int person_choice;
    cout << endl;
    cout << "KSIAZKA ADRESOWA\n";
    cout << "1. Dodaj adresata. \n";
    cout << "2. Wyszukaj po imieniu.\n";
    cout << "3. Wyszukaj po nazwisku.\n";
    cout << "4. Wyswietl wszystich adresatow. \n";
    cout << "5. Usun adresata. \n";
    cout << "6. Edytuj adresata. \n";
    cout << "7. Edytuj haslo. \n";
    cout << "9. Wyloguj. \n";
    cout << "Twoj wybor: \n";
    cin >> person_choice;
    return person_choice;
}

void File_out_add(vector<Person>&Person_vr_local, int id_add_handed)
{
    fstream file;
    fstream file_tmp;
    string line_out;

    file.open("Database.txt",ios::app);

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        if ((*itr_person).id == id_add_handed)
        {
            line_out.clear();
            line_out += to_string((*itr_person).id) + "|";
            line_out += to_string((*itr_person).user) + "|";
            line_out += (*itr_person).name + "|";
            line_out += (*itr_person).surname + "|";
            line_out += (*itr_person).tel + "|";
            line_out += (*itr_person).email + "|";
            line_out += (*itr_person).address + "|";
            file << line_out << endl;;
        }
    }
    file.close();
}

void File_out_edit(vector<Person>&Person_vr_local,int id_edit)
{
    Person person_local;
    fstream file;
    fstream file_tmp;
    string line_out,part,line,tmp_check;
    int i, part_int=0;

    file_tmp.open("Database_tmp.txt",ios::out);
    file.open("Database.txt",ios::in);
    while(getline(file,line))
    {
        i = 0;
        tmp_check = line[i];
        while (tmp_check != "|")
        {
            part.push_back(line[i]);
            i++;
            tmp_check = line[i];
        }
        part_int = atoi(part.c_str());

        if (id_edit == part_int)
        {
            for (vector<Person>::iterator itr_person = Person_vr_local.begin();
            itr_person != Person_vr_local.end();++itr_person)
            {
                if ((*itr_person).id == id_edit)
                {
                    line_out.clear();
                    line_out += to_string((*itr_person).id) + "|";
                    line_out += to_string((*itr_person).user) + "|";
                    line_out += (*itr_person).name + "|";
                    line_out += (*itr_person).surname + "|";
                    line_out += (*itr_person).tel + "|";
                    line_out += (*itr_person).email + "|";
                    line_out += (*itr_person).address + "|";
                    file_tmp << line_out << endl;
                }
            }
        }
        else
        {
            file_tmp << line << endl;
        }
        part.clear();
    }   //End while
    file_tmp.close();
    file.close();

    remove("Database.txt");
    rename("Database_tmp.txt","Database.txt");
}

void File_out_delete(vector<Person>&Person_vr_local,int id_delete)
{
    Person person_local;
    fstream file;
    fstream file_tmp;
    string line_out,part,line,tmp_check;
    int i, part_int=0;

    file_tmp.open("Database_tmp.txt",ios::out);
    file.open("Database.txt",ios::in);
    while(getline(file,line))
    {
        i = 0;
        tmp_check = line[i];
        while (tmp_check != "|")
        {
            part.push_back(line[i]);
            i++;
            tmp_check = line[i];
        }
        part_int = atoi(part.c_str());
        if (id_delete == part_int)
        {}
        else
        {
            file_tmp << line << endl;
        }
        part.clear();
    }   //End while
    file_tmp.close();
    file.close();

    remove("Database.txt");
    rename("Database_tmp.txt","Database.txt");
}

void Add_person(vector<Person>&Person_vr_local, int id_user)
{
    Person person_local;
    fstream file;
    string tmp_check,line,part;
    int i,part_int,id_last=1;
    //fstream file_add;
    cout << "-----------------------------" << endl;
    cout << "DODAJ ADRESATA" << endl;
    cout << "-----------------------------" << endl;
    cout << "Podaj imie: " << endl;
    cin.ignore();
    getline(cin,person_local.name);
    cout << "Podaj nazwisko: " << endl;
    getline(cin,person_local.surname);
    cout << "Podaj telefon: " << endl;
    getline(cin,person_local.tel);
    cout << "Podaj email: " << endl;
    getline(cin,person_local.email);
    cout << "Podaj adres: " << endl;
    getline(cin,person_local.address);

    /////////////////////////////////////////
    file.open("Database.txt",ios::in);
    while(getline(file,line))
    {
        i = 0;
        tmp_check = line[i];
        while (tmp_check != "|")
        {
            part.push_back(line[i]);
            i++;
            tmp_check = line[i];
        }
        part_int = atoi(part.c_str());
        if (id_last <= part_int)
            id_last = part_int+1;
        part.clear();
    }   //End while
    /////////////////////////////////////////
    person_local.id = id_last;
    person_local.user = id_user;

    Person_vr_local.push_back(person_local);

    File_out_add(Person_vr_local,id_last);
}

void Read_DB(vector<Person>&Person_vr_local, int user_local)
{
    Person person_local;
    fstream file;
    string line,part,tmp_check;
    int len,part_nr,part_int;

    file.open("Database.txt",ios::in);
    while(getline(file,line))
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
                    person_local.id = part_int;
                    break;
                case 2:
                    part_int = atoi(part.c_str());
                    person_local.user = part_int;
                    break;
                case 3:
                    person_local.name = part;
                    break;
                case 4:
                    person_local.surname = part;
                    break;
                case 5:
                    person_local.tel = part;
                    break;
                case 6:
                    person_local.email = part;
                    break;
                case 7:
                    person_local.address = part;
                    break;
                default:
                    cout << "Read_DB-ERROR: incorrect part_nr\n";
                    break;
                }
                if (part_nr == 7 & person_local.user == user_local)
                {
                    Person_vr_local.push_back(person_local);
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
    file.close();

}   //End Read_DB

void Find_name(vector<Person>&Person_vr_local)
{
    string name_search;
    cout << "-----------------------------" << endl;
    cout << endl << "WYSZUKAJ PO IMIENIU" << endl;
    cout << "-----------------------------" << endl;
    cin >> name_search;

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        if ((*itr_person).name == name_search)
        {
            cout << "-----------------------------" << endl;
            cout << "ID: " << (*itr_person).id << endl;
            cout << "Imie: " << (*itr_person).name << endl;
            cout << "Nazwisko: " << (*itr_person).surname << endl;
            cout << "Telefon: " << (*itr_person).tel << endl;
            cout << "Email: " << (*itr_person).email << endl;
            cout << "Adres: " << (*itr_person).address << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

void Find_surname(vector<Person>&Person_vr_local)
{
    string surname_search;

    cout << "-----------------------------" << endl;
    cout << endl << "WYSZUKAJ PO NAZWISKU" << endl;
    cout << "-----------------------------" << endl;
    cin >> surname_search;

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        if ((*itr_person).surname == surname_search)
        {
            cout << "-----------------------------" << endl;
            cout << "ID: " << (*itr_person).id << endl;
            cout << "Imie: " << (*itr_person).name << endl;
            cout << "Nazwisko: " << (*itr_person).surname << endl;
            cout << "Telefon: " << (*itr_person).tel << endl;
            cout << "Email: " << (*itr_person).email << endl;
            cout << "Adres: " << (*itr_person).address << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

void Show_all(vector<Person>&Person_vr_local)
{
    cout << "-----------------------------" << endl;
    cout << "WYSWIETL ADRESATOW" << endl;
    cout << "-----------------------------" << endl;
    cout << endl;

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        cout << "-----------------------------" << endl;
        cout << "ID: " << (*itr_person).id << endl;
        cout << "Imie: " << (*itr_person).name << endl;
        cout << "Nazwisko: " << (*itr_person).surname << endl;
        cout << "Telefon: " << (*itr_person).tel << endl;
        cout << "Email: " << (*itr_person).email << endl;
        cout << "Adres: " << (*itr_person).address << endl;
        cout << "-----------------------------" << endl;
    }
    cout << endl;
    cout << "Press Enter to go back to Menu\n";
    cin.ignore();
    cin.get();
}

void Delete_person(vector<Person> &Person_vr_local)
{
    int delete_id, delete_correct = 0;
    string confirmation;
    confirmation.clear();
    cout << "-----------------------------" << endl;
    cout << "USUN ZNAJOMEGO" << endl;
    cout << "-----------------------------" << endl;
    cout << "Prosze podac ID" << endl;
    cin >> delete_id;

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        if ((*itr_person).id == delete_id)
            delete_correct = 1;
    }


    cout << "Wcisnij 't' aby potwierdzic" << endl;
    cin >> confirmation;
    if (confirmation == "t" & delete_correct == 1)
    {
        Person_vr_local.erase(
            remove_if(Person_vr_local.begin(),Person_vr_local.end(),[&](Person const & person_to_delete)
                      {
                         return person_to_delete.id == delete_id;
                      }),
                      Person_vr_local.end());
        File_out_delete(Person_vr_local,delete_id);
    }
    else
        cout << "Wrong ID\n";


    cout << endl;
    cout << "Press Enter to go back to Menu\n";
    cin.ignore();
    cin.get();
}

void Edit_person(vector<Person> &Person_vr_local)
{
    Person person_local;
    int edit_id,edit_part,edit_correct=0;
    string edit_tmp;

    cout << "-----------------------------" << endl;
    cout << "EDYTUJ ADRESATA" << endl;
    cout << "-----------------------------" << endl;
    cout << "Prosze podaj id adresata:" << endl;
    cin >> edit_id;
    cout << "Prosze wybrac pole" << endl;
    cout << "1 - Imie" << endl;
    cout << "2 - Nazwisko" << endl;
    cout << "3 - Numer telefonu" << endl;
    cout << "4 - Email" << endl;
    cout << "5 - Adres" << endl;
    cout << "6 - Powrot do menu" << endl;
    cin >> edit_part;

////////////////////////////////////////////////////////////////////////////
    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        if ((*itr_person).id == edit_id)
        {
            switch(edit_part)
            {
            case 1:
                cout << "Podaj nowe imie: " << endl;
                cin.ignore();
                getline(cin,edit_tmp);
                cout << edit_tmp << endl;
                (*itr_person).name =  edit_tmp;
                break;
            case 2:
                cout << "Podaj nowe nazwisko: " << endl;
                cin.ignore();
                getline(cin,edit_tmp);
                (*itr_person).surname =  edit_tmp;
                break;
            case 3:
                cout << "Podaj nowy telefon: " << endl;
                cin.ignore();
                getline(cin,edit_tmp);
                (*itr_person).tel =  edit_tmp;
                break;
            case 4:
                cout << "Podaj nowy email: " << endl;
                cin.ignore();
                getline(cin,edit_tmp);
                (*itr_person).email =  edit_tmp;
                break;
            case 5:
                cout << "Podaj nowy adres: " << endl;
                cin.ignore();
                getline(cin,edit_tmp);
                (*itr_person).address =  edit_tmp;
                break;
            case 6:
                break;
            default:
                cout << "Wybrano bledna opcje\n";
                break;
            }
            edit_correct = 1;
            break;
        }
    }
////////////////////////////////////////////////////////////////////////////
    if (edit_correct == 1)
        File_out_edit(Person_vr_local,edit_id);
    else
        cout << "Brak adresata \n";

    cout << endl;
    cout << "Press Enter to go back to Menu\n";
    cin.get();
}

void Edit_pass(int user_id)
{
    vector<User>User_vr;
    fstream file_users;
    string pass,line, part, tmp_check,line_out;
    int len, part_nr, part_int;
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

    cout << "Podaj nowe haslo \n";
    cin >> pass;

    for (vector<User>::iterator itr_user = User_vr.begin();
    itr_user != User_vr.end();++itr_user)
    {
        if ((*itr_user).id == user_id)
        {
            (*itr_user).pass = pass;
        }
    }

    file_users.open("Users.txt",ios::out);

    for (vector<User>::iterator itr_user = User_vr.begin();
    itr_user != User_vr.end();++itr_user)
    {
        line_out.clear();
        line_out += to_string((*itr_user).id) + "|";
        line_out += (*itr_user).login + "|";
        line_out += (*itr_user).pass + "|";
        file_users << line_out << endl;
    }
    file_users.close();

}

int main()
{
    vector<Person>Person_vr;
    Menu_output flags;
    int user_choice;
    for (;;)
    {
        Person_vr.clear();
        flags = Main_Menu();
        if (flags.exit == 0)
        {
            if (flags.user != 0)
            {
                Read_DB(Person_vr,flags.user);
                for (;;)
                {
                    //Read_DB(Person_vr,flags.user);
                    user_choice = User_Menu();
                    switch(user_choice)
                    {
                    case 1:
                        Add_person(Person_vr,flags.user);
                        break;
                    case 2:
                        Find_name(Person_vr);
                        break;
                    case 3:
                        Find_surname(Person_vr);
                        break;
                    case 4:
                        Show_all(Person_vr);
                        break;
                    case 5:
                        Delete_person(Person_vr);
                        break;
                    case 6:
                        Edit_person(Person_vr);
                        break;
                    case 7:
                        Edit_pass(flags.user);
                        break;
                    case 9:
                        //return 0;
                        flags.user = 0;
                        break;
                    default:
                        cout << "bledna opcja\n";
                    }
                    if (flags.user == 0)
                        break;
                }
            }
        }
        else if (flags.exit == 1)
        {
            return 0;
        }
    }
}
