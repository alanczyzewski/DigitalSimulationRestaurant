#pragma once
#include "event.h"
class AlarmRang : public Event
{
public:
	AlarmRang(Restaurant &);
	void Execute() override;
};

