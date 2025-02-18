#pragma once
#include <SDL.h>
#include <vector>
#include "EventListener.h"

class EventManager
{
public:
	void AddSubscriber(EventListener* subscriber)
	{
		subscribers.push_back(subscriber);
	}

	void NotifySubsribers(const SDL_Event& event)
	{
		for (EventListener* subscriber : subscribers)
		{
			if (subscriber->IsInterested(event.type))
			{
				subscriber->ReceiveNotification(event);
			}
		}
	}

	EventManager() = default;

private:
	std::vector<EventListener*> subscribers;
};