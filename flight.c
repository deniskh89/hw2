#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flight.h"
#include "ex2.h"

typedef struct flight_t 
{
	int flight_ID;
	FlightType Type;
	BOOL Emr;
	char Dest[4];
} Flight;

PFlight createFlight(int Flight_num, FlightType Typef, char* Destenation, BOOL Emergency)
{
	int i=0;
	if (Flight_num<1 && Flight_num> MAX_ID)
		return NULL;
	if (strlen(Destenation) != 3)
		return NULL;
	for (i = 0; i < 3; i++)
	{
		if (Destenation[i] < 'A' || Destenation[i] > 'Z')
			return NULL;
	}

	PFlight temp = (PFlight) malloc(sizeof(Flight));
	if (temp == NULL)
		return NULL;
	for (i = 0; i < 3; i++)
	{
			temp->Dest[i]= Destenation[i];
	}
	temp->Dest[3] = '\0';
	temp->Emr = Emergency;
	temp->flight_ID = Flight_num;
	temp->Type = Typef;
	return temp;
}

void destroyFlight(PFlight flight)
{
	free(flight);
}

void printFlight(PFlight flight)
{
	char temp_type, temp_emr;
	if (flight->Emr)
		temp_emr = 'E';
	else
		temp_emr = 'R';
	if (flight->Type == INTERNATIONAL)
		temp_type = 'I';
	else
		temp_type = 'D';
	printf("Flight %d %c %s %c\n", flight->flight_ID, temp_type, flight->Dest, temp_emr);
}






int getFlightId(PFlight flight)
{
	if (flight == NULL)
		return -1;
	return flight->flight_ID;
}
FlightType getFlightType(PFlight flight)
{
	return flight->Type;
}
BOOL getFlightEmr(PFlight flight)
{
	return flight->Emr;
}

char* getFlightDes(PFlight flight)
{
	return flight->Dest;
}
void setFlightDes(PFlight flight, char* newDest)
{
	flight->Dest[0] = newDest[0];
	flight->Dest[1] = newDest[1];
	flight->Dest[2] = newDest[2];
}

