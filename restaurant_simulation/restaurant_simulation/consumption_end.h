#pragma once
#include "event.h"
class ConsumptionEnd : public Event
{
public:
	ConsumptionEnd(Restaurant *, EventList *, Client *);
	void Execute() override;
};

