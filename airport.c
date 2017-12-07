#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flight.h"
#include "runway.h"
#include "ex2.h"
#include "airport.h"


typedef struct node_runway   //linked list for different runways
{
	PRunway runway;
	struct node_runway* next_runway;
} Node_runway;

static Node_runway* Airport = NULL; // pointer to the first runway
/*************************************************************************************
// function name :  addRunway
// Description   :	Function that adds a runway to the airoprt if there isn't a runway
with the same number already in the airport.
// Parameters    :	New runway number, the type of the runway (domestic or internetional).
// Return value  :	sucsess if the function added the runway and faliure if it didnt.
//**************************************************************************************/
Result addRunway(int runway_num, FlightType runway_type)
{
	if (runway_num<1 || runway_num>MAX_ID)//checks if the number is valid .
		return FAILURE;
	if (Airport == NULL)//checks if the airport is empty.
	{
		Airport = (Node_runway*)malloc(sizeof(Node_runway));// creats the new runway linked list.
		if (Airport == NULL)
			return FAILURE;
		Airport->runway = createRunway(runway_num, runway_type);// adds the runway to the airport
		if (Airport->runway == NULL)
			return FAILURE;
		Airport->next_runway = NULL;// sets the next paramter in the runways list to null.
		return SUCCESS;
	}
	else//if there are already runways in the airport.
	{
		Node_runway* temp = Airport;//temp is set to the first runway in the airport.
		if (getRunwayID(temp->runway) == runway_num)//checks if the first runway has the same number.
			return FAILURE;
		while (temp->next_runway != NULL)//moves next to the last runway in the linked list.
		{
			if (getRunwayID(temp->next_runway->runway) == runway_num)//checks if there is a runway with the same number.
				return FAILURE;
			temp = temp->next_runway;
		}
		temp->next_runway = (Node_runway*)malloc(sizeof(Node_runway));//creates the new node in the list for the runway.
		if (temp->next_runway == NULL)
			return FAILURE;
		temp->next_runway->runway = createRunway(runway_num, runway_type); //adds the new runway to the list.
		if (temp->next_runway->runway == NULL)
			return FAILURE;
		temp->next_runway->next_runway = NULL;//sets the last runway node next paramter to null.
		return SUCCESS;
	}
}
/*************************************************************************************
// function name :  removeRunway
// Description   :	Function that removes a runway from the airport.
// Parameters    :	runway number.
// Return value  :	sucsess if the function was able to remove the runway, falirue else.
//**************************************************************************************/
Result removeRunway(int runway_num)
{
	if (runway_num<1 || runway_num>MAX_ID || Airport == NULL)//checks if the runway number is valid or that the airport has no runways.
		return FAILURE;
	Node_runway* current = Airport;
	Node_runway* next = current->next_runway;
	if (getRunwayID(current->runway) == runway_num)//if the current runway has the desired number.
	{
		Airport = next;
		destroyRunway(current->runway); //removes the runway and all the flights in it.
		free(current);//removes the runway node from the linked list.
		return SUCCESS;
	}
	if (next == NULL)//reached the end of the list.
		return FAILURE;
	while (getRunwayID(next->runway) != runway_num)//if the current runway dosent have the desired number.
	{
		current = next;//moves the pointer to the next runway node.
		next = next->next_runway;
		if (next == NULL)//if we got to the last runway and we didnt find the runway with the desired number.
			return FAILURE;
	}
	destroyRunway(next->runway);//delets the runway and all his flights.
	current->next_runway = next->next_runway;//corrects the linked lists pointers.
	free(next);//deltes the runways nodes
	return SUCCESS;
}

/*************************************************************************************
// function name :  addFlightToAirport
// Description   :	Function that adds a flight to the coorect runway in the airport.
// Parameters    :	Flight number,the type of the Flight, the destenetion of the flight,
if the flight is an emergency.
// Return value  :	sucsess if the function was able to add the flight to the airport, 
falirue else.
//**************************************************************************************/
Result addFlightToAirport(int Flight_num, FlightType Typef, char* Destenation, BOOL Emergency)
{
	if (Airport == NULL)//checks if the airport has no runways.
		return FAILURE;
	BOOL same_num = FALSE;//a flag that represents if there are 2 runways or more that have the same minimun of flights.
	Node_runway* min = NULL;// a pointer to the runway with the least number of flights
	Node_runway* curr = Airport;
	if (curr->next_runway == NULL)//if there is only one runway in the airport.
	{
		if (getRunwayType(curr->runway) == Typef)// checks if the runway has the same type as the flight we want to add.
		{
			min = curr;
		}
		else
			return FAILURE;
	}
	while (curr != NULL) //loops over the runway list and sets a pointer to the runway with the minium number of flights.
	{
		if (isFlightExists(curr->runway, Flight_num))//checks if there is already a flight in the airport with the same number.
			return FAILURE;
		if (getRunwayType(curr->runway) != Typef) // adavnces the curr poniter in the runway dosent have the same tyoe as the flight.
		{
			curr = curr->next_runway;
			continue;
		}
		if (min == NULL)//if there is no minimum runway set yet.
			min = curr;
		else
		{
			if (getFlightNum(curr->runway) < getFlightNum(min->runway)) // if we found a runway with less flights in it.
			{
				same_num = FALSE;//flags that we have a minimum runway.
				min = curr;//points to the minimum runway.
			}
			else if (getFlightNum(curr->runway) == getFlightNum(min->runway))//if there are two runways with the same number of minimum flights
				same_num = TRUE;
		}
		curr = curr->next_runway;//advances the loop index
	}
	if (same_num == TRUE)//if we found two or more runways with the same number of minimum flights.
	{
		int min_flights = getFlightNum(min->runway);//sets min_flights to the number of flights in the minimum runways
		curr = Airport;
		while (curr != NULL)//loops over all the runways in the airport.
		{
			if (getRunwayType(curr->runway) != Typef)//if the runway is not from the same type as the flight.
			{
				curr = curr->next_runway;
				continue;
			}
			if (getFlightNum(curr->runway) == min_flights &&
				getRunwayID(curr->runway) < getRunwayID(min->runway))//checks if the runways has the minimum flight number and the minimum id.
				min = curr;//sets the pointer min to the runway.
			curr = curr->next_runway;//advances the loops index;
		}
	}
	if (min == NULL)//if there is no matching runway to add the flight to.
		return FAILURE;
	PFlight temp = createFlight(Flight_num, Typef, Destenation, Emergency);//creats the new flight we want to add.
	if (temp == NULL)
		return FAILURE;
	return addFlight(min->runway, temp);//adds the flight to the runway.  
}

/*************************************************************************************
// function name :  departFromAirport
// Description   :	Function that removes a flight from the airport according to rules.
// Parameters    :	none.
// Return value  :	sucsess if the function was able to remove a flight, falirue else.
//**************************************************************************************/
Result departFromAirport()
{
	if (Airport == NULL)//checks if there are no runways in the airport.
		return	FAILURE;
	int minId = MAX_ID, maxEm = 0, maxAll = 0; //3 counters that we use to decide from what runway to depart.
	Node_runway *temp = Airport;//a pointer to the runways linked list.
	PRunway min_Id_Runway = NULL, max_Em_Runway = NULL, max_Flight_Runway = NULL;//pointers to the diffrent runways.
	BOOL sameEM = FALSE, sameMax = FALSE;//flags to tell if there are more than two runways with the same maximum.
	while (temp != NULL)//loops over all the runways in the airport.
	{
		if (getEmergencyNum(temp->runway) > maxEm)//if the runways has the maximum number of emergency flight.
		{
			maxEm = getEmergencyNum(temp->runway);//sets the new maximum of emergency flights.
			max_Em_Runway = temp->runway;//points to the maximum number of emergency runway.
			sameEM = FALSE;//flag if the there is a maximum emergency.
		}
		else if (getEmergencyNum(temp->runway) == maxEm)//if there are 2 or more runways with the same number of emergency flights.
			sameEM = TRUE;

		if (getFlightNum(temp->runway) > maxAll)//if the runways has the maximum number flights.
		{
			maxAll = getFlightNum(temp->runway);//sets the new maximum of flights.
			max_Flight_Runway = temp->runway;//points to the maximum number flights runway.
			sameMax = FALSE;//flag if the there is a maximum flight number.
		}
		else if (getFlightNum(temp->runway) == maxAll)//if there are 2 or more runways with the same number of flights.
			sameMax = TRUE;

		if (getRunwayID(temp->runway) < minId && getFlightNum(temp->runway)!=0)//finds the minimum runway id that has flights in it.
		{
			minId = getRunwayID(temp->runway);
			min_Id_Runway = temp->runway;
		}

		temp = temp->next_runway;//advances the while loop index.
	}
	if (sameEM == FALSE && maxEm!=0)//checks if there is one runway with maximum of emegency flights waiting.
		return depart(max_Em_Runway);//departs a flight from the runway.
	if (sameMax == FALSE && maxAll!=0)//checks if there is one runway with a maximum number of flights.
		return depart(max_Flight_Runway);//departs a flight from the runway.
	return depart(min_Id_Runway);//departs a flights from the minimum id runway.
}

/*************************************************************************************
// function name :  changeDest
// Description   :	A function that changes the destenation for all the flights with
a specsific destenation to a new one.
// Parameters    :	old destenation, new destenation.
// Return value  :	sucsess if the function was able to change the flights destenation 
,faliure if it didnt.
//**************************************************************************************/
Result changeDest(char* Destenation_old, char* Destenation_new)
{
	int i=0;
	Node_runway* temp_runway = Airport;
	if (strlen(Destenation_old) != 3 || strlen(Destenation_new) != 3)//checks if the destenations are valid.
		return FAILURE;
	for (i = 0; i < 3; i++)
	{
		if (Destenation_old[i] < 'A' || Destenation_old[i] > 'Z' ||
			Destenation_new[i] < 'A' || Destenation_new[i] > 'Z')
			return FAILURE;
	}
	while (temp_runway != NULL)
	{
		changeDestInRunway(temp_runway->runway, Destenation_new, Destenation_old);//calls the runway change destenation.
		temp_runway = temp_runway->next_runway;
	}
	return SUCCESS;
}

/*************************************************************************************
// function name :  delay
// Description   :	Function delays all the flights that are to a spesific destenation.
// Parameters    :	destenation.
// Return value  :	sucsess if the function was able to delay the flights, faliure if it didnt.
//**************************************************************************************/
Result delay(char* Destenation)
{
	int i=0;
	Node_runway* temp_runway = Airport;
	if (strlen(Destenation) != 3 )
		return FAILURE;
	for (i = 0; i < 3; i++)//checks if the destenation is valid.
	{
		if (Destenation[i] < 'A' || Destenation[i] > 'Z' )
			return FAILURE;
	}
	while (temp_runway != NULL)
	{
		if (delayRunway(temp_runway->runway, Destenation) == FAILURE)//calls the delay runway function.
			return FAILURE;
		temp_runway = temp_runway->next_runway;
	}
	return SUCCESS;
}

/*************************************************************************************
// function name :  printAirport
// Description   :	prints to the screen the airport status with all the runways and 
all the flights in the runways.
// Parameters    :	none.
// Return value  :	none.
//**************************************************************************************/
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


/*************************************************************************************
// function name :  destroyAirport
// Description   :	Function that deletes all the runways in the airport and all
the flights in the airport..
// Parameters    :	none.
// Return value  :	none.
//**************************************************************************************/
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
