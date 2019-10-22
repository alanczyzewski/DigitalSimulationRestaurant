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


Restaurant::Restaurant()
{
	event_list_ = new EventList();
	simulation_time_ = 0;
	clients_ = new std::list<Client*>;

	queue_buffet_ = new std::list<Client*>;
	queue_checkout_ = new std::list<Client*>;
	queue_table_ = new std::list<Client*>;
	queue_waiter_ = new std::list<Client*>;

	buffet_free_seats_ = kBuffetSeats;
	free_checkouts_ = kNumberCheckouts;
	free_tables_[0] = kNumberTables2;
	free_tables_[1] = kNumberTables3;
	free_tables_[2] = kNumberTables4;
	free_waiters_ = kNumberWaiters;

	manager_free_ = true;
}

Restaurant::~Restaurant()
{
	while (!(queue_buffet_->empty()))
		queue_buffet_->pop_front();
	delete queue_buffet_;

	while (!(queue_checkout_->empty()))
		queue_checkout_->pop_front();
	delete queue_checkout_;

	while (!(queue_table_->empty()))
		queue_table_->pop_front();
	delete queue_table_;

	while (!(queue_waiter_->empty()))
		queue_waiter_->pop_front();
	delete queue_waiter_;

	while (!(clients_->empty()))
	{
		Client *client = clients_->front();
		clients_->pop_front();
		delete client;
	}
	delete clients_;
}

void Restaurant::StartSimulation()
{
	event_list_->AddToEventList(new ClientArrival(*this));
	//event_list_->AddToEventList(new AlarmRang(restaurant, event_list));
}

void Restaurant::SetTime() 
{ 
	simulation_time_ = event_list_->First()->GetTime(); 
}

EventList * Restaurant::GetEventList()
{
	return event_list_;
}

void Restaurant::AddClientToSystem(Client* client)
{
	clients_->push_back(client);
}

bool Restaurant::AddToBuffetQueue(Client* client)
{
	if (client->GetNumberPeople() <= buffet_free_seats_)
		//if number of people is not bigger than number of seats
	{
		buffet_free_seats_ -= client->GetNumberPeople();
		return true; //client goes to buffet, not queue
	}
	queue_buffet_->push_back(client);
	return false;

}

void Restaurant::DeleteClientFromBuffet(Client* client)
{
	buffet_free_seats_ += client->GetNumberPeople(); // increase number of free seats
}

void Restaurant::AddToBuffetIfPossible()
{
	Client * client = nullptr;
	while (true)
	{
		client = ClientToAddBuffet();
		if (client == nullptr)
			return;
		event_list_->AddToEventList(new BuffetServiceEnd(*this, client));
	}
}
class Client* Restaurant::ClientToAddBuffet()
{
	Client * client = nullptr;
	if (!(queue_buffet_->empty()) && (queue_buffet_->front()->GetNumberPeople() <= buffet_free_seats_))
	{
		client = queue_buffet_->front(); //assign first client
		queue_buffet_->pop_front(); //delete client from queue
		buffet_free_seats_ -= client->GetNumberPeople(); // reduce number of free seats
	}
	return client;

}


bool Restaurant::AddToCheckoutQueue(Client* client)
{
	if(free_checkouts_) //if there is free checkout
	{
		free_checkouts_--;
		return true;
	}
	queue_checkout_->push_back(client);
	Statistics::AddSizeQueueCheckout(simulation_time_ - Statistics::reference_time_queue_checkout_, true); //statistics
	Statistics::reference_time_queue_checkout_ = simulation_time_;
	return false;
}

void Restaurant::DeleteClientFromSystem(Client* client)
{
	//delete from list of clients currently located in restaurant
	for (auto it = clients_->begin(); it != clients_->end(); ++it)
	{
		if ((*it)->GetId() == client->GetId())
		{
			clients_->erase(it); //delete from list
			break;
		}
	}
	//delete client from system
	delete client;
	free_checkouts_++;
}

void Restaurant::AddToCheckoutIfPossible()
{
	Client * client = nullptr;
	if (!(queue_checkout_->empty()))
	{
		client = queue_checkout_->front(); //assign first client
		queue_checkout_->pop_front(); //delete client from queue
		Statistics::AddSizeQueueCheckout(simulation_time_ - Statistics::reference_time_queue_checkout_, false); //statistics
		Statistics::reference_time_queue_checkout_ = simulation_time_; //statistics
		free_checkouts_--; // reduce number of free checkouts
		event_list_->AddToEventList(new CheckoutServiceEnd(*this, client));
	}
}

bool Restaurant::AddToTableQueue(Client* client)
{
	//1. Check, if client can go to a table
	if (manager_free_)
	{
		int people = client->GetNumberPeople();
		const int max_table = 4;
		for (int i = people; i <= max_table; i++)
		{
			if (i == 1)
				continue;
			if (free_tables_[i - 2]) //e.g. i=2 (2-person table = free_tables[0])
			{
				free_tables_[i - 2]--;
				manager_free_ = false;
				client->SetNumberSeats(i); //Set number of seats at the table to the client
				return true;
			}
		}
	}
	//2. Place client in the queue
	queue_table_->push_back(client);
	client->SetStartTimeTable(simulation_time_); //statistics
	Statistics::AddSizeQueueTable(simulation_time_ - Statistics::reference_time_queue_table_, true); //statistics
	Statistics::reference_time_queue_table_ = simulation_time_;
	return false;
}

bool Restaurant::AddToDrinksQueue(Client* client)
{
	manager_free_ = true; //release manager
	//Check, if there is free waiter
	if (free_waiters_)
	{
		free_waiters_--;
		return true;
	}
	queue_waiter_->push_back(client);
	client->SetStartTimeWaiter(simulation_time_); //statistics
	return false;
}
void Restaurant::AddToMealsQueue(Client* client)
{
	client->SetServedDrinks();
	free_waiters_++;
	queue_waiter_->push_back(client);
	ServiceFirstClient();
}

void Restaurant::ServiceFirstClient()
{
	Client * client = nullptr;
	if(!(queue_waiter_->empty()) && free_waiters_)
	{
		free_waiters_--;
		client = queue_waiter_->front();
		queue_waiter_->pop_front();
		if (client->GetServedDrinks())
		{
			event_list_->AddToEventList(new ServedFood(*this, client));
		}
		else
		{
			Statistics::AddTimeWaitingWaiter(simulation_time_ - client->GetStartTimeWaiter()); //statistics
			event_list_->AddToEventList(new ServedDrinks(*this, client));
		}
	}
}

void Restaurant::StartConsumption(Client* client)
{
	free_waiters_++;
	ServiceFirstClient();
}

void Restaurant::DeleteClientFromTable(Client* client)
{
	free_tables_[client->GetNumberSeats() - 2]++;
	AddClientToTable();
}

void Restaurant::AddClientToTable()
{
	Client * client = ClientToAddTable();
	if (client != nullptr)
	{
		//delete from queue
		for (auto it = queue_table_->begin(); it != queue_table_->end(); ++it)
		{
			if ((*it)->GetId() == client->GetId())
			{
				queue_table_->erase(it); //delete from list
				Statistics::AddSizeQueueTable(simulation_time_ - Statistics::reference_time_queue_table_, false); //statistics
				Statistics::reference_time_queue_table_ = simulation_time_;
				break;
			}
		}
		manager_free_ = false;
		Statistics::AddTimeWaitingTable(simulation_time_ - client->GetStartTimeTable());//statistics
		event_list_->AddToEventList(new TableTaken(*this, client));
	}
}

Client* Restaurant::ClientToAddTable()
{
	Client * client = nullptr;
	if (queue_table_->empty()) //if queue is empty
		return nullptr;
	bool first = true;
	//4-person
	if (free_tables_[2])
	{
		for (auto &i : *queue_table_)
		{
			if (i->GetNumberPeople() == 4)
			{
				free_tables_[2]--;
				i->SetNumberSeats(4);
				return i;
			}
			if (first) //if it's first iteration
			{
				client = i;
				first = false;
				continue;
			}
			if (i->GetNumberPeople() > client->GetNumberPeople())
			{
				client = i;
			}
		}
		free_tables_[2]--;
		client->SetNumberSeats(4);
		return client;
	}
	//3-person
	else if (free_tables_[1])
	{
		for (auto &i : *queue_table_)
		{
			if (i->GetNumberPeople() == 3)
			{
				free_tables_[1]--;
				i->SetNumberSeats(3);
				return i;
			}
			if (first) //if it's first iteration
			{
				if (i->GetNumberPeople() < 4)
				{
					client = i;
					first = false;
				}
				continue;
			}
			if (i->GetNumberPeople() > client->GetNumberPeople())
			{
				client = i;
			}
		}
		if (client != nullptr)
		{
			free_tables_[1]--;
			client->SetNumberSeats(3);
		}
		return client;
	}
	//2-person
	else if (free_tables_[0])
	{
		for (auto &i : *queue_table_)
		{
			if (i->GetNumberPeople() == 2)
			{
				free_tables_[0]--;
				i->SetNumberSeats(2);
				return i;
			}
			if (first) //if it's first iteration
			{
				if (i->GetNumberPeople() == 1)
				{
					client = i;
					first = false;
				}
			}
		}
		if (client != nullptr)
		{
			free_tables_[0]--;
			client->SetNumberSeats(2);
		}
		return client;
	}
	return client;
}

void Restaurant::Alarm()
{
	std::list<double> list_id;
	Client * client = nullptr;
	int number_clients = clients_->size();
	for (int i = 0; i < number_clients; ++i)
	{
		client = clients_->front();
		clients_->pop_front();
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
				delete client;
			}
			client = nullptr;
		}
		else 
			clients_->push_back(client);
	}
}

bool Restaurant::DeleteClientFromEvent(Client* client)
{
	Event * event = nullptr;
	std::string name = "";
	event = event_list_->DeleteEvent(client);
	if (event == nullptr)
		return false;
	name = event->GetName();
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
		AddToBuffetIfPossible();
	}
	else if (name == "CheckoutServiceEnd")
	{
		free_checkouts_++;
		AddToCheckoutIfPossible();
	}
	delete event; //delete event from system
	return true;
}

bool Restaurant::DeleteClientFromQueue(Client* client)
{
	for (auto it = queue_buffet_->begin(); it != queue_buffet_->end(); ++it)
	{
		if ((*it) == client)
		{
			queue_buffet_->erase(it); //delete from list
			return true;
		}
	}
	for (auto it = queue_table_->begin(); it != queue_table_->end(); ++it)
	{
		if (*it == client)
		{
			queue_table_->erase(it); //delete from list
			Statistics::AddSizeQueueTable(simulation_time_ - Statistics::reference_time_queue_table_, false); //statistics
			Statistics::reference_time_queue_table_ = simulation_time_;
			Show();
			return true;
		}
	}
	for (auto it = queue_checkout_->begin(); it != queue_checkout_->end(); ++it)
	{
		if (*it == client)
		{
			queue_checkout_->erase(it); //delete from list
			Statistics::AddSizeQueueCheckout(simulation_time_ - Statistics::reference_time_queue_checkout_, false); //statistics
			Statistics::reference_time_queue_checkout_ = simulation_time_; //statistics
			Show();
			return true;
		}
	}
	for (auto it = queue_waiter_->begin(); it != queue_waiter_->end(); ++it)
	{
		if (*it == client)
		{
			queue_waiter_->erase(it); //delete from list
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
	cout << "Free buffet seats: " << buffet_free_seats_ << " Free tables(2): " << free_tables_[0] << " Free tables(3): " << free_tables_[1] << " Free tables(4): " <<
		free_tables_[2] << " Free checkouts: " << free_checkouts_ << " Free waiters: " << free_waiters_ << " Manager: " << (manager_free_ ? "FREE\n" : "BUSY\n");
	cout << "Clients in system: " << GetNumberPeople() << endl;
}

void Restaurant::Show()
{
	std::cout << "\t\t\t\tmanager: " << manager_free_ << "\tfree tables: " << free_tables_[2] << "\t" << free_tables_[1] << "\t" << free_tables_[0] << std::endl;
	std::cout << "Waiters: " << free_waiters_ << std::endl << "free seats buffet: " << buffet_free_seats_ << std::endl;
}
