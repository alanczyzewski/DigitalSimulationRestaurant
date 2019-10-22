#pragma once
#include "event.h"
class TableTaken : public Event
{
public:
	TableTaken(Restaurant &, Client *);
	void Execute() override;
};

