#pragma once
#include <list>
#include "event.h"
//#include "client_arrival.h"
class Event;
class Client;
class EventList
{
public:
	EventList();
	~EventList();
	void AddToEventList(Event*);
	void ShowEventList();
	Event * First();
	void DeleteFirst();
	Event * DeleteEvent(Client *);
	std::list<Event *> *event_list_;
	std::list<Event *>::iterator it_;
};

