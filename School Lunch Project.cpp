#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int login();
void registration();
void seeAllUsers();
void adminLogin();
void adminView();
void deleteUser();
int attemptsRemaining = 2;

int main() {
    // MAIN MENU
    int choice;
    cout << "\n\n\tpress 1 to LOGIN" << endl;
    cout << "\tpress 2 for ADMIN LOGIN" << endl;
    cout << "\tpress 3 to REGISTER" << endl;
    cout << "\tpress 4 to EXIT" << endl;
    cout << "\tenter choice: ";
    cin >> choice;
    cout << endl;
    switch (choice) {
    case 1:
        login();
        system("pause");
        break;
    case 2:
        adminLogin();
        adminView();
        break;
    case 3:
        registration();
        break;


    case 4:
        return 0;

    default:
        cout << "enter valid choice\n";
    }
    return 0;
}
// USER ENTERS USERNAME AND PASSWORD AND IS CHECKED AGAINST RECORDS.TXT FILE AND 3 ATTEMPTS GIVEN
int login() {
    int count = 0;
    
    string userId, password, id, pass;
    system("cls");
    cout << "enter username: ";
    cin >> userId;
    cout << "enter password: ";
    cin >> password;
    ifstream input("records.txt");
        while (input >> id >> pass) {
            if (id == userId && pass == password) {
                count = 1;
                system("cls");
            }
            input.close();
            if (count == 1) {
                cout << "Welcome back " << userId << ", Login Succesful\n";
            }
            else if (count == 0 && attemptsRemaining != 0) {
                cout << "\nLogin Error...please try again\n";
                attemptsRemaining--;
                cout << endl << attemptsRemaining + 1 << " attempts left" << endl << endl;
                system("pause");
                system("cls");
                login();
            }
            else if (count == 0 && attemptsRemaining == 0) {
                cout << "\ntoo many attempts. goodbye" << endl << endl;
          
                return 0;
            }
        }
};
// REGISTER NEW USER, SAVE DATA TO RECORDS.TXT FILE
void registration() {
    string ruserId, rpassword, rid, rpass;
    system("cls");
    cout << "Enter user name: ";
    cin >> ruserId;
    cout << "\nenter password: ";
    cin >> rpassword;
    ofstream f1("records.txt", ios::app);
    f1 << ruserId << " " <<  rpassword << endl << endl;
    system("cls");
    cout << "Thank You " << ruserId << ", Registration Succesful\n";
    system("pause");
    main();
};
// SEE ALL USERS, PRINT RECORDS.TXT TO CONSOLE, ONLY AVAILABLE FOR ADMIN LOGIN
void seeAllUsers() {
    fstream myFile;
    myFile.open("records.txt", ios::in);
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            cout << line << endl;
        }
    }
}
// ADMIN LOGIN, CHECKED AGAINST ADMIN.TXT FILE. 
void adminLogin() {
    int count = 0;
    string userId, password, id, pass;
    system("cls");
    cout << "enter username: ";
    cin >> userId;
    cout << "enter password: ";
    cin >> password;
    ifstream input("admin.txt");
    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1) {
        cout << userId << "\nLogin Succesful\n";
        system("cls");

    }
    else {
        cout << "\nLogin Error\n";
        system("pause");
        system("cls");
        main();
    }
}
// ADMIN CAN VIEW/DELETE USERS
void adminView() {
    int choice;
    cout << "press 1 to see all users" << endl;
    cout << "press 2 to delete a user" << endl;
    cout << "press 3 to exit to main menu" << endl;

    cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        seeAllUsers();
        cout << endl;
        system("pause");
        system("cls");
        adminView();
        break;
    case 2:
        deleteUser();
        break;
    case 3:
        system("cls");
        main();
        break;
    default:
        cout << "enter valid choice";
    }
}
//ADMIN CAN REMOVE USER FROM DATABASE.
void deleteUser() {
    system("cls");
    string tempDelete;
    string line;
    ifstream myFile;
    myFile.open("records.txt");
    ofstream tempFile;  // TEMP FILE TO STORE DATA
    tempFile.open("temp.txt");
    cout << "enter the user name of the user you want to delete: ";
    cin >> tempDelete; 
    // FIND USER IN RECORDS.TXT FILE AND WRITE CONTENTS OF FILE MINUS DELETED USER TO TEMP FILE
    if (myFile.is_open() && tempFile.is_open()){
        while (getline(myFile, line)) {
            if (line.find(tempDelete) == string::npos) {
                tempFile << line << endl;
            }
        }
    }
    tempFile.close();
    myFile.close();
    remove("records.txt"); // DELETE ORIGINAL RECORDS.TXT
    rename("temp.txt", "records.txt"); // RENAME T4EMP FILE TO RECORDS.TXT 
    cout << "user deleted" << endl;
    system("pause");
    system("cls");
    adminView();
    
} 
 