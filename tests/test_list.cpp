#include <list>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct Event {
	int val;
};

struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
};

struct msg {
  char data[20];
};





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
	
	window[packet.seqnum - base] = packet;
	attempt_advance();
	
}


void Receiver_Window::attempt_advance() {
	int advancements = 0;
	for (int i = 0; i < size; i++) {
		if (window[i].seqnum != -1) {
			advancements ++;
		} else {
			break;
		}
	}
	
	for (int i = 0; i < advancements; i++) {
		printf("delivering seq_num %d\n", window[start_index].seqnum);
		window[start_index].seqnum = -1;
		start_index = (start_index + 1) % size;
		end_index = (end_index + 1) % size;
	}
	
	base += advancements;
	
}





int main() {
	
	int window_size = 5;
	Receiver_Window window(window_size);
	
	struct pkt example;
	example.seqnum = 1;
	
	printf("initial window\n");
	print_receiver_window_contents(window);
	
	window.record_packet(example);
	print_receiver_window_contents(window);
	
	example.seqnum = 0;
	
	window.record_packet(example);
	print_receiver_window_contents(window);
	
	window.record_packet(example);
	print_receiver_window_contents(window);
	
	/*
	std::list<Event> vals;
	
	struct Event one;
	one.val = 1;
	
	struct Event two;
	two.val = 2;
	
	struct Event three;
	three.val = 3;
	
	struct Event four;
	four.val = 4;
	
	vals.push_back(one);
	vals.push_back(two);
	vals.push_back(three);
	vals.push_back(four);
	
	//std::list<struct Event>::iterator it = vals.begin();
	
	for (std::list<struct Event>::iterator iter = vals.begin(); iter != vals.end(); std::advance(iter, 1)) {
		
		if (iter->val != 2) { 
			iter->val = iter->val * 10; 
		} else {
			iter = vals.erase(iter);
			iter --;
		}
		
	}
	
	//vals.erase(it);
	
	for (std::list<struct Event>::iterator iter = vals.begin(); iter != vals.end(); iter++) {
		
		std::cout << iter->val << std::endl;
		
	}
	 * */
	
}