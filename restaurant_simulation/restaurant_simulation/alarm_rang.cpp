#include "stdafx.h"
#include "alarm_rang.h"
#include "generators.h"


AlarmRang::AlarmRang(Restaurant & restaurant) : Event("AlarmRang", restaurant)
{
	SetTime(Generators::Normal(Generators::mi_e_, Generators::sigma_e_));
}


void AlarmRang::Execute()
{
	GetRestaurant()->Alarm();
	GetRestaurant()->GetEventList()->AddToEventList(new AlarmRang(*GetRestaurant()));
}
