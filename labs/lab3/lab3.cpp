#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;
int kayitsayisi=0;
struct Phone_Record{
	char name[30];
	char surname[15];
};
void print_menu()
{
	cout << "Phone Book Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Search Record" << endl;
	cout << "A: Add Record" << endl;
	cout << "U: Update Record" << endl;
	cout << "D: Delete Record" << endl;
	cout << "L: List Records" << endl;
	cout << "E: Exit" << endl;
	cout << "Enter an option {A, E, G, S, C, L} : ";
}
void alphabetic_order(Phone_Record* k)
{
	Phone_Record temp;
	for(int i=0;i<kayitsayisi-1;i++)
	{
		for(int j=i+1;j<kayitsayisi;j++)
		{
			if(strcmp((k+i)->name,(k+j)->name)>0)
			{
				strcpy(temp.name,k[j].name);
				strcpy(temp.surname,k[j].surname);
				strcpy(k[j].name,k[i].name);
				strcpy(k[j].surname,k[i].surname);
				strcpy(k[i].name,temp.name);
				strcpy(k[i].surname,temp.surname);	
			}
		}
	}
}
Phone_Record* realloc(Phone_Record* k,int maxkayit)
{
    Phone_Record* temp=new Phone_Record[maxkayit];
    for(int i=0;i<maxkayit;i++)
    {
      strcpy(temp[i].name,k[i].name);
      strcpy(temp[i].surname,k[i].surname);
    }
    delete k;
    k=new Phone_Record[2*maxkayit];
    for(int i=0;i<maxkayit;i++)
    {
      strcpy(k[i].name,temp[i].name);
      strcpy(k[i].surname,temp[i].surname);
    }
    maxkayit*=2;
    return k;
}
void list(Phone_Record* k)
{
	for(int i=0;i<kayitsayisi;i++)
	{
		cout<<i+1<<"."<<(k+i)->name<<"\t"<<(k+i)->surname<<endl;
	}
}
void search(Phone_Record* k)
{
	char a[10];
	cout<<"Enter the string you want to search(Press * to list all):";
	cin>>a;
	bool j=0;
	if(strcmp(a,"*")==0)
	{
		list(k);	
		j=true;
	}
	else
	{	 
		for(int i=0;i<kayitsayisi;i++)
		{
			if(strncmp((k+i)->name,a,strlen(a))==0)
			{
				cout<<i+1<<"."<<(k+i)->name<<"\t"<<(k+i)->surname<<endl;
				j=true;
			}
		}
	}
	if(!j) cout<<"Record not found."<<endl;
}
void add(Phone_Record* k)
{
	cout<<"Enter the name of new record:";
	cin>>(k+kayitsayisi)->name;
	cout<<"Enter the phone number of new record:";
	cin>>(k+kayitsayisi)->surname;	
	kayitsayisi++;	
	if(kayitsayisi>1) alphabetic_order(k);
}
void update(Phone_Record* k)
{
	Phone_Record temp;
	int kayitno;
	cout<<"Enter the index of record you want to update:";
	cin>>kayitno;
	cout<<"Enter the name of updated record:";
	cin>>temp.name;
	cout<<"Enter the phone number of updated record:";
	cin>>temp.surname;
	strcpy((k+kayitno-1)->name,temp.name);
	strcpy((k+kayitno-1)->surname,temp.surname);
	alphabetic_order(k);
}
void delete_record(Phone_Record* k)
{
	int kayitno;
	cout<<"Enter the index of record you want to delete:";
	cin>>kayitno;
	for(int i=kayitno-1;i<kayitsayisi;i++)
	{
		strcpy((k+i)->name,(k+i+1)->name);
		strcpy((k+i)->surname,(k+i+1)->surname);
	}
	kayitsayisi--;
}
int main()
{
	int maxkayit=3;
	Phone_Record* k=new Phone_Record[maxkayit];
	bool bitir=0;
	while(!bitir)
	{
		char secim,secim2;
		print_menu();
		cin >> secim;
		switch (secim) {
		case 'S': case 's':
			search(k);
			break;
		case 'A': case 'a':
			if(kayitsayisi+1>maxkayit) k=realloc(k,maxkayit);
			add(k);
			break;
		case 'U': case 'u':
			if(kayitsayisi!=0) update(k);
			break;
		case 'D': case 'd':	
			if(kayitsayisi!=0) delete_record(k);	
			break;
		case 'E': case 'e':
			cout << "Are you sure that you want to terminate the program? (Y / N) : ";
				cin >> secim2;
			if (secim2 == 'Y' || secim2 == 'y')
				bitir = true;
				delete[] k;
				break;
		case 'L': case 'l':
			list(k);
			break;
		default:
			cout << "Error: You have mnamee an invalid choice" << endl;
			cout << "Try again {S, A, U, D, L, E} :";
			cin >> secim;
			if(secim=='E' || secim=='e') bitir=true;
			break;
		}
	}
system("PAUSE");
return EXIT_SUCCESS;
}
