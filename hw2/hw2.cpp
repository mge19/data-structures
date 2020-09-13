/*BLG2333E-Data Structures and Laboratory
* Homework-2
* Student Name: Mehmet Gencay Ertürk
* Student ID : 150130118
* Date: 01/11/2017
*/ 
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#define LENGTH 15
using namespace std;
struct studentInfo
{
	char* name=new char[LENGTH];
	char* surname=new char[LENGTH];
	char* email=new char[2*LENGTH+12];
	studentInfo* prev;
	studentInfo* next;
};
struct surnameMap
{
	char* surname=new char[LENGTH];
	studentInfo* head;
	surnameMap* next;
};
void edit_characters(char* string)
{
	for(int i=0;i<LENGTH;i++)
	{
		if(i==0 && 96<string[0]<123){string[0]=toupper(string[0]);}
		else if(i>0 && 64<string[i]<91){string[i]=tolower(string[i]);}
	}
}
void list(surnameMap* head)
{
	if(head==NULL) {return;}
	surnameMap* traverse=head;
	studentInfo* traverse2;
	do
	{
		cout<<traverse->surname<<endl;
		traverse2=traverse->head;
		while(traverse2!=NULL)
		{
			cout<<traverse2->name<<"\t"<<traverse2->surname<<endl;
			traverse2=traverse2->next;
		}
		traverse=traverse->next;
	}while(traverse!=head);
}
int nodecount;
void print_menu()
{
	cout<<"e-mail Address Program"<<endl;
	cout<<"1) Create"<<endl;
	cout<<"2) Insert All"<<endl;
	cout<<"3) Insert New Record"<<endl;
	cout<<"4) Delete Student"<<endl;
	cout<<"5) Delete Surname Node"<<endl;
	cout<<"6) Update"<<endl;
	cout<<"7) Write to File"<<endl<<endl;
	cout<<"Enter a choice:";
}
struct list_operations
{
	surnameMap* head;
	void alphabetical_order();
	void createList();
	void insertAll();
	void insertNewRecord();
	bool deleteStudent(char*,char*);
	void deleteStudentNodes(studentInfo*);
	bool deleteSurnameNode(char*);
	void updateList();
	void create_emails();
	void writeToFile();
};
void list_operations::alphabetical_order()
{
	surnameMap* temp=head,*temp2;
	studentInfo* traverse;
	char* string=new char[LENGTH];
	char** string2=new char* [nodecount];
	char** string3=new char* [nodecount];
	for(int n=0;n<nodecount;n++){string2[n]=new char[LENGTH];string3[n]=new char[LENGTH];}
	while(temp->next!=head){
		temp2=temp->next;
		while(temp2!=head){
			if(strcmp(temp->surname,temp2->surname)>0){
				strcpy(string,temp->surname);
				strcpy(temp->surname,temp2->surname);
				strcpy(temp2->surname,string);
			}
			temp2=temp2->next;
		}
		temp=temp->next;
	}
	temp=head;
	int i=0;
	do{
		traverse=temp->head;
		while(traverse!=NULL)
		{
			strcpy(*(string2+i),traverse->name);
			strcpy(*(string3+i),traverse->surname);
			traverse=traverse->next;
			i++;
		}
		temp->head=NULL;
		temp=temp->next;
	}while(temp!=head);
	for(int j=0;j<nodecount;j++)
	{
		studentInfo* newNode=new studentInfo;
		newNode->next=NULL;
		strcpy(newNode->name,*(string2+j));
		strcpy(newNode->surname,*(string3+j));
		temp=head;
		while(strcmp(temp->surname,newNode->surname)!=0){temp=temp->next;}
		if(temp->head==NULL){newNode->prev=newNode->next=NULL;temp->head=newNode;}
		else{
			traverse=temp->head;
			while(traverse->next!=NULL){traverse=traverse->next;}
			traverse->next=newNode;
			newNode->prev=traverse;
		}
	}
	delete string;
	for(int n=0;n<nodecount;n++){ delete string2[n]; delete string3[n];}
}
void list_operations::createList(){head=NULL;nodecount=0;cout<<"The list has been created successfully."<<endl;}
void list_operations::insertAll()
{
	FILE* input=fopen("dataset_wOutTurkishChars.txt","r+");
	if(!input) {cout<<"Error opening file."<<endl;}
	char* name=new char[LENGTH];
	char* surname=new char[LENGTH];
	while(!feof(input))
	{
		fscanf(input,"%s\t%s\n",name,surname);
		edit_characters(name);
		edit_characters(surname);
		surnameMap* newNode=new surnameMap;
		strcpy(newNode->surname,surname);
		newNode->next=NULL;
		newNode->head=new studentInfo;
		strcpy(newNode->head->name,name);
		strcpy(newNode->head->surname,surname);	
		newNode->head->next=NULL;		
		if(head==NULL){head=newNode;newNode->next=head;nodecount=1;}
		else
		{
			surnameMap* temp=head;
			while(temp->next!=head && strcmp(newNode->surname,temp->surname)!=0) {temp=temp->next;}
			if(temp->next==head && strcmp(newNode->surname,temp->surname)!=0){temp->next=newNode;newNode->next=head;nodecount++;}
			else{
				if(temp->head==NULL){newNode->head->prev=newNode->head->next=NULL;temp->head=newNode->head;nodecount++;}
				else
				{
					studentInfo* traverse=temp->head;
					while(traverse->next!=NULL){traverse=traverse->next;}
					traverse->next=newNode->head;
					newNode->head->prev=traverse;
					nodecount++;
				}
			}
		}
	}
	alphabetical_order();
	cout<<"Records from input file have been inserted successfully."<<endl;
	fclose(input);
	delete name;
	delete surname;
}
void list_operations::insertNewRecord()
{
	char* name=new char[LENGTH];
	char* surname=new char[LENGTH];
	cout<<"Enter new record's name:";
	cin>>name;
	cout<<"Enter new record's surname:";
	cin>>surname;
	edit_characters(name);
	edit_characters(surname);
	surnameMap* newNode=new surnameMap;
	strcpy(newNode->surname,surname);
	newNode->next=NULL;
	newNode->head=new studentInfo;
	strcpy(newNode->head->name,name);
	strcpy(newNode->head->surname,surname);	
	newNode->head->next=NULL;		
	if(head==NULL){head=newNode;newNode->next=head;nodecount=1;}
	else
	{
		surnameMap* temp=head;
		while(temp->next!=head && strcmp(newNode->surname,temp->surname)!=0) {temp=temp->next;}
		if(temp->next==head && strcmp(newNode->surname,temp->surname)!=0){temp->next=newNode;newNode->next=head;nodecount++;}
		else{
			if(temp->head==NULL){newNode->head->prev=newNode->head->next=NULL;temp->head=newNode->head;nodecount++;}
			else
			{
				studentInfo* traverse=temp->head;
				while(traverse->next!=NULL){traverse=traverse->next;}
				traverse->next=newNode->head;
				newNode->head->prev=traverse;
				nodecount++;
			}
		}
	}
	alphabetical_order();
	delete name;
	delete surname;
}
void list_operations::create_emails()
{
	int counter1=1,counter2;
	surnameMap* temp=head;
	studentInfo* temp2;
	studentInfo* traverse;
	do
	{
		temp2=temp->head;
		if(64<temp2->surname[0]<91) temp2->surname[0]=tolower(temp2->surname[0]);
		if(64<temp2->name[0]<91) temp2->name[0]=tolower(temp2->name[0]);
		strcpy(temp2->email,temp2->surname);
		if(96<temp2->surname[0]<123) temp2->surname[0]=toupper(temp2->surname[0]);
		if(96<temp2->name[0]<123) temp2->name[0]=toupper(temp2->name[0]);		
		strcat(temp2->email,"@itu.edu.tr"); 
		temp2=temp2->next;
		while(temp2)
		{
			if(64<temp2->surname[0]<91) temp2->surname[0]=tolower(temp2->surname[0]);
			strcpy(temp2->email,temp2->surname);
			traverse=temp->head->next;
			while(traverse!=temp2)
			{
				if(counter1<=strlen(temp2->name))
				{
					if(memcmp(traverse->name,temp2->name,counter1)==0) counter1++;
				}
				else counter1++;
				traverse=traverse->next;
			}
			if(64<temp2->name[0]<91) temp2->name[0]=tolower(temp2->name[0]);
			if(counter1>strlen(temp2->name))
			{
				counter2=counter1-strlen(temp2->name)+1;
				char* buf=new char[3];
				strcat(temp2->email,temp2->name);
				sprintf(buf,"%d",counter2);
				strcat(temp2->email,buf); 
				delete buf;
			}
			else 
			{strncat(temp2->email,temp2->name,counter1);}
			if(96<temp2->surname[0]<123) temp2->surname[0]=toupper(temp2->surname[0]);
			if(96<temp2->name[0]<123) temp2->name[0]=toupper(temp2->name[0]);
			strcat(temp2->email,"@itu.edu.tr"); 
			counter1=1;
			temp2=temp2->next;
		}
		temp=temp->next;
	}while(temp!=head);
}
bool list_operations::deleteStudent(char* name,char* surname)
{
	if(head==NULL){cout<<"List is empty."<<endl;return false;}
	surnameMap* temp=head;
	studentInfo* traverse;
	bool x,found=false;
	while(temp->next!=head && strcmp(temp->surname,surname)!=0){temp=temp->next;}
	if(temp->next==head && strcmp(temp->surname,surname)!=0){cout<<"Given record is not found."<<endl;return false;}
	else
	{
		traverse=temp->head;
		while(traverse!=NULL)
		{
			if(strcmp(traverse->name,name)==0)
			{
				found=true;
				if(traverse->prev!=NULL){traverse->prev->next=traverse->next;}
				if(traverse->next!=NULL){traverse->next->prev=traverse->prev;}
				if(temp->head==traverse){temp->head=traverse->next;}
				delete traverse;
				nodecount--;
				break;
			}
			traverse=traverse->next;
		}
		if(!found){cout<<"Given record is not found."<<endl;return false;}		
		if(temp->head==NULL) x=deleteSurnameNode(surname);
	}		
	return true;
}
void list_operations::deleteStudentNodes(studentInfo* head)
{
	studentInfo* traverse=head;
	while(traverse){
		if(deleteStudent(traverse->name,traverse->surname)) traverse=traverse->next;
	}
}
bool list_operations::deleteSurnameNode(char* input_surname)
{
	if(head==NULL){cout<<"List is empty."<<endl;return false;}
	surnameMap* temp=head,*tail;
	if(strcmp(input_surname,head->surname)==0 && temp->next==head)
	{
		deleteStudentNodes(temp->head);
		if(temp->next==head){temp->next=NULL;head=NULL;}
	}
	else if(strcmp(input_surname,head->surname)==0 && temp->next!=head){
		deleteStudentNodes(temp->head);
		if(temp->next!=head){
			while(temp->next!=head) {temp=temp->next;}
			temp->next=temp->next->next;
			head=temp->next;
		}	
	}
	else{
		temp=temp->next;
		while(temp->next!=head && strcmp(input_surname,temp->surname)!=0){tail=temp;temp=temp->next;}
		if(temp->next==head && strcmp(input_surname,temp->surname)!=0){cout<<"Given input surname is not found."<<endl; return false;} 
		else{deleteStudentNodes(temp->head); tail->next=temp->next;}
	}
	return true;
}
void list_operations::updateList()
{
	char* name=new char[LENGTH];
	char* surname=new char[LENGTH];
	cout<<"Enter name of record which you want to update:";
	cin>>name;
	cout<<"Enter surname of record which you want to update:";
	cin>>surname;
	edit_characters(name);
	edit_characters(surname);
	if(deleteStudent(name,surname)) {insertNewRecord(); list(head); cout<<"The record has been updated successfully"<<endl;}
	delete name;
	delete surname;
}
void list_operations::writeToFile()
{
	FILE* output=fopen("emailList.txt","a+");
	if(!output){cout<<"File not found."<<endl;return;}
	create_emails();
	surnameMap* traverse=head;
	studentInfo* traverse2;
	do{
		traverse2=traverse->head;
		while(traverse2!=NULL)
		{
			fprintf(output,"%s\t%s\t%s\n",traverse2->name,traverse2->surname,traverse2->email);
			traverse2=traverse2->next;
		}
		traverse=traverse->next;
	}while(traverse!=head);	
	cout<<"Writing completed."<<endl;
	fclose(output);
}
list_operations new_list;
bool operations(int choice)
{
	bool exit=false;
	char* name=new char[LENGTH];
	char* surname=new char[LENGTH];
	char* input_surname=new char[LENGTH];
	switch(choice)
	{
		case 1:
			new_list.createList();
			break;
		case 2:
			new_list.insertAll();
			list(new_list.head);
			break;
		case 3:
			new_list.insertNewRecord();
			list(new_list.head);
			cout<<"The record has been inserted successfully."<<endl;
			break;
		case 4:
			cout<<"Enter name of record which you want to delete:";
			cin>>name;
			cout<<"Enter surname of record which you want to delete:";
			cin>>surname;				
			edit_characters(name);
			edit_characters(surname);
			if(new_list.deleteStudent(name,surname)) {list(new_list.head);cout<<"The record has been deleted sucessfully."<<endl;}
			break;
		case 5:
			cout<<"Enter the surname you want to delete:";
			cin>>input_surname;
			edit_characters(input_surname);
			if(new_list.deleteSurnameNode(input_surname)) cout<<"Given input surname has been deleted successfully."<<endl;
			list(new_list.head);
			break;
		case 6:
			new_list.updateList();
			break;
		case 7:
			new_list.writeToFile();
			exit=true;
			break;	
		default:
			cout<<"Invalid choice."<<endl;
			break;
	}
	delete name;
	delete surname;
	delete input_surname;
	return exit;
}
int main()
{
	bool exit=false;
	int choice;
	while(!exit)
	{
		print_menu();
		cin>>choice;
		exit=operations(choice);
	}
	delete new_list.head;
	system("PAUSE");
	return EXIT_SUCCESS;
}
