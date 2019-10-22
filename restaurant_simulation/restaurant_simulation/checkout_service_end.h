#pragma once
#include "event.h"
class CheckoutServiceEnd : public Event
{
public:
	CheckoutServiceEnd(Restaurant &, Client *);
	void Execute() override;
};

