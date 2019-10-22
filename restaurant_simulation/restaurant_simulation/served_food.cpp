#include "stdafx.h"
#include "served_food.h"
#include "consumption_end.h"


ServedFood::ServedFood(Restaurant & restaurant, Client * client) : Event("ServedDrinks", restaurant, client)
{
	SetTime(GetClient()->GetTimeServiceMeals());
}

void ServedFood::Execute()
{
	GetRestaurant()->GetEventList()->AddToEventList(new ConsumptionEnd(*GetRestaurant(), GetClient()));
	GetRestaurant()->StartConsumption(GetClient());
}
