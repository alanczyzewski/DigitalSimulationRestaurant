#pragma once
#include "event.h"
class ConsumptionEnd : public Event
{
public:
	ConsumptionEnd(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

