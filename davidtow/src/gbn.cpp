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

#include <stdio.h>
#include <queue>

#define TRUE 1
#define FALSE 0

#define FROM_A 0
#define FROM_B 1

int base; 
int expected_seqnum;  
int next_seqnum; 

#define WINDOW_SIZE 10
#define MESSAGE_BUFFERSIZE 100


struct Window {
	struct pkt window[WINDOW_SIZE];
	int start_index;
	int end_index;
	int packet_count;
	
	Window() : start_index(0), end_index(0), packet_count(0) {
		
	}
	
	void add_packet(struct pkt new_packet) {
		packet_count ++;
		end_index = (end_index + 1) % WINDOW_SIZE;
		window[end_index] = new_packet;
	}
	
	int window_full() {
		return (next_seqnum < (base + WINDOW_SIZE));
	}
	
};


struct Message_buffer {
	std::queue<msg> message_buffer;
	//struct msg message_buffer[MESSAGE_BUFFERSIZE];
	int start_index;
	int end_index;
	int current_index;
	
	Message_buffer() : start_index(0), end_index(0), current_index(0) {
		
	}
	
	void add_message(struct msg new_msg) {
		message_buffer.push(new_msg);
	}
	
	int is_empty() {
		return message_buffer.empty();
	}
	
	int is_full() {
		return (message_buffer.size() >= MESSAGE_BUFFERSIZE);
	}
	
};


struct Window window;
struct Message_buffer message_buffer;


int generate_checksum(struct pkt packet) {

	int checksum = 0;
	checksum += packet.seqnum;
	checksum += packet.acknum;

	for (int i = 0; i < 20; i++) {

		checksum += (int) packet.payload[i];

	}

	checksum ^= checksum;
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
	
	// set packet sequence number
	outgoing_packet->seqnum = next_seqnum;
	
	// set packet checksum
	outgoing_packet->checksum = generate_checksum(*outgoing_packet);
	
}


/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {

	printf("A_OUTPUT called: %s\n", message.data);
	
	struct pkt outgoing_packet;

	/* if window is not full */
	if ( ! window.window_full() ) {
		
		build_packet_a(&outgoing_packet, message);
	
		// if first in window, start timer
		if (next_seqnum == base) {
			starttimer(FROM_A, 100.00);
		}
	
		// send packet out
		printf("A_OUTPUT: packet leaving A\n");
		tolayer3(FROM_A, outgoing_packet);

		// copy packet to buffer
		window.add_packet(outgoing_packet);
		
		// increment sequence number
		next_seqnum ++;
		
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

	printf("A_INPUT: seq_num: %d message: %s\n", packet.seqnum, packet.payload);
	
	// check for valid checksum
	if (valid_packet(packet)) {
		printf("packet is valid\n");
		// check if sequence number is correct
		
	} else {
		// packet is not valid, drop it.
		printf("packet is not valid\n");
		return;
	}
	
}


/* called when A's timer goes off */
void A_timerinterrupt() {

	// timer went off, resend packet and restart timer
	printf("A_TIMER: resending packet");
	
}


/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {

	printf("a init just called\n");
	
}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {

	printf("B_INPUT: seq_num: %d message: %s\n", packet.seqnum, packet.payload);
	
}


/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() {

	printf("b init just called\n");
	
}