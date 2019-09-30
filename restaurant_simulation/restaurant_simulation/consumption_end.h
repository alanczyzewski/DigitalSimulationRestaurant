#pragma once
#include "event.h"
class ConsumptionEnd : public Event
{
public:
	ConsumptionEnd(Restaurant *, EventList *, Client *);
	~ConsumptionEnd();
	void Execute() override;
};

