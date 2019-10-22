#include "stdafx.h"
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "table_taken.h"
#include "generators.h"
#include "statistics.h"


ClientArrival::ClientArrival(Restaurant & restaurant) : Event("ClientArrival", restaurant, new Client())
{
	SetTime(generators::Normal(generators::mi_a_, generators::sigma_a_));
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
	restaurant_->AddClientToSystem(client_);
	//2
	double random = generators::Uniform();
	if (random < 0.5) //buffet
	{
		if (restaurant_->AddToBuffetQueue(client_)) //if true: client went to buffet, not queue
		{
			restaurant_->GetEventList()->AddToEventList(new BuffetServiceEnd(*restaurant_, client_));
		}
	}
	else //tables
	{
		if (restaurant_->AddToTableQueue(client_)) //if true: client went to table, not queue
		{
			statistics::AddTimeWaitingTable(0);
			restaurant_->GetEventList()->AddToEventList(new TableTaken(*restaurant_, client_));
		}
	}
	//3
	restaurant_->GetEventList()->AddToEventList(new ClientArrival(*restaurant_));
}
