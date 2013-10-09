/***************************************************************************
 * watchmen.c
 *
 * Author: mSatyam
 *
 * 2013, October
 *
 * Implements directory monitoring program that informs the user when
 * a file is CREATED, MODIFIED OR DELETED
 ***************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

#define BUF_LEN 100
#define CREATE 256
#define DELETE 512
#define MODIFY 2

/*
 * Display's event details when occured (On File Creation, Deletion and Modify)
 */
void display(unsigned int, const char*);


int main(int argc, char *argv[])
{
	// ensure proper usage
	if (argc != 2)
	{
		printf("Usage: %s DIR-NAME\n\n", argv[0]);
		return 1;
	}
	
	// buffer to read events as they occur
	char buf[BUF_LEN];

	// length of the event read
	int len;

	// initialize inotify
	int fd;
	fd = inotify_init();
	if (fd < 0)
		printf("Error initializing\n");

	int wd;

	// keep reading events infinitely
    	while(1)
    	{
		// add watch on directory which you want to monitor
		wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MODIFY | IN_DELETE);
		
		// yell at user if wrong add watch directory
		if (wd < 0)
		{
			printf("Error: Specified Directory Not found!\n\n");
			return 2;
		}

		// read event to buffer
		len = read(fd, buf, BUF_LEN);
		
		if (len < 0)
			printf("Error reading event");

		// inotify struct to access event attributes
		struct inotify_event *event;	
	
		// typecast char buffer to inotify_event struct in order to 
		// access event attributes
		event = (struct inotify_event *) buf;
		
		// display information 
		display(event->mask, event->name);		

		
    	}

return 0;

// thats all folk's
}

/*
 * Display's event details when occured (On File Creation, Deletion and Modify)
 */
void display(unsigned int mask, const char *name)
{
	// file created
	if (mask == CREATE)
		printf("\nFile Created: %s\n", name);
	// file deleted
	if (mask == DELETE)
		printf("\nFile Deleted: %s\n", name);
	// file modified
	if (mask == MODIFY)
		printf("\nFile Modified: %s\n", name);
	
	// clean out buffer	
	fflush(stdout);
}
