#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"
#include "include/utils.h"
#include <time.h>

/**
 * You can change these to communicate with another colleague.
 * There are several factors that could stop this from working over the
 * internet, but if you're on the same network it should work.
 * Just fill in their IP here and make sure that you use the same port.
 */
#define HOST "127.0.0.1"
#define PORT 10000

/* Here we have the Frame structure */
#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;

/* Function which our protocol implementation will provide to the upper layer. */
int send_frame(char *buf, int size)
{

	/* TODO 1.1: Create a new frame. */

	/* TODO 1.2: Copy the data from buffer to our frame structure */

	/* TODO 2.1: Set the destination and source */

	/* TODO 1.3: We can cast the frame to a char *, and iterate through sizeof(struct Frame) bytes
	 calling send_bytes. */

	/* if all went all right, return 0 */
	
	struct Frame fr;
	memset(&fr, 0, sizeof(fr));
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME,&ts);

	memcpy(fr.payload, &ts, sizeof(ts));
	strncpy(fr.payload + sizeof(ts), buf, strlen(buf));

	fr.frame_delim_start[0] = DLE;
	fr.frame_delim_start[1] = STX;
	fr.frame_delim_end[0] = DLE;
	fr.frame_delim_end[1] = ETX;


	char *p = (char *) &fr;

	for(int i = 0; i < sizeof(fr); i++)
		send_byte(p[i]);

	return 0;
}

int main(int argc,char** argv){
	// Don't touch this
	init(HOST,PORT);

	int size = 100;
	char buf[100] = "ana are mere si pere";
	// TODO remove these sends, whih are hardcoded to send a "Hello"
	// message, and replace them with code that can send any message.
	/* Send Hello */
	send_frame(buf,size);

	/* TODO 1.0: Get some input in a buffer and call send_frame with it */

	/* TODO 3.1: Get a timestamp of the current time copy it in the the payload */

	/* TODO 3.0: Update the maximum size of the payload in Frame to 100 (in common.h), send the frame */

	/* TODO 3.0: Update the maximum size of the payload in Frame to 300, send the frame */

	return 0;
}
