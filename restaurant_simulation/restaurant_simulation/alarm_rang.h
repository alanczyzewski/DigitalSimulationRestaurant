#pragma once
#include "event.h"
class AlarmRang : public Event
{
public:
	AlarmRang(Restaurant *, EventList *);
	void Execute() override;
};

