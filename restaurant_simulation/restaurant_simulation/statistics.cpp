#include "stdafx.h"
#include "statistics.h"
#include <iostream>

double Statistics::average_time_waiting_table_ = 0;
double Statistics::sum_times_waiting_table_ = 0;
double Statistics::number_times_waiting_table_ = 0;
void Statistics::AddTimeWaitingTable(double value)
{
	number_times_waiting_table_++;
	sum_times_waiting_table_ += value;
	average_time_waiting_table_ = sum_times_waiting_table_ / number_times_waiting_table_;
}

double Statistics::average_size_queue_table_ = 0;
double Statistics::weighted_sum_times_queue_table_ = 0;
double Statistics::sum_times_queue_table_ = 0;
double Statistics::current_size_queue_table_ = 0;
double Statistics::max_size_queue_table_ = 0;
double Statistics::reference_time_queue_table_ = 0;
void Statistics::AddSizeQueueTable(double value, bool increase)
{
	weighted_sum_times_queue_table_ += current_size_queue_table_ * value;
	sum_times_queue_table_ += value;
	average_size_queue_table_ = weighted_sum_times_queue_table_ / sum_times_queue_table_;
	if (increase) //if true, the size has increased
	{
		current_size_queue_table_++;
		if (current_size_queue_table_ > max_size_queue_table_)
			max_size_queue_table_ = current_size_queue_table_;
	}
	else
		current_size_queue_table_--;
}

double Statistics::average_time_waiting_waiter_ = 0;
double Statistics::sum_times_waiting_waiter_ = 0;
double Statistics::number_times_waiting_waiter_ = 0;
void Statistics::AddTimeWaitingWaiter(double value)
{
	number_times_waiting_waiter_++;
	sum_times_waiting_waiter_ += value;
	average_time_waiting_waiter_ = sum_times_waiting_waiter_ / number_times_waiting_waiter_;
}

double Statistics::average_size_queue_checkout_ = 0;
double Statistics::weighted_sum_times_queue_checkout_ = 0;
double Statistics::sum_times_queue_checkout_ = 0;
double Statistics::current_size_queue_checkout_ = 0;
double Statistics::max_size_queue_checkout_ = 0;
double Statistics::reference_time_queue_checkout_ = 0;
void Statistics::AddSizeQueueCheckout(double value, bool increase)
{
	weighted_sum_times_queue_checkout_ += current_size_queue_checkout_ * value;
	sum_times_queue_checkout_ += value;
	average_size_queue_checkout_ = weighted_sum_times_queue_checkout_ / sum_times_queue_checkout_;
	if (increase) //if true, the size has increased
	{
		current_size_queue_checkout_++;
		if (current_size_queue_checkout_ > max_size_queue_checkout_)
			max_size_queue_checkout_ = current_size_queue_checkout_;
	}
	else
		current_size_queue_checkout_--;
}

void Statistics::ShowStatistics()
{
	using std::cout;
	using std::endl;
	cout << "Average time waiting for table: " << average_time_waiting_table_ << endl;
	//cout << "Sum of times: " << sum_times_waiting_table_ << " Groups waiting for table: " << number_times_waiting_table_ << endl;
	cout << "Average time waiting for waiter: " << average_time_waiting_waiter_ << endl;
	//cout << "Sum of times: " << sum_times_waiting_waiter_ << " Groups waiting for waiter: " << number_times_waiting_waiter_ << endl;
	cout << "Average size of queue to table: " << average_size_queue_table_ << endl;
	cout << "Current: " << current_size_queue_table_ << " Max: " << max_size_queue_table_ << endl;
	cout << "Average size of queue to checkout: " << average_size_queue_checkout_ << endl;
	cout << "Current: " << current_size_queue_checkout_ << " Max: " << max_size_queue_checkout_ << endl;
}

void Statistics::Reset(double simulation_time)
{
	average_time_waiting_table_ = 0;
	sum_times_waiting_table_ = 0;
	number_times_waiting_table_ = 0;

	average_size_queue_table_ = current_size_queue_table_;
	max_size_queue_table_ = current_size_queue_table_;
	weighted_sum_times_queue_table_ = 0;
	sum_times_queue_table_ = 0;
	reference_time_queue_table_ = simulation_time;

	average_time_waiting_waiter_ = 0;
	sum_times_waiting_waiter_ = 0;
	number_times_waiting_waiter_ = 0;

	average_size_queue_checkout_ = current_size_queue_checkout_;
	max_size_queue_checkout_ = current_size_queue_checkout_;
	weighted_sum_times_queue_checkout_ = 0;
	sum_times_queue_checkout_ = 0;
	reference_time_queue_checkout_ = simulation_time;
}


void Statistics::SaveStatisticsToFile()
{
	;
}
