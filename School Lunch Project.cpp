#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

struct Users {
    string uName;
    string password;
};
struct Users users[10];
Users currentUser;
struct FoodMenu {

    string main;
    string mSize;
    string side;
    string drink;
    double totalCost = 0;
    string payment;

};
FoodMenu ap;
string mainArr[7] = { "Pizza", "Sandwich", "Salad", "Sushi", "Burger", "Rice Bowl", "Skip Main" };
string pMainArr[4] = { "Pepperoni", "Margherita", "Meatlovers", "Vegetarian" };
string sMainArr[4] = { "BLT", "Reuben", "Cheese & Ham", "Vegetarian" };
string sMainArr2[4] = { "Caesar", "Green", "Greek", "Fattoush" };
string sMainArr3[4] = { "Tuna", "Salmon", "Chicken & Avo", "Tamago" };
string bMainArr[4] = { "Traditional Cheese", "Spicy Chicken", "BBQ Beef", "Bacon & Cheese" };
string rMainArr[4] = { "Oyakodon", "Tofu", "Tempeh", "Pork" };
string sideArr[4] = { "Fries", "Fruit", "Protein Bar", "Skip Side" };
string drinkArr[4] = { "Soft Drink", "Juice", "Smoothie", "Skip Drink" };

int choiceMain = 0;
float mainCost = 0, sideCost = 0, drinkCost = 0;
// function prototypes
void usersFromFile();
void login();
void deleteUser();
void userEditUser(string userToEdit);
void registration();
void adminLogin();
void userView();
void profileView();
void orderFood();
void mainStart();
void mainSize();

int main()
{
    usersFromFile();
    cout << endl << endl;
    cout << "\t\t****************" << endl;
    cout << "\t\t   MAIN MENU" << endl;
    cout << "\t\t****************" << endl << endl << endl;
    cout << "\t1. CUSTOMER LOGIN" << endl;
    cout << "\t2. REGISTER" << endl;
    cout << "\t3. ADMIN LOGIN" << endl;
    cout << "\t4. EXIT" << endl << endl;
    int choice;
    cout << "\tChoose and option: ";
    cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        login();
        system("cls");
        userView();
        break;
    case 2:
        system("cls");
        registration();
        main();
        break;
    case 3:
        system("cls");
        adminLogin();
        /*adminView();*/
        break;
    case 4:
        return 0;
    }
}

void adminView() {
    cout << "";
}
void userView() {
    int choice;
    cout << "Welcome back " << currentUser.uName << endl << endl;
    cout << "1. Order Food" << endl << "2. View Profile" << endl << "3. Edit Profle" <<
        endl << endl;
    cout << "Choose an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
        /*orderFood():*/
        break;
    case 2:
        system("cls");
        profileView();
        break;
    case 3:
        userEditUser(currentUser.uName);
    }
}
void usersFromFile() {
    string user, password;
    int i = 0;
    ifstream myFile("users.txt");
    while (!myFile.eof()) {
        myFile >> user >> password;
        users[i].uName = user;
        users[i].password = password;
        i++;
    }
    /*for (b = 0; b < 5; b++) {
        cout << users[b].uName << " " << users[b].password << endl;
    }*/
}
void login() {
    string user, password;
    int count = 0, attemptsLeft = 3;
    while (attemptsLeft > 0 && count != 1) {
        cout << "username: ";
        cin >> user;
        cout << "password: ";
        cin >> password;
        attemptsLeft--;
        for (int i = 0; i < 6; i++) {
            if (user == users[i].uName && password == users[i].password) {
                count = 1;
                currentUser.uName = user;
                currentUser.password = password;
            }
        }
        if (count == 1) {
            cout << "login succesful";
        }
        else if (count != 1 && attemptsLeft > 0) {
            cout << "login failed, please try again...." << endl << endl;
            cout << "you have " << attemptsLeft << " attempts remaining" << endl;
            system("pause");
            system("cls");
        }
        else if (count != 1 && attemptsLeft == 0) {
            cout << "sorry, you have run out of attempts" << endl << "returning to main menu" 
                << endl << endl;
            system("pause");
            system("cls");
            main();
        }
    }
}
void deleteUser() {
    usersFromFile();
    string user;
    cout << "enter user to delete: ";
    getline(cin, user);
    fstream myFile("temp.txt", ios::app);
    for (int i = 0; i < 6; i++) {
        if (user != users[i].uName) {
            myFile << users[i].uName << " " << users[i].password << endl;
        }
    }
    myFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}
void userEditUser(string userToEdit) {
    usersFromFile();
    string password;
    int choice;
    cout << "would you like to update user name or password?" << endl;
    cout << "1. username\n2. password" << endl;
    cin >> choice;
    switch (choice) {
        case 1: {
            string newUserName;
            cout << "enter new username: ";
            cin >> newUserName;
            for (int i = 0; i < 10; i++) {
                if (users[i].uName == userToEdit) {
                    users[i].uName = newUserName;
                    currentUser.uName = newUserName;
                }
            }
            cout << "username updated";
            fstream myFile("temp.txt", ios::app);
            for (int i = 0; i < 10; i++) {
                myFile << users[i].uName << " " << users[i].password << endl;
            }
            myFile.close();
            remove("users.txt");
            rename("temp.txt", "users.txt");
            break;
        }
        case 2: {
            string newPassword, oldPassword;
            cout << "please confirm your password: ";
            cin >> oldPassword;
            if (oldPassword == currentUser.password) {
                cout << "enter new password: ";
                cin >> newPassword;
                for (int i = 0; i < 10; i++) {
                    if (users[i].uName == userToEdit) {
                        users[i].password = newPassword;
                        currentUser.password = newPassword;
                    }
                }
                cout << "password updated";
                fstream myFile("temp.txt", ios::app);
                for (int i = 0; i < 10; i++) {
                    myFile << users[i].uName << " " << users[i].password << endl;
                }
                myFile.close();
                remove("users.txt");
                rename("temp.txt", "users.txt");
            }
            break;
        }
    }
}
void adminEditUser() {
   
}
void registration() {
    system("cls");
    usersFromFile();
    string userName, password, passwordCheck;;
    cout << "enter a username:";
    cin >> userName;
passwordCheck:;
    cout << "enter a password: ";
    cin >> password;
    cout << "confrim password: ";
    cin >> passwordCheck;
    if (password == passwordCheck) {
        fstream myFile("users.txt", ios::app);
        myFile << userName << " " << password << endl;
        myFile.close();
    }
    else {
        cout << "paswords do not match, try again" << endl;
        goto passwordCheck;
    }
    cout << "Registration Succesful. Please log in from the main menu" << endl << endl;
}
void adminLogin() {
    string user, password, user1, password1;
    int count = 0, attemptsLeft = 3;
    while (attemptsLeft > 0 && count != 1) {
        attemptsLeft--;
        cout << "admin username: ";
        cin >> user;
        cout << "admin password: ";
        cin >> password;
        ifstream myFile("admin.txt");
        myFile >> user1 >> password1;
        if (user == user1 && password == password1) {
            count = 1;
        }
        if (count == 1) {
            cout << "login succesful";
            currentUser.password = password;
            currentUser.uName = user;
        }
        else if (count != 1 && attemptsLeft > 0) {
            cout << "login failed, please try again...." << endl << endl;
            cout << "you have " << attemptsLeft << " attempts remaining" << endl;
            system("pause");
            system("cls");
        }
        else if (count != 1 && attemptsLeft == 0) {
            cout << "sorry, you have run out of attempts" << endl << "returning to main menu"
                << endl << endl;
            system("pause");
            system("cls");
            main();
        }
    }
}
void profileView() {
    cout << "Username: " << currentUser.uName << endl;;
    cout << "Password: " << currentUser.password << endl;
}