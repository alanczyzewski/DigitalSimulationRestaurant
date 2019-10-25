#pragma once
#include <list>
#include "client.h"
#include "event_list.h"
#include "generators.h"

class EventList;
class Restaurant
{
public:
	Restaurant();
	~Restaurant();
	std::shared_ptr<EventList> event_list_;
	double GetTime() { return simulation_time_; }
	void SetStartPoint();
	void SetTime();
	void ExecuteFirstEvent();
	void DeleteFirstEvent();

	void AddClientToSystem(std::shared_ptr<Client>);
	void ChooseBuffet(std::shared_ptr<Client>);
	bool AddToBuffet();
	void ChooseTable(std::shared_ptr<Client>);
	void AddToTable();
	void TakeTable(std::shared_ptr<Client>);
	void AddToMealsQueue(std::shared_ptr<Client>);
	void ServiceFirstClient();
	void StartConsumption();
	void DeleteClientFromTable(std::shared_ptr<Client>);
	void FinishConsumption(std::shared_ptr<Client>);
	void DeleteClientFromSystem(std::shared_ptr<Client>);
	void AddToCheckout();


	void DeleteClientFromBuffet(std::shared_ptr<Client>);
	
	
	
	

	void Alarm();
	bool DeleteClientFromEvent(std::shared_ptr<Client>);
	bool DeleteClientFromQueue(std::shared_ptr<Client>);

	void ShowState();
	int GetNumberPeople() { return clients_.size(); }
	int GetSizeQueueTable() { return queue_table_.size(); }
	int GetSizeQueueCheckout() { return queue_checkout_.size(); }

private:
	double simulation_time_;
	std::list<std::shared_ptr<Client>> clients_; //all clients currently located in restaurant
	std::list<std::shared_ptr<Client>> queue_buffet_;
	std::list<std::shared_ptr<Client>> queue_checkout_;
	std::list<std::shared_ptr<Client>> queue_table_;
	std::list<std::shared_ptr<Client>> queue_waiter_; //clients waiting for waiter

	const int kBuffetSeats = generators::b_;
	const int kNumberTables2 = generators::n2_; // (2-person)
	const int kNumberTables3 = generators::n3_;; // (3-person)
	const int kNumberTables4 = generators::n4_;; // (4-person) 
	const int kNumberWaiters = generators::w_;
	const int kNumberCheckouts = generators::c_;

	int buffet_free_seats_;
	int free_tables_[3]; //sequentially: 2-person, 3-person, 4-person
	int free_waiters_; //number of free waiters
	int free_checkouts_; //number of free checkouts

	bool manager_free_; //if true, manager is not busy

};

