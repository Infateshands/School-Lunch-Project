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
        orderFood();
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
void orderFood() {
	string sizeMain1;
	void mainStart();
	//void MainChoice();
	void mainSize();
mainStart:;
	mainCost = 0;
	mainStart();
	switch (choiceMain) {

	case 1: cout << "You have chosen: " << mainArr[0] << "\nplease pick your choice of flavour\n";
		mainCost += 6;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << pMainArr[i] << endl;
		}
		int pChoice;
		cin >> pChoice;
		switch (pChoice) {
		case 1: ap.main = pMainArr[0];
			goto mainEnd;
		case 2: ap.main = pMainArr[1];
			goto mainEnd;
		case 3: ap.main = pMainArr[2];
			goto mainEnd;
		case 4: ap.main = pMainArr[3];
			goto mainEnd;
		default: cout << "Invalid choice please try again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 2: cout << "You have chosen: " << mainArr[1] << "\nplease pick your choice of sandwitch\n";
		mainCost += 5;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << sMainArr[i] << endl;
		}
		int sChoice;
		cin >> sChoice;
		switch (sChoice) {
		case 1: ap.main = sMainArr[0];
			goto mainEnd;
		case 2: ap.main = sMainArr[1];
			goto mainEnd;
		case 3: ap.main = sMainArr[2];
			goto mainEnd;
		case 4: ap.main = sMainArr[3];
			goto mainEnd;
		default: cout << "Invalid choice please try again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 3: cout << "You have chosen: " << mainArr[2] << "\nplease pick your choice of salad\n";
		mainCost += 5;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << sMainArr2[i] << endl;
		}
		int sChoice2;
		cin >> sChoice2;
		switch (sChoice2) {
		case 1: ap.main = sMainArr2[0];
			goto mainEnd;
		case 2: ap.main = sMainArr2[1];
			goto mainEnd;
		case 3: ap.main = sMainArr2[2];
			goto mainEnd;
		case 4: ap.main = sMainArr2[3];
			goto mainEnd;
		default: cout << "Invalid choice please try again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 4: cout << "You have chosen: " << mainArr[3] << "\nplease pick your choice of sushi\n";
		mainCost += 6;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << sMainArr3[i] << endl;
		}
		int sChoice3;
		cin >> sChoice3;
		switch (sChoice3) {
		case 1: ap.main = sMainArr3[0];
			goto mainEnd;
		case 2: ap.main = sMainArr3[1];
			goto mainEnd;
		case 3: ap.main = sMainArr3[2];
			goto mainEnd;
		case 4: ap.main = sMainArr3[3];
			goto mainEnd;
		default: cout << "Invalid choice please try again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 5: cout << "You have chosen: " << mainArr[4] << "\nplease pick your choice of burger\n";
		mainCost += 6;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << bMainArr[i] << endl;
		}
		int bChoice;
		cin >> bChoice;
		switch (bChoice) {
		case 1: ap.main = bMainArr[0];
			goto mainEnd;
		case 2: ap.main = bMainArr[1];
			goto mainEnd;
		case 3: ap.main = bMainArr[2];
			goto mainEnd;
		case 4: ap.main = bMainArr[3];
			goto mainEnd;
		default: cout << "Invalid choice please order again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 6: cout << "You have chosen: " << mainArr[5] << "\nplease pick your choice of rice bowl\n";
		mainCost += 5;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << rMainArr[i] << endl;
		}
		int rChoice;
		cin >> rChoice;
		switch (rChoice) {
		case 1: ap.main = rMainArr[0];
			goto mainEnd;
		case 2: ap.main = rMainArr[1];
			goto mainEnd;
		case 3: ap.main = rMainArr[2];
			goto mainEnd;
		case 4: ap.main = rMainArr[3];
			goto mainEnd;
		default: cout << "Invalid choice please order again\n";
			system("pause");
			system("cls");
			goto mainStart;
		}

	case 7: cout << "Main skipped\n";
		system("pause");
		ap.main = mainArr[6];
		goto sideStart;

	default: cout << "Please choose a valid number\n";
		system("pause");
		system("cls");
		choiceMain = NULL;
		goto mainStart;
	}

mainEnd:;

	mainSize();

	cout << "you have chosen a " << ap.mSize << " " << choiceMain << ". " << ap.main << " = $" << mainCost << endl;
	cout << "is this the correct order? y/n\n";
	char correct1;
	cin >> correct1;
	if (correct1 == 'n') {
		choiceMain = NULL;
		system("cls");
		goto mainStart;
	}

	else if (correct1 == 'y') {
		cout << "Main order successful. Please choose your side order\n\n";
		system("pause");
		system("cls");
		goto sideStart;
	}

	else
		cout << "Please enter either 'y' or 'n'\n";
	system("pause");
	system("cls");
	goto mainEnd;

sideStart:;

	cout << "Please choose your side item from the following list: \n";
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << ". " << sideArr[i] << endl;
	}
	int sideChoice;
	cin >> sideChoice;
	switch (sideChoice) {
	case 1: ap.side = sideArr[0];
		sideCost = 3;
		goto sideEnd;
	case 2: ap.side = sideArr[1];
		sideCost = 2;
		goto sideEnd;
	case 3: ap.side = sideArr[2];
		sideCost = 3;
		goto sideEnd;
	case 4: ap.side = sideArr[3];
		cout << "Are you sure you want to skip a side order? y/n\n";
	sideSkip:;
		char sideSkip;
		cin >> sideSkip;
		if (sideSkip == 'n') {
			sideChoice = NULL;
			goto sideStart;
		}
		else if (sideSkip == 'y') {
			goto drinkStart;
		}
		else {
			cout << "please enter either 'y' or 'n'\n";
			sideSkip = NULL;
			goto sideSkip;

	default: cout << "Invalid choice please order again\n";
		system("pause");
		system("cls");
		sideChoice = NULL;
		goto sideStart;
		}
	}
sideEnd:;

	cout << "you have chosen: " << sideChoice << ". " << ap.side << " = $" << sideCost << endl;

	cout << "is this the correct order? y/n\n";
	correct1 = NULL;
	cin >> correct1;
	if (correct1 == 'n') {
		sideChoice = NULL;
		system("cls");
		goto sideStart;
	}

	else if (correct1 == 'y') {
		cout << "Side order successful.\n\n";
		system("pause");
		system("cls");
		goto drinkStart;
	}

	else {
		cout << "Please enter either 'y' or 'n'\n";
		goto sideEnd;
	}

drinkStart:;

	cout << "Please choose your drink order from the following list: \n\n";
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << ". " << drinkArr[i] << endl;
	}
	int drinkChoice;
	cin >> drinkChoice;
	switch (drinkChoice) {
	case 1: ap.drink = drinkArr[0];
		drinkCost = 3;
		goto drinkEnd;
	case 2: ap.drink = drinkArr[1];
		drinkCost = 4;
		goto drinkEnd;
	case 3: ap.drink = drinkArr[2];
		drinkCost = 5;
		goto drinkEnd;
	case 4: ap.drink = drinkArr[3];
		cout << "Are you sure you want to skip a drink order? y/n\n";
	drinkSkip:;
		char drinkSkip;
		cin >> drinkSkip;
		if (drinkSkip == 'n') {
			drinkChoice = NULL;
			goto sideStart;
		}
		else if (drinkSkip == 'y') {
			goto orderEnd;
		}
		else {
			cout << "please enter either 'y' or 'n'\n";
			drinkSkip = NULL;
			goto drinkSkip;

		}


	default: cout << "Invalid choice please order again\n";
		system("pause");
		system("cls");
		drinkChoice = NULL;
		goto drinkStart;
	}

drinkEnd:;

	cout << "you have chosen: " << drinkChoice << ". " << ap.drink << " = $" << drinkCost << endl;

	cout << "is this the correct order? y/n\n";
	correct1 = NULL;
	cin >> correct1;
	if (correct1 == 'n') {
		drinkChoice = NULL;
		system("cls");
		goto drinkStart;
	}

	else if (correct1 == 'y') {

		cout << "Drink order successful.\n\n";
		system("pause");
		system("cls");
		goto orderEnd;
	}

	else {
		cout << "Please enter either 'y' or 'n'\n";
		goto drinkEnd;
	}

orderEnd:;


	cout << "Here is your final order: \n\n----------------------\n";
	if (ap.main != mainArr[6]) {
		cout << "1 x " << ap.mSize << " " << ap.main << " = $" << mainCost << endl;
	}
	else if (ap.main == mainArr[6]) {
		cout << "~~~~No main order~~~~\n";
	}

	if (ap.side != sideArr[3]) {
		cout << "1 x " << ap.side << " = $" << sideCost << endl;
	}
	else if (ap.side == sideArr[3]) {
		cout << "~~~~No side order~~~~\n";
	}

	if (ap.drink != drinkArr[3]) {
		cout << "1 x " << ap.drink << " = $" << drinkCost << endl;
	}
	else if (ap.drink == drinkArr[3]) {
		cout << "~~~~No drink order~~~~\n";
	}

	ap.totalCost = mainCost + sideCost + drinkCost; //summing costs of main, side and drink into totalCost
	if (ap.main != mainArr[6] && ap.side != sideArr[3] && ap.drink != drinkArr[3]) { //if user didnt choose to skip either main, side or drink
		// combo meal discount:
		// if user has all 3 orders filled { create 20% discount } 

		cout << "\n20% discount added for a meal combo\n";
		double discount;
		discount = 0.8 * ap.totalCost;
		cout << "The total is: $" << discount << endl;
		cout << "you have saved $" << ap.totalCost - discount << endl;
		ap.totalCost = discount; //storing discount price to total amount in FoodMenu structure
		discount = NULL;

	}
	else {
		cout << "The total is: $" << ap.totalCost << endl;

	}

	// Payment methods

	cout << "How would you like to pay?\n"
		<< "1.Cash\n2.Card\n3.Bitcoin";
	int payment;
	cin >> payment;
	system("cls");

	if (payment == 1) {
		cout << "Please insert cash into the machine\n";
		ap.payment = "cash";
	}

	else if (payment == 2) {
		cout << "please insert card into the machine\n";
		ap.payment = "card";
	}

	else if (payment == 3) {
		cout << "please deposit into this wallet address\n";
		ap.payment = "bitcoin";
	}


	system("pause");

	cout << "Payment Complete!\n"
		<< "Would you like to see your receipt?\n";
}
void mainStart() {

	cout << "Welcome to the food menu\n Please choose a main menu item\n";
	for (int i = 0; i < 7; i++) {
		cout << i + 1 << ". " << mainArr[i] << endl;
	}

	cin >> choiceMain;
}
void mainSize() {
mainSize:;
	FoodMenu ap;
	cout << "What size would you like to order?\n"
		<< "1.Small\n2.Medium\n3.Large\n";

	int sizeMain;
	cin >> sizeMain;
	if (sizeMain == 0) {
		ap.mSize = "skip";
	}
	else if (sizeMain == 1) {
		ap.mSize = "small";
		mainCost -= 1.5;
	}
	else if (sizeMain == 2) {
		ap.mSize = "medium";
	}
	else if (sizeMain == 3) {
		ap.mSize = "large";
		mainCost += 1.5;
	}
	else {
		cout << "Please enter valid number\n";
		system("pause");
		system("cls");
		goto mainSize;

	}


}
