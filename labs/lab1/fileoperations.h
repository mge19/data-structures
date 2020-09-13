#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "record.h"
struct Dosya{
	char *dosyaadi;
	FILE *teldefteri;
	void olustur();
	void kapat();
	void ekle(Tel_Kayit *);
	int ara(char[]);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_Kayit *);
	int maintain();
};
#endif