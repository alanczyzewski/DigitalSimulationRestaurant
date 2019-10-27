#pragma once
#include <vector>

class Statistics
{
public:
	void AddTimeWaitingTable(double);
	void AddSizeQueueTable(double, bool);
	void AddTimeWaitingWaiter(double);
	void AddSizeQueueCheckout(double, bool);
	friend std::ostream & operator<<(std::ostream &, const Statistics &);
	void Reset(double);

	//average time waiting for table
	double average_time_waiting_table_ = 0;
	double sum_times_waiting_table_ = 0;
	double number_times_waiting_table_ = 0;
	//average size of queue to table
	double average_size_queue_table_ = 0;
	double sum_times_queue_table_ = 0;
	double weighted_sum_times_queue_table_ = 0;
	double current_size_queue_table_ = 0;
	double max_size_queue_table_ = 0;
	double reference_time_queue_table_ = 0;
	//average time waiting for waiter	
	double average_time_waiting_waiter_ = 0;
	double sum_times_waiting_waiter_ = 0;
	double number_times_waiting_waiter_ = 0;
	//average size of queue to checkout	
	double average_size_queue_checkout_ = 0;
	double sum_times_queue_checkout_ = 0;
	double weighted_sum_times_queue_checkout_ = 0;
	double current_size_queue_checkout_ = 0;
	double max_size_queue_checkout_ = 0;
	double reference_time_queue_checkout_ = 0;
	//average number of clients
	//double average_number_clients_;
};

