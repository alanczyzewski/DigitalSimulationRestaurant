#pragma once
#include "event.h"
#include "event_list.h"
#include "restaurant.h"

class ClientArrival : public Event
{
public:
	ClientArrival(Restaurant &);
	void Execute() override;
};

