#include "simulator.h"
#include <queue>
#include <iostream>


#define TRUE 1
#define FALSE 0

#define FROM_A 0
#define FROM_B 1


struct Event {
	float alarm_time;
	int sequence_number;
};

class Timer {
	
	std::queue<Event> timed_events;
	float time_buffer;
	
	void set_timer_for_next_event();
	void handle_next_event_alarm();
	
public:
	
	Timer();
	
	void schedule_alarm(float time, int seq_num);
	
};


Timer::Timer() {
	time_buffer = 0;
}


void Timer::schedule_alarm(float time, int seq_num) {
	
	float alarm_time = get_sim_time() + time;
	
	struct Event new_event;
	new_event.alarm_time = alarm_time;
	new_event.sequence_number = seq_num;
	
	// check if this is the only event 
	if (timed_events.empty()) {
		// if no events scheduled already, handle immediately
		timed_events.push(new_event);
		
	}

}


void Timer::set_timer_for_next_event() {
	
	Event next_event = timed_events.front();
	float time_to_next_alarm = next_event.alarm_time - get_sim_time();
	starttimer(FROM_A, time_to_next_alarm);
	
}


void Timer::handle_next_event_alarm() {
	
	// get event, and pop from queue
	Event triggered_event = timed_events.front();
	timed_events.pop();
	
	std::cout << "HANDLE_EVENT: seq_num: " << triggered_event.sequence_number << std::endl;
	
	if ( ! timed_events.empty() ) {
		set_timer_for_next_event();
	}
	
}


//int main() {
	
	//return 0;
//}