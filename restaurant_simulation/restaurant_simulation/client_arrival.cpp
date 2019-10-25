#include "stdafx.h"
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "table_taken.h"
#include "generators.h"
#include "statistics.h"


ClientArrival::ClientArrival(Restaurant & restaurant) : Event("ClientArrival", restaurant, static_cast<std::shared_ptr<Client>>(new Client()))
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
	if (random < 0.5)
		restaurant_->ChooseBuffet(client_);
	else
		restaurant_->ChooseTable(client_);
	//3
	restaurant_->event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ClientArrival(*restaurant_)));
}
