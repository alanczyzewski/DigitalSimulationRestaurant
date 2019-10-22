#include "stdafx.h"
#include <iostream>
#include "event_list.h"
#include "alarm_rang.h"


EventList::EventList()
{
	event_list_ = new std::list<Event*>();
}

EventList::~EventList()
{
	while (!(event_list_->empty()))
	{
		Event *event = event_list_->front();
		event_list_->pop_front();
		delete event;
	}
	delete event_list_;
}

void EventList::AddToEventList(Event* eve)
{
	if (!(event_list_->empty())) //if not empty
	{
		it_ = event_list_->begin();
		while (it_ != event_list_->end())
		{
			if (eve->GetTime() < (*it_)->GetTime())
				break;
			else
				std::advance(it_, 1);
		}
		event_list_->insert(it_, eve);
	}
	else
	{
		event_list_->push_back(eve);
	}
	it_ = event_list_->begin();
}

void EventList::ShowEventList()
{
	using std::cout;
	using std::endl;
	cout << "Event List:\n";
	if (!(event_list_->empty()))
	{
		for (auto &i : *event_list_)
		{
			cout << "Time: " << i->GetTime() << ", Name: " << i->GetName();
			if (i->GetClient())
				cout << ", Client ID: " << i->GetClient()->GetId() << ", Run away? " << (i->GetClient()->GetRunAway() ? "YES" : "NO");
			cout << endl;	
		}
	}
	else
	{
		cout << "EMPTY\n";
	}
}

Event* EventList::First()
{
	if (!(event_list_->empty()))
		return event_list_->front();
	return nullptr;
}
void EventList::DeleteFirst()
{
	Event * event = First();
	if (event)
	{
		event_list_->pop_front();
		delete event;
	}
}

Event * EventList::DeleteEvent(Client* client)
{
	Event * event = nullptr;
	for (auto it = event_list_->begin(); it != event_list_->end();)
	{
		++it; //because first event on the list is AlarmRang
		if ((*it)->GetClient() == client)
		{
			event = *it;
			event_list_->erase(it); //delete event from list
			return event;
		}
	}
	return nullptr;
}
