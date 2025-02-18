#pragma once
#include <SDL.h>
#include <vector>

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
				subscriber->ReceiveNotification(event.type);
			}
		}
	}

	EventManager() = default;

private:
	std::vector<EventListener*> subscribers;
};

class EventListener
{
public:
	EventListener(EventManager* manager, std::vector<Uint32> flags)
	{
		this->flags = flags;
		manager->AddSubscriber(this);
	}

	virtual void ReceiveNotification(Uint32 flag) = 0;

	bool IsInterested(Uint32 interestFlag)
	{
		for (Uint32& flag : flags)
		{
			if (flag == interestFlag) return true;
		}
		return false;
	}

private:
	std::vector<Uint32> flags;
};