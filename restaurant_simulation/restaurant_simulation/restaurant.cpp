#include "stdafx.h"
#include "restaurant.h"
#include "served_food.h"
#include "served_drinks.h"
#include "table_taken.h"
#include <iostream>
#include "client_arrival.h"
#include "alarm_rang.h"
#include "buffet_service_end.h"
#include "checkout_service_end.h"
#include "statistics.h"
#include <immintrin.h>
#include <algorithm> //for_each

Restaurant::Restaurant() : simulation_time_(0), buffet_free_seats_(kBuffetSeats), free_checkouts_(kNumberCheckouts), free_waiters_(kNumberWaiters),
event_list_(static_cast<std::shared_ptr<EventList>> (new EventList())), manager_free_(true)
{
	free_tables_[0] = kNumberTables2;
	free_tables_[1] = kNumberTables3;
	free_tables_[2] = kNumberTables4;
}

Restaurant::~Restaurant() {}

void Restaurant::SetStartPoint()
{
	event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ClientArrival(*this)));
	//event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new AlarmRang(*this)));
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
	queue_buffet_.push_back(client);
	AddToBuffet();
}
bool Restaurant::AddToBuffet()
{
	std::shared_ptr<Client> client = nullptr;
	if (!(queue_buffet_.empty()) && (queue_buffet_.front()->GetNumberPeople() <= buffet_free_seats_))
	{
		client = queue_buffet_.front(); //assign first client
		queue_buffet_.pop_front(); //delete client from queue
		buffet_free_seats_ -= client->GetNumberPeople(); //reduce number of free seats
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new BuffetServiceEnd(*this, client)));
		return true;
	}
	return false;
}

void Restaurant::ChooseTable(std::shared_ptr<Client> client)
{
	queue_table_.push_back(client);
	statistics::AddSizeQueueTable(simulation_time_ - statistics::reference_time_queue_table_, true); //statistics
	client->SetStartTimeTable(simulation_time_); //statistics
	statistics::reference_time_queue_table_ = simulation_time_; //statistics
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
			if (free_tables_[2]) //4
			{
				free_tables_[2]--;
				client->SetNumberSeats(4);
				add_flag = true;
			}
			else if (free_tables_[0])
			{
				if (free_tables_[0] > 1) //2 and 2
				{
					free_tables_[0] -= 2;
					client->SetNumberSeats(2, 2);
					add_flag = true;
				}
				else if (free_tables_[1]) //2 and 3
				{
					free_tables_[0]--;
					free_tables_[1]--;
					client->SetNumberSeats(2, 3);
					add_flag = true;
				}
			}
			else if (free_tables_[1] > 1) //3 and 3
			{
				free_tables_[1] -= 2;
				client->SetNumberSeats(3, 3);
				add_flag = true;
			}
		}
		else if (client->GetNumberPeople() == 3)
		{
			if (free_tables_[1]) //3
			{
				free_tables_[1]--;
				client->SetNumberSeats(3);
				add_flag = true;
			}
			else if (free_tables_[2]) //4
			{
				free_tables_[2]--;
				client->SetNumberSeats(4);
				add_flag = true;
			}
			else if (free_tables_[0] > 1) //2 and 2
			{
				free_tables_[0] -= 2;
				client->SetNumberSeats(2, 2);
				add_flag = true;
			}
		}
		else //1 or 2 persons
		{
			for (int i = 0; i <= 2; i++)
			{
				if (free_tables_[i])
				{
					free_tables_[i]--;
					client->SetNumberSeats(i + 2);
					add_flag = true;
					break;
				}
			}
		}
		if (add_flag)
		{
			queue_table_.pop_front();
			statistics::AddSizeQueueTable(simulation_time_ - statistics::reference_time_queue_table_, false); //statistics
			statistics::reference_time_queue_table_ = simulation_time_;
			manager_free_ = false;
			statistics::AddTimeWaitingTable(simulation_time_ - client->GetStartTimeTable());//statistics
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
		statistics::AddTimeWaitingWaiter(0); //statistics
		event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ServedDrinks(*this, client))); //Plan next event
	}
	else
	{
		queue_waiter_.push_back(client);
		client->SetStartTimeWaiter(simulation_time_); //statistics
	}
}

void Restaurant::AddToMealsQueue(std::shared_ptr<Client> client)
{
	client->SetServedDrinks();
	++free_waiters_;
	queue_waiter_.push_back(client);
	ServiceFirstClient();
}

void Restaurant::ServiceFirstClient()
{
	if (!(queue_waiter_.empty()) && free_waiters_)
	{
		--free_waiters_;
		std::shared_ptr<Client> client = queue_waiter_.front();
		queue_waiter_.pop_front();
		if (client->GetServedDrinks())
			event_list_->AddToEventList(static_cast<std::shared_ptr<Event>> (new ServedFood(*this, client)));
		else
		{
			statistics::AddTimeWaitingWaiter(simulation_time_ - client->GetStartTimeWaiter()); //statistics
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
	free_tables_[client->GetNumberSeats() - 2]++;
	if (client->GetNumberPeople() > client->GetNumberSeats()) //it means there are 2 tables
		free_tables_[client->GetNumberSeats2() - 2]++;
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
		queue_checkout_.push_back(client);
		statistics::AddSizeQueueCheckout(simulation_time_ - statistics::reference_time_queue_checkout_, true); //statistics
		statistics::reference_time_queue_checkout_ = simulation_time_;
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
		queue_checkout_.pop_front(); //delete client from queue
		statistics::AddSizeQueueCheckout(simulation_time_ - statistics::reference_time_queue_checkout_, false); //statistics
		statistics::reference_time_queue_checkout_ = simulation_time_; //statistics
	}
}

void Restaurant::DeleteClientFromBuffet(std::shared_ptr<Client> client)
{
	buffet_free_seats_ += client->GetNumberPeople(); // increase number of free seats
	while (AddToBuffet());
	FinishConsumption(client);
}






void Restaurant::Alarm()
{
	std::list<double> list_id;
	std::shared_ptr<Client> client = nullptr;
	int number_clients = clients_.size();
	for (int i = 0; i < number_clients; ++i)
	{
		client = clients_.front();
		clients_.pop_front();
		bool event_removed = false;
		bool queue_removed = false;
		if (client->GetRunAway())
		{
			queue_removed = DeleteClientFromQueue(client);
			if (!queue_removed) 
				event_removed = DeleteClientFromEvent(client);
			if (queue_removed || event_removed) //if there was event related to client except ClientArrival OR client was in the queue
			{
				list_id.push_back(client->GetId());
			}
			client = nullptr;
		}
		else 
			clients_.push_back(client);
	}
}

bool Restaurant::DeleteClientFromEvent(std::shared_ptr<Client> client)
{
	std::shared_ptr<Event> event = nullptr;
	event = event_list_->DeleteEvent(client);
	if (event == nullptr)
		return false;
	std::string name = *event;
	if (name == "TableTaken")
	{
		manager_free_ = true;
	}
	else if (name == "ServedDrinks" || name == "ServedFood")
	{
		Show();
		free_waiters_++;
		DeleteClientFromTable(client);
		Show();
		std::cout << std::endl;
	}
	else if (name == "ConsumptionEnd")
	{
		DeleteClientFromTable(client);
	}
	else if (name == "BuffetServiceEnd")
	{
		DeleteClientFromBuffet(client);
		while (AddToBuffet());
	}
	else if (name == "CheckoutServiceEnd")
	{
		free_checkouts_++;
		AddToCheckout();
	}
	return true;
}

bool Restaurant::DeleteClientFromQueue(std::shared_ptr<Client> client)
{
	for (auto it = queue_buffet_.begin(); it != queue_buffet_.end(); ++it)
	{
		if ((*it) == client)
		{
			queue_buffet_.erase(it); //delete from list
			return true;
		}
	}
	for (auto it = queue_table_.begin(); it != queue_table_.end(); ++it)
	{
		if (*it == client)
		{
			queue_table_.erase(it); //delete from list
			statistics::AddSizeQueueTable(simulation_time_ - statistics::reference_time_queue_table_, false); //statistics
			statistics::reference_time_queue_table_ = simulation_time_;
			Show();
			return true;
		}
	}
	for (auto it = queue_checkout_.begin(); it != queue_checkout_.end(); ++it)
	{
		if (*it == client)
		{
			queue_checkout_.erase(it); //delete from list
			statistics::AddSizeQueueCheckout(simulation_time_ - statistics::reference_time_queue_checkout_, false); //statistics
			statistics::reference_time_queue_checkout_ = simulation_time_; //statistics
			Show();
			return true;
		}
	}
	for (auto it = queue_waiter_.begin(); it != queue_waiter_.end(); ++it)
	{
		if (*it == client)
		{
			queue_waiter_.erase(it); //delete from list
			free_tables_[client->GetNumberSeats() - 2]++;
			return true;
		}
	}
	return false;
}

void Restaurant::ShowState()
{
	using std::cout;
	using std::endl;
	cout << "Restaurant:\n";
	cout.width(20);
	cout << "Free buffet seats: " << buffet_free_seats_ << endl;
	cout.width(20); 
	cout << "Free tables(2): " << free_tables_[0] << endl;
	cout.width(20); 
	cout << "Free tables(3): " << free_tables_[1] << endl;
	cout.width(20); 
	cout << "Free tables(4): " << free_tables_[2] << endl;
	cout.width(20); 
	cout << "Free checkouts: " << free_checkouts_ << endl;
	cout.width(20); 
	cout << "Free waiters: " << free_waiters_ << endl;
	cout.width(20); 
	cout << "Manager: " << (manager_free_ ? "FREE\n" : "BUSY\n") << endl;
	cout.width(20); 
	cout << "Groups of clients in system: " << clients_.size() << endl;
	cout.width(20);
	cout << "Groups of clients at tables: " << kNumberTables2 + kNumberTables3 + kNumberTables4 - free_tables_[0] - free_tables_[1] - free_tables_[2] << endl;

	cout << "Queues:\tbuffet: " << queue_buffet_.size() << ", queue tables: " << queue_table_.size() << endl;
}
