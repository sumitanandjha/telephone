#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Contact {
public:
    string name;
    string phone;
    string email;

    void setContact(string n, string p, string e) {
        name = n;
        phone = p;
        email = e;
    }

    void display() {
        cout << left << setw(20) << name << setw(15) << phone << setw(25) << email << endl;
    }
};

class TelephoneDirectory {
private:
    const string fileName = "directory.txt";

public:
    // Function to add a new contact
    void addContact() {
        ofstream file;
        file.open(fileName, ios::app);

        Contact contact;
        string name, phone, email;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);

        contact.setContact(name, phone, email);
        file << name << "," << phone << "," << email << endl;
        file.close();

        cout << "Contact added successfully!\n";
    }

    // Function to display all contacts
    void viewAllContacts() {
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cout << "No contacts found!\n";
            return;
        }

        string line, name, phone, email;
        cout << left << setw(20) << "Name" << setw(15) << "Phone" << setw(25) << "Email" << endl;
        cout << "---------------------------------------------------------------\n";

        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            name = line.substr(0, pos1);
            phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            email = line.substr(pos2 + 1);

            Contact contact;
            contact.setContact(name, phone, email);
            contact.display();
        }
        file.close();
    }

    // Function to search a contact by name or phone
    void searchContact() {
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cout << "No contacts found!\n";
            return;
        }

        string searchQuery;
        cout << "Enter name or phone to search: ";
        cin.ignore();
        getline(cin, searchQuery);

        string line, name, phone, email;
        bool found = false;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            name = line.substr(0, pos1);
            phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            email = line.substr(pos2 + 1);

            if (name == searchQuery || phone == searchQuery) {
                cout << "\nContact Found:\n";
                cout << left << setw(20) << "Name" << setw(15) << "Phone" << setw(25) << "Email" << endl;
                cout << "---------------------------------------------------------------\n";
                Contact contact;
                contact.setContact(name, phone, email);
                contact.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No contact found with the given search term.\n";
        }

        file.close();
    }

    // Function to delete a contact
    void deleteContact() {
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cout << "No contacts found!\n";
            return;
        }

        ofstream tempFile;
        tempFile.open("temp.txt");

        string searchQuery;
        cout << "Enter name or phone to delete: ";
        cin.ignore();
        getline(cin, searchQuery);

        string line, name, phone, email;
        bool deleted = false;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            name = line.substr(0, pos1);
            phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            email = line.substr(pos2 + 1);

            if (name != searchQuery && phone != searchQuery) {
                tempFile << line << endl;
            } else {
                deleted = true;
            }
        }

        file.close();
        tempFile.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        if (deleted) {
            cout << "Contact deleted successfully.\n";
        } else {
            cout << "No contact found to delete.\n";
        }
    }

    // Function to update a contact
    void updateContact() {
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cout << "No contacts found!\n";
            return;
        }

        ofstream tempFile;
        tempFile.open("temp.txt");

        string searchQuery;
        cout << "Enter name or phone to update: ";
        cin.ignore();
        getline(cin, searchQuery);

        string line, name, phone, email;
        bool updated = false;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            name = line.substr(0, pos1);
            phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            email = line.substr(pos2 + 1);

            if (name == searchQuery || phone == searchQuery) {
                string newName, newPhone, newEmail;
                cout << "Enter new Name: ";
                getline(cin, newName);
                cout << "Enter new Phone: ";
                getline(cin, newPhone);
                cout << "Enter new Email: ";
                getline(cin, newEmail);

                tempFile << newName << "," << newPhone << "," << newEmail << endl;
                updated = true;
            } else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        if (updated) {
            cout << "Contact updated successfully.\n";
        } else {
            cout << "No contact found to update.\n";
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n==== Telephone Directory ====\n";
            cout << "1. Add Contact\n";
            cout << "2. View All Contacts\n";
            cout << "3. Search Contact\n";
            cout << "4. Delete Contact\n";
            cout << "5. Update Contact\n";
            cout << "6. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addContact();
                    break;
                case 2:
                    viewAllContacts();
                    break;
                case 3:
                    searchContact();
                    break;
                case 4:
                    deleteContact();
                    break;
                case 5:
                    updateContact();
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid option. Try again.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    TelephoneDirectory directory;
    directory.menu();
    return 0;
}
