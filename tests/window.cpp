
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
	
	Window();
	
	void insert_packet(struct pkt packet);
	
	void advance_window(int steps);
	
	int is_full();
	
};


Window::Window() {
	this->start_index = 0;
	this->end_index = 0;
}

void Window::insert_packet(struct pkt packet) {
	this->window[this->end_index] = packet;
	this->end_index = (this->end_index + 1) % WINDOW_SIZE;
}

void Window::advance_window(int steps) {
	for (int i = 0; i < steps; i++) {
		if (start_index == end_index) {
			start_index = (start_index + 1) % WINDOW_SIZE;
			end_index = (end_index + 1) % WINDOW_SIZE;
		} else {
			start_index = (start_index + 1) % WINDOW_SIZE;
		}
	}
	start_index = (start_index + steps) % WINDOW_SIZE;
}

int Window::is_full() {
	return (this->start_index == ( (this->end_index + 1) % WINDOW_SIZE) );
}

struct pkt gen_packet(int seq) {
	
	struct pkt new_pkt;
	new_pkt.seqnum = seq;
	return new_pkt;
	
}


void print_window_contents(Window window) {
	
	for (int i = window.start_index; i < window.end_index; i++) {
		std::cout << window.window[i].seqnum;
	}
	std::cout << std::endl;
	
}


int main() {
	
	Window window;
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(1));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(2));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(3));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(4));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(5));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(6));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(7));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	if ( ! window.is_full() ) {
		window.insert_packet(gen_packet(8));
	} else {
		std::cout << "window full" << std::endl;
	}
	
	print_window_contents(window);
	
	return 0;
}