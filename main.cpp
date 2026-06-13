#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include<ctime>

using namespace std;

const string ADMIN_PASSWORD = "pass";
const string ADMIN_NAME="ahmad";
const string LibraryFile="LMS.txt";
const string RentFile="RentBook.txt";

class Node{
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
        title="";
        Author="";
        Quantity=0;
        category="";
        addition=0;
        next=NULL;
    }
};
class Rent{
	public: 
	int Id,days,BookId;
	string name,contact,rentedDate,dueDate,BookName;
	Rent* next;
	Rent(string name,string contact,string rentedDate,string dueDate,string BookName,int Id,int days,int BookId){
		this->Id=Id;
		this->name=name;
		this->contact=contact;
		this->days=days;
		this->rentedDate=rentedDate;
		this->dueDate=dueDate;
		this->BookName=BookName;
		this->BookId=BookId;
		this->next=NULL;
		}
	Rent(){
		Id=1;
		name="";
		contact="";
		days =0;
		rentedDate="";
		dueDate="";
		BookName="";
		BookId=0;
		
	}
};

class Library {
    Node* head;
    Rent* Head;
public:
    int idCounter;
    int TotalBooks;

    Library(){
        head=NULL;
        Head=NULL;
        TotalBooks=0;
        idCounter=0;
    }

void LibraryList(const string& LibraryFile) {
        ifstream inFile("LMS.txt");
        if(!inFile){
            cout<<"Error opening file!" << endl;
            return;
        }
        string line;
        while(getline(inFile,line)){
            stringstream ss(line);
            string title,Author,category;
            int id,addition,Quantity;

            getline(ss,title,',');
            getline(ss,Author,',');
            getline(ss,category,',');

            ss>>id;
            ss.ignore(); 
            ss>>addition;
            ss.ignore(); 
            ss>>Quantity;

            Node* newNode = new Node(title,Author,category,id,addition,Quantity);
            if(head==NULL){
                head=newNode;
            }else{
                Node* temp=head;
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=newNode;
            }
        }
        inFile.close();
        IdCounter();
}

void RentList(const string& RentFile){
        ifstream inFile("RentBook.txt");
        if(!inFile){
            cout<<"Error opening file!" << endl;
            return;
        }
        string line;
        while(getline(inFile,line)){
            stringstream ss(line);
            string name,contact,rentedDate,dueDate,BookName;
            int Id,days,BookId;

            getline(ss,name,',');
            getline(ss,contact,',');
            getline(ss,rentedDate,',');
            getline(ss,dueDate,',');
			getline(ss,BookName,',');
            ss>>Id;
            ss.ignore(); 
            ss>>days;
            ss.ignore();
            ss>>BookId;
            ss.ignore();
			
			 

            Rent* rentNode=new Rent(name,contact,rentedDate,dueDate,BookName,Id,days,BookId);
            if(Head==NULL){
                Head=rentNode;
            }else{
                Rent* temp=Head;
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=rentNode;
            }
        }
        inFile.close();
}



void IdCounter(){
    	Node* temp=head;
    	while(temp->next!=NULL){
    		TotalBooks++;
    		temp=temp->next;
		}
		idCounter=temp->id;
}

void userMenu(){
	
        cout << "\t\t\t------------------------------------------------------" << endl;
        cout << "\t\t\t--------------- Welcome to User's Menu ----------------" << endl;
        cout << "\t\t\t------------------------------------------------------" << endl;
        cout << "\t\t1. View All Books" << endl;
        cout << "\t\t2. Search Books" << endl;
        cout << "\t\t3. Rent Book" << endl;
        cout << "\t\t4. Back to Main Menu" << endl;
        cout << "\t\tEnter your choice : ";

        int choice;
        while (!(cin>>choice) || choice<1 || choice>4){
            cout << "\nInvalid input! Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        switch (choice){
            case 1:
                View_All_Books();
                break;
            case 2:
                SearchBook();
                break;
            case 3:
                rentABook();
                break;
            case 4:
                menu();
                break;
			}
}

void adminMenu() {
        
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
        while (!(cin>>choice) || choice<1 || choice>7) {
            cout << "\nInvalid input! Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                AddBook();
                break;
            case 2:
                ModifyBooks();
                break;
            case 3:
                View_All_Books();
                break;
            case 4:
                SearchBook();
                break;
            case 5:
                rentABook();
                break;
			case 6:
                ViewRentBooks();
                break;    	    
            case 7:
                menu();
                break;    
        }
}

 
void AddBook() {
    	string category;
    	int id;
        string title;
        string Author;
        int addition;
        int Quantity;
        char i;
        do{
        	
        	
		cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t------------------Book Category-------------------" << endl;
        cout << "\t\t\t--------------------------------------------------" << endl;

        int choice;
        cout << "Please select the book Category\n1: Computer Science\n2: History \n3: GeoGraphy \n4: Busniess & Law \n5: Fiction \n6: Non-Fiction \n7: Art & Design" << endl;
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid input! Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        if (choice == 1) category = "Computer Science";
        else if(choice==2)category = "History";
        else if(choice==3)category = "GeoGraphy";
        else if(choice==4)category = "Busniess & Law";
        else if(choice==5)category = "Fiction";
        else if(choice==6)category = "Non-Fiction";
        else category="Art & Design";

        
        cout << "\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t------------------Book Information----------------" << endl;
        cout << "\t\t\t--------------------------------------------------" << endl;

        idCounter++;
        id=idCounter;
        cout<<"Category : "<<category<<endl;
        cout<<"Id : "<<id<< endl;
        cout<<"Enter Book Name : ";
        cin.ignore();
        getline(cin, title);
        cout<<"\nEnter Book author: ";
        bool validAuthor=false;
        do{
            getline(cin, Author);
            validAuthor=true;
            for(size_t i=0;i<Author.length();++i) {
                char ch = Author[i];
                if(!isalpha(ch)&&ch!=' ') {
                    validAuthor = false;
                    cout<<"\nInvalid input! Author name can only contain alphabets. Please enter again: ";
                    break;
                }
            }
        }while(!validAuthor);

        cout<<"\nEnter book Addition Number: ";
        while(!(cin >> addition) || addition < 0){
            cout << "\nInvalid input! Please enter a non-negative Addition number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "\nEnter book quantity: ";
        while (!(cin >> Quantity) || Quantity < 0) {
            cout << "\nInvalid input! Please enter a non-negative quantity: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        ofstream outFile(LibraryFile.c_str(), ios::app); 
        
        Node* newBook = new Node(title, Author, category,id,addition, Quantity); 
  	     outFile<<newBook->title<<","<<newBook->Author<<","<<newBook->category<<","<<newBook->id<<","<<newBook->addition<<","<<newBook->Quantity<<endl;
  	     Node*temp=head;
  	     while(temp->next!=NULL){
  	     	temp=temp->next;
		   }
		   temp->next=newBook;
	     
  	     TotalBooks++;
         cout << "\nBook added successfully!" << endl;
         outFile.close();
		 cout<<"\nDo you want to ADD another book \n PLEASE ANSWER IN 'Y' or 'N': ";
         cin>>i;
        do{if(i=='n' || i=='N' ){
    	adminMenu();
		break;
	    }else if(i=='Y' || i=='y'){	
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		 cout<<"\nPlease enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));
    }while(i=='y' || i=='Y');
     system("cls");
    }
    
    
void ModifyBooks(){
    		
    		char i;
    	    do{
			cout<<"\t\t\t--------------------------------------------------"<<endl;
        	cout<<"\t\t\t---------------MODIFY BOOKS-----------------------"<<endl;
    	    cout<<"\t\t\t--------------------------------------------------"<<endl;
    	    int IdBookModify;
    	    string category;
    	    string title;
      		string Author;
        	int addition;       	
        	int Quantity;
    	    Node* temp=head;
    	    bool found=false;
    	    cout<<"Enter the book Id To Modify the Book: ";
    	    while(!(cin >> IdBookModify) || IdBookModify < 0) {
            cout << "\nInvalid input! Please enter a non-negative Addition number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    	    while(temp->next != NULL){
    	      if(temp->id==IdBookModify){
    	      	cout<<"Search Id "<<IdBookModify<<" Found..."<<endl;
    	      	found=true;
    	      	break;
			  }
			  	temp=temp->next;
			}
			
			if(found){
			  cin.ignore(); //clear bufer	
			cout<<"\nEnter new Category (leave blank to keep old)";
			getline(cin, category);
            if(category.empty()){
               category=temp->category;
             }
             temp->category=category;
           	
			cout<<"\nEnter new Title (leave blank to keep old): ";
			getline(cin, title);
            if(title.empty()){
               title=temp->title;
             }
              temp->title=title;
           

            cout<<"\nEnter new Author(leave blank to keep old): ";
            bool validAuthor=false;
            do{
              getline(cin,Author);

            // Validate author name (only alphabets allowed)
              validAuthor=true;
              for (size_t i=0;i<Author.length();++i){
              char ch =Author[i];
              if(!isalpha(ch)){
              validAuthor = false;
              cout<<"\nInvalid input! Author name can only contain alphabets. Please enter again: ";
              break;
              }
			 }
            }while(!validAuthor);
            if(Author.empty()){
            Author=temp->Author;
            }
			temp->Author=Author;
            

            cout<<"\nEnter new Addition Number: ";
            while(!(cin>>temp->addition) || temp->addition<0){
            cout<<"\nInvalid input! Please enter a non-negative Addition: ";
            cin.clear();
            cin.ignore(10000, '\n');
            }

            cout<<"\nEnter new quantity: ";
            while(!(cin>>temp->Quantity) || temp->Quantity < 0){
            cout<<"\nInvalid input! Please enter a non-negative quantity: ";
            cin.clear();
            cin.ignore(10000, '\n');
            }
         cout << "\nBook Modified successfully!" << endl;    
            
		}else{
			cout<<"This Id do not exist in library "<<endl;
		}
		
		 cout<<"\nDo you want to try again/modify book again \n PLEASE ANSWER IN 'Y' or 'N': ";
         cin>>i;
        do{if(i=='n' || i=='N' ){
    	adminMenu();
		break;
	    }else if(i=='Y' || i=='y'){	
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		 cout<<"\nPlease enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));
    }while(i=='y' || i=='Y');
     system("cls"); 	    
	}
	
void View_All_Books(){
		
		char i;
    	    do{
			cout<<"\t\t\t--------------------------------------------------"<<endl;
        	cout<<"\t\t\t---------------View All BOOKS---------------------"<<endl;
    	    cout<<"\t\t\t--------------------------------------------------"<<endl;
    	    Node* temp=head;
    	    cout<< "\t\t\t----------------Total Books : "<<TotalBooks<<" -------------"<<endl;
    	    
    	    while(temp!=NULL){
    	    cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title<< "\nAuthor: " << temp->Author 
            << "\nCategory: "<<temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity<< endl;
         
               temp=temp->next;
			}
    	
		cout<<"Do you want to Refresh the Books";
        cin>>i;
        do{if(i=='n' || i=='N' ){
    	menu();
		break;
	    }else if(i=='Y' || i=='y'){	
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		 cout<<"\nPlease enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));
    }while(i=='y' || i=='Y');
     system("cls");

}

void SearchByCategory(){
	
	cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t-------------SEARCH BOOKS BY CATEGORY-------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;
    string category;
    int choice;
    cout << "Please select the book Category\n1: Computer Science\n2: History \n3: GeoGraphy \n4: Busniess & Law \n5: Fiction \n6: Non-Fiction \n7: Art & Design" << endl;
    while(!(cin >> choice) || choice < 1 || choice > 7) {
        cout << "Invalid input! Please enter a number between 1 and 7: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
        
        if (choice == 1) category = "Computer Science";
        else if(choice==2)category = "History";
        else if(choice==3)category = "GeoGraphy";
        else if(choice==4)category = "Busniess & Law";
        else if(choice==5)category = "Fiction";
        else if(choice==6)category = "Non-Fiction";
        else category="Art & Design";
    system("cls");
    cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t------------------Book Information----------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;    
        
    if(head==NULL){
    	cout<<"There is NO BOOK Available a this Moment"<<endl;
	}
	else{
		Node*temp=head;
		while(temp!=NULL){
		   if(temp->category==category){
		   	cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title<< "\nAuthor: " << temp->Author 
            << "Category: "<<temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity<< endl;
         
		   }
		   temp=temp->next;	
		}
		return;
	}
	
}

void SearchByID(){
	
	cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t--------------SEARCH BOOKS BY ID------------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;
    int IdBook;
    cout<<"Enter the Book Id To SEARCH that Book: ";
    	    while(!(cin >> IdBook) || IdBook<0) {
            cout << "\nInvalid input! Please enter a non-negative Addition number: ";
            cin.clear();
            cin.ignore(10000, '\n');
    }
	if(head==NULL){
    	cout<<"There is No Book Available at this Moment"<<endl;
	}
	else{
        Node* temp=head;		
    	while(temp!= NULL){
    	if(temp->id==IdBook){
    	cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title<< "\nAuthor: " << temp->Author 
            << "Category: "<<temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity<< endl;
         

             break;
		     }
		 temp=temp->next;
		}
		return;
	}
}

void SearchByName(){
	
	cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t--------------SEARCH BOOKS BY NAME----------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;
    string BookName;
    cout<<"Enter the Title of the book you want to Search: ";
    cin.ignore();
    getline(cin,BookName);
    if(head==NULL){
    	cout<<"There is No Book Available at this Moment"<<endl;
	}
	else{
        Node* temp=head;		
    	while(temp!= NULL){
    	if(temp->title==BookName){
    	cout << "\n\n ID: " << temp->id << "\nTitle: " << temp->title<< "\nAuthor: " << temp->Author 
            << "Category: "<<temp->category << "\nAddition: " << temp->addition << "\nQuantity: " << temp->Quantity<< endl;
         
		     }
		 temp=temp->next;
		}
		return;
    }
}

void SearchBook(){
	char i;
	do{
	system("cls");
	int choice;
	cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t--------------SEARCH BOOKS MENU-------------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;
	cout<<"\tSelect the Method you want to use to Search your Book"<<endl;
	cout<<"\t1: Search By Category"<<endl;
	cout<<"\t2: Search By ID"<<endl;
	cout<<"\t3: Search By Name"<<endl;
	cout<<"Please choose your Answer from 1-3"<<endl;
	while(!(cin >> choice) || choice < 1 || choice > 3) {
        cout<<"\nInvalid input! Please enter the number : ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    if(choice==1) {
	   SearchByCategory();
	}
    else if(choice==2){
	   SearchByID();
    }
    else if(choice==3){
    	SearchByName();
	}
	cout<<"\nDo you want to SEARCH another book ";
	cout<<"\n PRESS 'Y'  TO SEARCH AGAIN or 'N' TO GO TO MENU: ";
    cin>>i;
    do{
	if(i=='n' || i=='N' ){
    	system("cls");
    	menu();
    	break;
	    }else if(i=='Y' || i=='y'){
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		cout<<"Please enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));
    }while(i=='Y' || i=='y');
}

void handleBookRental(string BookName,int BookId) {
    char check;
    cout << "Do you want to Rent this Book? (Y/N): ";
    cin >> check;

    while (check != 'Y' && check != 'y' && check != 'N' && check != 'n') {
        cout << "Invalid input. Please enter 'Y' or 'N': ";
        cin >> check;
    }

    if (check == 'N' || check == 'n') {
        char searchAgain;
        cout << "\nSorry! This book is not available at this moment...";
        cout << "\nDo you want to SEARCH another book? (Y/N): ";
        cin >> searchAgain;

        while (searchAgain != 'Y' && searchAgain != 'y' && searchAgain != 'N' && searchAgain != 'n') {
            cout << "Invalid input. Please enter 'Y' or 'N': ";
            cin >> searchAgain;
        }

        if (searchAgain == 'N' || searchAgain == 'n') {
            system("cls");
            menu();
        } else {
            rentABook();
        }
    } else if (check == 'Y' || check == 'y') {
        rentForm(BookName,BookId);
    }
}



void rentABook(){
  	
	int Id;
	string BookName;
  	boolean found=false;
  	cout<<"\t\t\t--------------------------------------------------"<<endl;
    cout<<"\t\t\t--------------------RENT BOOKS--------------------"<<endl;
    cout<<"\t\t\t--------------------------------------------------"<<endl;
  	cout<<"Enter the ID of the Book : ";
  	while(!(cin >> Id) || Id<0){
            cout << "\nInvalid input! Please enter a non-negative number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
	Node* checkBookAvaliable=head;
	while(checkBookAvaliable!=NULL){
	  	    if(checkBookAvaliable->id==Id){
	  	    	    if(checkBookAvaliable->Quantity>0){
	  	    		cout<<"\nBook found Successfully..."<<endl;
	  	    		cout<< "\n ID: " << checkBookAvaliable->id << "\nTitle: " << checkBookAvaliable->title<< "\nAuthor: " << checkBookAvaliable->Author 
                        << "\nCategory: "<<checkBookAvaliable->category << "\nAddition: " << checkBookAvaliable->addition<< endl;
                        BookName=checkBookAvaliable->title;
         			found=true;
         			break;   
		    }else{
		    	cout<<"This Book is not avaliable..."<<endl;
			}
		}
		   checkBookAvaliable=checkBookAvaliable->next;	
        }
    if(found){
    	handleBookRental(BookName,Id);
    }
}

void ViewRentBooks(){
	
		char i;
    	    do{
			cout<<"\t\t\t--------------------------------------------------"<<endl;
        	cout<<"\t\t\t---------------RENTED BOOKS-----------------------"<<endl;
    	    cout<<"\t\t\t--------------------------------------------------"<<endl;
    	    Rent* temp=Head;
    	    if(Head==NULL){
    	    	cout<<"No book Rented at this Moment..."<<endl;
			}
    	   	while(temp!=NULL){
    	    cout << "\n\n ID: " << temp->Id << "\nName: " << temp->name<< "\nContact: " << temp->contact << "\nBook Name: " << temp->BookName 
            << "\nBook Id: " << temp->BookId << "\nDays: "<<temp->days << "\nRent_Date: " << temp->rentedDate << "\nDue_Date: " << temp->dueDate<< endl;
         
               temp=temp->next;
			}
		 
		cout<<"Do you want to Refresh the Books(Y/N) or (y/n) : ";
        cin>>i;
        do{if(i=='n' || i=='N' ){
    	adminMenu();
		break;
	    }else if(i=='Y' || i=='y'){	
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		 cout<<"\nPlease enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));
    }while(i=='y' || i=='Y');
     system("cls");

}

string currentDate(){
    time_t now=time(0);                // Get the current time
    tm *currentTime=localtime(&now);   // Convert to local time format
    stringstream rentedDate;
    rentedDate<<(1900 + currentTime->tm_year) << "-"  // Year
                <<(1 + currentTime->tm_mon) << "-"      // Month
                <<currentTime->tm_mday;                // Day

    return rentedDate.str();
}
string DueDate(const string& rentedDate,int days) {
    int year,month,day;
    char dash;  // For parsing the '-' in the date format
    stringstream ss(rentedDate);
    ss >>year>>dash>>month>>dash>>day;

    // Create a tm structure for the Borrowed Date
    tm date={};
    date.tm_year = year-1900;  // tm_year is years since 1900
    date.tm_mon = month-1;     // tm_mon is months since January (0-11)
    date.tm_mday = day;          // Day of the month

    // Add the given days
    date.tm_mday += days;
    mktime(&date);

    // Create the Due Date string
    stringstream dueDate;
    dueDate<<(1900 + date.tm_year)<< "-"  // Year
           <<(1 + date.tm_mon)<< "-"      // Month
           <<date.tm_mday;                 // Day

    return dueDate.str();
}

void rentForm(string BookName,int BookId){
  	
  		int Id,days;
  		string name,contact;
        system("color f0");
        cout<<"\t\t\t--------------------------------------------------------------------" << endl;
        cout<<"\t\t\t---------------------------RENT FORM--------------------------------" << endl;
        cout<<"\t\t\t--------------------------------------------------------------------" << endl;
        cout<<"\t\t\tId : ";
        while(true){
        cin>>Id;
        if(Id>=1123 && Id<=9989){
            break; // Valid input
        }else{
            cout << "Invalid ID! Please enter a 4-digit number between 1122 and 9990.\n";
             }
    	}
        cout<<"\t\t\tName : ";
        cin.ignore();
        getline(cin, name);
        cout<<"\t\t\tContact : ";
        while(true){
        cin >> contact;
        if ((contact.length() == 11 && contact.substr(0, 2) == "03") ||
            (contact.length() == 13 && contact.substr(0, 5) == "+92 3")) {
            // Ensure all characters after the prefix are digits
            bool valid = true;
            for (size_t i = (contact[0] == '+' ? 5 : 2); i < contact.length(); ++i) {
                if (!isdigit(contact[i])) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                break; // Valid input
            }
        }
        cout << "Invalid Contact! Please enter a valid 11-digit number starting with '03' or '+92 3'.\n";
    }
        cout<<"\t\t\tHow many do days you want to Rent this Book..."<<endl;
        cout<<"\t\t\t1. 7 Days" << endl;
        cout<<"\t\t\t2. 15 Days" << endl;
        cout<<"\t\t\t3. 30 Days" << endl;
        cout<<"\t\t\tEnter your choice (1/2/3): ";
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input! Please enter a number between 1 and 3: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if(choice==1){
        	days=7;
		}else if(choice==2){
			days=15;
		}else{
			days=30;
		}
		string rentedDate =currentDate();
		cout<<"\t\t\tCurrent Date : "<<rentedDate;
        string dueDate =DueDate(rentedDate, days);
        cout<<"\n\t\t\tDue Date : "<<dueDate<<endl;
        cout<<"\t\t\tYou have successfully rented the book..."<<endl;
        
        ofstream outfile(RentFile.c_str(), ios::app);
        
		Rent* newRent = new Rent(name,contact,rentedDate,dueDate,BookName,Id,days,BookId); 
		
  	    outfile<<newRent->name<<","<<newRent->contact<<","<<newRent->rentedDate<<","<<newRent->dueDate
  	    <<","<<newRent->BookName<<","<<newRent->Id<<","<<newRent->days<<","<<newRent->BookId<<endl;
  	    Rent* temp=Head;
  	    if(temp==NULL){
  	    	temp=newRent;
		  }else{
		        while(temp->next!=NULL){
  	         	temp=temp->next;
		    } 
		    temp->next=newRent;
    }
		cout<<"\t\t\t---------------------------------------------------------------" << endl;
        cout<<"\t\t\t---------------------------NOTE--------------------------------" << endl;
        cout<<"\t\t\tPlease! Return the Book within the "<<days<<" days"<<endl;
		cout<<"\t\t\tYou will get fined & your card will be banned & You will not be able to Enter the Library again"<<endl;
		
		char i;
		cout<<"\t\t\tDo you want to Rent another Book..."<<endl;
		cout<<"\t\t\tPlease Answer in Y/N or y/n : ";
    	cin>>i;
		do{if(i=='n' || i=='N' ){
    	menu();
		break;
	    }else if(i=='Y' || i=='y'){	
	    rentABook();
	  	break;
	    }
	    else if((i!='N' || i!='n') && (i!='Y' || i!='y')){
		 cout<<"\n\t\t\tPlease enter 'Y' or 'N' to answer..."<<endl;
		i=getch();
	    }
	    }while(((i!='N' || i!='n') && (i!='Y' || i!='y')));		
	    
		
}
 

  
void menu(){
  	
  	while(true) {
        system("color f0");
        cout<<"\t\t\t--------------------------------------------------------------------" << endl;
        cout<<"\t\t\t---------------Welcome to Library Management System---------------" << endl;
        cout<<"\t\t\t--------------------------------------------------------------------" << endl;
        cout<<"\t\t\t1. Admin" << endl;
        cout<<"\t\t\t2. User" << endl;
        cout<<"\t\t\t3. Exit" << endl;
        cout<<"\t\t\tEnter your choice (1/2/3): ";
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input! Please enter a number between 1 and 3: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        switch (choice) {
            case 1: {
                string adminPassword;
                string adminusername;
                char i;
                do {
                    system("cls");
                    cout << "\t\t\t--------------------------------------------------------------------" << endl;
                    cout << "\t\t\t-----------------------Welcome to LOGIN PANEL-----------------------" << endl;
                    cout << "\t\t\t--------------------------------------------------------------------" << endl;
                    cout << "\t\tEnter Username: ";
                    cin.ignore(10000, '\n');
                    cin >> adminusername;
                    cout << "\t\tEnter password: ";
                    cin.ignore(10000, '\n');
                    cin >> adminPassword;
                    if (adminusername == ADMIN_NAME && adminPassword == ADMIN_PASSWORD) {
                        adminMenu();
                    } else {
                        cout << "\nInvalid Username OR Password!" << endl;
                        cout << "You do want to try again Press 'Y' or 'y' to try again or 'N' or 'n' to return to Main menu: ";
                        cin >> i;
                        do {
                            if (i == 'n' || i == 'N') {
                                break;
                            } else if (i == 'Y' || i == 'y') {
                                system("cls");
                                break;
                            } else if ((i != 'N' || i != 'n') && (i != 'Y' || i != 'y')) {
                                cout << "\nPlease enter 'Y' or 'N' to answer..." << endl;
                                i = getch();
                            }
                        } while (((i != 'N' || i != 'n') && (i != 'Y' || i != 'y')));
                    }
                } while (i == 'y' || i == 'Y');
                
                break;
            }
            case 2:
                userMenu();
                break;
            case 3:
                cout << "\n\t\t\tThank you! For Visiting Our Library....\nHope to see you again..." << endl;
				return;
        }
    }
  }
		
};

int main() {
    Library Lib;
    Lib.LibraryList("LMS");
    Lib.RentList("RentBook");
    Lib.menu();

    return 0;
}

