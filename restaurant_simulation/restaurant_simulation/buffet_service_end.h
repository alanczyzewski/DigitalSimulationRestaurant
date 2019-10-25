#pragma once
#include "event.h"
#include "event_list.h"
#include "restaurant.h"
#include "client.h"

class BuffetServiceEnd : public Event
{
public:
	BuffetServiceEnd(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

