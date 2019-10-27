#pragma once
#include <list>
#include <memory>
#include "event.h"
//#include "client_arrival.h"

class Event;
class Client;
class EventList
{
public:
	EventList();
	~EventList();
	void AddToEventList(std::shared_ptr<Event>);
	std::shared_ptr<Event> First();
	void DeleteFirst();
	friend std::ostream & operator<<(std::ostream &, const EventList &);
private:
	std::list<std::shared_ptr<Event>> event_list_;
};

