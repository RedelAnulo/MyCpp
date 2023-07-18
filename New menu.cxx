#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string.h>

using namespace std;

// Define a struct for storing food items
struct FoodItem {
    string name;
    double price;
    int quantity;
};
const int MAX_ITEMS = 100;


// Define a function to display the menu
// Define a function to save the menu to a file
void saveMenuToFile(FoodItem *menu, int count) {
    std::ofstream outFile("menu.txt", std::ofstream::out| std::ofstream::trunc);
    if (!outFile) {
        cout << "Error opening file; unable to save menu.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        outFile << menu[i].name << " - " << menu[i].price << " - " << menu[i].quantity << endl;
    }
    outFile.close();
    cout << "Menu saved to file.\n";
}

// Define a function to load the menu from a file
void loadMenuFromFile(FoodItem *menu, int& count) {
    ifstream inFile("menu.txt");
    if (!inFile) {
        cout << "Error opening file; unable to load menu.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        inFile >> menu[i].name >> menu[i].price >> menu[i].quantity;
    }
    inFile.close();
    cout << "Menu loaded from file.\n";
}
void displayMenu(FoodItem *menu, int count) {
	loadMenuFromFile(menu, count);
    cout << "Menu:\n";
    for (int i = 0; i < count; i++) {
        cout << i+1 << ". " << menu[i].name << " - $" << menu[i].price << " - "<<menu[i].quantity << endl;
    }
    cout << endl;
}

// Define a function to update a food item
void updateItem(FoodItem *menu, int count) {
    int itemNum;
    cout << "Enter the item number to update: ";
    cin >> itemNum;
    itemNum--;
    if (itemNum < 0 || itemNum >= count) {
        cout << "Invalid item number.\n";
        return;
    }
    cout << "Enter the new name: ";
    cin >> menu[itemNum].name;
    cout << "Enter the new price: ";
    cin >> menu[itemNum].price;
    cout << "Enter the new quantity: ";
    cin >>menu[itemNum].quantity;
    cout << "Itemupdated.\n";
    saveMenuToFile(menu, count);
}

// Define a function to delete a food item
void deleteItem(FoodItem *menu, int& count) {
    int itemNum;
    displayMenu(menu, count);
    cout << "Enter the item number to delete: ";
    cin >> itemNum;
    itemNum--;
    if (itemNum < 0 || itemNum >= count) {
        cout << "Invalid item number.\n";
        return;
    }
    for (int i = itemNum; i < count-1; i++) {
        menu[i] = menu[i+1];
        saveMenuToFile(menu, count);
    }
    count--;
    cout << "Item deleted.\n";
}
// Define a function to register a new food item
void registerItem(FoodItem *menu, int& count) {
    if (count == MAX_ITEMS) {
        cout << "Menu is full.\n";
        return;
    }
    cout << "Enter the name: ";
    cin.ignore();  // Ignore any leftover input in the stream
    getline(cin, menu[count].name);  // Read the entire line into the name field
    cout << "Enter the price: ";
    cin >> menu[count].price;
    cout << "Enter the quantity: ";
    cin >> menu[count].quantity;
    count++;
    cout << "Item added.\n";
    saveMenuToFile(menu, count);
}

// Define a function to take an order from the user
void takeOrder(FoodItem *menu, int count) {
    int orderCount = 0;
    FoodItem order[MAX_ITEMS];
    char choice;
    do {
        system("cls");
		displayMenu(menu, count);
        int itemNum;
        cout << "Enter the item number to order: ";
        cin >> itemNum;
        itemNum--;
        if (itemNum < 0 || itemNum >= count) {
            cout << "Invalid item number.\n\n";
            continue;
        }
        cout << "Enter the quantity to order: ";
        int quantity;
        cin>> quantity;
        if (quantity <= 0) {
            cout << "Invalid quantity.\n\n";
            continue;
        }
        if (quantity > menu[itemNum].quantity) {
            cout << "Insufficient quantity.\n\n";
            continue;
        }
        order[orderCount] = menu[itemNum];
        order[orderCount].quantity = quantity;
        menu[itemNum].quantity -= quantity;
        orderCount++;
        saveMenuToFile(menu, count);
        system("cls");
        cout << "Item added to order.\n\n";
        cout << "Do you want to order another item? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    system("cls");
    cout << "Order Summary:\n\n";
    double total = 0;
    for (int i = 0; i < orderCount; i++) {
        cout << order[i].name << " x " << order[i].quantity << " - $" << order[i].price * order[i].quantity << endl;
        total += order[i].price * order[i].quantity;
    }
    cout << "Total: $" << total << endl;
}

void Login(){
	string ur;
	string pass;
	cout<<"Enter Username:"<<endl;
	getline(cin, ur);
	cout<<endl<<"Enter Password:"<<endl;
	getline(cin, pass);
	if(ur=="admin")
	{
		if(pass=="admin")
		{
			cout<<"Successful Login\n\n";
		}
		else
		{
			cout<<"Incorrect Password\n\n";
			Login();
		}
	}
	else
	{
		cout<<"Incorrect Username\n\n";
		Login();
	}
	system("cls");
}
  
void customerLogin(FoodItem *menu, int count){
	system("cls");
	cout << "Welcome to our food ordering system!\n\n";
	char choice;
    do {
        cout << "Enter your choice:\n\n"
             << "1. Order an Item\n\n"
             << "0. Exit\n\n";
        cin >> choice;
        switch (choice) {
            case '1':
            	system("cls");
                takeOrder(menu, count);
                break;
            case '0':
            	system("cls");
                break;
            default:
            	system("cls");
                cout << "Invalid choice.\n\n";
                break;
        }
    } while (choice != '0');
}

void managerLogin(FoodItem *menu, int count){
	cout << "Welcome to our food ordering system!\n\n";
	char choice;
    do {
        cout << "Enter your choice:\n\n"
             << "1. Login\n\n"
             << "0. Exit\n\n";
        cin >> choice;
        switch (choice) {
            case '1':
            	system("cls");
                Login();
                break;
		    case '0': 
		        break;
			default:
				cout << "Invalid choice.\n\n";
				break;
		}
		    cout << "Welcome to our food ordering system!\n";
		    do {
	        cout << "Enter your choice:\n\n"
	             << "1. Display menu\n\n"
	             << "2. Register a new item\n\n"
	             << "3. Update an existing item\n\n"
	             << "4. Delete an item\n\n"
	             << "5. Save menu to file\n\n"
	             << "6. Load menu from file\n\n"
	             << "0. Exit\n\n";
	        cin >> choice;
	        switch (choice) {
	            case '1':
	            	system("cls");
	                displayMenu(menu, count);
	                break;
	            case '2':            
	            	system("cls");
	                registerItem(menu, count);
	                break;
	            case '3':
	            	system("cls");
	                updateItem(menu, count);
	                break;
	            case '4':
	            	system("cls");
	                deleteItem(menu, count);
	                break;
	            case '5':
	            	system("cls");
	                saveMenuToFile(menu, count);
	                break;
	            case '6':
	            	system("cls");
	                loadMenuFromFile(menu, count);
	                break;
	            case '0':
	            	system("cls");                
					break;
	            default:
	            	system("cls");
	                cout << "Invalid choice.\n";
	                break;
	        }
	    } while (choice != '0');         
	}while(choice != '0');
}
int main() {
    FoodItem menu[MAX_ITEMS];
	int count = 0;
	char choice;
	
	menu[count] = {"Hamburger", 5.99, 10};count++;
    menu[count] = {"Cheeseburger", 6.99, 8};count++;
    menu[count++] ={"Chicken Sandwich", 7.99, 6};
    menu[count++] = {"French Fries", 2.99, 20};
    menu[count++] = {"Onion Rings", 3.99, 15};
    menu[count++] = {"Soda",1.99, 30};
    menu[count++] = {"Fish and Chips", 9.99, 5};
    menu[count++] = {"Steak and Potatoes", 15.99, 3};
    menu[count++] = {"Spaghetti and Meatballs", 8.99, 7};
    menu[count++] = {"Chicken Tikka Masala", 11.99, 4};
    menu[count++] = {"Pad Thai", 10.99, 6};
    menu[count++] = {"Sushi Platter", 18.99, 2};

	do{
        cout << "***   WELCOME   ***\n\n"
			 << "Enter your choice:\n\n"
             << "1. Customer\n\n"
             << "2. Manager\n\n"
             << "0. Exit\n\n";
        cin >> choice;
        switch (choice) {
            case '1':
            	system("cls");
                customerLogin(menu, count);
                break;
            case '2':
            	system("cls");
                managerLogin(menu, count);
                break;
            case '0':
            	system("cls");
                cout << "Goodbye!\n\n";
                break;
            default:
            	system("cls");
                cout << "Invalid choice.\n\n";
                break;
        }
    } while (choice != '0');
    return 0;
}