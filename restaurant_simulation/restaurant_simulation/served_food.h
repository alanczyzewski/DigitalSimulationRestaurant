#pragma once
#include "event.h"
class ServedFood : public Event
{
public:
	ServedFood(Restaurant *, EventList *, Client *);
	~ServedFood();
	void Execute() override;
};

