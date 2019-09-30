#include "stdafx.h"
#include "served_food.h"
#include "consumption_end.h"


ServedFood::ServedFood(Restaurant * restaurant, EventList * event_list, Client * client)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	client_ = client;
	event_name_ = "ServedFood";
	event_time_ = restaurant_->simulation_time_ + client_->GetTimeServiceMeals();
}

ServedFood::~ServedFood()
{}

void ServedFood::Execute()
{
	event_list_->AddToEventList(new ConsumptionEnd(restaurant_, event_list_, client_));
	restaurant_->StartConsumption(client_);
}
