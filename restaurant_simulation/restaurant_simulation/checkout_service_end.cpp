#include "stdafx.h"
#include "checkout_service_end.h"


CheckoutServiceEnd::CheckoutServiceEnd(Restaurant & restaurant, std::shared_ptr<Client> client) : Event("CheckoutServiceEnd", restaurant, client)
{
	SetTime(client_->GetTimeCheckout());
}

void CheckoutServiceEnd::Execute()
{
	restaurant_->DeleteClientFromSystem(client_);
}
