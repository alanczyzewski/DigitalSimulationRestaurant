#pragma once
#include <list>
#include <queue>
#include <map>
#include "client.h"
#include "event_list.h"
#include "statistics.h"
#include "generators.h"

class EventList;
class Restaurant
{
public:
	Restaurant();
	~Restaurant();
	std::shared_ptr<EventList> event_list_;
	std::shared_ptr<Statistics> stats_;
	double GetTime() { return simulation_time_; }
	void SetStartPoint();
	void SetTime();
	void ExecuteFirstEvent();
	void DeleteFirstEvent();
	void AddClientToSystem(std::shared_ptr<Client>);
	void ChooseBuffet(std::shared_ptr<Client>);
	void ChooseTable(std::shared_ptr<Client>);
	void TakeTable(std::shared_ptr<Client>);
	void AddToMealsQueue(std::shared_ptr<Client>);
	void StartConsumption();
	void DeleteClientFromTable(std::shared_ptr<Client>);
	void DeleteClientFromSystem(std::shared_ptr<Client>);
	void DeleteClientFromBuffet(std::shared_ptr<Client>);
	friend std::ostream & operator<<(std::ostream &, const Restaurant &);
	int GetNumberPeople() { return clients_.size(); }
	void ResetStatistics();

private:
	double simulation_time_;
	std::list<std::shared_ptr<Client>> clients_; //all clients currently located in restaurant
	std::queue<std::shared_ptr<Client>> queue_buffet_;
	std::queue<std::shared_ptr<Client>> queue_checkout_;
	std::queue<std::shared_ptr<Client>> queue_table_;
	std::queue<std::shared_ptr<Client>> queue_waiter_; //clients waiting for waiter

	const int kBuffetSeats = generators::b;
	const int kNumberTables2 = generators::n2; // (2-person)
	const int kNumberTables3 = generators::n3; // (3-person)
	const int kNumberTables4 = generators::n4; // (4-person) 
	const int kNumberWaiters = generators::k;
	const int kNumberCheckouts = generators::c;

	int buffet_free_seats_;
	std::map<const int, int> free_tables_; //key->number_persons
	int free_waiters_; //number of free waiters
	int free_checkouts_; //number of free checkouts

	bool manager_free_; //if true, manager is not busy

	bool AddToBuffet();
	void AddToTable();
	void ServiceFirstClient();
	void FinishConsumption(std::shared_ptr<Client>);
	void AddToCheckout();
};

