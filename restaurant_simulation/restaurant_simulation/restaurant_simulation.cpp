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
enum simulation_type { Continuous = 1, StepByStep };
simulation_type type;
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

	const int max_clients = 10000;
	bool initial_phase = true;
	// main simulation loop
	while (Client::GetLastClientId() <= max_clients)
	{
		restaurant.SetTime(); //set simulation time
		//display
		cout << "Simulation Time: " << restaurant.GetTime() << endl; //show simulation time
		restaurant.GetEventList()->ShowEventList(); cout << endl; //show event list
		statistics::ShowStatistics(); cout << endl; //show statistics
		restaurant.ShowState(); cout << endl; //show state of restaurant
		if (type == StepByStep)
		{
			cout << "Enter the key...";
			getchar(); //wait for key (step by step)
			cout << endl;
		}
		cout << endl;
		restaurant.GetEventList()->First()->Execute(); //execute the earliest event
		restaurant.GetEventList()->DeleteFirst(); //delete the earliest event
		if (initial_phase && Client::GetLastClientId()==6000) //end of initial phase
		{
			cout << "The initial phase has ended.\n";
			if (type == Continuous)
			{
				char ch;
				cout << "If you want to switch on Step by step, enter y... ";
				cin >> ch;
				if (ch == 'y' or ch == 'Y')
				{
					type = StepByStep;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			initial_phase = false;
			statistics::Reset(restaurant.GetTime()); //reset statistics
		}
		if (!initial_phase)
		{
			SaveToFile(); //save statistics to file
		}
	}
	cout << "\nSimulation completed!\n\n";
	getchar();

    return 0;
}

void ShowMenu()
{
	cout << "Choose the simulation type\n1. Continuous\n2. Step by step" << endl;
	int x;
	while (!(cin >> x) || (x != 1 && x != 2))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("CLS");
		cout << "Choose type of simulation\n1. Continuous\n2. Step by step\n";
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	type = static_cast<simulation_type>(x);
	cout << "Chosen type: ";
	if (x == 1)
		cout << "Continuous\n\n";
	else
		cout << "Step by step\n\n";
}
void SaveToFile()
{
	//my_file_1 << restaurant->GetNumberPeople() << endl;
	//my_file_2 << current_size_queue_table_ << endl;//restaurant->GetSizeQueueTable() << endl;
	//my_file_3 << current_size_queue_checkout_ << endl;//restaurant->GetSizeQueueCheckout() << endl;
	//my_file_4 << average_time_waiting_table_ << endl;
	//my_file_5 << average_time_waiting_waiter_ << endl;
	//my_file_6 << average_size_queue_table_ << endl;
	//my_file_7 << average_size_queue_checkout_ << endl;
}

