#include "stdafx.h"
#include "checkout_service_end.h"


CheckoutServiceEnd::CheckoutServiceEnd(Restaurant & restaurant, Client * client) : Event("CheckoutServiceEnd", restaurant, client)
{
	SetTime(GetClient()->GetTimeCheckout());
}

void CheckoutServiceEnd::Execute()
{
	/*
	1. Release the checkout and delete the client from system
	2. Add people to free checkout
	*/
	GetRestaurant()->DeleteClientFromSystem(GetClient());
	GetRestaurant()->AddToCheckoutIfPossible();
}
