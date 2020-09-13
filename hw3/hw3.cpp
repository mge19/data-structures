/*BLG233E-Data Structures and Laboratory
Homework-3
Mehmet Gencay Ertürk-150130118*/
#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
int timeslot=0;
void define_patients(queue* red,queue* yellow,queue* green) //Takes information of patients and places them in related queues with respect to their arriving time.
{
	std::ifstream text("patientsInfo.txt");
    std::string line;
    std::getline(text,line);
    queue* temp=new queue;
    while(std::getline(text,line))
    {
    	patient* newPatient=new patient;
        newPatient->next=NULL;
        newPatient->name=line.substr(0,9);
        std::stringstream(line.substr(14,2))>>newPatient->arriving_time;
        std::stringstream(line.substr(33,2))>>newPatient->treatment_time;
        timeslot+=newPatient->treatment_time;
        newPatient->complaint=line.substr(51,6);
        if(newPatient->complaint.substr(0,3)=="RED")
		{
			while(!red->isempty() && newPatient->arriving_time<red->peek()->arriving_time) {temp->enqueue(red->dequeue());}
			red->enqueue(newPatient);
			while(!temp->isempty()){red->enqueue(temp->dequeue());}
		}
        if(newPatient->complaint.substr(0,6)=="YELLOW")
		{
			while(!yellow->isempty() && newPatient->arriving_time<yellow->peek()->arriving_time) {temp->enqueue(yellow->dequeue());}
			yellow->enqueue(newPatient);
			while(!temp->isempty()){yellow->enqueue(temp->dequeue());}			
		}
        if(newPatient->complaint.substr(0,5)=="GREEN")
		{
			while(!green->isempty() && newPatient->arriving_time<green->peek()->arriving_time) {temp->enqueue(green->dequeue());}
			green->enqueue(newPatient);
			while(!temp->isempty()){green->enqueue(temp->dequeue());}					
		}
    }
    text.close();
	delete temp;
}
int main()
{
    queue* red=new queue;
	queue* yellow=new queue;
	queue* green=new queue; 
    define_patients(red,yellow,green);
    int time=0;
    patient* x;
    int state;
    while(time<timeslot) 
    {
        if(!red->isempty() && time>=red->peek()->arriving_time){x=red->dequeue();state=1;} //Patient choosing
        else if(!yellow->isempty() && time>=yellow->peek()->arriving_time){x=yellow->dequeue();state=2;}
        else if(!green->isempty() && time>=green->peek()->arriving_time){x=green->dequeue();state=3;}
		for(int i=0;time!=timeslot && i<state && x->treated!=x->treatment_time;i++) //Treating
        {
            std::cout<<time+1<<". time slice "<<x->name<<std::endl;
            time++;
            x->treated++;
        }
        if(x->treated==x->treatment_time) delete x; //Deleting if treatment time is over
        else if(state==1) yellow->enqueue(x); //If not,(s)he will be added in another queue
        else green->enqueue(x);
    }
    delete red;
    delete yellow;
    delete green;
    getchar();
    return 0;
}
