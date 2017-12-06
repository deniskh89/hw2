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

/*************************************************************************************
// function name : createFlight
// Description   :	Function create a new flight .
// Parameters    :	Flight number (int) , type of the flight (FlightType) , 
//						destination (char* [3]) and if the flight is emergency.
// Return value  :	Pointer to the new flight.
//**************************************************************************************/
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

/*************************************************************************************
// function name : destroyFlight
// Description   :	Function that frees the memery and destroy the flight .
// Parameters    :	Flight number (int) , type of the flight (FlightType) .
// Return value  :	Pointer to the new flight.
//**************************************************************************************/
void destroyFlight(PFlight flight)
{
	free(flight);
}

/*************************************************************************************
// function name : printFlight
// Description   :	Function that prints the flight .
// Parameters    :	Pointer to the flight (PFlight) .
// Return value  :	none.
//**************************************************************************************/
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

/*************************************************************************************
// function name : getFlightId
// Description   :	Function that gets the Id of the flight .
// Parameters    :	Pointer to the flight (PFlight) .
// Return value  :	Id of the flight (int).
//**************************************************************************************/
int getFlightId(PFlight flight)
{
	if (flight == NULL)
		return -1;
	return flight->flight_ID;
}

/*************************************************************************************
// function name : getFlightType
// Description   :	Function that gets the type of the flight .
// Parameters    :	Pointer to the flight (PFlight) .
// Return value  :	Type of the flight DOMESTIC or INTERNATIONAL.
//**************************************************************************************/
FlightType getFlightType(PFlight flight)
{
	return flight->Type;
}

/*************************************************************************************
// function name : getFlightEmr
// Description   :	Function that gets if the flight is emergency.
// Parameters    :	Pointer to the flight (PFlight) .
// Return value  :	TRUE if the flight is emergency or FALSE if it is not.
//**************************************************************************************/
BOOL getFlightEmr(PFlight flight)
{
	return flight->Emr;
}

/*************************************************************************************
// function name : getFlightDes
// Description   :	Function that gets the flight destination.
// Parameters    :	Pointer to the flight (PFlight) .
// Return value  :	Destination of the flight (char* [3]).
//**************************************************************************************/
char* getFlightDes(PFlight flight)
{
	return flight->Dest;
}

/*************************************************************************************
// function name : setFlightDes
// Description   :	Function that changes the flight destination.
// Parameters    :	Pointer to the flight (PFlight) , new destination (char* [3]).
// Return value  :	none.
//**************************************************************************************/
void setFlightDes(PFlight flight, char* newDest)
{
	flight->Dest[0] = newDest[0];
	flight->Dest[1] = newDest[1];
	flight->Dest[2] = newDest[2];
}

