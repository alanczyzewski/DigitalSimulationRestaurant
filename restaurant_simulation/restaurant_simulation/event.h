#pragma once
#include <string>
#include <memory> //smart pointers
#include "event_list.h"
#include "client.h"
#include "restaurant.h"

class Restaurant;
class EventList;
class Event
{
public:
	Event(std::string name, Restaurant & restaurant, std::shared_ptr<Client> client) : event_name_(name), restaurant_(&restaurant), client_(client) {}
	virtual ~Event() {}
	virtual void Execute() = 0;
	void SetTime(double time);
	Restaurant * GetRestaurant() { return restaurant_; }
	std::shared_ptr<Client> GetClient() const { return client_; }
	friend bool operator<(const Event &, const Event &);
	friend bool operator>(const Event &, const Event &);
	friend std::ostream & operator<<(std::ostream &, const Event &);
	operator double() { return event_time_; }
	operator std::string() { return event_name_; }
protected:
	std::string event_name_;
	double event_time_;
	Restaurant * restaurant_;
	std::shared_ptr<Client> client_;
};


