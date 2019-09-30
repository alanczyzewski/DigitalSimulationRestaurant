#include "stdafx.h"
#include "served_drinks.h"


ServedDrinks::ServedDrinks(Restaurant * restaurant, EventList * event_list, Client * client)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	client_ = client;
	event_name_ = "ServedDrinks";
	event_time_ = restaurant_->simulation_time_ + client_->GetTimeServiceDrinks();
}


ServedDrinks::~ServedDrinks()
{}

void ServedDrinks::Execute()
{
	restaurant_->AddToMealsQueue(client_);
}
