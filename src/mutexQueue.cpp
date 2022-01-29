#include <mutexQueue.h>
void mutexQueue::lock(void)
{
	queueLock.lock(); 
	if(queue.empty() && theLock.try_lock()) //Note, LTR: We don't try the lock if the queue isn't empty
	{
		queueLock.unlock();
		return;
	}
	//If we get here, then the lock was not able to be acquired directly
	//Insert our own ticket at the back of the queue. When a thread finishes using the lock, it is required to 
	std::atomic_flag ticket;; //Making an assumption that this on the stack is okay
	ticket.clear();
	queue.push_back(&ticket);
	queueLock.unlock(); 
	
	while(!ticket.test())
	{
		std::this_thread::yield();
	}
	//At this point, We've been told that the lock is available!
	theLock.lock();
	queueLock.lock();
	queue.pop_front();
	queueLock.unlock();
	
}

void mutexQueue::unlock(void)
{
	queueLock.lock();
	theLock.unlock();
	if(!queue.empty())
	{
		queue.front()->test_and_set(); //Tell the waiting thread that the lock is available
	}
	queueLock.unlock();
}

bool mutexQueue::trylock(void)
{
	queueLock.lock(); 
	if(queue.empty() && theLock.try_lock()) //Note, LTR: We don't try the lock if the queue isn't empty
	{
		queueLock.unlock();
		return true;
	}
	queueLock.unlock();
	return false;
}
