#pragma once
#include <string>
#include "event_list.h"
#include "client.h"
#include "restaurant.h"

class Restaurant;
class EventList;

class Event
{
public:
	Event(std::string name, Restaurant & restaurant, Client * client = nullptr) : event_name_(name), restaurant_(&restaurant), client_(client) {}
	virtual ~Event() {}
	virtual void Execute() = 0;
	std::string GetName() const { return event_name_; }
	double GetTime() const { return event_time_; }
	void SetTime(double time); //{ event_time_ = restaurant_->GetTime() + time; }
	Restaurant * GetRestaurant() { return restaurant_; }
	Client * GetClient() const { return client_; }
private:
	std::string event_name_;
	double event_time_;
	Restaurant * restaurant_;
	Client * client_;
};

