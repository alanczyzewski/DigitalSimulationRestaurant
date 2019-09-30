#include "stdafx.h"
#include "checkout_service_end.h"


CheckoutServiceEnd::CheckoutServiceEnd(Restaurant * restaurant, EventList * event_list, Client * client)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	client_ = client;
	event_name_ = "CheckoutServiceEnd";
	event_time_ = restaurant_->simulation_time_ + client_->GetTimeCheckout();
}

CheckoutServiceEnd::~CheckoutServiceEnd(){}

void CheckoutServiceEnd::Execute()
{
	/*
	1. Release the checkout and delete the client from system
	2. Add people to free checkout
	*/
	restaurant_->DeleteClientFromSystem(client_);
	restaurant_->AddToCheckoutIfPossible();
}
