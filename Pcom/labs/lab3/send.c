#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "link_emulator/lib.h"
#include <arpa/inet.h>
#include "include/utils.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv) {
	init(HOST,PORT);

	/* Look in common.h for the definition of l3_msg */
	struct l3_msg t;

	/* We set the payload */
	sprintf(t.payload, "Hello my World of PC!");
	t.hdr.len = htons(strlen(t.payload) + 1);

	/* Add the checksum */
	/* Note that we compute the checksum for both header and data. Thus
	 * we set the checksum equal to 0 when computing it */
	t.hdr.sum = 0;

	/* Since sum is on 32 bits, we have to convert it to network order */
	t.hdr.sum = htonl(crc32((void *) &t, sizeof(struct l3_msg)));

	/* TODO 2.0: Call crc32 function */

	uint32_t test = crc32((uint8_t *) "123456789", 9);
	printf("TEST CRC = 0x%08X (trebuie sa fie 0xCBF43926)\n", test);

	/* Send the message */

	/* TODO 3.1: Receive the confirmation */

	/* TODO 3.2: If we received a NACK, retransmit the previous frame */

	/* TODO 3.3: Update this to read the content of a file and send it as
	 * chunks of that file given a MTU of 1500 bytes */
	
	uint8_t response;

	int retries  = 0;
	int count;

	do{
		link_send(&t, sizeof(struct l3_msg));
		int len = link_recv(&response,sizeof(response));
		DIE(len < 0, "Receive ACK/NACK");

		count = 0;

		for (int i = 0; i < 8; i++){
			if(response & (1 << i))
				count ++;
		}

		retries ++;

		if(count >= 4)
			printf("NACK.Retrimit!\n");
		
	}while(count >= 4 && retries < 10);
	
	return 0;
}
