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
#include <fstream>

using std::cout;
using std::endl;
using std::cin;

int simulation_type = 0;
double simulation_time = 0;
//std::fstream my_file_1("NumberPeople.csv");
//std::fstream my_file_2("QueueTable.csv");
//std::fstream my_file_3("QueueCheckout.csv");
//std::fstream my_file_4("AverageTimeQueueTable.csv");
//std::fstream my_file_5("AverageTimeWaitingWaiter.csv");
//std::fstream my_file_6("AverageSizeQueueTable.csv");
//std::fstream my_file_7("AverageSizeQueueCheckout.csv");

void ShowMenu();
void SaveToFile();

int main()
{
	ShowMenu();

	Restaurant restaurant = Restaurant();
	restaurant.StartSimulation();

	const int max_clients = 15000;
	bool initial_phase = true;
	// main simulation loop
	while (Client::GetLastClientId() <= max_clients)
	{

		//set simulation time
		restaurant.SetTime();
		//display
		cout << "Simulation Time: " << restaurant.GetTime() << endl; //show simulation time
		restaurant.GetEventList()->ShowEventList(); cout << endl; //show event list
		Statistics::ShowStatistics(); cout << endl; //show statistics
		restaurant.ShowState(); cout << endl; //show state of restaurant
		//wait for key (step by step)
		if (simulation_type == 2)
		{
			getchar(); getchar();
		}
		//execute the earliest event
		restaurant.GetEventList()->First()->Execute();
		//delete the earliest event
		restaurant.GetEventList()->DeleteFirst();
		//end of initial phase
		if (initial_phase && Client::GetLastClientId()==6000)
		{
			initial_phase = false;
			Statistics::Reset(restaurant.GetTime()); //reset statistics
		}
		//save statistics to file
		if (!initial_phase)
		{
			SaveToFile();
		}
	}
	cout << "\nSimulation completed!\n\n";
	//my_file_1.close();
	//my_file_2.close();
	//my_file_3.close();
	//my_file_4.close();
	//my_file_5.close();
	//my_file_6.close();
	//my_file_7.close();
	getchar(); getchar();

    return 0;
}

void ShowMenu()
{
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
}
void SaveToFile()
{
	//my_file_1 << restaurant->GetNumberPeople() << endl;
	//my_file_2 << Statistics::current_size_queue_table_ << endl;//restaurant->GetSizeQueueTable() << endl;
	//my_file_3 << Statistics::current_size_queue_checkout_ << endl;//restaurant->GetSizeQueueCheckout() << endl;
	//my_file_4 << Statistics::average_time_waiting_table_ << endl;
	//my_file_5 << Statistics::average_time_waiting_waiter_ << endl;
	//my_file_6 << Statistics::average_size_queue_table_ << endl;
	//my_file_7 << Statistics::average_size_queue_checkout_ << endl;
}

