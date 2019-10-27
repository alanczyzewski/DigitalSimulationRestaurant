#include "stdafx.h"
#include "client.h"
#include "generators.h"
#include <iostream>

int Client::id_iterator_ = 0;

Client::Client() : kId(++id_iterator_)
{
	double random = generators::Uniform();
	if (random <= generators::p1)
		number_people_ = 1;
	else if (random <= generators::p1 + generators::p2)
		number_people_ = 2;
	else if (random <= 1 - generators::p4)
		number_people_ = 3;
	else
		number_people_ = 4;
	served_drinks_ = false;

	time_buffet_ = generators::Normal(generators::mi_b, generators::sigma_b);
	time_checkout_ = generators::Exponential(generators::lambda_p);
	time_consumption_ = generators::Exponential(generators::lambda_f);
	time_service_drinks_ = generators::Exponential(generators::lambda_n);
	time_service_meals_ = generators::Exponential(generators::lambda_j);
	number_seats_at_table_ = 0;

	time_start_table_ = 0;
	time_start_waiter_ = 0;
}

std::ostream & operator<<(std::ostream & os, const Client & client)
{
	os << "Client ID: " << std::right;
	os.width(5);
	os << client.kId << " Number of people: " << client.number_people_;
	return os;
}

