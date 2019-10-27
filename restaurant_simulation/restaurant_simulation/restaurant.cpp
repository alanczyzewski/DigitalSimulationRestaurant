#include "stdafx.h"
#include "restaurant.h"
#include "served_food.h"
#include "served_drinks.h"
#include "table_taken.h"
#include <iostream>
#include "client_arrival.h"
#include "buffet_service_end.h"
#include "checkout_service_end.h"
#include "statistics.h"
#include <immintrin.h>
#include <algorithm> //for_each

Restaurant::Restaurant() : simulation_time_(0), buffet_free_seats_(kBuffetSeats), free_checkouts_(kNumberCheckouts), free_waiters_(kNumberWaiters),
event_list_(static_cast<std::shared_ptr<EventList>> (new EventList())), manager_free_(true), stats_(std::shared_ptr<Statistics> (new Statistics()))
{
	free_tables_[2] = kNumberTables2;
	free_tables_[3] = kNumberTables3;
	free_tables_[4] = kNumberTables4;
}

Restaurant::~Restaurant() {}

void Restaurant::SetStartPoint()
{
	event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ClientArrival(*this)));
}

void Restaurant::SetTime() 
{ 
	simulation_time_ = *(event_list_->First()); 
}
void Restaurant::ExecuteFirstEvent()
{
	event_list_->First()->Execute();
}
void Restaurant::DeleteFirstEvent()
{
	event_list_->DeleteFirst();
}
void Restaurant::AddClientToSystem(std::shared_ptr<Client> client)
{
	clients_.push_back(client);
}
void Restaurant::ChooseBuffet(std::shared_ptr<Client> client)
{
	queue_buffet_.push(client);
	AddToBuffet();
}
bool Restaurant::AddToBuffet()
{
	std::shared_ptr<Client> client = nullptr;
	if (!(queue_buffet_.empty()) && (queue_buffet_.front()->GetNumberPeople() <= buffet_free_seats_))
	{
		client = queue_buffet_.front(); //assign first client
		queue_buffet_.pop(); //delete client from queue
		buffet_free_seats_ -= client->GetNumberPeople(); //reduce number of free seats
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new BuffetServiceEnd(*this, client)));
		return true;
	}
	return false;
}

void Restaurant::ChooseTable(std::shared_ptr<Client> client)
{
	queue_table_.push(client);
	stats_->AddSizeQueueTable(simulation_time_ - stats_->reference_time_queue_table_, true); //statistics
	client->SetStartTimeTable(simulation_time_); //statistics
	stats_->reference_time_queue_table_ = simulation_time_; //statistics
	if (queue_table_.size() == 1)
		AddToTable();
}

void Restaurant::AddToTable()
{
	if (manager_free_ && !(queue_table_.empty()))
	{
		bool add_flag = false;
		std::shared_ptr<Client> client = queue_table_.front();
		if (client->GetNumberPeople() == 4)
		{
			if (free_tables_[4]) //4
			{
				free_tables_[4]--;
				client->SetNumberSeats(4);
				add_flag = true;
			}
			else if (free_tables_[2])
			{
				if (free_tables_[2] > 1) //2 and 2
				{
					free_tables_[2] -= 2;
					client->SetNumberSeats(2, 2);
					add_flag = true;
				}
				else if (free_tables_[3]) //2 and 3
				{
					free_tables_[2]--;
					free_tables_[3]--;
					client->SetNumberSeats(2, 3);
					add_flag = true;
				}
			}
			else if (free_tables_[3] > 1) //3 and 3
			{
				free_tables_[3] -= 2;
				client->SetNumberSeats(3, 3);
				add_flag = true;
			}
		}
		else if (client->GetNumberPeople() == 3)
		{
			if (free_tables_[3]) //3
			{
				free_tables_[3]--;
				client->SetNumberSeats(3);
				add_flag = true;
			}
			else if (free_tables_[4]) //4
			{
				free_tables_[4]--;
				client->SetNumberSeats(4);
				add_flag = true;
			}
			else if (free_tables_[2] > 1) //2 and 2
			{
				free_tables_[2] -= 2;
				client->SetNumberSeats(2, 2);
				add_flag = true;
			}
		}
		else //1 or 2 persons
		{
			for (int i = 2; i <= 4; i++)
			{
				if (free_tables_[i])
				{
					free_tables_[i]--;
					client->SetNumberSeats(i);
					add_flag = true;
					break;
				}
			}
		}
		if (add_flag)
		{
			queue_table_.pop();
			stats_->AddSizeQueueTable(simulation_time_ - stats_->reference_time_queue_table_, false); //statistics
			stats_->reference_time_queue_table_ = simulation_time_;
			manager_free_ = false;
			stats_->AddTimeWaitingTable(simulation_time_ - client->GetStartTimeTable());//statistics
			event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new TableTaken(*this, client)));
		}
	}
}

void Restaurant::TakeTable(std::shared_ptr<Client> client)
{
	manager_free_ = true;
	AddToTable();
	if (free_waiters_)
	{
		--free_waiters_;
		stats_->AddTimeWaitingWaiter(0); //statistics
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ServedDrinks(*this, client))); //Plan next event
	}
	else
	{
		queue_waiter_.push(client);
		client->SetStartTimeWaiter(simulation_time_); //statistics
	}
}

void Restaurant::AddToMealsQueue(std::shared_ptr<Client> client)
{
	client->SetServedDrinks();
	++free_waiters_;
	queue_waiter_.push(client);
	ServiceFirstClient();
}

void Restaurant::ServiceFirstClient()
{
	if (!(queue_waiter_.empty()) && free_waiters_)
	{
		--free_waiters_;
		std::shared_ptr<Client> client = queue_waiter_.front();
		queue_waiter_.pop();
		if (client->GetServedDrinks())
			event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ServedFood(*this, client)));
		else
		{
			stats_->AddTimeWaitingWaiter(simulation_time_ - client->GetStartTimeWaiter()); //statistics
			event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ServedDrinks(*this, client)));
		}
	}
}

void Restaurant::StartConsumption()
{
	++free_waiters_;
	ServiceFirstClient();
}

void Restaurant::DeleteClientFromTable(std::shared_ptr<Client> client)
{
	free_tables_[client->GetNumberSeats()]++;
	if (client->GetNumberPeople() > client->GetNumberSeats()) //it means there are 2 tables
		free_tables_[client->GetNumberSeats2()]++;
	AddToTable();
	FinishConsumption(client);
}

void Restaurant::FinishConsumption(std::shared_ptr<Client> client)
{
	if (free_checkouts_) //if there is free checkout
	{
		--free_checkouts_;
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new CheckoutServiceEnd(*this, client)));
	}
	else
	{
		queue_checkout_.push(client);
		stats_->AddSizeQueueCheckout(simulation_time_ - stats_->reference_time_queue_checkout_, true); //statistics
		stats_->reference_time_queue_checkout_ = simulation_time_;
	}
}

void Restaurant::DeleteClientFromSystem(std::shared_ptr<Client> client)
{
	clients_.remove(client);
	++free_checkouts_;
	AddToCheckout();
}

void Restaurant::AddToCheckout()
{
	if (!(queue_checkout_.empty()))
	{
		--free_checkouts_; // reduce number of free checkouts
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new CheckoutServiceEnd(*this, queue_checkout_.front())));
		queue_checkout_.pop(); //delete client from queue
		stats_->AddSizeQueueCheckout(simulation_time_ - stats_->reference_time_queue_checkout_, false); //statistics
		stats_->reference_time_queue_checkout_ = simulation_time_; //statistics
	}
}

void Restaurant::DeleteClientFromBuffet(std::shared_ptr<Client> client)
{
	buffet_free_seats_ += client->GetNumberPeople(); // increase number of free seats
	while (AddToBuffet());
	FinishConsumption(client);
}

std::ostream & operator<<(std::ostream & os, const Restaurant & r)
{
	using std::endl;
	os << "Restaurant:\n";
	os.width(20);
	os << "Free buffet seats: " << r.buffet_free_seats_ << endl;
	os.width(20);
	os << "Free tables(2): " << r.free_tables_.at(2) << endl;
	os.width(20);
	os << "Free tables(3): " << r.free_tables_.at(3) << endl;
	os.width(20);
	os << "Free tables(4): " << r.free_tables_.at(4) << endl;
	os.width(20);
	os << "Free checkouts: " << r.free_checkouts_ << endl;
	os.width(20);
	os << "Free waiters: " << r.free_waiters_ << endl;
	os.width(20);
	os << "Manager: " << (r.manager_free_ ? "FREE\n" : "BUSY\n") << endl;
	os.width(20);
	os << "Groups of clients in system: " << r.clients_.size() << endl;
	os.width(20);
	os << "Groups of clients at tables: " << r.kNumberTables2 + r.kNumberTables3 + r.kNumberTables4 - r.free_tables_.at(2) - r.free_tables_.at(3) - r.free_tables_.at(4);
	os << "\nQueues:\tTo buffet: " << r.queue_buffet_.size() << ", To waiter: " << r.queue_waiter_.size() << endl;
	return os;
}

void Restaurant::ResetStatistics()
{
	stats_->Reset(simulation_time_);
}