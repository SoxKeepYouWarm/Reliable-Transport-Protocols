
#include <iostream>

#define WINDOW_SIZE 6

struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
};

class Window {
	
public:
	
	struct pkt window[WINDOW_SIZE];
	int start_index;
	int end_index;
	int size;
	
	Window(int size);
	
	void insert_packet(struct pkt packet);
	
	void advance_window(int steps);
	
	int is_full();
	
};


Window::Window(int size) {
	this->start_index = -1;
	this->end_index = -1;
}


void Window::insert_packet(struct pkt packet) {
	if ( ( end_index + 1 ) % size == start_index ) {
		std::cout << "\nQueue is full" << std::endl;
		return;
	}
	end_index = ( end_index + 1 ) % size;
	window[end_index] = packet;
	if ( start_index == -1 )
		start_index = 0 ;
}


void Window::advance_window(int steps) {
	
	for (int i = 0; i < steps; i++) {
		if ( start_index == -1 ) {
			std::cout << "\nQueue is empty" ;
			return;
		}
 
		//delete window[start_index];
		
		if ( start_index == end_index ) {
			start_index = -1 ;
			end_index = -1 ;
		} else
			start_index = ( start_index + 1 ) % size;
	}
	
}


int Window::is_full() {
	return (start_index == ( (end_index + 1) % size) );
}


struct pkt gen_packet(int seq) {
	
	struct pkt new_pkt;
	new_pkt.seqnum = seq;
	return new_pkt;
	
}


void print_window_contents(Window window) {
	
	if (window.start_index != window.end_index) {
		for (int i = window.start_index; i != window.end_index; i = (i + 1) % window.size) {
			std::cout << window.window[i].seqnum;
		}
		std::cout << "    start: " << window.start_index << " end: " << window.end_index << std::endl;
	} else {
		std::cout << "window is empty" << std::endl;
	}
	
}


int main() {
	
	struct pkt* test;
	
	test = new pkt[5];
	
	/*
	Window window(WINDOW_SIZE);
	
	print_window_contents(window);
	
	
	for (int i = 1; i < 6; i++) {
		
		if ( ! window.is_full() ) {
			window.insert_packet(gen_packet(i));
		} else {
			std::cout << "window full" << std::endl;
		}
	
		print_window_contents(window);
		
	}
	
	window.advance_window(2);
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(13));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	*/
	
	return 0;
}