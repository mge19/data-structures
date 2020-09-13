#include <cstdio>
#include <cstring>
#include <iostream>

#include "car.h"

#define MAXN 50

using namespace std;

int N,M=4;
int cnt[5];

void init(){
	
	beg=end=NULL;
	st[0]=st[1]=st[2]=st[3]=st[4]=NULL;
}

bool isEmpty( car *p ){
	return p==NULL;
}

int search( licencePlate s ){
	
	for( int i=1 ; i<=M ; i++ )
		if( !isEmpty(st[i]) )
			for( car *p=st[i] ; p ; p=p->nx )
				if( !strcmp(p->plate,s) )
					return i;
	
	if( !isEmpty(beg) )
		for( car *p=beg ; p ; p=p->nx )
			if( !strcmp(p->plate,s) )
				return 5;
	
	return 0;
}

void stackPush( int num , licencePlate s ){
	
	car *tmp;
	
	tmp=new car;
	tmp->plate=new char[(strlen(s))];
	strcpy(tmp->plate,s);
	
	if( num==1 ){
		tmp->nx=st[1];
		st[1]=tmp;
	}
	else if( num==2 ){
		tmp->nx=st[2];
		st[2]=tmp;
	}
	else if( num==3 ){
		tmp->nx=st[3];
		st[3]=tmp;
	}
	else if( num==4 ){
		tmp->nx=st[4];
		st[4]=tmp;
	}
}
void queuePush( licencePlate s ){
	
	car *tmp;
	
	tmp=new car;
	tmp->plate=new char[(strlen(s))];
	strcpy(tmp->plate,s);
	tmp->nx=tmp->pr=NULL;
	
	if( !beg )
		beg=end=tmp;
	else{
		tmp->nx=beg;
		beg->pr=tmp;
		beg=tmp;
	}
}

void add( licencePlate s , int dont ){
	
	for( int i=1 ; i<=M ; i++ )
		if( cnt[i]<N && i!=dont){
			stackPush(i,s);
			cnt[i]++;
			return;
		}
	
	queuePush(s);
}

void remove( licencePlate s ){
	
	int place=search(s);
	
	if(!place){
		cout << "Car not found" << endl;
		return;
	}
	
	car *tmp;
	
	while( strcmp(st[place]->plate,s) ){
		
		cnt[place]--;
		
		tmp=st[place];
		//~ queuePush(tmp->plate);
		add(tmp->plate,place);
		st[place]=st[place]->nx;
		
		delete(tmp->plate);
		delete(tmp);
	}
	
	cnt[place]--;
	tmp=st[place];
	st[place]=st[place]->nx;
	
	delete(tmp->plate);
	delete(tmp);
	
	licencePlate t;
	
	while( cnt[1]+cnt[2]+cnt[3]+cnt[4]<4*N && end ){
		
		t=new char[strlen(end->plate)];
		strcpy(t,end->plate);
		tmp=end;
		end=end->pr;
		if(end)
			end->nx=NULL;
		delete(tmp->plate);
		delete(tmp);
		
		add(t,0);
		delete(t);
	}
	
	if( !end )
		beg=end=NULL;
}

void write(){
	
	cout << "1. STACK" << endl;
	for( car *p=st[1] ; p ; p=p->nx )
		cout << p->plate << ' ';
	cout << endl;
		
	cout << "2. STACK" << endl;
	for( car *p=st[2] ; p ; p=p->nx )
		cout << p->plate << ' ';
	cout << endl;
	
	cout << "3. STACK" << endl;
	for( car *p=st[3] ; p ; p=p->nx )
		cout << p->plate << ' ';
	cout << endl;
	
	cout << "4. STACK" << endl;
	for( car *p=st[4] ; p ; p=p->nx )
		cout << p->plate << ' ';
	cout << endl;
	
	cout << "QUEUE" << endl;
	for( car *p=beg ; p ; p=p->nx )
		cout << p->plate << ' ';
	cout << endl;
}

void finish(){
	
	car *tmp;
	
	for( int i=1 ; i<5 ; i++ )
		while(st[i]){
			tmp=st[i];
			st[i]=st[i]->nx;
			delete(tmp->plate);
			delete(tmp);
		}
	
	while(beg){
		tmp=beg;
		beg=beg->nx;
		delete(tmp->plate);
		delete(tmp);
	}
}

int main(){
	
	init();
	
	char ch;
	char s[MAXN];
	
	cout << "Please enter N: ";
	cin >> N;
	
	while(1){
		
		cin >> ch;
		
		if( ch=='E' || ch=='e' )
			break;
		else if( ch=='a' || ch=='A' ){
			cin >> s;
			if( !search(s) )
				add(s,0);
			else
				cout << "This car is already in the park" << endl;
		}
		else if( ch=='R' || ch=='r'){
			cin >> s;
			remove(s);
		}
		else if( ch=='w' || ch=='W' )
			write();
		
	}
	
	finish();
	return 0;
}