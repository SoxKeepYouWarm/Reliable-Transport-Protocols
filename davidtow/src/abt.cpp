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

#define TRUE 1
#define FALSE 0

#define FROM_A 0
#define FROM_B 1

int sequence_num_a;
int sequence_num_b;

pkt current_packet;

void flip_sequence_bit_a() {
	
	if (sequence_num_a == 1) {
		sequence_num_a = 0;
	} else {
		sequence_num_a = 1;
	}
	
}


void flip_sequence_bit_b() {
	
	if (sequence_num_b == 1) {
		sequence_num_b = 0;
	} else {
		sequence_num_b = 1;
	}
	
}


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


int IN_TRANSIT;
/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {

	printf("A_OUTPUT called: %s\n", message.data);
	
	// check if packet already in transit
	if (IN_TRANSIT) {
		printf("A_OUTPUT: message in_transit, returning\n");
		return;
	}
	
	struct pkt outgoing_packet;
	
	// load message into packet
	for (int i = 0; i < 20; i++) {
		outgoing_packet.payload[i] = message.data[i];
	}
	
	// set packet sequence number
	outgoing_packet.seqnum = sequence_num_a;
	
	// set packet checksum
	outgoing_packet.checksum = generate_checksum(outgoing_packet);
	
	// save current packet
	current_packet = outgoing_packet;
	
	// start timer
	starttimer(FROM_A, 100.00);
	
	// send packet out
	IN_TRANSIT = TRUE;
	printf("A_OUTPUT: packet leaving A\n");
	tolayer3(FROM_A, outgoing_packet);
	
}


/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {

	printf("A_INPUT: seq_num: %d message: %s\n", packet.seqnum, packet.payload);
	
	// check for valid checksum
	if (valid_packet(packet)) {
		printf("packet is valid\n");
		// check if sequence number is correct
		if (packet.acknum == sequence_num_a) {
			printf("correct sequence number\n");
			// stop timer, and advance seq number
			stoptimer(FROM_A);
			flip_sequence_bit_a();
			
			// allow another message to come from above
			IN_TRANSIT = FALSE;
			
		} else {
			// wrong ack received, drop it.
			printf("wrong sequence number\n");
			return;
		}
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
	starttimer(FROM_A, 100.00);
	tolayer3(FROM_A, current_packet);
	
}


/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {

	printf("a init just called\n");
	IN_TRANSIT = FALSE;
	sequence_num_a = 0;
	
}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {

	printf("B_INPUT: seq_num: %d message: %s\n", packet.seqnum, packet.payload);
	
	if (packet.seqnum == sequence_num_b) {
		// correct packet received
		printf("B_INPUT: correct packet received\n");
		packet.acknum = sequence_num_b;
		packet.seqnum = -1;
		
		// send packet back with ACK
		tolayer3(FROM_B, packet);
		tolayer5(FROM_B, packet.payload);
		
		// flip sequence for next packet
		flip_sequence_bit_b();
	} else {
		// wrong seq number, drop packet
		printf("B_INPUT: wrong packet received\n");
		return;
	}
	
}


/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() {

	printf("b init just called\n");
	sequence_num_b = 0;
	
}
