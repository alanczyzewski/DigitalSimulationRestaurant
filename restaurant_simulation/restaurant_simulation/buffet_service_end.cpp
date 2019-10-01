#include "stdafx.h"
#include "buffet_service_end.h"
#include "checkout_service_end.h"


BuffetServiceEnd::BuffetServiceEnd(Restaurant * restaurant, EventList * event_list, Client * client)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	client_ = client;
	event_name_ = "BuffetServiceEnd";
	event_time_ = restaurant_->simulation_time_ + client_->GetTimeBuffet();
}

void BuffetServiceEnd::Execute()
{
	/*
	1. Leave place at the buffet and
	2. Add people to free seats
	3. Place the client at the end of the queue to the checkout.
	*/
	//1
	restaurant_->DeleteClientFromBuffet(client_);
	//2
	restaurant_->AddToBuffetIfPossible();
	//3
	if(restaurant_->AddToCheckoutQueue(client_))
	{
		event_list_->AddToEventList(new CheckoutServiceEnd(restaurant_, event_list_, client_));
	}
}
