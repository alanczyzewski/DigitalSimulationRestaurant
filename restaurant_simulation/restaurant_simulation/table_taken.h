#pragma once
#include "event.h"
class TableTaken : public Event
{
public:
	TableTaken(Restaurant *, EventList *, Client *);
	void Execute() override;
};

