#pragma once
#include <vector>

class Statistics
{
public:
	static void AddTimeWaitingTable(double);
	static void AddSizeQueueTable(double, bool);
	static void AddTimeWaitingWaiter(double);
	static void AddSizeQueueCheckout(double, bool);
	static void ShowStatistics();
	static void Reset(double);

	//average time waiting for table
	static double average_time_waiting_table_;
	static double sum_times_waiting_table_;
	static double number_times_waiting_table_;
	//average size of queue to table
	static double average_size_queue_table_;
	static double sum_times_queue_table_;
	static double weighted_sum_times_queue_table_;
	static double current_size_queue_table_;
	static double max_size_queue_table_;
	static double reference_time_queue_table_;
	//average time waiting for waiter	
	static double average_time_waiting_waiter_;
	static double sum_times_waiting_waiter_;
	static double number_times_waiting_waiter_;
	//average size of queue to checkout	
	static double average_size_queue_checkout_;
	static double sum_times_queue_checkout_;
	static double weighted_sum_times_queue_checkout_;
	static double current_size_queue_checkout_;
	static double max_size_queue_checkout_;
	static double reference_time_queue_checkout_;
	//average number of clients
	static double average_number_clients_;

};

