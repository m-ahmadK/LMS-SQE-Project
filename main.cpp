#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <cctype>

// Platform-Specific Configuration
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define CLS() system("cls")
#else
    #include <unistd.h>
    #define CLS() system("clear")
    // Stub definitions for Linux execution
    inline int getch() { return getchar(); }
#endif

using namespace std;

const string ADMIN_PASSWORD = "pass";
const string ADMIN_NAME = "ahmad";
const string LibraryFile = "LMS.txt";
const string RentFile = "RentBook.txt";

class Node {
public:
    int id;
    string title;
    string Author;
    int Quantity;
    string category;
    int addition;
    Node* next;

    Node(string title, string Author, string category, int id, int addition, int Quantity) {
        this->id = id;
        this->title = title;
        this->Author = Author;
        this->Quantity = Quantity;
        this->category = category;
        this->addition = addition;
        this->next = NULL;
    }

    Node() {
        id = 1;
        title = "";
        Author = "";
        Quantity = 0;
        category = "";
        addition = 0;
        next = NULL;
    }
};

class Rent {
public: 
    int Id, days, BookId;
    string name, contact, rentedDate, dueDate, BookName;
    Rent* next;
    Rent(string name, string contact, string rentedDate, string dueDate, string BookName, int Id, int days, int BookId) {
        this->Id = Id;
        this->name = name;
        this->contact = contact;
        this->days = days;
        this->rentedDate = rentedDate;
        this->dueDate = dueDate;
        this->BookName = BookName;
        this->BookId = BookId;
        this->next = NULL;
    }
    Rent() {
        Id = 1;
        name = "";
        contact = "";
        days = 0;
        rentedDate = "";
        dueDate = "";
        BookName = "";
        BookId = 0;
        next = NULL;
    }
};

class Library {
    Node* head;
    Rent* Head;
public:
    int idCounter;
    int TotalBooks;

    Library() {
        head = NULL;
        Head = NULL;
        TotalBooks = 0;
        idCounter = 0;
    }

    // Forward declarations to ensure visibility across methods
    void menu();
    void adminMenu();
    void userMenu();
    void AddBook();
    void ModifyBooks();
    void View_All_Books();
    void SearchBook();
    void SearchByCategory();
    void SearchByID();
    void SearchByName();
    void rentABook();
    void ViewRentBooks();
    void rentForm(string BookName, int BookId);
    void handleBookRental(string BookName, int BookId);
    void IdCounter();

    void LibraryList(const string& filename) {
        ifstream inFile(LibraryFile.c_str());
        if (!inFile) {
            return;
        }
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string title, Author, category;
            string idStr, additionStr, quantityStr;

            getline(ss, title, ',');
            getline(ss, Author, ',');
            getline(ss, category, ',');
            getline(ss, idStr, ',');
            getline(ss, additionStr, ',');
            getline(ss, quantityStr, ',');

            int id = idStr.empty() ? 0 : atoi(idStr.c_str());
            int addition = additionStr.empty() ? 0 : atoi(additionStr.c_str());
            int Quantity = quantityStr.empty() ? 0 : atoi(quantityStr.c_str());

            Node* newNode = new Node(title, Author, category, id, addition, Quantity);
            if (head == NULL) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        inFile.close();
        IdCounter();
    }

    void RentList(const string& filename) {
        ifstream inFile(RentFile.c_str());
        if (!inFile) {
            return;
        }
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string name, contact, rentedDate, dueDate, BookName;
            string idStr, daysStr, bookIdStr;

            getline(ss, name, ',');
            getline(ss, contact, ',');
            getline(ss, rentedDate, ',');
            getline(ss, dueDate, ',');
            getline(ss, BookName, ',');
            getline(ss, idStr, ',');
            getline(ss, daysStr, ',');
            getline(ss, bookIdStr, ',');

            int Id = idStr.empty() ? 0 : atoi(idStr.c_str());
            int days = daysStr.empty() ? 0 : atoi(daysStr.c_str());
            int BookId = bookIdStr.empty() ? 0 : atoi(bookIdStr.c_str());

            Rent* rentNode = new Rent(name, contact, rentedDate, dueDate, BookName, Id, days, BookId);
            if (Head == NULL) {
                Head = rentNode;
            } else {
                Rent* temp = Head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = rentNode;
            }
        }
        inFile.close();
    }
};

void Library::IdCounter() {
    TotalBooks = 0;
    if (head == NULL) {
        idCounter = 0;
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        TotalBooks++;
        idCounter = temp->id;
        temp = temp->next;
    }
}

void Library::userMenu() {
    cout << "\t\t\t------------------------------------------------------" << endl;
    cout << "\t\t\t--------------- Welcome to User's Menu ----------------" << endl;
    cout << "\t\t\t------------------------------------------------------" << endl;
    cout << "\t\t1. View All Books" << endl;
    cout << "\t\t2. Search Books" << endl;
    cout << "\t\t3. Rent Book" << endl;
    cout << "\t\t4. Back to Main Menu" << endl;
    cout << "\t\tEnter your choice : ";

    int choice;
    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "\nInvalid input! Returning to main menu." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        menu();
        return;
    }
    switch (choice) {
        case 1: View_All_Books(); break;
        case 2: SearchBook(); break;
        case 3: rentABook(); break;
        case 4: menu(); break;
    }
}

void Library::adminMenu() {
    cout << "\t\t\t------------------------------------------------------" << endl;
    cout << "\t\t\t--------------- Welcome to Admin's Menu ---------------" << endl;
    cout << "\t\t\t------------------------------------------------------" << endl;
    cout << "\t\t1. Add Books" << endl;
    cout << "\t\t2. Modify Books" << endl;
    cout << "\t\t3. View All Books" << endl;
    cout << "\t\t4. Search Books" << endl;
    cout << "\t\t5. Rent Book" << endl;
    cout << "\t\t6. View Rent Books" << endl;
    cout << "\t\t7. Back to Main Menu" << endl;
    cout << "\t\tEnter your choice : ";

    int choice;
    if (!(cin >> choice) || choice < 1 || choice > 7) {
        cout << "\nInvalid input! Returning to main menu." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        menu();
        return;
    }

    switch (choice) {
        case 1: AddBook(); break;
        case 2: ModifyBooks(); break;
        case 3: View_All_Books(); break;
        case 4: SearchBook(); break;
        case 5: rentABook(); break;
        case 6: ViewRentBooks(); break;       
        case 7: menu(); break;    
    }
}

void Library::AddBook() {
    string category;
    int id;
    string title;
    string Author;
    int addition;
    int Quantity;
    char choiceChar;
    do {
        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t------------------Book Category-------------------" << endl;
        cout << "\t\t\t------------------Book Category-------------------" << endl;

        int choice;
        cout << "Please select the book Category\n1: Computer Science\n2: History \n3: GeoGraphy \n4: Busniess & Law \n5: Fiction \n6: Non-Fiction \n7: Art & Design" << endl;
        if (!(cin >> choice) || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 1; // Default fallback
        }
        
        if (choice == 1) category = "Computer Science";
        else if(choice == 2) category = "History";
        else if(choice == 3) category = "GeoGraphy";
        else if(choice == 4) category = "Busniess & Law";
        else if(choice == 5) category = "Fiction";
        else if(choice == 6) category = "Non-Fiction";
        else category = "Art & Design";

        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t------------------Book Information----------------" << endl;
        cout << "\t\t\t--------------------------------------------------" << endl;

        idCounter++;
        id = idCounter;
        cout << "Category : " << category << endl;
        cout << "Id : " << id << endl;
        cout << "Enter Book Name : ";
        cin.ignore(10000, '\n');
        getline(cin, title);
        cout << "Enter Book author: ";
        
        bool validAuthor = false;
        do {
            getline(cin, Author);
            validAuthor = true;
            if (Author.empty()) {
                validAuthor = false;
                continue;
            }
            for (size_t idx = 0; idx < Author.length(); ++idx) {
                char ch = Author[idx];
                if (!isalpha(ch) && ch != ' ') {
                    validAuthor = false;
                    cout << "\nInvalid input! Author name can only contain alphabets. Please enter again: ";
                    break;
                }
            }
        } while (!validAuthor);

        cout << "Enter book Addition Number: ";
        while (!(cin >> addition) || addition < 0) {
            cout << "\nInvalid input! Please enter a non-negative Addition number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Enter book quantity: ";
        while (!(cin >> Quantity) || Quantity < 0) {
            cout << "\nInvalid input! Please enter a non-negative quantity: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        ofstream outFile(LibraryFile.c_str(), ios::app); 
        Node* newBook = new Node(title, Author, category, id, addition, Quantity); 
        outFile << newBook->title << "," << newBook->Author << "," << newBook->category << "," << newBook->id << "," << newBook->addition << "," << newBook->Quantity << endl;
        outFile.close();

        if (head == NULL) {
            head = newBook;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
         
        TotalBooks++;
        cout << "\nBook added successfully!" << endl;
        cout << "\nDo you want to ADD another book \n PLEASE ANSWER IN 'Y' or 'N': ";
        cin >> choiceChar;
    } while (choiceChar == 'y' || choiceChar == 'Y');
    adminMenu();
}
    
void Library::ModifyBooks() {
    char choiceChar;
    do {
        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t---------------MODIFY BOOKS-----------------------" << endl;
        cout << "\t\t\t--------------------------------------------------" << endl;
        int IdBookModify;
        string category;
        string title;
        string Author;
        
        if (head == NULL) {
            cout << "No books available to modify." << endl;
            adminMenu();
            return;
        }

        cout << "Enter the book Id To Modify the Book: ";
        while (!(cin >> IdBookModify) || IdBookModify < 0) {
            cout << "\nInvalid input! Please enter a valid ID number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        Node* temp = head;
        bool found = false;
        while (temp != NULL) {
            if (temp->id == IdBookModify) {
                cout << "Search Id " << IdBookModify << " Found..." << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
        
        if (found) {
            cin.ignore(10000, '\n');   
            cout << "\nEnter new Category (leave blank to keep old): ";
            getline(cin, category);
            if (!category.empty()) {
                temp->category = category;
            }
            
            cout << "\nEnter new Title (leave blank to keep old): ";
            getline(cin, title);
            if (!title.empty()) {
                temp->title = title;
            }

            cout << "\nEnter new Author (leave blank to keep old): ";
            bool validAuthor = false;
            do {
                getline(cin, Author);
                if (Author.empty()) {
                    validAuthor = true;
                    break;
                }
                validAuthor = true;
                for (size_t idx = 0; idx < Author.length(); ++idx) {
                    char ch = Author[idx];
                    if (!isalpha(ch) && ch != ' ') {
                        validAuthor = false;
                        cout << "\nInvalid input! Author name can only contain alphabets. Please enter again: ";
                        break;
                    }
                }
            } while (!validAuthor);

            if (!Author.empty()) {
                temp->Author = Author;
            }
            
            cout << "\nEnter new Addition Number: ";
            int newAdd;
            if (cin >> newAdd && newAdd >= 0) temp->addition = newAdd;
            cin.clear(); cin.ignore(10000, '\n');

            cout << "\nEnter new quantity: ";
            int newQty;
            if (cin >> newQty && newQty >= 0) temp->Quantity = newQty;
            cin.clear(); cin.ignore(10000, '\n');

            cout << "\nBook Modified successfully!" << endl;    
        } else {
            cout << "This Id does not exist in library." << endl;
        }
        
        cout << "\nDo you want to try again/modify book again (Y/N): ";
        cin >> choiceChar;
    } while (choiceChar == 'y' || choiceChar == 'Y');
    adminMenu();
}
    
void Library::View_All_Books() {
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t---------------View All BOOKS---------------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t----------------Total Books : " << TotalBooks << " -------------" << endl;
    
    Node* temp = head;
    while (temp != NULL) {
        cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title << "\nAuthor: " << temp->Author 
             << "\nCategory: " << temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity << endl;
        temp = temp->next;
    }
    
    cout << "\nPress any key to go back to Menu...";
    getch();
    menu();
}

void Library::SearchByCategory() {
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t-------------SEARCH BOOKS BY CATEGORY-------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    string category;
    int choice;
    cout << "Please select the book Category\n1: Computer Science\n2: History \n3: GeoGraphy \n4: Busniess & Law \n5: Fiction \n6: Non-Fiction \n7: Art & Design" << endl;
    while (!(cin >> choice) || choice < 1 || choice > 7) {
        cout << "Invalid input! Please enter a number between 1 and 7: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
        
    if (choice == 1) category = "Computer Science";
    else if(choice == 2) category = "History";
    else if(choice == 3) category = "GeoGraphy";
    else if(choice == 4) category = "Busniess & Law";
    else if(choice == 5) category = "Fiction";
    else if(choice == 6) category = "Non-Fiction";
    else category = "Art & Design";

    CLS();
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t------------------Book Information----------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;    
        
    if (head == NULL) {
        cout << "There is NO BOOK Available at this Moment" << endl;
    } else {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->category == category) {
                cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title << "\nAuthor: " << temp->Author 
                     << "\nCategory: " << temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity << endl;
            }
            temp = temp->next; 
        }
    }
}

void Library::SearchByID() {
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t--------------SEARCH BOOKS BY ID------------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    int IdBook;
    cout << "Enter the Book Id To SEARCH that Book: ";
    while (!(cin >> IdBook) || IdBook < 0) {
        cout << "\nInvalid input! Please enter a valid number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    if (head == NULL) {
        cout << "There is No Book Available at this Moment" << endl;
    } else {
        Node* temp = head;        
        while (temp != NULL) {
            if (temp->id == IdBook) {
                cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title << "\nAuthor: " << temp->Author 
                     << "\nCategory: " << temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity << endl;
                break;
            }
            temp = temp->next;
        }
    }
}

void Library::SearchByName() {
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t--------------SEARCH BOOKS BY NAME----------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    string BookName;
    cout << "Enter the Title of the book you want to Search: ";
    cin.ignore(10000, '\n');
    getline(cin, BookName);
    if (head == NULL) {
        cout << "There is No Book Available at this Moment" << endl;
    } else {
        Node* temp = head;        
        while (temp != NULL) {
            if (temp->title == BookName) {
                cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title << "\nAuthor: " << temp->Author 
                     << "\nCategory: " << temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity << endl;
            }
            temp = temp->next;
        }
    }
}

void Library::SearchBook() {
    char choiceChar;
    do {
        int choice;
        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t--------------SEARCH BOOKS MENU-------------------" << endl;
        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\tSelect the Method you want to use to Search your Book" << endl;
        cout << "\t1: Search By Category" << endl;
        cout << "\t2: Search By ID" << endl;
        cout << "\t3: Search By Name" << endl;
        cout << "Please choose your Answer from 1-3: ";
        if (!(cin >> choice) || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 1;
        }
        if (choice == 1) SearchByCategory();
        else if (choice == 2) SearchByID();
        else if (choice == 3) SearchByName();
        
        cout << "\nDo you want to SEARCH another book (Y/N): ";
        cin >> choiceChar;
    } while (choiceChar == 'Y' || choiceChar == 'y');
    menu();
}

void Library::handleBookRental(string BookName, int BookId) {
    char check;
    cout << "Do you want to Rent this Book? (Y/N): ";
    cin >> check;

    if (check == 'N' || check == 'n') {
        menu();
    } else if (check == 'Y' || check == 'y') {
        rentForm(BookName, BookId);
    }
}

void Library::rentABook() {
    int Id;
    string BookName;
    bool found = false;
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t--------------------RENT BOOKS--------------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "Enter the ID of the Book : ";
    while (!(cin >> Id) || Id < 0) {
        cout << "\nInvalid input! Please enter a valid non-negative number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    Node* checkBookAvaliable = head;
    while (checkBookAvaliable != NULL) {
        if (checkBookAvaliable->id == Id) {
            if (checkBookAvaliable->Quantity > 0) {
                cout << "\nBook found Successfully..." << endl;
                cout << "\n ID: " << checkBookAvaliable->id << "\nTitle: " << checkBookAvaliable->title << "\nAuthor: " << checkBookAvaliable->Author 
                     << "\nCategory: " << checkBookAvaliable->category << "\nAddition: " << checkBookAvaliable->addition << endl;
                BookName = checkBookAvaliable->title;
                found = true;
                break;   
            } else {
                cout << "This Book is not avaliable..." << endl;
            }
        }
        checkBookAvaliable = checkBookAvaliable->next;    
    }
    if (found) {
        handleBookRental(BookName, Id);
    } else {
        cout << "Book ID not found." << endl;
        menu();
    }
}

void Library::ViewRentBooks() {
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "\t\t\t---------------RENTED BOOKS-----------------------" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    Rent* temp = Head;
    if (Head == NULL) {
        cout << "No book Rented at this Moment..." << endl;
    }
    while (temp != NULL) {
        cout << "\n\n ID: " << temp->Id << "\nName: " << temp->name << "\nContact: " << temp->contact << "\nBook Name: " << temp->BookName 
             << "\nBook Id: " << temp->BookId << "\nDays: " << temp->days << "\nRent_Date: " << temp->rentedDate << "\nDue_Date: " << temp->dueDate << endl;
        temp = temp->next;
    }
    cout << "\nPress any key to return to Admin Menu...";
    getch();
    adminMenu();
}

string currentDate() {
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    stringstream rentedDate;
    rentedDate << (1900 + currentTime->tm_year) << "-"
               << (1 + currentTime->tm_mon) << "-" 
               << currentTime->tm_mday;
    return rentedDate.str();
}

string DueDate(const string& rentedDate, int days) {
    int year, month, day;
    char dash;
    stringstream ss(rentedDate);
    ss >> year >> dash >> month >> dash >> day;

    tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_mday += days;
    mktime(&date);

    stringstream dueDate;
    dueDate << (1900 + date.tm_year) << "-"
            << (1 + date.tm_mon) << "-"   
            << date.tm_mday;
    return dueDate.str();
}

void Library::rentForm(string BookName, int BookId) {
    int Id, days;
    string name, contact;
    cout << "\t\t\t--------------------------------------------------------------------" << endl;
    cout << "\t\t\t---------------------------RENT FORM--------------------------------" << endl;
    cout << "\t\t\t--------------------------------------------------------------------" << endl;
    cout << "\t\t\tId : ";
    while (true) {
        if (cin >> Id) {
            if (Id >= 1123 && Id <= 9989) break;
        }
        cout << "Invalid ID! Please enter a 4-digit number between 1122 and 9990.\n";
        cin.clear(); cin.ignore(10000, '\n');
    }
    cout << "\t\t\tName : ";
    cin.ignore(10000, '\n');
    getline(cin, name);
    cout << "\t\t\tContact : ";
    while (true) {
        cin >> contact;
        if (contact.length() == 11 && contact.substr(0, 2) == "03") break;
        cout << "Invalid Contact! Please enter a valid 11-digit number starting with '03'.\n";
    }
    cout << "\t\t\tHow many days do you want to Rent this Book..." << endl;
    cout << "\t\t\t1. 7 Days" << endl;
    cout << "\t\t\t2. 15 Days" << endl;
    cout << "\t\t\t3. 30 Days" << endl;
    cout << "\t\t\tEnter your choice (1/2/3): ";
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Invalid input! Please enter a number between 1 and 3: ";
        cin.clear(); cin.ignore(10000, '\n');
    }
    if (choice == 1) days = 7;
    else if (choice == 2) days = 15;
    else days = 30;

    string rentedDate = currentDate();
    cout << "\t\t\tCurrent Date : " << rentedDate;
    string dueDate = DueDate(rentedDate, days);
    cout << "\n\t\t\tDue Date : " << dueDate << endl;
    cout << "\t\t\tYou have successfully rented the book..." << endl;
    
    ofstream outfile(RentFile.c_str(), ios::app);
    outfile << name << "," << contact << "," << rentedDate << "," << dueDate << "," << BookName << "," << Id << "," << days << "," << BookId << endl;
    outfile.close();

    Rent* newRent = new Rent(name, contact, rentedDate, dueDate, BookName, Id, days, BookId); 
    if (Head == NULL) {
        Head = newRent;
    } else {
        Rent* temp = Head;
        while (temp->next != NULL) {
            temp = temp->next;
        } 
        temp->next = newRent;
    }
    
    // Decrement the book structure inventory count smoothly
    Node* bTemp = head;
    while (bTemp != NULL) {
        if (bTemp->id == BookId) {
            if (bTemp->Quantity > 0) bTemp->Quantity--;
            break;
        }
        bTemp = bTemp->next;
    }

    cout << "\t\t\tPlease! Return the Book within the " << days << " days" << endl;
    cout << "\nPress any key to continue...";
    getch();
    menu();
}

void Library::menu() {
    while (true) {
        cout << "\t\t\t--------------------------------------------------------------------" << endl;
        cout << "\t\t\t---------------Welcome to Library Management System---------------" << endl;
        cout << "\t\t\t--------------------------------------------------------------------" << endl;
        cout << "\t\t\t1. Admin" << endl;
        cout << "\t\t\t2. User" << endl;
        cout << "\t\t\t3. Exit" << endl;
        cout << "\t\t\tEnter your choice (1/2/3): ";
        int choice;
        if (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid choice! Try again." << endl;
            cin.clear(); cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) {
            string adminPassword;
            string adminusername;
            cout << "\t\tEnter Username: ";
            cin >> adminusername;
            cout << "\t\tEnter password: ";
            cin >> adminPassword;
            if (adminusername == ADMIN_NAME && adminPassword == ADMIN_PASSWORD) {
                adminMenu();
            } else {
                cout << "\nInvalid Username OR Password!" << endl;
            }
        } else if (choice == 2) {
            userMenu();
        } else if (choice == 3) {
            cout << "\n\t\t\tThank you! For Visiting Our Library....\nHope to see you again..." << endl;
            exit(0);
        }
    }
}

int main() {
    Library Lib;
    Lib.LibraryList("LMS");
    Lib.RentList("RentBook");
    Lib.menu();
    return 0;
}