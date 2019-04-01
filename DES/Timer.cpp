#include "Timer.h"

Timer::Timer(const string& func):funcName(func) {
	start = chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	end = chrono::high_resolution_clock::now();
	duration = end - start;
	cout << "Function: " << funcName << endl;
	cout << "Thread id: " << this_thread::get_id() << endl;
	cout << "Execution time: " << duration.count() << endl;
}


	
