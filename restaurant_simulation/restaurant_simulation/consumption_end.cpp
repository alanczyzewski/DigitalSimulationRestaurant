#include "stdafx.h"
#include <memory>
#include "consumption_end.h"
#include "checkout_service_end.h"


ConsumptionEnd::ConsumptionEnd(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("ConsumptionEnd", restaurant, client)
{
	SetTime(client_->GetTimeConsumption());
}

void ConsumptionEnd::Execute()
{
	restaurant_->DeleteClientFromTable(client_);
}
