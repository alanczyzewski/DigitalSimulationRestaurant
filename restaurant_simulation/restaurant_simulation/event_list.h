#pragma once
#include <list>
#include <memory>
#include "event.h"
//#include "client_arrival.h"

class Event;
class Client;
class EventList
{
private:
	std::list<std::shared_ptr<Event>> event_list_;
public:
	EventList();
	~EventList();
	void AddToEventList(std::shared_ptr<Event>);
	void ShowEventList();
	std::shared_ptr<Event> First();
	void DeleteFirst();
	std::shared_ptr<Event> DeleteEvent(std::shared_ptr<Client>);
};

