#include "stdafx.h"
#include "table_taken.h"
#include "served_drinks.h"
#include "statistics.h"


TableTaken::TableTaken(Restaurant * restaurant, EventList * event_list, Client * client)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	client_ = client;
	event_name_ = "TableTaken";
	event_time_ = restaurant_->simulation_time_ + Generators::s_;
}

TableTaken::~TableTaken(){}

void TableTaken::Execute()
{
	if(restaurant_->AddToDrinksQueue(client_)) //if waiter is free
	{
		Statistics::AddTimeWaitingWaiter(0);
		event_list_->AddToEventList(new ServedDrinks(restaurant_,event_list_,client_)); //Plan next event
	}
}
