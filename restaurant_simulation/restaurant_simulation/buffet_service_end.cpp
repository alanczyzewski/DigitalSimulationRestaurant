#include "stdafx.h"
#include "buffet_service_end.h"
#include "checkout_service_end.h"


BuffetServiceEnd::BuffetServiceEnd(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("BuffetServiceEnd", restaurant, client)
{
	SetTime(client_->GetTimeBuffet());
}

void BuffetServiceEnd::Execute()
{
	restaurant_->DeleteClientFromBuffet(client_);
}
