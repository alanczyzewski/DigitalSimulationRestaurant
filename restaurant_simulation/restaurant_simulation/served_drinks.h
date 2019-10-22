#pragma once
#include "event.h"
class ServedDrinks : public Event
{
public:
	ServedDrinks(Restaurant &, Client *);
	void Execute() override;
};

