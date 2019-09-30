#pragma once
#include <list>
#include "client.h"
#include "event_list.h"
#include "generators.h"

class EventList;

class Restaurant
{
public:
	Restaurant(EventList *);
	~Restaurant();
	void AddClientToSystem(Client * client);
	bool AddToBuffetQueue(Client * client);
	void DeleteClientFromBuffet(Client * client);
	void AddToBuffetIfPossible();
	Client * ClientToAddBuffet();
	bool AddToCheckoutQueue(Client * client);
	void DeleteClientFromSystem(Client * client);
	void AddToCheckoutIfPossible();
	bool AddToTableQueue(Client * client);
	bool AddToDrinksQueue(Client * client);
	void AddToMealsQueue(Client * client);
	void ServiceFirstClient();
	void StartConsumption(Client * client);
	void DeleteClientFromTable(Client * client);
	void AddClientToTable();
	Client * ClientToAddTable();
	double simulation_time_;
	void Alarm();
	bool DeleteClientFromEvent(Client *);
	bool DeleteClientFromQueue(Client *);

	void ShowState();
	int GetNumberPeople();
	int GetSizeQueueTable();
	int GetSizeQueueCheckout();

	void Show();
private:
	EventList * event_list_;

	std::list<Client*> * clients_; //all clients currently located in restaurant

	std::list<Client*> * queue_buffet_;
	std::list<Client*> * queue_checkout_;
	std::list<Client*> * queue_table_;
	std::list<Client*> * queue_waiter_; //clients waiting for waiter

	const int kBuffetSeats = Generators::b_;
	const int kNumberTables2 = Generators::n2_; // (2-person)
	const int kNumberTables3 = Generators::n3_;; // (3-person)
	const int kNumberTables4 = Generators::n4_;; // (4-person) 
	const int kNumberWaiters = Generators::w_;
	const int kNumberCheckouts = Generators::c_;

	int buffet_free_seats_;
	int free_tables_[3]; //sequentially: 2-person, 3-person, 4-person
	int free_waiters_; //number of free waiters
	int free_checkouts_; //number of free checkouts

	bool manager_free_; //if true, manager is not busy

};

