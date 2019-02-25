#include "mutex.h"

int poor;
std::mutex mut;
//std::lock_guard<std::mutex> lg;


enum coltype{INT,DOUBLE,STRING};

int poor_mutex()
{
	mut.lock();
	mut.unlock();
	return 0;
}

struct school
{
	int population;
	int year;
};

struct school zju;

int test_mutex()
{
	return 0;
}




