#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Number {
	char* number = (char*)malloc(10);
	char* type = (char*)malloc(10);
    Number * next;
};

struct Person{
	char* name = (char*)malloc(10);
    Person * next;
    Person * back;
    Number * phonenum = NULL, *tailNum;
};

struct Liste{
    Person * head = NULL;
    void addPerson(char*);   // +
    void addNumber(char*,char*,char*);   // +
    void removePerson(char*);    // +
    void removeNumber();    // +
    void updatePerson();
    void updateNumber();    //+
    void search();          // +
    void list();
    void finish();// +
};

void Liste::addPerson(char* name){
    
    Person * tail = NULL;
    Person * traverse = head;
    Person * newNode = new Person;
    newNode->next = NULL;
    newNode->back = NULL;
    newNode->phonenum = NULL;
    strcpy(newNode->name,name);
    if (head==NULL) {
        
        head = newNode;
        tail = head;
        return;
        
    }
    
    if (strcmp(newNode->name,head->name) < 0) {
        
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        return;
    }
    
    while (traverse && (strcmp(newNode->name,traverse->name) > 0)) {
        tail = traverse;
        traverse = traverse->next;
    }
    
    if (traverse) {
        
        newNode->next = traverse;
        newNode->back = tail;
        tail->next = newNode;
        traverse->back = newNode;
        
    } else {
        
        tail->next = newNode;
        newNode->back = tail;
    }
}

void Liste::addNumber(char* name,char* number,char* type){
    
    Person * traverse = head;
    Number * headNum;
    Number * eklenecek;
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
          
        traverse = traverse->next;
    	}
    	eklenecek = new Number;
        strcpy(eklenecek->number, number);
        strcpy(eklenecek->type, type);
        eklenecek->next = NULL;
        
        if (traverse->phonenum == NULL) {
            
            traverse->phonenum = eklenecek;
            traverse->tailNum = traverse->phonenum;
            
        } else {
            
            traverse->tailNum->next = eklenecek;
            traverse->tailNum = traverse->tailNum->next;
        }
}
void Liste::removePerson(char* name)
{
    Person * traverse = head;
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
    } else {
        
        Number * p = traverse->phonenum;
        Number * silinecek;
        
        while (p) {
            
            silinecek = p;
            p = p->next;
            delete silinecek;
        }
        
        if (traverse == head) {
            head = traverse->next;
            delete traverse;
            return;
        
        }
        
        if (traverse->next == NULL) {
            traverse->back->next = traverse->next;
            delete traverse;
            return;
        }
        
        
        traverse->back->next = traverse->next;
        traverse->next->back = traverse->back;
        delete traverse;
    }
}

void Liste::list(){
    
    Person * traverse = head;
    Number * p;
    
    while (traverse) {
        
        cout << endl << traverse->name;
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << "    " << p->type << " " << p->number;
            p=p->next;
        }
        
        cout << endl;
        
        traverse = traverse->next;
    }
}


void Liste::removeNumber(){
    
    Person * traverse = head;
    int i=0;
    int index;
    Number * silinecek, *p;
	char* name = (char*)malloc(10);
    
    cout << endl << "Enter the name: ";
    cin >> name;
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    
    if (!traverse) {
    
        cout << endl << "Could not be found";
    
    } else {
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << ++i << " " << p->type << "" << p->number;
            p = p->next;
        }
        
        cout << endl;
        
        cout << endl << "Enter the index: ";
        cin >> index;
        
        p = traverse->phonenum;
        
        Number * son = NULL;
        
        for (int a = 1; a < index; a++) {
            son = p;
            p = p->next;
        }
        
        silinecek = p;
        
        if (silinecek == traverse->phonenum) {
            traverse->phonenum = silinecek->next;
            delete silinecek;
        } else {
            son->next = silinecek->next;
            delete silinecek;
        }
        
        cout << endl << "Removed";
    }
}

void Liste::updatePerson()
{
	int i = 1;
	char* name = (char*)malloc(10);
	char* new_name = (char*)malloc(10);
    cout<<"Enter the old name:";
    cin>>name;
    Person * traverse=head;
    while (traverse) 
	{    
        if (strcmp(name,traverse->name)==0){break;}
		i++;
        traverse = traverse->next;
    }
    if (traverse==NULL) {
        
        cout << endl << "Could not be found";
        return;     
    } 
    else
	{
		cout << i << "." << traverse->name << endl;
		cout << "It is found." << endl;
		cout<<"Enter the new name:";
		cin>>new_name;
		Number* p=traverse->phonenum;
		addPerson(new_name);	
		while(p)
		{
			addNumber(new_name,p->number,p->type);
			p=p->next;
		}
		removePerson(name);
	}
}
void Liste::updateNumber(){
    
    Person * traverse = head;
    Number * p;
    int i=0;
    int index;
	int x = 3;
	char* name = (char*)malloc(x);
    
    cout << endl << "Enter the name: ";
    cin >> name;
	if(strlen(name) > 3)
	{
		x *= 2;
		realloc(name, x);
	}
    while (traverse) {
        
        if (strcmp(name,traverse->name)==0){
            break;
        }
        
        traverse = traverse->next;
    }
    if (!traverse) {
        
        cout << endl << "Could not be found";
        
    } else {
        
        p = traverse->phonenum;
        
        while (p) {
            cout << endl << ++i << " " << p->type << "" << p->number;
            p = p->next;
        }
        
        cout << endl;
        
        cout << endl << "Enter the index: ";
        cin >> index;
        
        p = traverse->phonenum;
        
        for (int a = 1; a < index; a++) {
            p = p->next;
        }
        
        cout << endl << "Enter the new number: ";
        cin >> p->number;
		cout << endl << "Enter the new number type: ";
		cin >> p->type;
        cout << endl << "Updated";
    }
}

void Liste::search(){
	char* arama = (char*)malloc(10);
    cout << endl << "Enter the name";
    cin >> arama;
    Number * p;
    
    Person * traverse = head;
    
    while (traverse && !(strncmp(traverse->name,arama,strlen(arama)) > 0) ) {
        
        if (strncmp(arama,traverse->name,strlen(arama)) == 0) {
            
            cout << endl << traverse->name;
            p = traverse->phonenum;
            
            while (p) {
                cout << endl << " " << p->type << "" << p->number;
                p=p->next;
            }
            
            cout << endl;
            
        }
        
        traverse = traverse->next;
    }
}

void Liste::finish(){

    Person * traverse = head, * perSil;
    Number * p, *silinecek;
    
    while (traverse) {
        
        perSil = traverse;
        p = traverse->phonenum;
        traverse = traverse->next;
        
        while (p) {
            
            silinecek = p;
            p = p->next;
            delete silinecek;
        }
        
        delete perSil;
        
    }
    
    cout << endl << "Tum kayitlar silindi - Programdan cikiliyor...";
}

typedef Liste Phonebook;
Phonebook linkedList;
void menuYazdir();
int main(){
	char* name = (char*)malloc(10);
	char* name2 = (char*)malloc(10);
	char* name3 = (char*)malloc(10);
	char* number = (char*)malloc(10);
	char* type = (char*)malloc(10);
    char secim;
    int index;
    while (1) {
        Person * traverse = linkedList.head;  	
        menuYazdir();
        cin >> secim;
        switch (secim) {
            case 'A': case 'a':
            	cout<<"Enter the name:";
            	cin>>name;
                linkedList.addPerson(name);
                break;
            
            case 'N': case 'n':
            	cout<<"Enter the name:";
            	cin>>name2;
            	while (traverse) 
				{
        			if (strcmp(name2,traverse->name)==0){break;}
        			traverse = traverse->next;
    			}
    			if (!traverse) {cout << endl << "Could not be found";}
            	else
            	{
            		cout<<"Enter the number:";
            		cin>>number;
            		cout<<"Enter the number type:";
            		cin>>type;
            	    linkedList.addNumber(name2,number,type);
            	}
            	break;
            case 'R': case 'r':
            	cout<<"Enter the name:";
            	cin>>name3;
                linkedList.removePerson(name3);
                break;
            
            case 'V': case 'v':
                linkedList.removeNumber();
                break;
                
            case 'U': case 'u':
                linkedList.updatePerson();
                break;
            
            case 'P': case 'p':
                linkedList.updateNumber();
                break;
            
            case 'S': case 's':
                linkedList.search();
                break;
                
            case 'L': case 'l':
                linkedList.list();
                break;
            
            case 'E': case 'e':
                linkedList.finish();
                exit(EXIT_SUCCESS);
                break;
            
            default:
                cout << endl << "Invalid choice";
                break;
        }
    }
    return 0;
}

void menuYazdir(){
    cout << endl << endl << "Phone Book" << endl;
    cout << "A: Add Person" << endl;
    cout << "N: Add Number" << endl;
    cout << "R: Remove Person" << endl;
    cout << "V: Remove Number" << endl;
    cout << "U: Update Person" << endl;
    cout << "P: Update Number" << endl;
    cout << "S: Search" << endl;
    cout << "L: List" << endl;
    cout << "E: Exit" << endl;
    cout << endl << "Enter your option: ";
}
