#include "stdafx.h"
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "table_taken.h"
#include "generators.h"
#include "statistics.h"


ClientArrival::ClientArrival(Restaurant * restaurant, EventList * event_list)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	event_name_ = "ClientArrival";
	event_time_ = restaurant_->simulation_time_ + Generators::Normal(Generators::mi_a_, Generators::sigma_a_);
	client_ = new Client();
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
	double random = Generators::Uniform();
	if (random < 0.5) //buffet
	{
		if (restaurant_->AddToBuffetQueue(client_)) //if true: client went to buffet, not queue
		{
			event_list_->AddToEventList(new BuffetServiceEnd(restaurant_, event_list_, client_));
		}
	}
	else //tables
	{
		if (restaurant_->AddToTableQueue(client_)) //if true: client went to table, not queue
		{
			Statistics::AddTimeWaitingTable(0);
			event_list_->AddToEventList(new TableTaken(restaurant_, event_list_, client_));
		}
	}
	//3
	event_list_->AddToEventList(new ClientArrival(restaurant_, event_list_));
}
