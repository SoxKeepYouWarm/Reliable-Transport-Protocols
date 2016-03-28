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

int generate_checksum(struct pkt packet) {

	int checksum = 0;
	checksum += packet.seqnum;
	checksum += packet.acknum;

	for (int i = 0; i < 20; i++) {

		checksum += (int) packet.payload[i];

	}

	printf("checksum is %d\n", checksum);
	return checksum;

}



int valid_packet(struct pkt packet) {
	
	if (packet.checksum == generate_checksum(packet)) {
		return TRUE;
	} else {
		return FALSE;
	}
	
}


int main() {
	
	struct msg message;
	memcpy(message.data, "1234567890123456789", 20);
	
	struct pkt new_packet;
	new_packet.acknum = 0;
	new_packet.seqnum = 0;
	for (int i = 0; i < 20; i++) {
		new_packet.payload[i] = message.data[i];
	}
	new_packet.checksum = generate_checksum(new_packet);
	
	new_packet.payload[0] = 'z';
	
	if (valid_packet(new_packet)) {
		printf("valid packet\n");
	} else {
		printf("invalid packet\n");
	}
	
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