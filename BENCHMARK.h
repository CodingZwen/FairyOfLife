#include <iostream>
#include <memory>
#include <chrono>
#pragma once



class Timer
{
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{

		Stop();
	}

private:
	//milli > micro > nano > piko
	void Stop()
	{	//oder auto -> wir merken uns vergangene zeit
		//std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint = std::chrono::high_resolution_clock::now();
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start; //micro sek
		double ms = duration * 0.001; // millisec

		std::cout << "microsek: " << duration << " millisec: " << ms << std::endl;

	}


	typedef std::chrono::time_point < std::chrono::high_resolution_clock> zeit;
	zeit m_StartTimepoint;

};



class BENCHMARK
{

	


public:
	BENCHMARK();
	~BENCHMARK();
};

