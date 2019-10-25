#include "stdafx.h"
#include "served_food.h"
#include "consumption_end.h"


ServedFood::ServedFood(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("ServedDrinks", restaurant, client)
{
	SetTime(client_->GetTimeServiceMeals());
}

void ServedFood::Execute()
{
	restaurant_->event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ConsumptionEnd(*restaurant_, client_)));
	restaurant_->StartConsumption();
}
