#pragma once
#include "event.h"
class ServedFood : public Event
{
public:
	ServedFood(Restaurant &, Client *);
	void Execute() override;
};

