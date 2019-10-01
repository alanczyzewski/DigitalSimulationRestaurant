#pragma once
#include "event.h"
class ServedDrinks : public Event
{
public:
	ServedDrinks(Restaurant *, EventList *, Client *);
	void Execute() override;
};

