#pragma once
#include "event.h"
class ServedFood : public Event
{
public:
	ServedFood(Restaurant *, EventList *, Client *);
	void Execute() override;
};

