#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void login();
void registration();
void seeAllUsers();
void adminLogin();
void adminView();
int count();
void deleteUser();

int main() {

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
void login() {
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
    }
    input.close();
    if (count == 1) {
        cout << "Welcome back " << userId << ", Login Succesful\n";
        main();
    }
    else {
        cout << "\nLogin Error\n";
        system("pause");
        system("cls");
        main();
    }
};
void registration() {
    string ruserId, rpassword, rid, rpass;
    system("cls");
    cout << "Enter user name: ";
    cin >> ruserId;
    cout << "\nenter password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << endl << rpassword << endl << endl;
    system("cls");
    cout << "Thank You " << ruserId << ", Registration Succesful\n";
    system("pause");
    main();
};
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
}void adminView() {
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
        break;
    case 3:
        system("cls");
        main();
        break;
    default:
        cout << "enter valid choice";
    }
}
void deleteUser() {
    system("cls");


}
int count() {
    string line;
    int count{};
    ifstream input;
    input.open("records.txt");

    while (getline(input, line)) {
        count++;
    }
    return count;
}
