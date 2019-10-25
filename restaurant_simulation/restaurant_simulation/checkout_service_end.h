#pragma once
#include "event.h"
class CheckoutServiceEnd : public Event
{
public:
	CheckoutServiceEnd(Restaurant &, std::shared_ptr<Client>);
	void Execute() override;
};

