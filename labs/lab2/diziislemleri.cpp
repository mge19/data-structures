#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;

void Dizi::kayit() {
	
    teldefteri = fopen("text.txt", "r+");

	for (int i = 0; i < kayitsayisi; i++) {
		fwrite(k + i, sizeof(Tel_Kayit), 1, teldefteri);
	}
	
    fclose(teldefteri);
}


void Dizi::ekle(Tel_Kayit *ykptr) {
    
    char * record1 = ykptr->ad;
    int i;
    for (i = 0; i < kayitsayisi; i++) {
        
        if (strcmp(record1,(k+i)->ad) < 0) {
            break;
        }
    }
    
    for (int sira = kayitsayisi; sira > i; sira--) {
        
        strcpy((k + sira)->ad,(k + sira - 1)->ad);
        strcpy((k + sira)->telno, (k + sira - 1)->telno);
    }
    
    strcpy((k+i)->ad, ykptr->ad);
    strcpy((k+i)->telno, ykptr->telno);
    
    kayitsayisi++;
}


void Dizi::olustur() {
	
    kayitsayisi = 0;
	
	
    teldefteri = fopen("text.txt", "r+");

	if (!teldefteri) {
		teldefteri = fopen("text.txt", "w+");
		if (!teldefteri) {
			cout << "dosya acilamadi" << endl;
			exit(1);
		}
	}
	int i = 0;
	
    /*for ( ;!feof(teldefteri); i++) {
		fread( k+i , sizeof(Tel_Kayit), 1, teldefteri);
		if (feof(teldefteri)) break;
	}*/
    
    while (!feof(teldefteri)) {
        
        fread( k+i , sizeof(Tel_Kayit), 1, teldefteri);
        
        if (feof(teldefteri)) break;
        
        i++;
    }
	
	kayitsayisi += i;


}

int Dizi::ara(char aranacak[]) {
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	for (int i = 0;i<kayitsayisi;i++) {
		if (tumu || strncmp((k+i)->ad,aranacak,strlen(aranacak)) == 0)
		{
			cout << i + 1 << ". " << (k+i)->ad <<"\t"<<(k+i)->telno<< endl;
			bulunan = i;
			flag = 1;
		}
	}
	return flag;
}
void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr) {
	Tel_Kayit temp;
	strcpy((k+kayitno-1)->ad, ykptr->ad);
	strcpy((k+kayitno-1)->telno, ykptr->telno);
	for(int i=0;i<kayitsayisi-1;i++)
	{
		for(int j=i+1;j<kayitsayisi;j++)
		{
			if(strcmp((k+i)->ad,(k+j)->ad)>0)
			{
				strcpy(temp.ad,(k+j)->ad);
				strcpy(temp.telno,(k+j)->telno);
				strcpy((k+j)->ad,(k+i)->ad);
				strcpy((k+j)->telno,(k+i)->telno);
				strcpy((k+i)->ad,temp.ad);
				strcpy((k+i)->telno,temp.telno);	
			}
		}
	}
}
void Dizi::sil(int kayitno) {
	int i;
	for(i=kayitno-1;i<kayitsayisi;i++)
	{
		strcpy((k+i)->ad,(k+i+1)->ad);
		strcpy((k+i)->telno,(k+i+1)->telno);
	}
	kayitsayisi--;
}

void Dizi::listele() {
	for (int i = 0;i<kayitsayisi;i++)
		cout << i + 1 << ". " << (k+i)->ad << " " << (k+i)->telno << endl;
}
