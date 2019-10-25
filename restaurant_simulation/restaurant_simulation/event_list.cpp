#include "stdafx.h"
#include <iostream>
#include "event_list.h"
#include "alarm_rang.h"


EventList::EventList(){}

EventList::~EventList()
{/*
	while (!(event_list_.empty()))
	{
		event_list_.pop_front();
	}
	*/
}

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

void EventList::ShowEventList()
{
	std::cout << "Event List:\n";
	if (!(event_list_.empty()))
		for (auto &i : event_list_)
			std::cout << *i << std::endl;
	else
		std::cout << "EMPTY\n";
}

std::shared_ptr<Event> EventList::First()
{
	if (!(event_list_.empty()))
		return event_list_.front();
	return nullptr;
}
void EventList::DeleteFirst()
{
	std::shared_ptr<Event> event = First();
	if (event)
		event_list_.pop_front();
}

std::shared_ptr<Event> EventList::DeleteEvent(std::shared_ptr<Client> client)
{
	std::shared_ptr<Event> event = nullptr;
	for (auto iterator_list = event_list_.begin(); iterator_list != event_list_.end(); ++iterator_list)
	{
		if (static_cast<std::string>(**iterator_list) == "AlarmRang")
			continue;
		if ((*iterator_list)->GetClient() == client)
		{
			event = *iterator_list;
			event_list_.erase(iterator_list); //delete event from list
			return event;
		}
	}
	return nullptr;
}
