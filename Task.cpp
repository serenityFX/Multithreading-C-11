

#include "Calc.h"
#include "MajorThread.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
using namespace std;
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	MajorThread maj;
	maj.start();

	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
