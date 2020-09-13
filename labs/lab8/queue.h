#ifndef QUEUE_H
#define QUEUE_H

typedef char* licencePlate;

struct Queue{
	licencePlate plate;
	Queue *nx;
}*start,*finish;

#endif
