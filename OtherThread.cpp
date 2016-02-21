#include "OtherThread.h"
//-------------------------------------------------------------------------------------------------------------------
OtherThread::OtherThread(std::queue<size_t> &Queue, std::mutex &MutexQueue, Map &_map, std::mutex &MutexMap,
	std::mutex &MutexExit, std::condition_variable	&VarExit, std::atomic<bool> &Exit,
	std::condition_variable &VarCalc, std::mutex &MutexCalc, std::atomic<bool> &Calc, std::atomic<bool> &ExitSignal) :
	queue(Queue), mutexQueue(MutexQueue), map(_map), mutexMap(MutexMap), mutexExit(MutexExit), varExit(VarExit),
	exit(Exit), varCalc(VarCalc), mutexCalc(MutexCalc), calc(Calc), exitSignal(ExitSignal), value(0)
{
}
//-------------------------------------------------------------------------------------------------------------------
OtherThread::~OtherThread()
{
}
//-------------------------------------------------------------------------------------------------------------------
int OtherThread::startProcess()
{
	while (!exitSignal)
	{
		std::unique_lock<std::mutex> lock(mutexCalc);

		if (!calc && varCalc.wait_for(lock, std::chrono::milliseconds(DEFAULT_TIME_WAITING_VALUE_MILLISEC)) 
			== std::cv_status::no_timeout)
		{
			calc = false;
			if (getQueue() != EXECUTE_ERROR)
			{
				fact();
			}
				
		}
	
	}

	std::unique_lock<std::mutex> lock(mutexExit);
	exit = true;
	std::notify_all_at_thread_exit(varExit, std::move(lock));

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int OtherThread::getQueue()
{
	std::lock_guard<std::mutex> lock(mutexQueue);
	if (!queue.empty())
	{
		value = queue.front();
		queue.pop();
		return EXECUTE_SUCCESSFULLY;
	}
	return EXECUTE_ERROR;
}
//-------------------------------------------------------------------------------------------------------------------
int  OtherThread::fact()
{
	std::lock_guard<std::mutex> lock(mutexMap);
	Calc::factorization(value,map);
	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
