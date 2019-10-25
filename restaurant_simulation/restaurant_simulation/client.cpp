#include "stdafx.h"
#include "client.h"
#include "generators.h"
#include <iostream>

double Client::id_iterator_ = 0;

Client::Client() : kId(++id_iterator_)
{
	double random = generators::Uniform();
	if (random <= generators::p1_)
		number_people_ = 1;
	else if (random <= generators::p1_ + generators::p2_)
		number_people_ = 2;
	else if (random <= 1 - generators::p4_)
		number_people_ = 3;
	else
		number_people_ = 4;
	served_drinks_ = false;
	random = generators::Uniform();
	if (random <= 0.7) //70%
		run_away_ = false;
	else //30%
		run_away_ = true;

	time_buffet_ = generators::Normal(generators::mi_b_, generators::sigma_b_);
	time_checkout_ = generators::Exponential(generators::lambda_p_);
	time_consumption_ = generators::Exponential(generators::lambda_f_);
	time_service_drinks_ = generators::Exponential(generators::lambda_n_);
	time_service_meals_ = generators::Exponential(generators::lambda_j_);
	number_seats_at_table_ = 0;

	time_start_table_ = 0;
	time_start_waiter_ = 0;
}

std::ostream & operator<<(std::ostream & os, const Client & client)
{
	os << "Client ID: " << std::right;
	os.width(5);
	os << client.kId << " Number of people: " << client.number_people_ << " Run away? " << (client.run_away_ ? "YES" : "NO");
	return os;
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
