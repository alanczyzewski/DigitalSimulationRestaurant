#include "stdafx.h"
#include "alarm_rang.h"
#include "generators.h"


AlarmRang::AlarmRang(Restaurant * restaurant, EventList * event_list)
{
	restaurant_ = restaurant;
	event_list_ = event_list;
	event_name_ = "AlarmRang";
	event_time_ = restaurant_->simulation_time_ + Generators::Normal(Generators::mi_e_, Generators::sigma_e_);
}


void AlarmRang::Execute()
{
	restaurant_->Alarm();
	event_list_->AddToEventList(new AlarmRang(restaurant_, event_list_));
}
