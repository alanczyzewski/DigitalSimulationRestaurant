#pragma once
#include <string>
#include "event_list.h"
#include "client.h"
#include "restaurant.h"

class Restaurant;
class EventList;

class Event
{
public:
	Event() = default;
	//Event(Restaurant *, EventList *);
	//~Event();
	void virtual Execute() = 0;
	std::string GetName();
	std::string event_name_;
	double event_time_;
	Restaurant * restaurant_;
	EventList * event_list_;
	Client * client_;
};

