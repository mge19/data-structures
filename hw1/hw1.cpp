/* BLG233E-Data Structures and Laboratory
*  Homework 1
* Student Name: Mehmet Gencay Ertürk
* Student ID : 150130118
* Date: 09-10-2017
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#define MAX_LENGTH 10
#define LENGTH 15
#define NUMBER_OF_WORDS 9
//This code should be compiled in Dev-C++ (on Windows) for better performance
using namespace std;
struct searchedWord {
int id;
char* word;
int wordLength;
};
char* reverse_string(char* text) //This is necessary for controlling strings from right to left and from down to the top
{
	char* reversed_string=new char[strlen(text)];
    for(unsigned int a=0;a<strlen(text);a++)
    {
    	strncpy(reversed_string+strlen(text)-a-1,text+a,1);
	}
	return reversed_string;
}
bool** clear_control=new bool*[LENGTH]; //This variable keeps which characters will be deleted in lastVersionPuzzle.txt
void start(bool** clear_control)
{
	for(int i=0;i<LENGTH;i++)
	{
		*(clear_control+i)=new bool[LENGTH];
		for(int j=0;j<LENGTH;j++)
		{
			*(*(clear_control+i)+j)=true; //If treue,it won't be deleted.
		}
	}
}
void makezero(bool** clear_control,int i,int j,int x,int state) //This function turns characters that will be deleted false in horizontal and vertical searches. 
{
	for(int y=j;y<x;y++)
	{
		if(state==0) *(*(clear_control+i)+y)=false;
		else 	*(*(clear_control+y)+i)=false;
	}
}
void makezero_diagonal(bool** clear_control,int row1,int col1,int row2,int col2,int state) //This function turns characters that will be deleted false in horizontal and vertical searches. 
{
	for(int i=row1;i<=row2;i++)
	{
		if(state==0)
		{
			for(int j=col1;j>=col2;j--)
			{
				if(abs(i-row1)==abs(j-col1)) 	*(*(clear_control+i)+j)=false;
			}
		}
		else if(state==1)
		{
			for(int j=col1;j<=col2;j++)
			{
				if(abs(i-row1)==abs(j-col1)) 	*(*(clear_control+i)+j)=false;
			}
		}
	}
}
void store_puzzle(char** puzzleArray) //This function takes characters from puzzle.txt and stores them at an 2-D array
{
	FILE* input=fopen("puzzle.txt","r+");
	if(input==NULL) cerr<<"Error opening puzzle.txt";
	else
	{
		for(int i=0;!feof(input);i++)
		{
			for(int j=0;j<LENGTH+1;j++)
			{
				if(j<LENGTH) { fscanf(input,"%s",*(puzzleArray+i)+j); }
				else { fscanf(input,"\0",NULL); }
			}
		}
		fclose(input);
	}
}
void reversed_puzzle(char** puzzleArray,char** reversed_array) //This function creates reversed puzzle array for vertical search
{
	for(int i=0;i<LENGTH;i++)
	{
		for(int j=0;j<LENGTH;j++) {strncpy(*(reversed_array+i)+j,*(puzzleArray+j)+i,1);}
	}
}
void diagonalized_puzzle(char** diagonal1,char** diagonal2,char** puzzleArray) //This function creates arrays for diagonal search.In a diagpnal line,sum or difference of row and difference is constant
{
	bool z=false,u=false;
	for(int k=0;k<2*LENGTH-1;k++)
	{
		for(int i=0;i<LENGTH;i++)
		{
			for(int j=0;j<LENGTH;j++)
			{
				if(i+j==k) 
				{
					if(!z) 
					{ strncpy(*(diagonal1+k),*(puzzleArray+i)+j,1); z=true;}
					else { strncat(*(diagonal1+k),*(puzzleArray+i)+j,1);}						
				}
				if(i-j==k-LENGTH+1) 
				{
					if(!u) 
					{ strncpy(*(diagonal2+k),*(puzzleArray+i)+j,1); u=true;}
					else {strncat(*(diagonal2+k),*(puzzleArray+i)+j,1);}
				}
			}
		}
	}
}
void find_indexes(int** index_i_1,int** index_j_1,int** index_i_2,int** index_j_2) //This function places row and column number data of diagonal arrays.
{
	for(int k=0;k<2*LENGTH-1;k++)
	{
		int l=0,m=0;
		for(int i=0;i<LENGTH;i++)
		{
			for(int j=0;j<LENGTH;j++)
			{
				if(i+j==k) 
				{
					*(*(index_i_1+k)+l)=i;
					*(*(index_j_1+k)+l)=j;
					l++;
				}
				if(i-j==k-LENGTH+1) 
				{
					*(*(index_i_2+k)+m)=i;
					*(*(index_j_2+k)+m)=j;
					m++;
				}
			}
		}
	}
}
void store_words(searchedWord* word) //This function stores searched words and their necessary data.
{
	FILE* words=fopen("searchedwords.txt","r+");
	if(words==NULL) cerr<<"Error opening searchedwords.txt";
	else
	{
		for(int i=0;!feof(words);i++)
    	{
    		(word+i)->word=new char[MAX_LENGTH];
    		fscanf(words,"%d %s",&((word+i)->id),(word+i)->word);
    		(word+i)->wordLength=strlen((word+i)->word);
		}
		fclose(words);
	}
}
bool horizontalSearch(char** puzzleArray,searchedWord* word)
{
	FILE* output=fopen("foundWordsInfo.txt","a+");	
	if(output==NULL) { cerr<<"Error opening foundWordsInfo.txt";}
	else for(int i=0;i<LENGTH;i++)
	{
		for(int j=0;j<LENGTH+1-word->wordLength;j++)
		{
			if(strncmp(word->word,*(puzzleArray+i)+j,word->wordLength)==0) //If the word has been found...
			{
				fprintf(output,"%s\tHORIZONTAL\t[%d][%d] - [%d][%d]\n",word->word,i,j,i,j+word->wordLength-1);
				makezero(clear_control,i,j,j+word->wordLength,0);
				fclose(output);
				return true;
			}
			else if(strncmp(reverse_string(word->word),*(puzzleArray+i)+j,word->wordLength)==0) 
			{
				fprintf(output,"%s\tHORIZONTAL\t[%d][%d] - [%d][%d]\n",word->word,i,j+word->wordLength-1,i,j);
				makezero(clear_control,i,j,j+word->wordLength,0);
				fclose(output);
				return true;				
			}			
		}
	}
	fclose(output);
	return false;
}
bool verticalSearch(char** puzzleArray,searchedWord* word)
{
	FILE* output=fopen("foundWordsInfo.txt","a+");	
	if(output==NULL) { cerr<<"Error opening foundWordsInfo.txt";}
    else
	{
		char** reversed_array=reversed_array=new char*[LENGTH];
		for(int i=0;i<LENGTH;i++) {*(reversed_array+i)=new char[LENGTH];}
		reversed_puzzle(puzzleArray,reversed_array);
		for(int i=0;i<LENGTH;i++)
		{
			for(int j=0;j<LENGTH+1-word->wordLength;j++)
			{
				if(strncmp(word->word,*(reversed_array+i)+j,word->wordLength)==0) 
				{
					fprintf(output,"%s\tVERTICAL\t[%d][%d] - [%d][%d]\n",word->word,j,i,j+word->wordLength-1,i);
					makezero(clear_control,i,j,j+word->wordLength,1);
					delete reversed_array;
					fclose(output);
					return true;
				}
			    else if(strncmp(reverse_string(word->word),*(reversed_array+i)+j,word->wordLength)==0) 
				{
					fprintf(output,"%s\tVERTICAL\t[%d][%d] - [%d][%d]\n",word->word,j+word->wordLength-1,i,j,i);
					makezero(clear_control,i,j,j+word->wordLength,1);
					delete reversed_array;
					fclose(output);
					return true;
				}
			} 
		}
		delete reversed_array;
		fclose(output);
		return false;
	}
}
bool diagonalSearch(char** puzzleArray,searchedWord* word)
{
	FILE* output=fopen("foundWordsInfo.txt","a+");	
	if(output==NULL) { cerr<<"Error opening foundWordsInfo.txt";}
	else
 	{
		char** diagonal1=new char*[2*LENGTH-1];
		char** diagonal2=new char*[2*LENGTH-1];
		int** index_i_1=new int*[2*LENGTH-1];
		int** index_i_2=new int*[2*LENGTH-1];
		int** index_j_1=new int*[2*LENGTH-1];
		int** index_j_2=new int*[2*LENGTH-1];
		for(int i=0;i<2*LENGTH-1;i++)
		{
			if(i<LENGTH) 
			{
				*(diagonal1+i)=new char[i+1];	
				*(diagonal2+i)=new char[i+1];
				*(index_i_1+i)=new int[i+1];
				*(index_i_2+i)=new int[i+1];
				*(index_j_1+i)=new int[i+1];
				*(index_j_2+i)=new int[i+1];
			}
			else 
			{
				*(diagonal1+i)=new char[2*LENGTH-1-i];
				*(diagonal2+i)=new char[2*LENGTH-1-i];
				*(index_i_1+i)=new int[2*LENGTH-1-i];
				*(index_i_2+i)=new int[2*LENGTH-1-i];
				*(index_j_1+i)=new int[2*LENGTH-1-i];
				*(index_j_2+i)=new int[2*LENGTH-1-i];
			}		
		}
		diagonalized_puzzle(diagonal1,diagonal2,puzzleArray);
		find_indexes(index_i_1,index_j_1,index_i_2,index_j_2);
		for(int i=0;i<2*LENGTH-1;i++)
		{
			for(unsigned int j=0;j<strlen(*(diagonal2+i));j++)
			{
				if(strncmp(word->word,*(diagonal1+i)+j,word->wordLength)==0) //Every words are printed only once.
				{
					fprintf(output,"%s\tDIAGONAL\t[%d][%d] - [%d][%d]\n",word->word,*(*(index_i_1+i)+j),*(*(index_j_1+i)+j),*(*(index_i_1+i)+j+word->wordLength-1),*(*(index_j_1+i)+j+word->wordLength-1));					
					makezero_diagonal(clear_control,*(*(index_i_1+i)+j),*(*(index_j_1+i)+j),*(*(index_i_1+i)+j+word->wordLength-1),*(*(index_j_1+i)+j+word->wordLength-1),0);
					fclose(output);
					delete diagonal1;
					delete diagonal2,
					delete index_i_1;
					delete index_i_2;
					delete index_j_1;
					delete index_j_2;
					return true;
				}
				else if(strncmp(reverse_string(word->word),*(diagonal1+i)+j,word->wordLength)==0) 
				{
					fprintf(output,"%s\tDIAGONAL\t[%d][%d] - [%d][%d]\n",word->word,*(*(index_i_1+i)+j+word->wordLength-1),*(*(index_j_1+i)+j+word->wordLength-1),*(*(index_i_1+i)+j),*(*(index_j_1+i)+j));			
					makezero_diagonal(clear_control,*(*(index_i_1+i)+j),*(*(index_j_1+i)+j),*(*(index_i_1+i)+j+word->wordLength-1),*(*(index_j_1+i)+j+word->wordLength-1),0);
					fclose(output);
					delete diagonal1;
					delete diagonal2,
					delete index_i_1;
					delete index_i_2;
					delete index_j_1;
					delete index_j_2;
					return true;
				}
				else if(strncmp(word->word,*(diagonal2+i)+j,word->wordLength)==0) 
				{
					fprintf(output,"%s\tDIAGONAL\t[%d][%d] - [%d][%d]\n",word->word,*(*(index_i_2+i)+j),*(*(index_j_2+i)+j),*(*(index_i_2+i)+j+word->wordLength-1),*(*(index_j_2+i)+j+word->wordLength-1));								
					makezero_diagonal(clear_control,*(*(index_i_2+i)+j),*(*(index_j_2+i)+j),*(*(index_i_2+i)+j+word->wordLength-1),*(*(index_j_2+i)+j+word->wordLength-1),1);		
					fclose(output);
					delete diagonal1;	
					delete diagonal2,
					delete index_i_1;
					delete index_i_2;
					delete index_j_1;
					delete index_j_2;
					return true;
				}	
				else if(strncmp(reverse_string(word->word),*(diagonal2+i)+j,word->wordLength)==0) 
				{
					fprintf(output,"%s\tDIAGONAL\t[%d][%d] - [%d][%d]\n",word->word,*(*(index_i_2+i)+j+word->wordLength-1),*(*(index_j_2+i)+j+word->wordLength-1),*(*(index_i_2+i)+j),*(*(index_j_2+i)+j));										
					makezero_diagonal(clear_control,*(*(index_i_2+i)+j),*(*(index_j_2+i)+j),*(*(index_i_2+i)+j+word->wordLength-1),*(*(index_j_2+i)+j+word->wordLength-1),1);										
					fclose(output);
					delete diagonal1;
					delete diagonal2,
					delete index_i_1;
					delete index_i_2;
					delete index_j_1;
					delete index_j_2;
					return true;
				}
			} 
		}
		delete diagonal1;
		delete diagonal2,
		delete index_i_1;
		delete index_i_2;
		delete index_j_1;
		delete index_j_2;
		fclose(output);
		return false;
	}
}
void print_last_puzzle(char** puzzleArray) //Print puzzle without words.
{
    FILE* lastpuzzle=fopen("lastVersionPuzzle.txt","a+");
	if(lastpuzzle==NULL) cerr<<"Error opening lastVersionPuzzle.txt";
	else
	{
		const char* blank=" ";
		for(int i=0;i<LENGTH;i++)
		{
			for(int j=0;j<LENGTH+1;j++)
			{
				if(j<LENGTH)
				{
					if(!*(*(clear_control+i)+j)){ memcpy(*(puzzleArray+i)+j,blank,1);}
					fseek(lastpuzzle,1,SEEK_CUR);
					fwrite(*(puzzleArray+i)+j,1,1,lastpuzzle);
					fseek(lastpuzzle,1,SEEK_CUR);
					if(j!=LENGTH-1) fprintf(lastpuzzle,blank);
				}
				else fprintf(lastpuzzle,"\n");
			}
		}
		fclose(lastpuzzle);
	}
}
int main()
{
	char** puzzleArray;
	puzzleArray=new char*[LENGTH];
	start(clear_control);
	for(int i=0;i<LENGTH;i++) {*(puzzleArray+i)=new char[LENGTH];}
	store_puzzle(puzzleArray);
	searchedWord* word=new searchedWord[NUMBER_OF_WORDS];
	store_words(word);
	for(int i=1;i<=NUMBER_OF_WORDS;i++) //Words are found according to their priority order
	{
		for(int j=0;j<NUMBER_OF_WORDS;j++)
		{
			if(i==(word+j)->id) 
			{
				if(!horizontalSearch(puzzleArray,word+j))
				{
					if(!verticalSearch(puzzleArray,word+j))
					{
						if(diagonalSearch(puzzleArray,word+j)){}
					}	
				}
			}
		}
	}
	print_last_puzzle(puzzleArray);
	delete clear_control;
	delete puzzleArray;
	delete word;
	system("PAUSE");
	return 0;
}
