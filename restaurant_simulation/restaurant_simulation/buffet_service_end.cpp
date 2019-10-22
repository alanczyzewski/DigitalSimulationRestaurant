#include "stdafx.h"
#include "buffet_service_end.h"
#include "checkout_service_end.h"


BuffetServiceEnd::BuffetServiceEnd(Restaurant & restaurant, Client * client) : Event("BuffetServiceEnd", restaurant, client)
{
	SetTime(GetClient()->GetTimeBuffet());
}

void BuffetServiceEnd::Execute()
{
	/*
	1. Leave place at the buffet and
	2. Add people to free seats
	3. Place the client at the end of the queue to the checkout.
	*/
	//1
	GetRestaurant()->DeleteClientFromBuffet(GetClient());
	//2
	GetRestaurant()->AddToBuffetIfPossible();
	//3
	if(GetRestaurant()->AddToCheckoutQueue(GetClient()))
	{
		GetRestaurant()->GetEventList()->AddToEventList(new CheckoutServiceEnd(*GetRestaurant(), GetClient()));
	}
}
