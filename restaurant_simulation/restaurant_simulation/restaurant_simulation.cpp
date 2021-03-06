// restaurant_simulation.cpp : Defines the entry point for the console application.
// Digital simulation - Alan Czyzewski

#include "stdafx.h"
#include <iostream>
#include "restaurant.h"
#include "client.h"
#include "statistics.h"
#include <fstream>
#include <array>
using std::cout;
using std::endl;
using std::cin;
enum simulation_type { Continuous = 1, StepByStep };
simulation_type type;
const int number_simulations = 10;
std::array<std::ofstream, 5> files;
std::array<std::string, 5> files_names{ "\\NumberPeople.csv", "\\AverageTimeQueueTable.csv","\\AverageTimeWaitingWaiter.csv", 
										"\\AverageSizeQueueTable.csv", "\\AverageSizeQueueCheckout.csv" };
void RunSimulation(Restaurant &);
void ShowMenu();
void DisplaySimulationInfo(Restaurant &);
void SetFilesToSave(int);
void SaveStatistics(Restaurant &);

int main()
{
	Restaurant restaurant[number_simulations];
	auto ptr = &generators::seeds[0];
	int i = 0;
	for (auto & rest : restaurant)
	{
		cout << ++i << ". simulation\n\n";
		Client::ResetIterator();
		//SetFilesToSave(i);
		RunSimulation(rest);
		generators::seed = *(++ptr);
	}
	cout << "It's over. All simulations are completed.\n";
	getchar(); getchar();
    return 0;
}

void RunSimulation(Restaurant & restaurant)
{
	ShowMenu();
	restaurant.SetStartPoint();
	const int max_clients = 15000;
	bool initial_phase = true;
	//main simulation loop
	while (Client::GetLastClientId() <= max_clients)
	{
		restaurant.SetTime(); //set simulation time
	    DisplaySimulationInfo(restaurant);
		if (type == StepByStep)
		{
			cout << "Enter the key...";
			getchar();
			cout << endl;
		}
		cout << endl << endl;
		restaurant.ExecuteFirstEvent(); //execute the earliest event
		restaurant.DeleteFirstEvent(); //delete the earliest event
		
		if (initial_phase && Client::GetLastClientId() >= 8000) //end of initial phase
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
			restaurant.ResetStatistics();
		}
		if (!initial_phase)
		{
			//SaveStatistics(restaurant);
		}
	}
	cout << "FINAL RESULTS:\n";
	DisplaySimulationInfo(restaurant);
	cout << "\nSimulation completed!\n\n";
	getchar();
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

void DisplaySimulationInfo(Restaurant & restaurant)
{
	cout << "Simulation Time: " << restaurant.GetTime() << endl; //show simulation time
	cout << *(restaurant.event_list_) << endl; //show event list
	cout << *(restaurant.stats_) << endl; //show statistics
	cout << restaurant << endl; //show state of restaurant
}
void SetFilesToSave(int n)
{
	for (auto &file : files)
	{
		if (file.is_open())
			file.close();
	}
	auto name = files_names.begin();
	for (auto &file : files)
	{
		std::string path = "Results\\";
		path += std::to_string(n) + *name;
		++name;
		file.open(path);
		file.precision(8);
	}
}

void SaveStatistics(Restaurant & restaurant)
{
	files[0] << restaurant.GetNumberPeople() << endl;
	files[1] << restaurant.stats_->average_time_waiting_table_ << endl;
	files[2] << restaurant.stats_->average_time_waiting_waiter_ << endl;
	files[3] << restaurant.stats_->average_size_queue_table_ << endl;
	files[4] << restaurant.stats_->average_size_queue_checkout_ << endl;
}

