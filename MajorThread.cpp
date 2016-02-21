#include "MajorThread.h"
//-------------------------------------------------------------------------------------------------------------------
MajorThread::MajorThread() :max(1), calc(false), exitSignal(false)
{
	int size = otherThreads.size();
	for (int i = 0; i < size; ++i)
	{
		exit[i] = false;
		otherThreads[i] = std::shared_ptr<OtherThread>(new OtherThread(queue, mutexQueue, maps[i], mutexMap[i], mutexExit[i], varExit[i], exit[i], varCalc, mutexCalc, calc, exitSignal));
	}
}
//-------------------------------------------------------------------------------------------------------------------
MajorThread::~MajorThread()
{
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::start()
{
	startOtherThreads();
	readData();
	waitExitOtherThreads();
	mergeMaps();	
	calcSmallMult();
	

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::pushQueue(size_t value)
{
	std::lock_guard<std::mutex> lock(mutexQueue);
	queue.push(value);
	if (value > max) max = value;
	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::readData()
{
	std::string line;
	do {
		getline(std::cin, line);	
		pushQueue(static_cast<size_t>(atoi(line.c_str())));
		calc = true;
		varCalc.notify_one();
	} while (!line.empty());

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::waitExitOtherThreads()
{
	exitSignal = true;
	int size = threads.size();
	for (int i = 0; i < size; ++i)
	{
		std::unique_lock<std::mutex> lock(mutexExit[i]);
		while (!exit[i])
			varExit[i].wait(lock);
	}

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::startOtherThreads()
{
	int size = threads.size();
	for (int i = 0; i < size; ++i)
	{
		threads[i] = std::thread(&OtherThread::startProcess, otherThreads[i]);
		threads[i].detach();
	}

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::mergeMaps()
{
	int size = maps.size();
	for (int i = 1; i < size; ++i)
		mergeTwoMap(maps[0],maps[i]);
	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::mergeTwoMap(Map & base,Map &joined)
{
	for (auto m : joined)
	{
		if (!base.count(m.first) || base[m.first] < m.second)
			base[m.first] = m.second;
	}
	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int MajorThread::calcSmallMult()
{
	uint64_t result;
	Map		 resMap;

	Calc::smallMult(max, maps[0], result);
	Calc::factorizationR(result, resMap);

	std::cout << "result: ";
	
	auto m = resMap.begin();
	while ( m != resMap.end())
	{
		std::cout << m->first << "^" << m->second;
		if (++m != resMap.end())
		{
			std::cout << "*";
		}
			
	}
	std::cout << std::endl;

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
