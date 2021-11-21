#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

struct Person
{
    int id;
    string name;
    string surname;
    string tel;
    string email;
    string address;
};

int Menu()
{
    int choice;
    cout << endl;
    cout << "KSIAZKA ADRESOWA\n";
    cout << "1. Dodaj adresata. \n";
    cout << "2. Wyszukaj po imieniu.\n";
    cout << "3. Wyszukaj po nazwisku.\n";
    cout << "4. Wyswietl wszystich adresatow. \n";
    cout << "5. Usun adresata. \n";
    cout << "6. Edytuj adresata. \n";
    cout << "9. Zakoncz program. \n";
    cout << "Twoj wybor: \n";
    cin >> choice;
    return choice;
}

void File_out(vector<Person>&Person_vr_local)
{
    fstream file;
    string line_out;
    file.open("Database.txt",ios::out);

    for (vector<Person>::iterator itr_person = Person_vr_local.begin();
    itr_person != Person_vr_local.end();++itr_person)
    {
        line_out.clear();
        line_out += to_string((*itr_person).id) + "|";
        line_out += (*itr_person).name + "|";
        line_out += (*itr_person).surname + "|";
        line_out += (*itr_person).tel + "|";
        line_out += (*itr_person).email + "|";
        line_out += (*itr_person).address + "|";
        file << line_out << endl;;
    }
    file.close();
}

void Add_person(vector<Person>&Person_vr_local)
{
    Person person_local;
    fstream file_add;
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

    if (!Person_vr_local.empty())
    {
        person_local.id = Person_vr_local.back().id + 1;
    }
    else
    {
        person_local.id = 1;
    }
    Person_vr_local.push_back(person_local);
    File_out(Person_vr_local);

}

void Read_DB(vector<Person>&Person_vr_local)
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
                        person_local.name = part;
                        break;
                    case 3:
                        person_local.surname = part;
                        break;
                    case 4:
                        person_local.tel = part;
                        break;
                    case 5:
                        person_local.email = part;
                        break;
                    case 6:
                        person_local.address = part;
                        break;
                    default:
                        cout << "Read_DB-ERROR: incorrect part_nr\n";
                        break;
                    }
                    if (part_nr == 6)
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
    int delete_id;
    string confirmation;
    confirmation.clear();
    cout << "-----------------------------" << endl;
    cout << "USUN ZNAJOMEGO" << endl;
    cout << "-----------------------------" << endl;
    cout << "Prosze podac ID" << endl;
    cin >> delete_id;
    cout << "Wcisnij 't' aby potwierdzic" << endl;
    cin >> confirmation;
    if (confirmation == "t")
    {
        Person_vr_local.erase(
            remove_if(Person_vr_local.begin(),Person_vr_local.end(),[&](Person const & person_to_delete)
                      {
                         return person_to_delete.id == delete_id;
                      }),
                      Person_vr_local.end());
        File_out(Person_vr_local);
    }

    cout << endl;
    cout << "Press Enter to go back to Menu\n";
    cin.ignore();
    cin.get();
}

void Edit_person(vector<Person> &Person_vr_local)
{
    Person person_local;
    int edit_id,edit_part;
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
        }
    }

    File_out(Person_vr_local);
    cout << endl;
    cout << "Press Enter to go back to Menu\n";
    cin.get();
}

int main()
{
    vector<Person>Person_vr;
    fstream menufile;
    int choice;
    for (;;)
    {
        Person_vr.clear();
        Read_DB(Person_vr);
        choice = Menu();
        switch(choice)
        {
        case 1:
            Add_person(Person_vr);
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
        case 9:
            return 0;
            break;
        default:
            cout << "bledna opcja\n";
        }
    }
}
