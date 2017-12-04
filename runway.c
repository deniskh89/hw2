#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flight.h"
#include "runway.h"
#include "ex2.h"



typedef struct node
{
	PFlight flight;//maybe not pointer
	struct node* next_flight;
} Node;

Result destroy_aux(Node *head, int flight_num,PRunway runway);

typedef struct runway_t
{
	int Runway_ID,Emr_num,Reg_num;
	FlightType Type;
	Node* Emr_list_head;
	Node* Reg_list_head;
} Runway;

PRunway createRunway(int runway_num, FlightType runway_type)
{
	if (runway_num<1 || runway_num>MAX_ID)
		return NULL;
	PRunway temp = (PRunway)malloc(sizeof(Runway));
	if (temp == NULL)
		return NULL;
	temp->Runway_ID = runway_num;
	temp->Type = runway_type;
	temp->Emr_list_head = NULL;
	temp->Emr_num = 0;
	temp->Reg_list_head = NULL;
	temp->Reg_num = 0;
	return temp;
}

void destroyRunway(PRunway runway)
{
	if (runway == NULL)
		return;
	while (runway->Reg_list_head != NULL || runway->Emr_list_head != NULL)
		depart(runway);
	free(runway);
	return;
}

Result addFlight(PRunway runway, PFlight flight)
{
	Node *temp=NULL;
	if (runway->Type != getFlightType(flight))
		return FAILURE;
	if (getFlightEmr(flight) == TRUE)
	{
		temp = runway->Emr_list_head;
		runway->Emr_num=runway->Emr_num++;
	}
	else
	{
		temp = runway->Reg_list_head;
		runway->Reg_num++;
	}
	if (temp != NULL)
	{
		while (temp->next_flight != NULL)
		{
			temp = temp->next_flight;
		}
		temp->next_flight = (Node*)malloc(sizeof(Node));
		if (temp->next_flight == NULL)
			return FAILURE;
		temp->next_flight->flight = flight;
		temp->next_flight->next_flight = NULL;
		return SUCCESS;
	}
	else     // if it is the first flight
	{
		if (getFlightEmr(flight) == TRUE)
		{
			runway->Emr_list_head = (Node*)malloc(sizeof(Node));
			if (runway->Emr_list_head == NULL)
				return FAILURE;
			runway->Emr_list_head->flight = flight;
			runway->Emr_list_head->next_flight = NULL;
			return SUCCESS;
		}
		else
		{
			runway->Reg_list_head = (Node*)malloc(sizeof(Node));
			if (runway->Reg_list_head == NULL)
				return FAILURE;
			runway->Reg_list_head->flight = flight;
			runway->Reg_list_head->next_flight = NULL;
			return SUCCESS;
		}
	}
}

BOOL isFlightExists(PRunway runway, int flight_num)
{
	if (flight_num<1 || flight_num>MAX_ID || runway == NULL)
		return FALSE;
	Node *temp = runway->Emr_list_head;
	while (temp!=NULL ) //&& temp->next_flight != NULL
	{
		if (getFlightId(temp->flight) == flight_num)
			return TRUE;
		temp = temp->next_flight;
	}
	temp = runway->Reg_list_head;
	while (temp != NULL ) //&& temp->next_flight != NULL
	{
		if (getFlightId(temp->flight) == flight_num)
			return TRUE;
		temp = temp->next_flight;
	}
	return FALSE;
}

int getFlightNum(PRunway runway)
{
	if (runway == NULL)
		return -1;
	return (runway->Emr_num + runway->Reg_num);
}

int getEmergencyNum(PRunway runway)
{
	if (runway == NULL)
		return -1;
	return runway->Emr_num;
}

Result destroy_aux(Node *head, int flight_num,PRunway runway)
{
	Node *current;
	Node *next;
	current = head;
	if (current == NULL)
		return FAILURE;
	next = current->next_flight;
	if (getFlightId(current->flight) == flight_num)
	{
		if (getFlightEmr(current->flight) == TRUE)
		{
		  runway->Emr_num--;
			runway->Emr_list_head = next;
		}
		if (getFlightEmr(current->flight) == FALSE)
		{
			runway->Reg_num--;
			runway->Reg_list_head = next;
		}
		destroyFlight(current->flight);
		free(current);
		if(getEmergencyNum(runway)==0)
			runway->Emr_list_head=NULL;
		if(getFlightNum(runway)-getEmergencyNum(runway)==0)
			runway->Reg_list_head=NULL;
		return SUCCESS;
	}
	if (next == NULL)
		return FAILURE;
	while (getFlightId(next->flight) != flight_num)
	{
		current = next;
		next = next->next_flight;
		if (next == NULL)
			return FAILURE;
	}
	if (getFlightEmr(next->flight) == TRUE)
			runway->Emr_num--;
	if (getFlightEmr(next->flight) == FALSE)
		 	runway->Reg_num--;
	destroyFlight(next->flight);
	current->next_flight = next->next_flight;
	free(next);
	if(getEmergencyNum(runway)==0)
			runway->Emr_list_head=NULL;
	if(getFlightNum(runway)-getEmergencyNum(runway)==0)
			runway->Reg_list_head=NULL;
	return SUCCESS;
}

Result removeFlight(PRunway runway, int flight_num)
{
	if (flight_num<1 || flight_num>MAX_ID || runway == NULL)
		return FAILURE;
	return (destroy_aux(runway->Emr_list_head, flight_num, runway) ||
		destroy_aux(runway->Reg_list_head, flight_num, runway));
}

Result depart(PRunway runway)
{
	if(runway == NULL)
		return FAILURE;
	Node *temp = runway->Emr_list_head;
	if (temp != NULL)
	{
		return destroy_aux(temp, getFlightId(temp->flight),runway);
	}
	temp = runway->Reg_list_head;
	if (temp != NULL)
	{
		return destroy_aux(temp, getFlightId(temp->flight),runway);
	}
	return FAILURE;
}

int getRunwayID(PRunway runway)
{
	if (runway == NULL)
		return -1;
	return runway->Runway_ID;
}

FlightType getRunwayType(PRunway runway)
{
	if (runway == NULL)
		return DOMESTIC;
	return runway->Type;
}

void printRunway(PRunway runway)
{
	if (runway == NULL)
		return;
	if (getRunwayType(runway) == INTERNATIONAL)
		printf("Runway %d international\n", getRunwayID(runway));
	else
		printf("Runway %d domestic\n", getRunwayID(runway));
	int temp = getFlightNum(runway);
	printf("%d flights are waiting:\n", temp);
	Node *current = runway->Emr_list_head;
	while (current != NULL)
	{
		printFlight(current->flight);
		current = current->next_flight;
	}
	current = runway->Reg_list_head;
	while (current != NULL)
	{
		printFlight(current->flight);
		current = current->next_flight;
	}
}

void changeDestInRunway(PRunway runway, char* newDest, char* oldDest)
{
	if ( runway == NULL)
		return ;
	Node *temp = runway->Emr_list_head;
	while (temp != NULL)
	{
		if (!strcmp(getFlightDes(temp->flight), oldDest))
			setFlightDes(temp->flight, newDest);
		temp = temp->next_flight;
	}
	temp = runway->Reg_list_head;
	while (temp != NULL)
	{
		if (!strcmp(getFlightDes(temp->flight), oldDest))
			setFlightDes(temp->flight, newDest);
		temp = temp->next_flight;
	}
	return;
}
Result delayRunway(PRunway runway, char* Dest)
{
	int i=0;
	if (runway == NULL)
		return FAILURE;
	if (runway->Emr_list_head == NULL && runway->Reg_list_head == NULL)
		return SUCCESS;
	Node* temp;
	temp = runway->Emr_list_head;
	int EM = 0;
	if (temp != NULL)
	{
		EM = getEmergencyNum(runway);
		for (i = 0; i < EM; i++)
		{
			Node* remover_Flight = temp->next_flight;
			if (!strcmp(getFlightDes(temp->flight), Dest))
			{
				PFlight flight_temp = createFlight(getFlightId(temp->flight),
											getFlightType(temp->flight),
											Dest, getFlightEmr(temp->flight));
				if (removeFlight(runway, getFlightId(temp->flight)) == FAILURE)
					return FAILURE;
				if (addFlight(runway, flight_temp) == FAILURE)
					return FAILURE;
			}
			temp = remover_Flight;
		}
	}
	temp = (Node*)(runway->Reg_list_head);
	int REG;
	if (temp != NULL)
	{
		REG = (getFlightNum(runway)-EM);
		for (i = 0; i < REG; i++)
		{
			Node* remover_Flight = temp->next_flight;
			if (!strcmp(getFlightDes(temp->flight), Dest))
			{
				PFlight flight_temp = createFlight(getFlightId(temp->flight),
					getFlightType(temp->flight),
					Dest, getFlightEmr(temp->flight));
				if (removeFlight(runway, getFlightId(temp->flight)) == FAILURE)
					return FAILURE;
				if (addFlight(runway, flight_temp) == FAILURE)
					return FAILURE;
			}
			temp = remover_Flight;
		}
	}
	return SUCCESS;
}
