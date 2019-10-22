#include "stdafx.h"
#include "served_drinks.h"


ServedDrinks::ServedDrinks(Restaurant & restaurant, Client * client) : Event("ServedDrinks", restaurant, client)
{
	SetTime(GetClient()->GetTimeServiceDrinks());
}

void ServedDrinks::Execute()
{
	GetRestaurant()->AddToMealsQueue(GetClient());
}
