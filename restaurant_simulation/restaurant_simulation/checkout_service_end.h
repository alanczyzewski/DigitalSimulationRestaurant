#pragma once
#include "event.h"
class CheckoutServiceEnd : public Event
{
public:
	CheckoutServiceEnd(Restaurant *, EventList *, Client *);
	~CheckoutServiceEnd();
	void Execute() override;
};

