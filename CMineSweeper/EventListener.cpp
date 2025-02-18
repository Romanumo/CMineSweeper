#pragma once
#include<vector>
#include<SDL.h>
#include"EventListener.h"
#include"EventManager.h"

void EventListener::Subscribe(EventManager* manager)
{
	manager->AddSubscriber(this);
}
