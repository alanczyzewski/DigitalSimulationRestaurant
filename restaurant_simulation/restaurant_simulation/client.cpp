#include "stdafx.h"
#include "client.h"
#include "generators.h"
#include <iostream>

double Client::id_iterator_ = 1;

Client::Client() : kId(id_iterator_++)
{
	double random = Generators::Uniform();
	if (random <= Generators::p1_)
		number_people_ = 1;
	else if (random <= Generators::p1_ + Generators::p2_)
		number_people_ = 2;
	else if (random <= 1 - Generators::p4_)
		number_people_ = 3;
	else
		number_people_ = 4;
	served_drinks_ = false;
	random = Generators::Uniform();
	if (random <= 0.7) //70%
		run_away_ = false;
	else //30%
		run_away_ = true;

	time_buffet_ = Generators::Normal(Generators::mi_b_, Generators::sigma_b_);
	time_checkout_ = Generators::Exponential(Generators::lambda_p_);
	time_consumption_ = Generators::Exponential(Generators::lambda_f_);
	time_service_drinks_ = Generators::Exponential(Generators::lambda_n_);
	time_service_meals_ = Generators::Exponential(Generators::lambda_j_);
	number_seats_at_table_ = 0;

	time_start_table_ = 0;
	time_start_waiter_ = 0;
}


double Client::GetLastClientId()
{
	return id_iterator_ - 1;
}

double Client::GetId()
{
	return kId;
}

int Client::GetNumberPeople()
{
	return number_people_;
}

int Client::GetNumberSeats()
{
	return number_seats_at_table_;
}

void Client::SetNumberSeats(int seats)
{
	number_seats_at_table_ = seats;
}

bool Client::GetServedDrinks()
{
	return served_drinks_;
}

void Client::SetServedDrinks()
{
	served_drinks_ = true;
}

bool Client::GetRunAway()
{
	return run_away_;
}

int Client::GetTimeBuffet()
{
	return time_buffet_;
}

int Client::GetTimeCheckout()
{
	return  time_checkout_;
}

int Client::GetTimeConsumption()
{
	return time_consumption_;
}

int Client::GetTimeServiceDrinks()
{
	return time_service_drinks_;
}

int Client::GetTimeServiceMeals()
{
	return time_service_meals_;
}
/*
void Client::ShowInfo()
{
	std::cout << "id_iterator_ " << id_iterator_ << std::endl;
	std::cout << "kId " << kId << std::endl;
	std::cout << "number_people_ " << number_people_ << std::endl;
	std::cout << "number_seats_at_table_" << number_seats_at_table_ << std::endl;
	std::cout << "time_buffet_ " << time_buffet_ << std::endl;
	std::cout << "time_service_drinks_ " << time_service_drinks_<< std::endl;
	std::cout << "time_service_meals_ " << time_service_meals_<< std::endl;
	std::cout << "time_consumption_ " << time_consumption_ << std::endl;
	std::cout << "time_checkout_ " << time_checkout_ << std::endl;
	std::cout << "served_drinks_ " << served_drinks_<< std::endl;
	std::cout << "run_away_ " << run_away_<< std::endl;

}
*/

void Client::SetStartTimeTable(double v)
{
	time_start_table_ = v;
}

double Client::GetStartTimeTable()
{
	return time_start_table_;
}

void Client::SetStartTimeWaiter(double v)
{
	time_start_waiter_ = v;
}

double Client::GetStartTimeWaiter()
{
	return time_start_waiter_;
}
