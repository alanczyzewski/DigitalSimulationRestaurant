#include "stdafx.h"
#include "statistics.h"
#include <iostream>
namespace statistics
{
	void AddTimeWaitingTable(double value)
	{
		number_times_waiting_table_++;
		sum_times_waiting_table_ += value;
		average_time_waiting_table_ = sum_times_waiting_table_ / number_times_waiting_table_;
	}

	void AddSizeQueueTable(double value, bool increase)
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

	void AddTimeWaitingWaiter(double value)
	{
		number_times_waiting_waiter_++;
		sum_times_waiting_waiter_ += value;
		average_time_waiting_waiter_ = sum_times_waiting_waiter_ / number_times_waiting_waiter_;
	}

	void AddSizeQueueCheckout(double value, bool increase)
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

	void ShowStatistics()
	{
		using std::cout;
		using std::endl;
		cout.width(35);
		cout << std::left << "Average time waiting for table: " << average_time_waiting_table_ << endl;
		//cout << "Sum of times: " << sum_times_waiting_table_ << " Groups waiting for table: " << number_times_waiting_table_ << endl;
		cout.width(35);
		cout << "Average time waiting for waiter: " << average_time_waiting_waiter_ << endl;
		//cout << "Sum of times: " << sum_times_waiting_waiter_ << " Groups waiting for waiter: " << number_times_waiting_waiter_ << endl;
		cout.width(35);
		cout << "Average size of queue to table: " << average_size_queue_table_ << endl;
		cout << "Current: " << current_size_queue_table_ << " Max: " << max_size_queue_table_ << endl;
		cout.width(35);
		cout << "Average size of queue to checkout: " << average_size_queue_checkout_ << endl;
		cout << "Current: " << current_size_queue_checkout_ << " Max: " << max_size_queue_checkout_ << endl;
	}

	void Reset(double simulation_time)
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
	void Reset()
	{
		average_time_waiting_table_ = 0;
		sum_times_waiting_table_ = 0;
		number_times_waiting_table_ = 0;

		average_size_queue_table_ = 0;
		sum_times_queue_table_ = 0;
		weighted_sum_times_queue_table_ = 0;
		current_size_queue_table_ = 0;
		max_size_queue_table_ = 0;
		reference_time_queue_table_ = 0;

		average_time_waiting_waiter_ = 0;
		sum_times_waiting_waiter_ = 0;
		number_times_waiting_waiter_ = 0;

		average_size_queue_checkout_ = 0;
		sum_times_queue_checkout_ = 0;
		weighted_sum_times_queue_checkout_ = 0;
		current_size_queue_checkout_ = 0;
		max_size_queue_checkout_ = 0;
		reference_time_queue_checkout_ = 0;
	}
}