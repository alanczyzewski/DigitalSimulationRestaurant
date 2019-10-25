#pragma once
#include "event.h"
class ServedDrinks : public Event
{
public:
	ServedDrinks(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

