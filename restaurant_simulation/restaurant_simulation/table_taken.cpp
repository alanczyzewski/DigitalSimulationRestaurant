#include "stdafx.h"
#include "table_taken.h"
#include "served_drinks.h"
#include "statistics.h"


TableTaken::TableTaken(Restaurant & restaurant, Client * client) : Event("TableTaken", restaurant, client)
{
	SetTime(Generators::s_);
}

void TableTaken::Execute()
{
	if(GetRestaurant()->AddToDrinksQueue(GetClient())) //if waiter is free
	{
		Statistics::AddTimeWaitingWaiter(0);
		GetRestaurant()->GetEventList()->AddToEventList(new ServedDrinks(*GetRestaurant(), GetClient())); //Plan next event
	}
}
