#include "stdafx.h"
#include "table_taken.h"
#include "served_drinks.h"
#include "statistics.h"


TableTaken::TableTaken(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("TableTaken", restaurant, client)
{
	SetTime(generators::s);
}

void TableTaken::Execute()
{
	restaurant_->TakeTable(client_);
}
