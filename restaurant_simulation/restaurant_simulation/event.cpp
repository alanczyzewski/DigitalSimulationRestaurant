#include "stdafx.h"
#include "event.h"

void Event::SetTime(double time) { event_time_ = restaurant_->GetTime() + time; }

bool operator<(const Event & event1, const Event & event2)
{
	return (event1.event_time_ < event2.event_time_);
}

bool operator>(const Event & event1, const Event & event2)
{
	return (event1.event_time_ > event2.event_time_);
}

std::ostream & operator<<(std::ostream & os, const Event & eve)
{
	os << "Time: ";
	os.width(13);
	os << std::left << eve.event_time_ << " Name: ";
	os.width(18);
	os << eve.event_name_;
	if (eve.client_)
	{
		os << "  " << *(eve.client_);
	}
	return os;
}