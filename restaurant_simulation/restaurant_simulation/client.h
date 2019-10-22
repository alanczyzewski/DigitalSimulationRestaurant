#pragma once

class Client //class representing group of clients (1, 2, 3 or 4 people)
{
public:
	Client();
	static double GetLastClientId() { return id_iterator_; }
	double GetId() const { return kId; }
	int GetNumberPeople() const { return number_people_; }
	int GetNumberSeats() const { return number_seats_at_table_; }
	void SetNumberSeats(int seats) { number_seats_at_table_ = seats; }
	bool GetServedDrinks() const { return served_drinks_; }
	void SetServedDrinks() { served_drinks_ = true; }
	bool GetRunAway() const { return run_away_; }
	double GetTimeBuffet() const { return time_buffet_; }
	double GetTimeServiceDrinks() const { return time_service_drinks_; }
	double GetTimeServiceMeals() const { return time_service_meals_; }
	double GetTimeConsumption() const { return time_consumption_; }
	double GetTimeCheckout() const { return time_checkout_; }
	//void ShowInfo();

	void SetStartTimeTable(double value) { time_start_table_ = value; }
	double GetStartTimeTable() const { return time_start_table_; }
	void SetStartTimeWaiter(double value) { time_start_waiter_ = value; }
	double GetStartTimeWaiter() const { return time_start_waiter_; }
	
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

