#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <wiring.h>

struct timespec prog_start_time;

unsigned long millis()
{
	return micros()/1000;
}

unsigned long long micros()
{
	struct timespec gettime_now;
	clock_gettime(CLOCK_MONOTONIC, &gettime_now);
	return ((gettime_now.tv_sec - prog_start_time.tv_sec)*1000000 +
			(gettime_now.tv_nsec - prog_start_time.tv_nsec)/1000);
}

void delay(unsigned long ms)
{
	usleep(ms*1000);
}

void delayMicroseconds(unsigned int us)
{
	/* usleep(us); */
	long int start_time;
	long int time_difference;
	struct timespec gettime_now;

	clock_gettime(CLOCK_MONOTONIC, &gettime_now);
	start_time = gettime_now.tv_nsec;		//Get nS value
	while (1)
	{
		clock_gettime(CLOCK_MONOTONIC, &gettime_now);
		time_difference = gettime_now.tv_nsec - start_time;
		if (time_difference < 0)
			time_difference += 1000000000;				//(Rolls over every 1 second)
		if ((unsigned int)time_difference > (us * 1000))		//Delay for # nS
			break;
	}

}
