#include "stdafx.h"
#include "consumption_end.h"
#include "checkout_service_end.h"


ConsumptionEnd::ConsumptionEnd(Restaurant & restaurant, Client * client) : Event("ConsumptionEnd", restaurant, client)
{
	SetTime(GetClient()->GetTimeConsumption());
}

void ConsumptionEnd::Execute()
{
	/*
	1. Leave table and add people to free table
	2. Place the client at the end of the queue to the checkout.
	//1
	restaurant_->DeleteClientFromBuffet(client_);
	//2
	Client * client = nullptr;
	while(restaurant_->AddToBuffetIfPossible(client))
	{
	event_list_->AddToEventList(new BuffetServiceEnd(restaurant_, event_list_, client));
	//GetEventList()->Schedule(new BuffetServiceEnd(this, client));
	}
	//3
	if(restaurant_->AddToCheckoutQueue(client_))
	{
	event_list_->AddToEventList(new CheckoutServiceEnd(restaurant_, event_list_, client_));
	}
	*/
	//1
	GetRestaurant()->DeleteClientFromTable(GetClient());
	//2
	if (GetRestaurant()->AddToCheckoutQueue(GetClient()))
	{
		GetRestaurant()->GetEventList()->AddToEventList(new CheckoutServiceEnd(*GetRestaurant(), GetClient()));
	}
}
