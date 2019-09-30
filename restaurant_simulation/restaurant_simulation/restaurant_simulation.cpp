// restaurant_simulation.cpp : Defines the entry point for the console application.
// Digital simulation - Alan Czyzewski

#include "stdafx.h"
#include <iostream>
#include "restaurant.h"
#include "client.h"
#include "event.h"
#include "event_list.h"
#include "client_arrival.h"
#include "alarm_rang.h"
#include "statistics.h"
//#include <fstream>

int main()
{
	//std::fstream my_file_1("NumberPeople.csv");
	//std::fstream my_file_2("QueueTable.csv");
	//std::fstream my_file_3("QueueCheckout.csv");
	//std::fstream my_file_4("AverageTimeQueueTable.csv");
	//std::fstream my_file_5("AverageTimeWaitingWaiter.csv");
	//std::fstream my_file_6("AverageSizeQueueTable.csv");
	//std::fstream my_file_7("AverageSizeQueueCheckout.csv");

	using std::cout;
	using std::endl;
	using std::cin;

	int simulation_type = 0;
	double simulation_time = 0;
	cout << "Choose the simulation type\n1. Continuous\n2. Step by step" << endl;
	while (!(cin >> simulation_type) || (simulation_type != 1 && simulation_type != 2))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		cout << "Choose type of simulation\n1. Continuous\n2. Step by step\n";
	}
	cout << "Chosen type: ";
	if (simulation_type == 1)
		cout << "Continuous\n\n";
	else
		cout << "Step by step\n\n";


	EventList *event_list = new EventList();
	Restaurant *restaurant = new Restaurant(event_list);
	event_list->AddToEventList(new ClientArrival(restaurant, event_list));
	event_list->AddToEventList(new AlarmRang(restaurant, event_list));
	// main simulation loop
	const int max_clients = 15000;
	while (Client::GetLastClientId() <= max_clients)
	{
		//simulation_time
		restaurant->simulation_time_ = event_list->First()->event_time_; //set simulation time
		cout << "Simulation Time: " << restaurant->simulation_time_ << endl;
		event_list->ShowEventList(); //show event list
		cout << endl;
		Statistics::ShowStatistics(); //show statistics
		cout << endl << endl;
		event_list->First()->Execute(); //execute the earliest event
		event_list->DeleteFirst(); //delete the earliest event
		//save to file
		//my_file_1 << restaurant->GetNumberPeople() << endl;
		//my_file_2 << Statistics::current_size_queue_table_ << endl;//restaurant->GetSizeQueueTable() << endl;
		//my_file_3 << Statistics::current_size_queue_checkout_ << endl;//restaurant->GetSizeQueueCheckout() << endl;
		//my_file_4 << Statistics::average_time_waiting_table_ << endl;
		//my_file_5 << Statistics::average_time_waiting_waiter_ << endl;
		//my_file_6 << Statistics::average_size_queue_table_ << endl;
		//my_file_7 << Statistics::average_size_queue_checkout_ << endl;
		if (simulation_type == 2)
		{
			getchar(); getchar();
		}
	}
	cout << "\nSimulation completed!\n\n";
	getchar(); getchar();

    return 0;
}


