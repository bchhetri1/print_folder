#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <cups/cups.h>

char * inodes[128];		/* Keeps track of all the files (names) added to the folder */
int idx;				/* Index of where we are in the array */
int g_fd;				/* file descriptor for the folder we are monitoring */

int main();

/* If a change has been detected on the folder (i.e. a file was added or removed) then
we will look for a new file, thus making a distinction from a modification even.
If the new file is present, it will be sent to the printer. */

void handle_changes();

/* Checks to see if the new file was added or an existing file was modified.
 If an existing file was modified, no action is taken. */
int exists(char * c);