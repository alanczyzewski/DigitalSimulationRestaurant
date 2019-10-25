#include "stdafx.h"
#include "alarm_rang.h"
#include "generators.h"


AlarmRang::AlarmRang(Restaurant & restaurant) : Event("AlarmRang", restaurant)
{
	SetTime(generators::Normal(generators::mi_e_, generators::sigma_e_));
}


void AlarmRang::Execute()
{
	restaurant_->Alarm();
	restaurant_->event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new AlarmRang(*GetRestaurant())));
}
