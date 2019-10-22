#include "stdafx.h"
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "table_taken.h"
#include "generators.h"
#include "statistics.h"


ClientArrival::ClientArrival(Restaurant & restaurant) : Event("ClientArrival", restaurant, new Client())
{
	SetTime(Generators::Normal(Generators::mi_a_, Generators::sigma_a_));
}

void ClientArrival::Execute()
{
	/*
	1. Add Client to system
	2. Buffet(1) or Table(2)? (50/50)
	2.1 Place the client at the end of the queue to the buffet.
	2.2 Place the client at the end of the queue to the table.
	3. Plan new event (ClientArrival)
	*/
	//1
	GetRestaurant()->AddClientToSystem(GetClient());
	//2
	double random = Generators::Uniform();
	if (random < 0.5) //buffet
	{
		if (GetRestaurant()->AddToBuffetQueue(GetClient())) //if true: client went to buffet, not queue
		{
			GetRestaurant()->GetEventList()->AddToEventList(new BuffetServiceEnd(*GetRestaurant(), GetClient()));
		}
	}
	else //tables
	{
		if (GetRestaurant()->AddToTableQueue(GetClient())) //if true: client went to table, not queue
		{
			Statistics::AddTimeWaitingTable(0);
			GetRestaurant()->GetEventList()->AddToEventList(new TableTaken(*GetRestaurant(), GetClient()));
		}
	}
	//3
	GetRestaurant()->GetEventList()->AddToEventList(new ClientArrival(*GetRestaurant()));
}
