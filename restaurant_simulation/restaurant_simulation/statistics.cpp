#include "stdafx.h"
#include "statistics.h"
#include <iostream>

void Statistics::AddTimeWaitingTable(double value)
{
	number_times_waiting_table_++;
	sum_times_waiting_table_ += value;
	average_time_waiting_table_ = sum_times_waiting_table_ / number_times_waiting_table_;
}

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

void Statistics::AddTimeWaitingWaiter(double value)
{
	number_times_waiting_waiter_++;
	sum_times_waiting_waiter_ += value;
	average_time_waiting_waiter_ = sum_times_waiting_waiter_ / number_times_waiting_waiter_;
}

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

std::ostream & operator<<(std::ostream & os, const Statistics & stats)
{
	using std::endl;
	os.width(35);
	os << std::left << "Average time waiting for table: " << stats.average_time_waiting_table_ << endl;
	os.width(35);
	os << "Average time waiting for waiter: " << stats.average_time_waiting_waiter_ << endl;
	os.width(35);
	os << "Average size of queue to table: " << stats.average_size_queue_table_ << endl;
	os << "Current: " << stats.current_size_queue_table_ << " Max: " << stats.max_size_queue_table_ << endl;
	os.width(35);
	os << "Average size of queue to checkout: " << stats.average_size_queue_checkout_ << endl;
	os << "Current: " << stats.current_size_queue_checkout_ << " Max: " << stats.max_size_queue_checkout_ << endl;
	return os;
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