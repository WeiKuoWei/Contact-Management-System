// #include<string>
// #include<fstream>
// #include<ostream>
// #include<exception>
// #include<sstream>
// #include<cstdlib>
// #include<ctime>
// #include<iomanip>
// #include<algorithm>
// #include<cctype>
// #include<typeinfo>

#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include "contactbst.h"
#include "myvector.h"

using namespace std;

ContactBST::ContactBST(){
    this->root = nullptr;
}
ContactBST::~ContactBST(){
    // //Keep removing the root of the tree until it becomes empty
	// while(root)
	// 	root=del(root,root->key);
}
Node* ContactBST::getRoot(){
    return this->root;
}
Node* ContactBST::add(Node* ptr, string key, Contact* data){
    if(ptr == nullptr){
        // instantiate a vector, push back the contact data, then put into a node
        // MyVector<Contact>* newVector = new MyVector<Contact>;
        Node* newNode = new Node(key, new MyVector<Contact>());
        newNode->contactVector->push_back(*data);
        return newNode;
    }
    // comparing the values of string
    if(key == ptr->key){
        // add to vector
        ptr->getData()->push_back(*data); 
    }
    else if(key < ptr->key){
        ptr->left = add(ptr->left, key, data); 
    } 
    else if(key > ptr->key){
        ptr->right = add(ptr->right, key, data);
    }
    return ptr;
}

Node* ContactBST::del(Node* ptr, string key){
    // if key doesn't exist
    if(search(ptr, key) == nullptr){
        cout << "Key does not exist!" << endl;
        return nullptr;
    }
    // check vector size
    int size = search(ptr, key)->getData()->v_size;
    Node* newNode = search(ptr, key);
    // size == 1, remove the node from the BST
    if(size == 1){
        // node has no child
        if (newNode->left == nullptr && newNode->right == nullptr){
            delete newNode;
            return nullptr;
        }
        // node with only one child or no child
        else if (newNode->left == nullptr) {
            Node* temp = newNode->right;
            newNode = nullptr;
            return temp;
        }
        else if (newNode->right == nullptr) {
            Node* temp = newNode->left;
            newNode = nullptr;
            return temp;
        }
        else{
            // node with two children
            Node* temp = findMin(newNode->right);
            newNode->key = temp->key;
            newNode->right = del(newNode->right, temp->key);
        }
        return newNode;
    }

    // size != 1, remove the name from the vector
    if(size > 1){
        cout << size << " records found: " << endl;
        MyVector<Contact>* temp = search(ptr, key)->getData();
        for(int i = 0; i < size; i++){
            cout << i+1 << ". "  
                << temp->at(i).fname << ", "
                << temp->at(i).lname << ", "
                << temp->at(i).email << ", "
                << temp->at(i).primaryPhone << ", "
                << temp->at(i).city << ", "
                << temp->at(i).country << endl;
        }
        int option;
        string parameter_string;
        
        do{
            cout << "Please select the record you want to delete: " << endl;
            string temp;
            cin >> temp;
            stringstream input(temp);
            input >> option;
            if(option == 0 || option < 0 || option >size ) cout << "Invalid command!" << endl;
        } while(option == 0);
        search(ptr, key)->getData()->erase(option - 1);
    }
    return ptr;
}

Node* ContactBST::delHelper(Node* ptr, string key){
    del(ptr, key);
}

Node* ContactBST::update(Node* ptr, string key){
    // if key doesn't exist
    if(search(ptr, key) == nullptr){
        cout << "Key does not exist!" << endl;
        return nullptr;
    }

    // // check vector size
    int size = search(ptr, key)->getData()->v_size;

    // search the tree with key
    cout << size << " record found: " << endl;
    MyVector<Contact>* temp = search(ptr, key)->getData();
    for(int i = 0; i < size; i++){
        cout << i+1 << ". " 
            << temp->at(i).fname << ", "
            << temp->at(i).lname << ", "
            << temp->at(i).email << ", "
            << temp->at(i).primaryPhone << ", "
            << temp->at(i).city << ", "
            << temp->at(i).country << ", "
            << temp->at(i).isFav << endl;
    }
    // input the option that will be changed
    int contact, option;
    do{
        cout << "Please select the record you want to edit: ";
        string temp;
        cin >> temp;
        stringstream input(temp);
        input >> contact;
        if(contact == 0 || contact < 0 || contact > size) cout << "Invalid command!" << endl;
    } while(contact == 0 || contact < 0 || contact > size);
    contact--;
    string YesNo = "y";
    do{
        do{
            cout << "Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) city, or 6) Country: " << endl;
            string temp;
            cin >> temp;
            stringstream input(temp);
            input >> option;
            if(option == 0 || option < 0 || option > 6) cout << "Invalid command!" << endl;
        } while(option == 0 );
 
        // case1: update name then will need to remove and add a new node
        string input, field[6] = {"First Name", "Last Name", "Email", "Phone#", "city", "Country"};
        cout << "Please enter the new " << field[option-1] << ": "; cin >> input;
        if(option == 1 || option == 2){
            if(option == 1) temp->at(contact).fname = input;
            else temp->at(contact).lname = input;
            // update the new key
            string newKey = temp->at(contact).fname + " " + temp->at(contact).lname;
            // add the new node with new key
            add(ptr, newKey, temp[contact].getData()); // # not sure if this is correct
            
            // remove the node
            // case1: more than one contact in the vector
            search(ptr, key)->getData()->erase(contact);
            // case2: only one contact in the vector
            del(ptr, key);
        }
        // case2: other attributes
        else{
            if(option == 3) temp->at(contact).email = input;
            if(option == 4) temp->at(contact).primaryPhone = input;
            if(option == 5){
                 temp->at(contact).city = input;
                 // cout << "city changed! " << input << endl;
            }
            if(option == 6){
                 temp->at(contact).country = input;
                 // cout << "country changed! " << input << endl;
            }
        }

        // ask the user if adding another field is needed
        do{
            cout << "Do you want to add another field? [y/n]: "; cin >> YesNo;
            if(YesNo != "n" && YesNo != "y") cout << "Invalid commnand!" << endl;
        } while(YesNo != "n" && YesNo != "y");
    } while(YesNo != "n");
    
    fflush(stdin); // clean up left over input
    cout << "The contact record has successfully been updated!" << endl;
}

Node* ContactBST::search(Node* ptr,string key){
    if(ptr != nullptr){
        if(ptr->key > key) return search(ptr->left, key);
        else if(ptr->key < key) return search(ptr->right, key);
        if(ptr->key == key) return ptr;
    } 
    return nullptr;
}

Node* ContactBST::searchHelper(Node* &ptr, string key){
        if(ptr != nullptr){
        if(ptr->key > key) return search(ptr->left, key);
        else if(ptr->key < key) return search(ptr->right, key);
        if(ptr->key == key){
            ptr = nullptr;
            return ptr;
        }
    } 
    return nullptr;
}


void ContactBST::searchFor(Node* ptr, string key){
    // check if the contact exist
    if(search(ptr,key) == nullptr){
        cout << "Contact doesn't exist!" << endl; 
        return;
    }
    int size = search(ptr, key)->getData()->v_size;
    int counter = 1; 
    MyVector<Contact>* temp = search(ptr, key)->getData();

    cout << size << " records found: " << endl;
    for(int i = 0; i < size; i++){
        cout << counter << ". "
            << "First name: " << temp->at(i).fname << " "
            << "Last name:" << temp->at(i).lname << endl
            << "Email: " << temp->at(i).email << endl
            << "Phone#: " << temp->at(i).primaryPhone << endl
            << "City: " << temp->at(i).city << endl
            << "Country: " << temp->at(i).country << endl;
        counter++;
    }
}
Node* ContactBST::findMin(Node *ptr){
    if(ptr->left == nullptr) return ptr;
    return findMin(ptr->left);
}
bool ContactBST::markFav(Node* ptr, string key){
    // if BST is empty
    if(this->getRoot() == nullptr){
        cout << "THere is no contact!" << endl;
        return 0;
    }
    // if key doesn't exist
    if(search(ptr, key) == nullptr){
        cout << "Key does not exist!" << endl;
        return 0;
    }
    // search the tree with the key
    // update the content in within the key
    int size = search(ptr, key)->getData()->v_size, counter = 1;
    cout << size << " record found: " << endl;
    MyVector<Contact>* temp = search(ptr, key)->getData();
    for(int i = 0; i < size; i++){
        cout << i+1 << ". "
            << temp->at(i).fname << ", "
            << temp->at(i).lname << ", "
            << temp->at(i).email << ", "
            << temp->at(i).primaryPhone << ", "
            << temp->at(i).city << ", "
            << temp->at(i).country << ", "
            << temp->at(i).isFav << endl;
    }
    int option;

    fflush(stdin); // clean up left over input
    
    do{
        cout << "Please select the record you want to mark as favorite: " << endl;
        string temp;
        cin >> temp;
        stringstream input(temp);
        input >> option;
        if(option == 0 || option < 0 || option > size ) cout << "Invalid command!" << endl;
    } while(option == 0);

    fflush(stdin); // clean up left over input

    temp->at(option-1).isFav = 1;
    cout << key << " [" << temp->at(option-1).email << "] has successfully been marked as favorite." << endl;
}
bool ContactBST::unmarkFav(Node* ptr, string key){
    // if BST is empty
    if(this->getRoot() == nullptr){
        cout << "THere is no contact!" << endl;
        return 0;
    }
    // if key doesn't exist
    if(search(ptr, key) == nullptr){
        cout << "Key does not exist!" << endl;
        return 0;
    }
    // search the tree with the key
    // update the content in within the key
    int size = search(ptr, key)->getData()->v_size;
    cout << size << " record found: " << endl;
    MyVector<Contact>* temp = search(ptr, key)->getData();
    for(int i = 0; i < size; i++){
        cout << i+1 << ". "
            << temp->at(i).fname << ", "
            << temp->at(i).lname << ", "
            << temp->at(i).email << ", "
            << temp->at(i).primaryPhone << ", "
            << temp->at(i).city << ", "
            << temp->at(i).country << ", "
            << temp->at(i).isFav << endl;

    }
    int option;

    fflush(stdin); // clean up left over input

    do{
        cout << "Please select the record you want to unmark as favorite: " << endl;
        string temp;
        cin >> temp;
        stringstream input(temp);
        input >> option;
        if(option == 0 || option < 0 || option > size ) cout << "Invalid command!" << endl;
    } while(option == 0);
    
    fflush(stdin); // clean up left over input

    temp->at(option-1).isFav = 0;
    cout << key << " [" << temp->at(option-1).email << "] has successfully been unmarked as favorite." << endl;
}
void ContactBST::printASC(Node* ptr){
    if(ptr == nullptr) return;
    printASC(ptr->left);
    // cout the data here
    int size = ptr->getData()->v_size;
    // MyVector<Contact>* temp = ptr->getData();
    for(int i = 0; i < size; i++){
        cout << ptr->contactVector->at(i).fname << " "
            << ptr->contactVector->at(i).lname << " "
            << ptr->contactVector->at(i).email << " "
            << ptr->contactVector->at(i).primaryPhone << " "
            << ptr->contactVector->at(i).city << " "
            << ptr->contactVector->at(i).country << " "
            << ptr->contactVector->at(i).isFav << endl;
    }
    printASC(ptr->right);
}
void ContactBST::printDES(Node* ptr){
    if(ptr == nullptr) return;
    printDES(ptr->right);
    // cout the data here
    int size = ptr->getData()->v_size;
    MyVector<Contact>* temp = ptr->getData();
    for(int i = 0; i < size; i++){
        cout << temp->at(i).fname << " "
            << temp->at(i).lname << " "
            << temp->at(i).email << " "
            << temp->at(i).primaryPhone << " "
            << temp->at(i).city << " "
            << temp->at(i).country << " "
            << temp->at(i).isFav << endl;
    }
    printDES(ptr->left);
}
void ContactBST::printFav(Node* ptr){
    // # DONE # Not checked
    if(ptr == nullptr) return;
    printFav(ptr->right);
    // cout the data here
    int size = ptr->getData()->v_size;
    MyVector<Contact>* temp = ptr->getData();
    for(int i = 0; i < size; i++){
        if(temp->at(i).isFav == 1){
            cout << temp->at(i).fname << " "
                << temp->at(i).lname << " "
                << temp->at(i).email << " "
                << temp->at(i).primaryPhone << " "
                << temp->at(i).country << " "
                << temp->at(i).isFav << endl;
        }
    }
    printFav(ptr->left);
}
int ContactBST::importCSV(Node* ptr, string path){
    ifstream fileContact(path);
    //read txt file
    string line;
    string x[7];
    while(getline(fileContact, line)){
        int num = 0;
        stringstream linestream(line);
        string value;
        while(getline(linestream, value, ',')){
            x[num] = value; num++;
        } 
        bool isFav = (x[6] == " 1"  ? 1 : 0);
        // loading attributes
        Contact* temp = new Contact(x[0], x[1], x[2], x[3], x[4], x[5], isFav); // cout << x[0]+x[1];
        insert_helper(x[0]+x[1], temp);
        
    }
}

int ContactBST::exportCSV(Node* ptr, string path){
    MyVector<Contact>* vector = new MyVector<Contact>; 
    // save contacts
    ofstream out1;
    out1.open(path);
    MyVector<Contact>* newVector = export_helper(ptr, vector);
    int size = newVector->v_size;
    // out1 the data here
    for(int i = 0; i < size; i++){
        out1<< newVector->at(i).fname << ", "
            << newVector->at(i).lname << ", "
            << newVector->at(i).email << ", "
            << newVector->at(i).primaryPhone << ", "
            << newVector->at(i).country << ", "
            << newVector->at(i).country << ", "
            << newVector->at(i).isFav << endl;
    }
    out1.close();
}

MyVector<Contact>* ContactBST::export_helper(Node* ptr, MyVector<Contact>* vector){
        if(ptr == nullptr) return vector;
        export_helper(ptr->left, vector);
        int size = ptr->getData()->v_size;
        MyVector<Contact>* temp = ptr->getData();
        for(int i = 0; i < size; i++){
            vector->push_back(temp->at(i)); // # Might be an issue here
        }
        export_helper(ptr->right, vector);
}

void ContactBST::insert_helper(string key, Contact* data){
    root = add(root, key, data); 
}
void ContactBST::remove_helper(string key){
    root = del(root, key);
}
void ContactBST::printTreeHelper(string* A, bool* B, Node* ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}