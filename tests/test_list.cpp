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

/*struct Window {
	int* window;
	int base;
	int size;
	int start_index;
	int end_index;
	
	void attempt_advance() {
		int advancements = 0;
		for (int i = 0; i < size; i++) {
			if (window[i] == TRUE) {
				advancements ++;
			} else {
				break;
			}
		}
		
	}
	
	void set_received(int seq) {
		window[seq - base] = TRUE;
	}
};*/



class Window {
	
public:
	
	int* window;
	int base;
	int start_index;
	int end_index;
	int size;
	
	Window(int size);
	
	void record_packet(int seqnum);
	
	void attempt_advance();
	
	//void advance_window(int steps);
	
};


Window::Window(int size) {
	this->base = 0;
	this->start_index = 0;
	this->end_index = size - 1;
	this->window = new int[size]();
	this->size = size;
}


void Window::record_packet(int seqnum) {
	
	window[seqnum - base] = TRUE;
	attempt_advance();
	
}


void Window::attempt_advance() {
	int advancements = 0;
	for (int i = 0; i < size; i++) {
		if (window[i] == TRUE) {
			advancements ++;
		} else {
			break;
		}
	}
	
	for (int i = 0; i < advancements; i++) {
		window[start_index] = FALSE;
		start_index = (start_index + 1) % size;
		end_index = (end_index + 1) % size;
	}
	
	base += advancements;
	
}


/*void Window::advance_window(int steps) {
	
	for (int i = 0; i < steps; i++) {
		if ( start_index == -1 ) {
			std::cout << "\nQueue is empty";
			packet_count = 0;
			return;
		}
 
		//delete window[start_index];
		
		if ( start_index == end_index ) {
			start_index = -1 ;
			end_index = -1 ;
			packet_count = 0;
		} else
			start_index = ( start_index + 1 ) % size;
			packet_count --;
	}
	
}*/




void print_window_contents(Window window) {
	
	printf("base: %d\n", window.base);
	
	for (int i = 0; i < window.size; i++) {
		int pos = (window.start_index + i) % window.size;
		printf("%d ", window.window[pos]);
	}
	printf("\n");
	
}




int main() {
	
	int window_size = 5;
	Window window(window_size);
	
	printf("initial window\n");
	print_window_contents(window);
	
	window.record_packet(2);
	print_window_contents(window);
	
	window.record_packet(1);
	print_window_contents(window);
	
	window.record_packet(0);
	print_window_contents(window);
	
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