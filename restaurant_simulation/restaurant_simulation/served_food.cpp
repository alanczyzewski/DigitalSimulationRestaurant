#include "stdafx.h"
#include "served_food.h"
#include "consumption_end.h"


ServedFood::ServedFood(Restaurant & restaurant, Client * client) : Event("ServedDrinks", restaurant, client)
{
	SetTime(client_->GetTimeServiceMeals());
}

void ServedFood::Execute()
{
	restaurant_->GetEventList()->AddToEventList(new ConsumptionEnd(*restaurant_, client_));
	restaurant_->StartConsumption(client_);
}
