#include "stdafx.h"
#include "event.h"
void Event::SetTime(double time) { event_time_ = restaurant_->GetTime() + time; }