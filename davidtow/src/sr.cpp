#include "../include/simulator.h"

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional data transfer 
   protocols (from A to B). Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <list>

#define TRUE 1
#define FALSE 0

#define FROM_A 0
#define FROM_B 1

#define TIME_A 100

#define ACK_RETURNED -2

int base; 
int next_seqnum; 

int expected_seqnum;  

#define MESSAGE_BUFFERSIZE 1000


struct Window_frame {
	struct pkt packet;
	int packet_received;
};


class Window {
	
public:
	
	struct Window_frame* window;
	int start_index;
	int end_index;
	int size;
	int packet_count;
	
	Window(int size);
	
	void insert_packet(struct pkt packet);
	
	void advance_window(int steps);
	
	int is_full();
	
	struct Window_frame* get_window_frame_by_seqnum(int seqnum);
	
};


Window::Window(int size) {
	this->start_index = -1;
	this->end_index = -1;
	this->packet_count = 0;
	this->window = new Window_frame[size];
	this->size = size;
	
	for (int i = 0; i < size; i++) {
		this->window[i].packet.seqnum = -1;
		this->window[i].packet.acknum = 0; 
		strcpy(this->window[i].packet.payload, "");
		this->window[i].packet_received = FALSE;
	}
	
}


void Window::insert_packet(struct pkt packet) {
	if ( ( end_index + 1 ) % size == start_index ) {
		std::cout << "\nQueue is full" << std::endl;
		return;
	}
	end_index = ( end_index + 1 ) % size;
	
	// set window frame
	window[end_index].packet = packet;
	window[end_index].packet_received = FALSE;
	
	packet_count++;
	if ( start_index == -1 ) {
		start_index = 0;
	}
	
}


void Window::advance_window(int steps) {
	
	for (int i = 0; i < steps; i++) {
		if ( start_index == -1 ) {
			std::cout << "\nQueue is empty\n";
			packet_count = 0;
			return;
		}
 
		//delete window[start_index];
		
		if ( start_index == end_index ) {
			window[start_index].packet_received = FALSE;
			start_index = -1 ;
			end_index = -1 ;
			packet_count = 0;
			printf("ADVANCE_WINDOW: reset indeces to -1, cleared flags\n");
		} else {
			window[start_index].packet_received = FALSE;
			start_index = ( start_index + 1 ) % size;
			packet_count --;
			printf("ADVANCE_WINDOW: cleared received flag\n");
		}
	
	}
	
}


int Window::is_full() {
	return (start_index == ( (end_index + 1) % size) );
}


struct Window_frame* Window::get_window_frame_by_seqnum(int seqnum) {
	printf("SUSPECT CODE: parameter seqnum: %d\n", seqnum);
	int frame_index = seqnum - base;
	int position = (frame_index + start_index) % size;
	printf("SUSPECT CODE: base: %d size: %d frame_index: %d position: %d\n", base, size, frame_index, position);
	return &window[position];
}


struct pkt gen_packet(int seq) {
	
	struct pkt new_pkt;
	new_pkt.seqnum = seq;
	return new_pkt;
	
}


void print_window_contents(Window window) {
	
	if (window.start_index == -1 && window.end_index == -1) {
		std::cout << "WINDOW CONTENTS: window is empty" << std::endl;
		return;
	}
	
	std::cout << "WINDOW CONTENTS: ";
	for (int i = 0; i <= window.size; i++) {
		int pos = (window.start_index + i) % window.size;
		std::cout << window.window[pos].packet.seqnum << " ";
		
		if (pos == window.end_index) {
			std::cout << "    start: " << window.start_index << " end: " << window.end_index << std::endl;
			return;
		}
	}
	
	std::cout << "    start: " << window.start_index << " end: " << window.end_index << std::endl;
	
}


class Receiver_Window {
	
public:
	
	struct pkt* window;
	int base;
	int start_index;
	int end_index;
	int size;
	
	Receiver_Window(int size);
	
	void record_packet(struct pkt packet);
	
	void attempt_advance();
	
	//void advance_window(int steps);
	
};


void print_receiver_window_contents(Receiver_Window window) {
	
	printf("base: %d\n", window.base);
	
	for (int i = 0; i < window.size; i++) {
		int pos = (window.start_index + i) % window.size;
		printf("%d ", window.window[pos].seqnum);
	}
	printf("\n");
	
}


Receiver_Window::Receiver_Window(int size) {
	this->base = 0;
	this->start_index = 0;
	this->end_index = size - 1;
	this->window = new struct pkt[size]();
	this->size = size;
	
	for (int i = 0; i < size; i++) {
		window[i].seqnum = -1;
		window[i].acknum = -1;
		window[i].checksum = -1;
	}
	
	print_receiver_window_contents(*this);
	
}


void Receiver_Window::record_packet(struct pkt packet) {
	
	int position = packet.seqnum - base + start_index;
	printf("RECORD_PACKET: position: %d seqnum: %d base: %d start_index: %d end_index %d\n", 
			position, packet.seqnum, base, start_index, end_index);
	
	window[position] = packet;
	attempt_advance();
	
}


void Receiver_Window::attempt_advance() {
	int advancements = 0;
	for (int i = 0; i < size; i++) {
		
		int position = (start_index + i) % size;
		if (window[position].seqnum != -1) {
			advancements ++;
		} else {
			break;
		}
		
	}
	
	printf("ATTEMPT_ADVANCE: steps: %d\n", advancements);
	
	for (int i = 0; i < advancements; i++) {
		printf("B_INPUT: delivering seq_num %d\n", window[start_index].seqnum);
		tolayer5(FROM_B, window[start_index].payload);
		window[start_index].seqnum = -1;
		start_index = (start_index + 1) % size;
		end_index = (end_index + 1) % size;
	}
	
	base += advancements;
	
}


struct Message_buffer {
	std::queue<msg> message_buffer;
	int start_index;
	int end_index;
	int current_index;
	
	Message_buffer() : start_index(0), end_index(0), current_index(0) {
		
	}
	
	void add_message(struct msg new_msg) {
		message_buffer.push(new_msg);
	}
	
	struct msg pop_message() {
		struct msg next_msg = message_buffer.front();
		message_buffer.pop();
		return next_msg;
		
	}
	
	int is_empty() {
		return message_buffer.empty();
	}
	
	int is_full() {
		return (message_buffer.size() >= MESSAGE_BUFFERSIZE);
	}
	
};


struct Event {
	float alarm_time;
	struct pkt packet; // CHANGE THIS LATER
};

class Timer {
	
	std::list<Event> timed_events;
	float time_buffer;
	
	void set_timer_for_next_event();
	
public:
	
	Timer();
	
	void schedule_alarm(float time, struct pkt packet);
	void handle_next_event_alarm();
	void remove_alarm(int seq_num);
	
};


Timer::Timer() {
	time_buffer = 0;
}


void Timer::schedule_alarm(float time, struct pkt sent_packet) {
	// TODO switch to using packets
	float alarm_time = get_sim_time() + time;
	
	struct Event new_event;
	new_event.alarm_time = alarm_time;
	
	
	new_event.packet = sent_packet;
	
	// check if this is the only event 
	if (timed_events.empty()) {
		
		// if no events scheduled already, push and start timer immediately
		timed_events.push_back(new_event);
		set_timer_for_next_event();
		
	} else {
		
		// push event to the back of the queue
		timed_events.push_back(new_event);
		
	}

}


void Timer::set_timer_for_next_event() {
	
	Event next_event = timed_events.front();
	float time_to_next_alarm = next_event.alarm_time - get_sim_time();
	starttimer(FROM_A, time_to_next_alarm);
	
}


void Timer::handle_next_event_alarm() {
	
	// get event, and pop from queue
	if ( ! timed_events.empty() ) {
		Event triggered_event = timed_events.front();
		timed_events.pop_front();
		
		std::cout << "HANDLE_EVENT: seq_num: " << triggered_event.packet.seqnum << std::endl;
		
		// set alarm for packet
		schedule_alarm(TIME_A, triggered_event.packet);
	
		// send packet out
		printf("A_OUTPUT: resending packet %d\n", triggered_event.packet.seqnum);
		tolayer3(FROM_A, triggered_event.packet);
		
	} else {
		printf("event queue empty, no event to be handled :(\n");
	}
	
}


void Timer::remove_alarm(int seq_num) {
	
	printf("REMOVE_ALARM: seqnum: %d\n", seq_num);
	
	int i = 0;
	for (std::list<struct Event>::iterator iter = timed_events.begin(); iter != timed_events.end(); std::advance(iter, 1)) {
	
		if (iter->packet.seqnum == seq_num) {
			printf("REMOVE_ALARM: alarm found\n");
			
			// if the timer is running this alarm, need to set timer to next event
			int reset_timer = (i == 0);
			
			iter = timed_events.erase(iter);
			iter --;
			
			if (reset_timer) {
				printf("REMOVE_ALARM: timer needs to be stopped for removed alarm\n");
				stoptimer(FROM_A);
					
				if ( ! timed_events.empty() ) {
					printf("REMOVE_ALARM: timer needs to be set for next event\n");
					set_timer_for_next_event();
				} else {
					printf("REMOVE_ALARM: event queue is empty, timer will not be restarted\n");
				}
			} else {
				printf("REMOVE_ALARM: timer does not need to be reset\n");
			}
			
			
			// check if this packet is associated with the current alarm
			/*if ( ! timed_events.empty() ) {
				
				Event current_event = timed_events.front();
				if (current_event.packet.seqnum == seq_num) {
					// if so, stop the alarm
					printf("REMOVE_ALARM: returned packet is associated with current timer alarm, stopping timer\n");
					stoptimer(FROM_A);
					if ( ! timed_events.empty() ) {
						set_timer_for_next_event();
					} 
				} else {
					printf("REMOVE_ALARM: returned packet alarm event removed from queue\n");
				}
			
			}*/
			
			return;
		}
		
		i++;
		
	}
	
	printf("REMOVE_ALARM: FAILED\n");

}


Window* window;
Receiver_Window* receiver_window;
Timer* timer;
struct Message_buffer message_buffer;


int generate_checksum(struct pkt packet) {

	int checksum = 0;
	checksum += packet.seqnum;
	checksum += packet.acknum;

	for (int i = 0; i < 20; i++) {

		checksum += (int) packet.payload[i];

	}

	return checksum;

}


int valid_packet(struct pkt packet) {
	
	if (packet.checksum == generate_checksum(packet)) {
		return TRUE;
	} else {
		return FALSE;
	}
	
}


void build_packet_a(struct pkt* outgoing_packet, struct msg message) {
	
	// load message into packet
	for (int i = 0; i < 20; i++) {
		outgoing_packet->payload[i] = message.data[i];
	}
	
	// default ack_num
	outgoing_packet->acknum = -1;
	
	// set packet sequence number
	outgoing_packet->seqnum = next_seqnum;
	
	// set packet checksum
	outgoing_packet->checksum = generate_checksum(*outgoing_packet);
	
}


/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {

	printf("A_OUTPUT called: %.*s\n", 20, message.data);
	
	struct pkt outgoing_packet;

	/* if window is not full */
	if ( ! window->is_full() ) {
		
		build_packet_a(&outgoing_packet, message);
		
		// set alarm for packet
		timer->schedule_alarm(TIME_A, outgoing_packet);
	
		// send packet out
		printf("A_OUTPUT: packet leaving A\n");
		tolayer3(FROM_A, outgoing_packet);

		// copy packet to buffer
		window->insert_packet(outgoing_packet);
		
		// increment sequence number
		next_seqnum ++;
		
		print_window_contents(*window);
		
	} else {
		printf("A_output send window is full\n");

		if (message_buffer.is_full()) {
			
			printf ("message buffer is full, dropping packet\n");
			return;
		
		} else {
			
			printf("buffering message\n");
			message_buffer.add_message(message);
			
		}  
	}          
	
}


/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {

	printf("A_INPUT: ack_num: %d message: %.*s\n", packet.acknum, 20, packet.payload);
	
	// check for valid checksum
	if (valid_packet(packet)) {
		printf("A_INPUT: packet is valid\n");
		
		struct Window_frame* frame = window->get_window_frame_by_seqnum(packet.acknum);
		printf("A_INPUT: ABOUT TO RUN SUSPECT CODE\n");
		frame->packet_received = TRUE;
		
		// move window up past last ack
		int advancements = 0;
		for (int i = 0; i < window->size; i++) {
			
			int position = (window->start_index + i) % window->size;
			printf("A_INPUT: packet_received: %d position: %d seqnum: %d acknum: %d payload: %.*s\n", 
					window->window[position].packet_received,
					position,
					window->window[position].packet.seqnum,
					window->window[position].packet.acknum,
					20,
					window->window[position].packet.payload);
			
			if (window->window[position].packet_received) {
				printf("A_INPUT: making advancement due to seqnum: %d at position %d\n", 
						window->window[position].packet.seqnum, position);
				advancements ++;
			} else {
				break;
			}
		
		}
	
		window->advance_window(advancements);
		
		// update new base
		printf("SUSPECT CODE: base: %d += advancements: %d\n", base, advancements);
		base += advancements;
		
		// stop frame timer
		timer->remove_alarm(packet.acknum);
		printf("DEBUGGING: just returned from remove_alarm\n");
		
		print_window_contents(*window);
		printf("DEBUGGING: just returned from print_window_contents\n");
		
		// send buffered messages as long as window isn't full
		while ( ( ! message_buffer.is_empty()) && ( ! window->is_full() ) ) {
			printf("A_INPUT: sending buffered messages\n");
			struct pkt new_packet;
			
			build_packet_a(&new_packet, message_buffer.pop_message());
			
            if ( base == next_seqnum ) {
		 		starttimer(FROM_A, TIME_A);
		 		printf ("send packets\n");
            }

            tolayer3(FROM_A, new_packet);

            window->insert_packet(new_packet);
				
			next_seqnum ++;
			
			print_window_contents(*window);
			
		}
		
		printf("DEBUGGING: about to finish a_input call\n");
		
	} else {
		// packet is not valid, drop it.
		printf("packet is not valid\n");
		return;
	}
	
}


/* called when A's timer goes off */
void A_timerinterrupt() {

	// timer went off, resend packet and restart timer
	
	timer->handle_next_event_alarm();
	
	
}


/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {

	printf("a init just called\n");
	base = 0;
	next_seqnum = 0;
	window = new Window(getwinsize());
	timer = new Timer();
	
}




/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {

	printf("B_INPUT: seq_num: %d message: %.*s\n", packet.seqnum, 20, packet.payload);
	
	if (valid_packet(packet)) {
		printf("B_INPUT: received valid packet from A\n");
		
		receiver_window->record_packet(packet);
		
		packet.acknum = packet.seqnum;
		
		packet.checksum = generate_checksum(packet);
		
		tolayer3(FROM_B, packet);
		
	} else {
		printf("B_INPUT: received packet with invalid checksum\n");
	}
	
}


/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() {

	printf("b init just called\n");
	receiver_window = new Receiver_Window(getwinsize());
	
}