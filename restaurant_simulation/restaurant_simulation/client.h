#pragma once
#include <memory>

class Client //class representing group of clients (1, 2, 3 or 4 people)
{
public:
	Client();
	static int GetLastClientId() { return id_iterator_; }
	int GetId() const { return kId; }
	int GetNumberPeople() const { return number_people_; }
	int GetNumberSeats() const { return number_seats_at_table_; }
	void SetNumberSeats(int seats, int seats2 = 0) { number_seats_at_table_ = seats; number_seats_at_table_2_ = seats2; }
	int GetNumberSeats2() const { return number_seats_at_table_2_; }
	bool GetServedDrinks() const { return served_drinks_; }
	void SetServedDrinks() { served_drinks_ = true; }
	double GetTimeBuffet() const { return time_buffet_; }
	double GetTimeServiceDrinks() const { return time_service_drinks_; }
	double GetTimeServiceMeals() const { return time_service_meals_; }
	double GetTimeConsumption() const { return time_consumption_; }
	double GetTimeCheckout() const { return time_checkout_; }
	friend std::ostream & operator<<(std::ostream &, const Client &);

	void SetStartTimeTable(double value) { time_start_table_ = value; }
	double GetStartTimeTable() const { return time_start_table_; }
	void SetStartTimeWaiter(double value) { time_start_waiter_ = value; }
	double GetStartTimeWaiter() const { return time_start_waiter_; }
	
	static void ResetIterator() { id_iterator_ = 0; }
private:
	static int id_iterator_;
	const int kId; //group ID
	int number_people_; //number of people in the group
	int number_seats_at_table_; //number of seats at table (taken by client)
	int number_seats_at_table_2_; //number of seats at second table (taken by client)

	double time_buffet_; //time spent at the buffet
	double time_service_drinks_; //waiting time for serving drinks
	double time_service_meals_; //waiting time for serving meals
	double time_consumption_;
	double time_checkout_; //time spent at the checkout
	bool served_drinks_; //if true, client got drinks

	//statistics
	double time_start_table_;
	double time_start_waiter_;
};

