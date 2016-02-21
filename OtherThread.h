#ifndef __OTHER_THREAD_H__
#define __OTHER_THREAD_H__
//-------------------------------------------------------------------------------------------------------------------
#include <thread>
#include <condition_variable>

#include "Define.h"
#include "Calc.h"
//-------------------------------------------------------------------------------------------------------------------
class OtherThread
{
public:
	OtherThread(std::queue<size_t> &Queue, std::mutex &MutexQueue, Map &_map, std::mutex &MutexMap,
		std::mutex &MutexExit, std::condition_variable	&VarExit, std::atomic<bool> &Exit,
		std::condition_variable &VarCalc, std::mutex &MutexCalc, std::atomic<bool> &Calc, std::atomic<bool> &ExitSignal);
	~OtherThread();

	int startProcess();

private:
	std::queue<size_t>		&queue;			// queue foe values from STDIN
	std::mutex				&mutexQueue;	// for synchronization access to queue

	Map						&map;			// maps for each other thread
	std::mutex				&mutexMap;		// for synchronization access to map

	std::mutex				&mutexExit;		// for signal exit thread
	std::condition_variable	&varExit;		// for signal exit thread
	std::atomic<bool>		&exit;			// to prevent spirius wakeup signal exit thread	

	std::condition_variable &varCalc;		// for signal calc
	std::mutex				&mutexCalc;		// for signal calc
	std::atomic<bool>		&calc;			// to prevent spirius wakeup signal calc

	std::atomic<bool>		&exitSignal;	// signal to other threads, what data is end

	size_t value;

	inline int getQueue();
	inline int fact();
	
};
//-------------------------------------------------------------------------------------------------------------------
#endif	// __MAJOR_THREAD_H__
