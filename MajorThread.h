#ifndef __MAJOR_THREAD_H__
#define __MAJOR_THREAD_H__
//-------------------------------------------------------------------------------------------------------------------
// Class majors thread, which creates other threads, receive values from STDIN, pushed it in deque and calculate smallest multiple.
//-------------------------------------------------------------------------------------------------------------------


#include "Define.h"
#include "OtherThread.h"
//-------------------------------------------------------------------------------------------------------------------
class MajorThread
{
public:
	MajorThread();
	~MajorThread();

	int start();																			// start program (start others threads, start read from STDIN and etc)

private:

	size_t max;																			// max value from STDIN

	std::queue<size_t>	queue;																// queue foe values from STDIN
	std::mutex			mutexQueue;															// for synchronization access to queue

	std::array	<std::shared_ptr<OtherThread>	, NUMBER_OF_OTHERS_THREAD> otherThreads;	// objects other threads
	std::array	<std::thread					, NUMBER_OF_OTHERS_THREAD> threads;			// others thread

	std::array	<Map							, NUMBER_OF_OTHERS_THREAD> maps;			// maps for each other thread
	std::array	<std::mutex						, NUMBER_OF_OTHERS_THREAD> mutexMap;		// for synchronization access to map

	std::array	<std::mutex						, NUMBER_OF_OTHERS_THREAD> mutexExit;		// for signal exit thread
	std::array	<std::condition_variable		, NUMBER_OF_OTHERS_THREAD> varExit;			// for signal exit thread
	std::array	<std::atomic<bool>				, NUMBER_OF_OTHERS_THREAD> exit;			// to prevent spirius wakeup signal exit thread	
	
	std::condition_variable varCalc;														// for signal calc
	std::mutex				mutexCalc;														// for signal calc
	std::atomic<bool>		calc;															// to prevent spirius wakeup signal calc

	std::atomic<bool> exitSignal;															// signal to other threads, what data is end

	inline int pushQueue(size_t value);
	inline int readData();
	inline int waitExitOtherThreads();
	inline int startOtherThreads();

	int mergeMaps();
	int mergeTwoMap(Map & base, Map &joined);
	int calcSmallMult();
};
//-------------------------------------------------------------------------------------------------------------------
#endif	// __MAJOR_THREAD_H__

