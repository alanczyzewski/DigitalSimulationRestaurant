#pragma once
#include "event.h"
class ConsumptionEnd : public Event
{
public:
	ConsumptionEnd(Restaurant &, Client *);
	void Execute() override;
};

