#ifndef CAR_H
#define CAR_H

typedef char* licencePlate;

struct car{
	licencePlate plate;
	car *nx,*pr;
}*st[5],*beg,*end;

#endif
