#pragma once
#include <thread>
#include <mutex>
#include <deque>
#include <atomic>

//!A mutex where threads queue up for access - Giving a more fair access to the resource.
class mutexQueue 
{
	public:
	void lock(void);
	bool trylock(void);
	void unlock(void);
	
	private:
	std::mutex queueLock;
	std::deque<std::atomic_bool *> queue;
	std::mutex theLock;
};

