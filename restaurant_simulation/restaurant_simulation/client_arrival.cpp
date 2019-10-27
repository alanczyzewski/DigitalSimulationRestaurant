#include "stdafx.h"
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "table_taken.h"
#include "generators.h"

ClientArrival::ClientArrival(Restaurant & restaurant) : Event("ClientArrival", restaurant, static_cast<std::shared_ptr<Client>>(new Client()))
{
	SetTime(generators::Normal(generators::mi_a, generators::sigma_a));
}

void ClientArrival::Execute()
{
	restaurant_->AddClientToSystem(client_);
	if (generators::Uniform() < generators::p)
		restaurant_->ChooseBuffet(client_);
	else
		restaurant_->ChooseTable(client_);
	restaurant_->event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ClientArrival(*restaurant_)));
}
