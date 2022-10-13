#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Recipient {
    int id = 0;
    string name = "", surname = "", phoneNumber = "", email = "", address = "";
};

string readTheLine() {
    string entryData;
    getline (cin,entryData);
    return entryData;
}

int makeNubersNotWords (string lineOfDataSub) {
    int numberIsId = 0;
    int numberLength = lineOfDataSub.size();
    int positionOfDidgit = 0;
    if (numberLength == 1) {
        numberIsId = lineOfDataSub[positionOfDidgit] - '0';
    } else {
        while (positionOfDidgit < numberLength) {
            numberIsId += lineOfDataSub[positionOfDidgit] - '0';
            numberIsId *= 10;
            positionOfDidgit++;
        }
        numberIsId /= 10;
    }
    return numberIsId;
}

string makeWordsNotNumbers (int number) {
    string stringNumber = "";
    stringNumber = to_string (number);
    return stringNumber;
}

void splitRecipientDataFromFile (string lineOfData, vector <Recipient> &recipient) {
    string lineOfDataSub = "";
    int rowOfData = 0;
    Recipient persons;
    for (int i = 0; i < (int) lineOfData.size(); i++) {
        if (lineOfData[i] != '|') {
            lineOfDataSub.push_back (lineOfData[i]);
        } else if (lineOfData[i] == '|') {
            if (rowOfData == 0) {
                int idOfAPerson = makeNubersNotWords (lineOfDataSub);
                persons.id = idOfAPerson;
                lineOfDataSub.erase();
            } else if (rowOfData == 1) {
                persons.name = lineOfDataSub;
                lineOfDataSub.erase();
            } else if (rowOfData == 2) {
                persons.surname = lineOfDataSub;
                lineOfDataSub.erase();
            } else if (rowOfData == 3) {
                persons.phoneNumber = lineOfDataSub;
                lineOfDataSub.erase();
            } else if (rowOfData == 4) {
                persons.email = lineOfDataSub;
                lineOfDataSub.erase();
            } else if (rowOfData == 5) {
                persons.address = lineOfDataSub;
                lineOfDataSub.erase();
            }
            rowOfData++;
        }
    }
    recipient.push_back (persons);
    rowOfData = 0;
}

int readTheDataFromFile (vector <Recipient> &recipient, int amountOfRecipients) {

    string lineOfData = "";
    fstream myFile;

    myFile.open ("ListaAdresow.txt",ios::app);
    myFile.close();

    myFile.open ("ListaAdresow.txt",ios::in);

    while (getline (myFile,lineOfData) ) {
        amountOfRecipients++;
        splitRecipientDataFromFile (lineOfData, recipient);
    }
    myFile.close();
    return amountOfRecipients;
}

int readTheLastId (vector <Recipient> recipient) {
    int lastId = 0;
    if(!recipient.size() == 0){
        int endOfVector = recipient.size()-1;
        lastId = recipient[endOfVector].id;
    }
    return lastId;
}

vector <Recipient> getDataFromUser (vector <Recipient> &recipient, int amountOfRecipients) {

    string name="", surname="", phoneNumber="", email="", address="";
    Recipient newPerson;
    int lastId = readTheLastId (recipient);

    system ( "cls" );
    cout << "Podaj imie: ";
    cin >> name;

    cout << "Podaj nazwisko: ";
    cin >> surname;

    cout << "Podaj numer telefonu: ";
    cin.sync();
    phoneNumber = readTheLine();

    cout << "Podaj email: ";
    email = readTheLine();

    cout << "Podaj adres: ";
    address = readTheLine();

    newPerson.id = lastId+1;
    newPerson.name = name;
    newPerson.surname = surname;
    newPerson.phoneNumber = phoneNumber;
    newPerson.email = email;
    newPerson.address = address;

    recipient.push_back (newPerson);

    return recipient;
}

void saveDataToFile (vector<Recipient> &recipient, int indexOfPerson,  int caseOfFunction) {

    const int AMOUNT_OF_LOOPS = 6;
    fstream myFile;
    string personsData = "";
    int indexOfData = 0;

    for (int i = 0; i < AMOUNT_OF_LOOPS; i++) {
        if (indexOfData == 0) {
            string id = makeWordsNotNumbers (recipient[indexOfPerson].id);
            personsData.append (id);
        } else if (indexOfData == 1) {
            personsData.append (recipient[indexOfPerson].name);
        } else if (indexOfData == 2) {
            personsData.append (recipient[indexOfPerson].surname);
        } else if (indexOfData == 3) {
            personsData.append (recipient[indexOfPerson].phoneNumber);
        } else if (indexOfData == 4) {
            personsData.append (recipient[indexOfPerson].email);
        } else if (indexOfData == 5) {
            personsData.append (recipient[indexOfPerson].address);
        }
        personsData.push_back ('|');
        indexOfData++;
    }

    if(caseOfFunction == 1) {
        myFile.open ("ListaAdresow.txt",ios::app);
        myFile << personsData << endl;
        myFile.close();
    } else if(caseOfFunction == 2) {
        if(indexOfPerson == 0) {
            myFile.open ("ListaAdresow.txt",ios::out);
            myFile.close();
        }
        myFile.open ("ListaAdresow.txt",ios::app);
        myFile << personsData << endl;
        myFile.close();
    } else {
        cout << "Nic sie nie stalo, zly kod zapisu do funkcji" << endl;
    }
}

int addNewRecipient (vector <Recipient> &recipient, int amountOfRecipients) {
    
    int index = amountOfRecipients;
    recipient = getDataFromUser (recipient, amountOfRecipients);
    saveDataToFile (recipient, recipient.size()-1, 1);
    amountOfRecipients += 1;

    system ("cls");
    cout << left << setw (10) << "Dodano nowa osobe!!" << endl;
    cout << left << setw (10) << "ID osoby: " << recipient[index].id << endl;
    cout << left << setw (10) << "Imie: "     << recipient[index].name << endl;
    cout << left << setw (10) << "Nazwisko: " << recipient[index].surname<< endl;
    cout << left << setw (10) << "Nr. Tel: "  << recipient[index].phoneNumber << endl;
    cout << left << setw (10) << "Email: "    << recipient[index].email << endl;
    cout << left << setw (10) << "Adres: "    << recipient[index].address << endl << endl;
    system ("pause");

    return amountOfRecipients;
}

void findName (vector <Recipient> recipient, int amountOfRecipients) {
    string searchedName = "";
    bool foundTheName = false;
    cout << "Podaj imie do wyszukania : ";
    getchar();
    searchedName = readTheLine();

    system ( "cls" );
    for (int i = 0; i < amountOfRecipients; i++) {
        if (searchedName == recipient[i].name) {
            foundTheName = true;
            cout << left << setw (10) << "ID osoby: " << recipient[i].id << endl;
            cout << left << setw (10) << "Imie: "     << recipient[i].name << endl;
            cout << left << setw (10) << "Nazwisko: " << recipient[i].surname<< endl;
            cout << left << setw (10) << "Nr. Tel: "  << recipient[i].phoneNumber << endl;
            cout << left << setw (10) << "Email: "    << recipient[i].email << endl;
            cout << left << setw (10) << "Adres: "    << recipient[i].address << endl << endl;
        }
    }
    if(foundTheName == false){
        cout << "Nie znaleziono podanego imienia!!" << endl;
    }
    system ("pause");
}

void findSurname (vector <Recipient> recipient, int amountOfRecipients) {
    string searchedSurname = "";
    bool foundTheSurname = false;
    cout << "Podaj nazwisko do wyszukania : ";
    getchar();
    searchedSurname = readTheLine();

    system ( "cls" );
    for (int i = 0; i < amountOfRecipients; i++) {
        if (searchedSurname == recipient[i].surname) {
            foundTheSurname = true;
            cout << left << setw (10) << "ID osoby: " << recipient[i].id << endl;
            cout << left << setw (10) << "Imie: "     << recipient[i].name << endl;
            cout << left << setw (10) << "Nazwisko: " << recipient[i].surname<< endl;
            cout << left << setw (10) << "Nr. Tel: "  << recipient[i].phoneNumber << endl;
            cout << left << setw (10) << "Email: "    << recipient[i].email << endl;
            cout << left << setw (10) << "Adres: "    << recipient[i].address << endl << endl;
        }
    }
    if(foundTheSurname == false){
        cout << "Nie znaleziono podanego nazwiska!!" << endl;
    }
    system ("pause");
}

void writeAllRecipientsOut (vector <Recipient> recipient, int amountOfRecipients) {
    system ( "cls" );
    cout << "Adresaci : " << amountOfRecipients << endl << endl;
    for (int i = 0; i < amountOfRecipients; i++) {
        cout << left << setw (10) << "ID osoby: " << recipient[i].id << endl;
        cout << left << setw (10) << "Imie: "     << recipient[i].name << endl;
        cout << left << setw (10) << "Nazwisko: " << recipient[i].surname<< endl;
        cout << left << setw (10) << "Nr. Tel: "  << recipient[i].phoneNumber << endl;
        cout << left << setw (10) << "Email: "    << recipient[i].email << endl;
        cout << left << setw (10) << "Adres: "    << recipient[i].address << endl << endl;
    }
    system ("pause");
}

bool findTheGivenId(int idToKill, vector <Recipient> recipient) {
    for(int i = 0; i < (int)recipient.size(); i++) {
        if(recipient[i].id == idToKill) {
            return true;
        }
    }
    return false;
}

int deleteRecipient (vector <Recipient> &recipient, int amountOfRecipients) {

    int idToKill = 0;
    char confirmingChar;
    cout << "Podaj ID osoby ktora chesz usunac z ksiazki adresowej : ";
    cin >> idToKill;

    if(!findTheGivenId(idToKill, recipient)) {
        cout << "Nie znaleziono podanego ID: " << idToKill << endl;
    } else {
        cout << "Napewno chcesz usunac adresata?" << endl;
        cout << "dla potwierdzenia wpisz 't': ";
        cin >> confirmingChar;
        if(confirmingChar == 't') {
            for (int i = 0; i < amountOfRecipients; i++) {
                if (recipient[i].id == idToKill) {
                    recipient.erase (recipient.begin()+i);
                    amountOfRecipients-=1;
                }
            }
            for (int i = 0; i < amountOfRecipients; i++) {
                saveDataToFile (recipient, i, 2);
            }
        }
    }
    cin.clear();
    system ("pause");
    return amountOfRecipients;
}

int positionOfPersonInFile(vector <Recipient> recipient, int idToEdit) {
    int i;
    for(i = 0; i < (int)recipient.size(); i++) {
        if(recipient[i].id == idToEdit) {
            break;
        }
    }
    return i;
}

void changeTheName(vector <Recipient> &recipient, int positionOfPerson) {
    string newName = "";
    cout << "Podaj nowe imie: ";
    cin >> newName;

    recipient[positionOfPerson].name = newName;
}

void changeTheSurname(vector <Recipient> &recipient, int positionOfPerson) {
    string newSurname = "";
    cout << "Podaj nowe nazwisko: ";
    cin >> newSurname;

    recipient[positionOfPerson].surname = newSurname;
}

void changeThePhoneNumber(vector <Recipient> &recipient, int positionOfPerson) {
    string newPhoneNumber = "";
    cout << "Podaj nowy numer telefonu: ";
    getchar();
    newPhoneNumber = readTheLine();

    recipient[positionOfPerson].phoneNumber = newPhoneNumber;
}

void changeTheEmail(vector <Recipient> &recipient, int positionOfPerson) {
    string newEmail = "";
    cout << "Podaj nowy e-mail: ";
    cin >> newEmail;

    recipient[positionOfPerson].email = newEmail;
}

void changeTheAddress(vector <Recipient> &recipient, int positionOfPerson) {
    string newAddress = "";
    cout << "Podaj nowy adres: ";
    getchar();
    newAddress = readTheLine();

    recipient[positionOfPerson].address = newAddress;
}

void editRecipient(vector <Recipient> &recipient, int amountOfRecipients) {

    char menuOptions;
    int idToEdit = 0;
    int positionOfPerson = 0;
    cout << "Podaj ID osoby ktorej informacje chesz edytowac: ";
    cin >> idToEdit;

    if(!findTheGivenId(idToEdit, recipient)) {
        cout << "Nie znaleziono podanego ID: " << idToEdit << endl;
    } else {
        positionOfPerson = positionOfPersonInFile(recipient, idToEdit);
        while (1) {
            system ( "cls" );
            cout << "1. imie" << endl;
            cout << "2. nazwisko" << endl;
            cout << "3. numer telefonu" << endl;
            cout << "4. email" << endl;
            cout << "5. adres" << endl;
            cout << "0. powrut do menu" << endl;
            cout << "Podaj wybor : ";
            menuOptions = getchar();

            switch (menuOptions) {
            case '1':
                changeTheName(recipient, positionOfPerson);
                break;
            case '2':
                changeTheSurname(recipient, positionOfPerson);
                break;
            case '3':
                changeThePhoneNumber(recipient, positionOfPerson);
                break;
            case '4':
                changeTheEmail(recipient, positionOfPerson);
                break;
            case '5':
                changeTheAddress(recipient, positionOfPerson);
                break;
            case '0':
                for(int i =0; i < amountOfRecipients; i++) {
                    saveDataToFile(recipient,i,2);
                }
                return;
            }
        }
    }
    cin.clear();
    system ("pause");
}

int main() {
    int amountOfRecipients = 0;
    char menuOptions;
    vector <Recipient> recipient;

    amountOfRecipients = readTheDataFromFile (recipient, amountOfRecipients);

    while (1) {
        system ( "cls" );
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukanie po imieniu" << endl;
        cout << "3. Wyszukanie po nazwisku" << endl;
        cout << "4. Wypisanie wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "0. Wyjdz z programu" << endl;
        cout << "Podaj wybor : ";
        menuOptions = getchar();

        switch (menuOptions) {
        case '1':
            amountOfRecipients = addNewRecipient (recipient, amountOfRecipients);
            break;
        case '2':
            findName (recipient, amountOfRecipients);
            break;
        case '3':
            findSurname (recipient, amountOfRecipients);
            break;
        case '4':
            writeAllRecipientsOut (recipient, amountOfRecipients);
            break;
        case '5':
            amountOfRecipients = deleteRecipient (recipient, amountOfRecipients);
            break;
        case '6':
            editRecipient(recipient, amountOfRecipients);
            break;
        case '0':
            exit (0);
            break;
        }
    }
    return 0;
}
