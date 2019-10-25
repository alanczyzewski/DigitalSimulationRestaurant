#include "stdafx.h"
#include "served_drinks.h"


ServedDrinks::ServedDrinks(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("ServedDrinks", restaurant, client)
{
	SetTime(client_->GetTimeServiceDrinks());
}

void ServedDrinks::Execute()
{
	restaurant_->AddToMealsQueue(client_);
}
