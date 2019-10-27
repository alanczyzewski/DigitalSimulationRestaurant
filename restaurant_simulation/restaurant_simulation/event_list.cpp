#include "stdafx.h"
#include <iostream>
#include "event_list.h"


EventList::EventList(){}
EventList::~EventList(){}

void EventList::AddToEventList(std::shared_ptr<Event> eve)
{
	if (!(event_list_.empty())) //if not empty
	{
		auto iterator_list = event_list_.begin();
		while (iterator_list != event_list_.end())
		{
			if (*eve < **(iterator_list))
				break;
			else
				std::advance(iterator_list, 1);
		}
		event_list_.insert(iterator_list, eve);
	}
	else
		event_list_.push_back(eve);
}

std::ostream & operator<<(std::ostream & os, const EventList & ev)
{
	os << "Event List:\n";
	if (!(ev.event_list_.empty()))
		for (auto &i : ev.event_list_)
			os << *i << std::endl;
	return os;
}

std::shared_ptr<Event> EventList::First()
{
	if (!(event_list_.empty()))
		return event_list_.front();
	return nullptr;
}
void EventList::DeleteFirst()
{
	if (First())
		event_list_.pop_front();
}
