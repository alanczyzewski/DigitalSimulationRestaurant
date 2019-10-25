#pragma once
#include <vector>

namespace statistics
{

	//average time waiting for table
	static double average_time_waiting_table_ = 0;
	static double sum_times_waiting_table_ = 0;
	static double number_times_waiting_table_ = 0;
	//average size of queue to table
	static double average_size_queue_table_ = 0;
	static double sum_times_queue_table_ = 0;
	static double weighted_sum_times_queue_table_ = 0;
	static double current_size_queue_table_ = 0;
	static double max_size_queue_table_ = 0;
	static double reference_time_queue_table_ = 0;
	//average time waiting for waiter	
	static double average_time_waiting_waiter_ = 0;
	static double sum_times_waiting_waiter_ = 0;
	static double number_times_waiting_waiter_ = 0;
	//average size of queue to checkout	
	static double average_size_queue_checkout_ = 0;
	static double sum_times_queue_checkout_ = 0;
	static double weighted_sum_times_queue_checkout_ = 0;
	static double current_size_queue_checkout_ = 0;
	static double max_size_queue_checkout_ = 0;
	static double reference_time_queue_checkout_ = 0;
	//average number of clients
	//double average_number_clients_;

	void AddTimeWaitingTable(double);
	void AddSizeQueueTable(double, bool);
	void AddTimeWaitingWaiter(double);
	void AddSizeQueueCheckout(double, bool);
	void ShowStatistics();
	void Reset(double);
	void Reset();

}

