#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flight.h"
#include "runway.h"
#include "ex2.h"
#include "airport.h"


typedef struct node_runway   //linked list
{
	PRunway runway;
	struct node_runway* next_runway;
} Node_runway;

static Node_runway* Airport = NULL; // ADD STATIC , TURNED OFF BECAUSE OF DEBUG

Result addRunway(int runway_num, FlightType runway_type)
{
	if (runway_num<1 || runway_num>MAX_ID)
		return FAILURE;
	if (Airport == NULL)
	{
		Airport = (Node_runway*)malloc(sizeof(Node_runway));
		if (Airport == NULL)
			return FAILURE;
		Airport->runway = createRunway(runway_num, runway_type);
		if (Airport->runway == NULL)
			return FAILURE;
		Airport->next_runway = NULL;
		return SUCCESS;
	}
	else
	{
		Node_runway* temp = Airport;
		if (getRunwayID(temp->runway) == runway_num)
			return FAILURE;
		while (temp->next_runway != NULL)
		{
			if (getRunwayID(temp->next_runway->runway) == runway_num)
				return FAILURE;
			temp = temp->next_runway;
		}
		temp->next_runway = (Node_runway*)malloc(sizeof(Node_runway));
		if (temp->next_runway == NULL)
			return FAILURE;
		temp->next_runway->runway = createRunway(runway_num, runway_type);
		if (temp->next_runway->runway == NULL)
			return FAILURE;
		temp->next_runway->next_runway = NULL;
		return SUCCESS;
	}
}

Result removeRunway(int runway_num)
{
	if (runway_num<1 || runway_num>MAX_ID || Airport == NULL)
		return FAILURE;
	Node_runway* current = Airport;
	Node_runway* next = current->next_runway;
	if (getRunwayID(current->runway) == runway_num)
	{
		Airport = next;
		destroyRunway(current->runway);
		free(current);
		return SUCCESS;
	}
	if (next == NULL)
		return FAILURE;
	while (getRunwayID(next->runway) != runway_num)
	{
		current = next;
		next = next->next_runway;
		if (next == NULL)
			return FAILURE;
	}
	destroyRunway(next->runway);
	current->next_runway = next->next_runway;
	free(next);
	return SUCCESS;
}

Result addFlightToAirport(int Flight_num, FlightType Typef, char* Destenation, BOOL Emergency)
{
	if (Airport == NULL)
		return FAILURE;
	BOOL same_num = FALSE;
	Node_runway* min = NULL;
	Node_runway* curr = Airport;
	if (curr->next_runway == NULL)
	{
		if (getRunwayType(curr->runway) == Typef)
		{
			min = curr;
		}
		else
			return FAILURE;
	}
	while (curr != NULL) 
	{
		if (isFlightExists(curr->runway, Flight_num))
			return FAILURE;
		if (getRunwayType(curr->runway) != Typef)
		{
			curr = curr->next_runway;
			continue;
		}
		if (min == NULL)
			min = curr;
		else
		{
			if (getFlightNum(curr->runway) < getFlightNum(min->runway))
			{
				same_num = FALSE;
				min = curr;
			}
			else if (getFlightNum(curr->runway) == getFlightNum(min->runway))
				same_num = TRUE;
		}
		curr = curr->next_runway;
	}
	if (same_num == TRUE)
	{
		int min_flights = getFlightNum(min->runway);
		curr = Airport;
		while (curr != NULL)
		{
			if (getRunwayType(curr->runway) != Typef)
			{
				curr = curr->next_runway;
				continue;
			}
			if (getFlightNum(curr->runway) == min_flights &&
				getRunwayID(curr->runway) < getRunwayID(min->runway))
				min = curr;
			curr = curr->next_runway;
		}
	}
	if (min == NULL)
		return FAILURE;
	PFlight temp = createFlight(Flight_num, Typef, Destenation, Emergency);
	if (temp == NULL)
		return FAILURE;
	return addFlight(min->runway, temp);
}

Result departFromAirport()
{
	if (Airport == NULL)
		return	FAILURE;
	int minId = MAX_ID, maxEm = 0, maxAll = 0;
	Node_runway *temp = Airport;
	PRunway min_Id_Runway = NULL, max_Em_Runway = NULL, max_Flight_Runway = NULL;
	BOOL sameEM = FALSE, sameMax = FALSE;
	while (temp != NULL)
	{
		if (getEmergencyNum(temp->runway) > maxEm)
		{
			maxEm = getEmergencyNum(temp->runway);
			max_Em_Runway = temp->runway;
			sameEM = FALSE;
		}
		else if (getEmergencyNum(temp->runway) == maxEm)
			sameEM = TRUE;

		if (getFlightNum(temp->runway) > maxAll)
		{
			maxAll = getFlightNum(temp->runway);
			max_Flight_Runway = temp->runway;
			sameMax = FALSE;
		}
		else if (getFlightNum(temp->runway) == maxAll)
			sameMax = TRUE;

		if (getRunwayID(temp->runway) < minId && getFlightNum(temp->runway)!=0)
		{
			minId = getRunwayID(temp->runway);
			min_Id_Runway = temp->runway;
		}

		temp = temp->next_runway;
	}
	if (sameEM == FALSE && maxEm!=0)
		return depart(max_Em_Runway);
	if (sameMax == FALSE && maxAll!=0)
		return depart(max_Flight_Runway);
	return depart(min_Id_Runway);
}

Result changeDest(char* Destenation_old, char* Destenation_new)
{
	int i=0;
	Node_runway* temp_runway = Airport;
	if (strlen(Destenation_old) != 3 || strlen(Destenation_new) != 3)
		return FAILURE;
	for (i = 0; i < 3; i++)
	{
		if (Destenation_old[i] < 'A' || Destenation_old[i] > 'Z' ||
			Destenation_new[i] < 'A' || Destenation_new[i] > 'Z')
			return FAILURE;
	}
	while (temp_runway != NULL)
	{
		changeDestInRunway(temp_runway->runway, Destenation_new, Destenation_old);
		temp_runway = temp_runway->next_runway;
	}
	return SUCCESS;
}

Result delay(char* Destenation)
{
	int i=0;
	Node_runway* temp_runway = Airport;
	if (strlen(Destenation) != 3 )
		return FAILURE;
	for (i = 0; i < 3; i++)
	{
		if (Destenation[i] < 'A' || Destenation[i] > 'Z' )
			return FAILURE;
	}
	while (temp_runway != NULL)
	{
		if (delayRunway(temp_runway->runway, Destenation) == FAILURE)
			return FAILURE;
		temp_runway = temp_runway->next_runway;
	}
	return SUCCESS;
}

void printAirport()
{
	printf("Airport status:\n");
	Node_runway* temp_runway = Airport;
	if (temp_runway == NULL)
		return;
	while (temp_runway != NULL)
	{
		printRunway(temp_runway->runway);
		temp_runway = temp_runway->next_runway;
	}
}

void destroyAirport()
{
	Node_runway* temp_runway = Airport;
	while (temp_runway != NULL)
	{
		Node_runway* temp = temp_runway->next_runway;
		removeRunway(getRunwayID(temp_runway->runway));
		temp_runway = temp;
	}
	Airport = NULL;
	return;
}
