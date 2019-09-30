#pragma once

class Client //class representing group of clients (1, 2, 3 or 4 people)
{
public:
	Client();
	~Client();
	static double GetLastClientId();
	double GetId();
	int GetNumberPeople();
	int GetNumberSeats();
	void SetNumberSeats(int);
	bool GetServedDrinks();
	void SetServedDrinks();
	bool GetRunAway();
	int GetTimeBuffet();
	int GetTimeServiceDrinks();
	int GetTimeServiceMeals();
	int GetTimeConsumption();
	int GetTimeCheckout();
	//void ShowInfo();

	void SetStartTimeTable(double);
	double GetStartTimeTable();
	void SetStartTimeWaiter(double);
	double GetStartTimeWaiter();
	
private:
	static double id_iterator_;
	const double kId; //group ID
	int number_people_; //number of people in the group
	int number_seats_at_table_; //number of seats at table (taken by client)
	double time_buffet_; //time spent at the buffet
	double time_service_drinks_; //waiting time for serving drinks
	double time_service_meals_; //waiting time for serving meals
	double time_consumption_;
	double time_checkout_; //time spent at the checkout
	bool served_drinks_; //if true, client got drinks
	bool run_away_; //if true, client will run away after alarm

	//statistics
	double time_start_table_;
	double time_start_waiter_;
};

