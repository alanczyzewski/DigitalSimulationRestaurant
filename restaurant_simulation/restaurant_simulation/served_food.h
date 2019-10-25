#pragma once
#include "event.h"
class ServedFood : public Event
{
public:
	ServedFood(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

