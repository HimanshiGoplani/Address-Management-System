#include <iostream>
#include <fstream>

using namespace std;

class Contacts {
public:
    char FirstName[50], LastName[50], Address[50], Email[50];
    long long PhoneNo;
    Contacts* next;

    Contacts() {
        next = nullptr;
    }
};

class ContactList {
private:
    Contacts* head;

public:
    ContactList() {
        head = nullptr;
    }

    void AddContact() {
        Contacts* NewNode = new Contacts;
        cout << "Enter First Name: ";
        cin >> NewNode->FirstName;
        cout << "Enter Last Name: ";
        cin >> NewNode->LastName;
        cout << "Enter Phone Number: ";
        cin >> NewNode->PhoneNo;
        cout << "Enter Address: ";
        cin >> NewNode->Address;
        cout << "Enter Email: ";
        cin >> NewNode->Email;

        NewNode->next = head;
        head = NewNode;
    }

    void ShowContact(Contacts* contact) {
        cout << "Name: " << contact->FirstName << " " << contact->LastName << endl;
        cout << "Phone: " << contact->PhoneNo << endl;
        cout << "Address: " << contact->Address << endl;
        cout << "Email: " << contact->Email << endl;
    }

    void WriteOnFile() {
        char ch;
        ofstream f1;
        f1.open("AMS.dat", ios::binary | ios::app);

        do {
            AddContact();
            f1.write(reinterpret_cast<char*>(head), sizeof(Contacts));
            cout << "Do you have next data?(y/n)";
            cin >> ch;
        } while (ch == 'y');

        cout << "***Contact has been Successfully Created***";
        f1.close();
    }

    void ReadFromFile() {
        ifstream f2;
        f2.open("AMS.dat", ios::binary);

        cout << "\n================================\n";
        cout << "LIST OF CONTACTS";
        cout << "\n================================\n";

        while (!f2.eof()) {
            Contacts* temp = new Contacts;
            if (f2.read(reinterpret_cast<char*>(temp), sizeof(Contacts))) {
                ShowContact(temp);
                cout << "\n================================\n";
            }
        }
        f2.close();
    }

    void searchOnFile() {
        ifstream f3;
        long long Phone;
        cout << "Enter Phone Number: ";
        cin >> Phone;
        f3.open("AMS.dat", ios::binary);

        while (!f3.eof()) {
            Contacts* temp = new Contacts;
            if (f3.read(reinterpret_cast<char*>(temp), sizeof(Contacts))) {
                if (Phone == temp->PhoneNo) {
                    ShowContact(temp);
                    return;
                }
            }
        }
        cout << "\n\n Record Not Found";
        f3.close();
    }

    void DeleteFromFile() {
        long long num;
        int flag = 0;
        ofstream f4;
        ifstream f5;

        f5.open("AMS.dat", ios::binary);
        f4.open("temp.dat", ios::binary);

        cout << "Enter Phone Number to delete: ";
        cin >> num;

        while (!f5.eof()) {
            Contacts* temp = new Contacts;
            if (f5.read(reinterpret_cast<char*>(temp), sizeof(Contacts))) {
                if (temp->PhoneNo != num) {
                    f4.write(reinterpret_cast<char*>(temp), sizeof(Contacts));
                }
                else
                    flag = 1;
            }
        }
        f5.close();
        f4.close();
        remove("AMS.dat");
        rename("temp.dat", "AMS.dat");

        flag == 1 ?
            cout << endl << endl << "\tContact Deleted..." :
            cout << endl << endl << "\tContact Not Found...";
    }

    void EditContact() {
        long long num;
        fstream f6;

        cout << "Edit contact";
        cout << "\n======================================================\n\n";
        cout << "Enter the Phone Number of the Contact you want to Edit: ";
        cin >> num;

        f6.open("AMS.dat", ios::binary | ios::out | ios::in);

        while (!f6.eof()) {
            Contacts* temp = new Contacts;
            if (f6.read(reinterpret_cast<char*>(temp), sizeof(Contacts))) {
                if (temp->PhoneNo == num) {
                    cout << "Enter New Record\n";
                    AddContact();
                    int pos = -1 * sizeof(Contacts);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char*>(head), sizeof(Contacts));
                    cout << endl << endl << "\t Contact Successfully Updated...";
                    return;
                }
            }
        }
        cout << "\n\n Record Not Found";
        f6.close();
    }
};

int main() {
    system("cls");
    system("Color 3F"); 

    cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO ADDRESS MANAGEMENT SYSTEM *";
    cin.get();

    while (1) {
        ContactList ContactList;
        int Option;

        system("cls");
        system("Color 03");

        cout << "\nADDRESS MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n=====================\n";
        cout << "What would you like to do?" << endl;
        cout << "1.) Add a New Contact\n";
        cout << "2.) List all Contacts\n";
        cout << "3.) Search for a Contact\n";
        cout << "4.) Delete a Contact\n";
        cout << "5.) Edit a Contact\n";
        cout << "0.) Exit";
        cout << "\n=====================\n";
        cout << "Choose an Option: ";
        cin >> Option;

        switch (Option) {
        case 1:
            system("cls");
            ContactList.WriteOnFile();
            break;

        case 2:
            system("cls");
            ContactList.ReadFromFile();
            break;

        case 3:
            system("cls");
            ContactList.searchOnFile();
            break;

        case 4:
            system("cls");
            ContactList.DeleteFromFile();
            break;

        case 5:
            system("cls");
            ContactList.EditContact();
            break;

        case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank you for using AMS." << endl << endl;
            exit(0);
            break;

        default:
            continue;
        }

        int opt;
        cout << "\n\n..::Choose an Option:\n 1.) Return to Main Menu\t\t 0.) Exit\n";
        cin >> opt;

        switch (opt) {
        case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank You for using AMS." << endl << endl;
            exit(0);
            break;

        default:
            continue;
        }
    }

    return 0;
}
