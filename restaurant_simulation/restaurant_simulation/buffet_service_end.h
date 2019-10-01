#pragma once
#include "event.h"
#include "event_list.h"
#include "restaurant.h"
#include "client.h"

class BuffetServiceEnd : public Event
{
public:
	BuffetServiceEnd(Restaurant *,EventList *,Client *);
	void Execute() override;
};

