#include "stdafx.h"
#include "table_taken.h"
#include "served_drinks.h"
#include "statistics.h"


TableTaken::TableTaken(Restaurant & restaurant, Client * client) : Event("TableTaken", restaurant, client)
{
	SetTime(generators::s_);
}

void TableTaken::Execute()
{
	if(restaurant_->AddToDrinksQueue(client_)) //if waiter is free
	{
		statistics::AddTimeWaitingWaiter(0);
		restaurant_->GetEventList()->AddToEventList(new ServedDrinks(*restaurant_, client_)); //Plan next event
	}
}
