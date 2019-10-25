#pragma once
#include "event.h"
class TableTaken : public Event
{
public:
	TableTaken(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

