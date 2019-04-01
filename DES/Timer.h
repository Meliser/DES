#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_
#include <thread>
#include <iostream>
#include <string>
using namespace std;
typedef chrono::steady_clock::time_point Time;

class Timer {
		Time start;
		Time end;
		chrono::duration<float> duration;
		string funcName;
		
	public:
		Timer(const string& func);
		~Timer();
	};

#endif

