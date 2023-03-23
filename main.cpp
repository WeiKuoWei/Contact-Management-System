
//=================================================================================
// Name         : DS Assignment#3 
// Author       : Wei Kuo
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified: 12-04-2022
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "contact.h"
#include "contactbst.h"
#include "myvector.h"

template class MyVector<Contact>;


//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"1. import <path>      :Import contacts from a CSV file"<<endl
		<<"2. export <path>      :Export contacts to a CSV file"<<endl
		<<"3. add                :Add a new contact"<<endl
		<<"4. edit <key>         :Update a contact's details"<<endl
		<<"5. del <key>          :Delete a contact"<<endl
		<<"6. searchFor <key>    :Search for a contact"<<endl
		<<"7. markfv <key>       :Mark as favourite"<<endl
		<<"8. unmarkfv <key>      :Unmark as favourite"<<endl
		<<"9. printASC           :Print contacts in ascending order"<<endl
		<<"10. printDES           :Print contacts in descending order"<<endl
		<<"11. printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

int main(void)
{
	ContactBST myContactBST; // initializing the binary search tree
	string user_input;
	string command;
	string argument;

	// Contact* temp1 = new Contact("fname", "lname", "email1", "phone1", "city1", "country1", 0);
	// Contact* temp2 = new Contact("fname", "lname", "email2", "phone2", "city2", "country2", 1);
	// myContactBST.insert_helper("fname lname", temp1);
	// myContactBST.insert_helper("fname lname", temp2);

	listCommands();

	while(true)
	{
		try
		{
			cout<<">";
			getline(cin,user_input);

			// parse userinput into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,argument); // the second part, which is the <key>
		
		    if(command =="import" || command == "1") myContactBST.importCSV(myContactBST.getRoot(), argument);
			else if(command == "exit" ){
				fflush(stdin);
				break;
			}
			else if(command =="export" || command == "2") myContactBST.exportCSV(myContactBST.getRoot(), argument);
			else if(command =="add" || command == "3") {
				string fname, lname, email, primaryPhone, city, country, fav; bool isFav;
				cout << "Please enter the details of the contact: " << endl;
				cout << "First Name: "; 	cin >> fname; 
				cout << "Last Name: "; 		cin >> lname;
				cout << "Email: ";			cin >> email;
				cout << "Phone#: ";			cin >> primaryPhone;
				cout << "City: ";			cin >> city;
				cout << "Country: ";		cin >> country;
				
				do{
					cout << endl << "Do you want to add the contact in your favorites [y/n]: "; cin >> fav;
					if(fav == "n" || fav == "y"){
						if(fav == "n") isFav = 0;
						else isFav = 1;
					}
					else cout << "Input incorrect!";
				} while(fav != "n" && fav != "y"); 
				
				// add to contact
				Contact* temp = new Contact(fname, lname, email, primaryPhone, city, country, isFav);
				myContactBST.insert_helper(fname+" "+lname, temp);	  		
			}
			else if(command =="edit" || command == "4") 		myContactBST.update(myContactBST.getRoot(), argument);
			else if(command =="del" || command == "5"){
				// Node* temp = myContactBST.search(myContactBST.getRoot(), argument);
				myContactBST.delHelper(myContactBST.getRoot(), argument);
			}
			else if(command =="searchFor" || command == "6"){
				myContactBST.searchFor(myContactBST.getRoot(), argument);
			}	
			else if(command =="markfv" || command == "7")		myContactBST.markFav(myContactBST.getRoot(), argument);
			else if(command =="unmarkfv" || command == "8") 	myContactBST.unmarkFav(myContactBST.getRoot(), argument);
			else if(command =="printASC" || command == "9"){
				if(myContactBST.getRoot() == nullptr) cout << "There is no contact!" << endl;
				else myContactBST.printASC(myContactBST.getRoot());
			}	
			else if(command =="printDES" || command == "10"){
				if(myContactBST.getRoot() == nullptr) cout << "There is no contact!" << endl;
				else myContactBST.printDES(myContactBST.getRoot());
			}
			else if(command =="printfv" || command == "11"){
				if(myContactBST.getRoot() == nullptr) cout << "There is no contact!" << endl;
				myContactBST.printFav(myContactBST.getRoot());
			}

			else if(command == "help")         					listCommands();
			else cout <<"Invalid command !!!"<<endl; 
			fflush(stdin); // clean up left over input
	
	
		}
		catch (exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}
	return 0;
}

// like binary tree, the characters for names0 should be a reference of sorting