/*BLG233E-Data Structures and Laboratory
Homework-3
Mehmet Gencay Ertürk-150130118*/
#include <string>
#include <iostream>
struct patient
{
    std::string name;
    int treated=0;
    int arriving_time;
    int treatment_time;
    std::string complaint;
    patient* next;
};
struct queue
{
    bool isempty();
    patient* front=NULL;
    patient* rear=NULL;
    void enqueue(patient* newPatient);
    patient* dequeue();
    patient* peek();
};
bool queue::isempty()
{
    return peek()==NULL;
}
void queue::enqueue(patient* newPatient)
{
    if(!front) front=rear=newPatient;
    else
    {
        rear->next=newPatient;
        rear=newPatient;
    }
}
patient* queue::dequeue()
{
    patient* temp=front;
    front=front->next;
    return temp;
}
patient* queue::peek()
{
    return front;
}
