#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;

//Search function that uses a template to apply to all 3 vectors
template<class type>
void search(const vector<type> &b, string x, string t){
	bool counter = 0;
	for (unsigned int i = 0; i < b.size(); i++){
		if (x == b[i].getTitle()){
			cout << left << setw(25) << b[i].getTitle();
			cout << setw(6) << left << b[i].getID();
			cout << setw(6) << left << b[i].getStatus();
			counter = 1;
		}
	}
	if (!counter){
		cout << "Item not found!" << endl;
	}
	cout << endl;
}

//Search function specific to authors
void authorSearch(const vector<book>&b, string x){
	bool counter = 0;
	for (unsigned int i = 0; i < b.size(); i++){
		if (x == b[i].getAuthor()){
			cout << left << setw(25) << b[i].getTitle();
			cout << left << setw(20) << b[i].getAuthor();
			cout << setw(6) << left << b[i].getID();
			cout << setw(6) << left << b[i].getStatus();
			counter = 1;
		}
	}
	if (!counter){
		cout << "Author not found!" << endl;
	}
	cout << endl;
}

//Function that uses template to be a generic checkout for all 3 types of items
template<class type>
void checkout(vector<type>&b, string z, string x, int i){
	char c;

	if (z == b[i].getTitle()){
		if (b[i].getStatus() == 0){
			cout << z << " already checked out!" << endl;
		}
		else{
			cout << "Check out " << x << "(Y/N): ";
			cin >> c;
			if (c == 'Y'){
				b[i].setStatus(0);
				cout << x << " successfully checked out!" << endl;
			}
		}
	}
}

//Generic template function to return items for a 3 types
template<class type>
void returnBook(vector<type>&b, string z, string x){
	char c;
	int flag = 0;
	for (unsigned int i = 0; i < b.size(); i++){
		if (z == b[i].getTitle()){
			flag = 1;
			if (b[i].getStatus() == 1){
				cout << "Item already returned!" << endl;
			}
			else{
				cout << "Return " << x << "(Y/N): ";
				cin >> c;
				if (c == 'Y'){
					b[i].setStatus(1);
					cout << x << " successfully returned!" << endl;
				}
			}
		}
	}
	if (flag == 0){
		cout << "Item doesn't exist!" << endl;
	}
}

int main()
{
	//Declare vectors for storage
	vector<book> bookList;
	vector<journal> journalList;
	vector<magazine> magazineList;
	ifstream input("Input.txt");
	ofstream output("Output.txt");
 
	string title, writer;
	int id, status, volume, issue;

	//Stores the catalog in the vectors
	while (input){

		input >> title;
		input >> writer;
		input >> id >> status;
		book newbook(title, writer, id, status);
		bookList.push_back(newbook);

		for (int i = 1; i < 10; i++){
			getline(input, title, '\t');
			getline(input, writer, '\t');
			input >> id >> status;
			book newbook(title, writer, id, status);
			bookList.push_back(newbook);
		}
		for (int i = 10; i < 16; i++){
			getline(input, title, '\t');
			input >> volume >> id >> status;
			journal newjournal(title, volume, id, status);
			journalList.push_back(newjournal);
		}
		for (int i = 16; i < 22; i++){
			getline(input, title, '\t');
			input >> issue >> id >> status;
			magazine newMagazine(title, issue, id, status);
			magazineList.push_back(newMagazine);
		}
	}

	//Main Menu
	while (2 > 1){
		string choice;
		while (2 > 1){
			cout << "Library Catalog" << endl;
			cout << "===========================" << endl;
			cout << "1. Search Catalog" << endl;
			cout << "2. Check Out" << endl;
			cout << "3. Return" << endl;
			cout << "4. Add a new item" << endl;
			cout << "5. Exit" << endl;
			cout << "Choose an option: ";
			cin >> choice;

			if (choice == "1"){//================================================  Search

				string item, title, choice;
				cout << "\nSearch Catalog" << endl;
				cout << "===========================" << endl;
				cout << "Enter item type (book, magazine, or journal): ";
				cin >> item;
				cin.ignore(256, '\n');

				if (item == "book"){//Book Search
					cout << "Search by title or author: ";
					cin >> choice;
					cin.ignore(256, '\n');

					if (choice == "title"){//Search by title
						cout << "Enter book title" << endl;
						getline(cin, title, '\n');
						title = "\n" + title;
						search(bookList, title, "book");
					}
					else if (choice == "author"){//Search by author
						cout << "Enter author name" << endl;
						getline(cin, title, '\n');
						authorSearch(bookList, title);
					}
					else{//Error message
						cout << "Invalid input!" << endl;
					}

				}
				else if (item == "magazine"){//Magazine Search
					cout << "Enter magazine title" << endl;
					getline(cin, title, '\n');
					title = "\n" + title;
					search(magazineList, title, "magazine");
				}
				else if (item == "journal"){//Journal Search
					cout << "Enter journal title" << endl;
					getline(cin, title, '\n');
					title = "\n" + title;
					search(journalList, title, "journal");
				}

				else{//Error Message
					cout << "Invalid input!" << endl;
				}

				_getch();
			}
			else if (choice == "2"){//==============================================  Check Out

				string z;
				cout << "\nCheck Out" << endl;
				cout << "===========================" << endl;
				cout << "Enter item name" << endl;
				cin.ignore(256, '\n');
				getline(cin, z, '\n');
				z= "\n" + z;
				
				for (unsigned int i = 0; i < bookList.size(); i++){//Book check out
					if (z == bookList[i].getTitle())
						checkout(bookList, z, "Book", i);
				}

				for (unsigned int i = 0; i < journalList.size(); i++){//Journal check out
					if (z == journalList[i].getTitle())
						checkout(journalList, z, "Journal", i);
					
				}
				for (unsigned int i = 0; i < magazineList.size(); i++){//Magazine check out
					if (z == magazineList[i].getTitle())
						checkout(magazineList, z, "Magazine", i);
				}
				_getch();
			}

			else if (choice == "3"){//====================================================  Return
				
				string r;
				cout << "\nReturn" << endl;
				cout << "===========================" << endl;
				cout << "Enter item name" << endl;
				cin.ignore(256, '\n');
				getline(cin, r, '\n');
				r = "\n" + r;

				int flag = 0;
				for (unsigned int i = 0; i < bookList.size(); i++){//Returning books
					if (r == bookList[i].getTitle()){
						flag = 1;
						returnBook(bookList, r, "Book");
					}
				}

				for (unsigned int i = 0; i < journalList.size(); i++){//Returning journals
					if (r == journalList[i].getTitle()){
						flag = 1;
						returnBook(journalList, r, "Journal");
					}
				}
				for (unsigned int i = 0; i < magazineList.size(); i++){//Returning Magazines
					if (r == magazineList[i].getTitle()){
						flag = 1;
						returnBook(magazineList, r, "Magazine");
					}
				}
				if (flag == 0){
					cout << "Item doesn't exist!" << endl;
				}

			}
			else if (choice == "4"){//==============================================  Add Item

				string type;
				string newTitle, newAuthor;
				bool flag = 1;
				int newID, newStatus, newVolume, newIssue;
				cout << "\nAdd new item" << endl;
				cout << "===========================" << endl;
				cout << "Type of item (book, magazine, journal): ";
				cin >> type;

				if (type == "book"){//Adding a new book
					cout << "Enter book title" << endl;
					cin.ignore(256, '\n');
					getline(cin, newTitle, '\n');
					newTitle = "\n" + newTitle;

					for (int i = 0; i < bookList.size(); i++){//Book already exists!
						if (newTitle == bookList[i].getTitle()){
							cout << "Book already exists!" << endl;
							flag = 0;
						}
					}

					if (flag){
						cout << "Enter author name" << endl;//If new books, adds book.
						getline(cin, newAuthor, '\n');

						newID = 1000 + bookList.size();

						book newBook(newTitle, newAuthor, newID, 1);
						bookList.push_back(newBook);
					}
				}


				else if (type == "magazine"){//Add a new magazine
					cout << "Enter magazine title" << endl;
					cin.ignore(256, '\n');
					getline(cin, newTitle, '\n');
					newTitle = "\n" + newTitle;

					for (int i = 0; i < magazineList.size(); i++){
						if (newTitle == magazineList[i].getTitle()){
							cout << "Magazine already exists!" << endl;
							flag = 0;
						}
					}

					if (flag){
						cout << "Enter issue number" << endl;
						cin >> newIssue;

						newID = 3000 + magazineList.size();

						magazine newMag(newTitle, newIssue, newID, 1);
						magazineList.push_back(newMag);
					}
				}
				else if (type == "journal"){
					cout << "Enter journal title" << endl;
					cin.ignore(256, '\n');
					getline(cin, newTitle, '\n');
					newTitle = "\n" + newTitle;

					for (int i = 0; i < journalList.size(); i++){
						if (newTitle == journalList[i].getTitle()){
							cout << "Journal already exists!" << endl;
							flag = 0;
						}
					}

					if (flag){
						cout << "Enter volume number" << endl;
						cin >> newVolume;

						newID = 2000 + journalList.size();

						journal newJ(newTitle, newVolume, newID, 1);
						journalList.push_back(newJ);
					}
				}
				else{
					cout << "Invalid type!" << endl;
				}
				
				cout << endl;
			}
			else if (choice == "5"){//======================================================  Exit Program
				cout << "Press any key to exit." << endl;
				break;
			}
			else{//===========================================================  Invalid Input
				system("CLS");
				cout << "Invalid Input!" << endl;
				system("pause");
				system("CLS");
			}

			cout << endl;
		}
		break;
	}

	//Print out catalog to text file
	output << "================================================================" << endl;
	output << left << setw(30) << "Title" << setw(20) << "Author" << setw(8) << "ID" << setw(1) << "Status" << endl;
	output << "================================================================";
	for (unsigned int i = 1; i < bookList.size(); i++){
		output << left << setw(31) << bookList[i].getTitle();
		output << setw(20) << left << bookList[i].getAuthor();
		output << setw(8) << left << bookList[i].getID();
		output << setw(1) << left << bookList[i].getStatus();
	}

	output << "\n\n\n================================================================" << endl;
	output << left << setw(30) << "Title" << setw(20) << "Volume" << setw(8) << "ID" << setw(1) << "Status" << endl;
	output << "================================================================";
	for (unsigned int i = 0; i < journalList.size(); i++){
		output << left << setw(31) << journalList[i].getTitle();
		output << setw(20) << left << journalList[i].getJournal();
		output << setw(8) << left << journalList[i].getID();
		output << setw(1) << left << journalList[i].getStatus();
	}

	output << "\n\n\n================================================================" << endl;
	output << left << setw(30) << "Title" << setw(20) << "Issue" << setw(8) << "ID" << setw(1) << "Status" << endl;
	output << "================================================================";
	for (unsigned int i = 0; i < magazineList.size(); i++){
		output << left << setw(31) << magazineList[i].getTitle();
		output << setw(20) << left << magazineList[i].getMag();
		output << setw(8) << left << magazineList[i].getID();
		output << setw(1) << left << magazineList[i].getStatus();
	}
	output << endl << endl;
	cout << endl;
	_getch();
	return 0;
}
