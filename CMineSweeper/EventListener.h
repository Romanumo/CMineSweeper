#pragma once
#include<vector>
#include<SDL.h>

class EventManager;

class EventListener
{
public:
	EventListener(std::vector<Uint32> flags)
		: flags(flags)
	{}

	void Subscribe(EventManager* manager);

	virtual void ReceiveNotification(const SDL_Event& event) = 0;

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