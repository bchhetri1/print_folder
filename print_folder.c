#include "print_folder.h"
int exists(char * c){
	int i = 0;
	FILE* files = fopen("files.txt","a+");
	char * line = NULL;
	size_t size;
	while(getline(&line,&size,files) > 0){
		char * temp = strdup(line);
		if(temp[strlen(temp) - 1] == '\n')
			temp[strlen(temp) - 1] = '\0';
		if(strcmp(temp,c)==0){
			fclose(files);
			return 1;
		}
		free(temp);
	}
	fclose(files);
	return 0;
}


/* Traverses the list of file names to see if a new file was added
 or just a old file was modified. If an old file was modified, nothing is
 done, else the new file is sent to the printed.

 A better implementation would keep track of the number of files previously,
 if there was a change, only then go through the array.
 
 */

void handle_changes(){
	DIR * dirp = fdopendir(g_fd);
	struct dirent *dp;
	while((dp = readdir(dirp))){

		if(dp->d_type == DT_REG && dp->d_name[0]!='.'){
			if(!exists(dp->d_name)){
				printf("Filename: %s\n",dp->d_name );
				FILE* files = fopen("files.txt","w");
				if(!files)
					perror("wfrwfefefe\n");
				fprintf(files, "%s\n",dp->d_name);
				fclose(files);
				char * s = malloc(1024);
				strcat(strcat(strcpy(s,"/Users/Bhawesh/Desktop/print_folder"),"/"),dp->d_name);
				cups_dest_t *dests;
				int num_dests = cupsGetDests(&dests);
				cups_dest_t *dest = cupsGetDest(NULL, NULL, num_dests, dests);
				if(cupsPrintFile(dest->name, s, "cairo PS", dest->num_options,dest->options)==0){
					printf("error!!!\n");
					puts(ippErrorString(cupsLastError()));  
				}
			}
		}
	}
	lseek(g_fd,0,SEEK_SET);
}

int main(int argc, char **argv){
	struct	kevent event;	 /* Event we want to monitor */
	struct	kevent tevent;	 /* Event triggered */
	int kq, ret;
	g_fd = open("/Users/Bhawesh/Desktop/print_folder", O_RDONLY); /* Get the dir from argv */
	int log_fd = open("files.txt",O_RDWR|O_CREAT,S_IRWXO| S_IRWXG|S_IRWXU);
	if(log_fd < 0){
		printf("Error!\n");
	}
	if (g_fd == -1){
		// add this to the err log (along with date)
	    err(EXIT_FAILURE, "Failed to open '%s'", argv[1]);
	   	exit(EXIT_FAILURE);
	}
	kq = kqueue();
	if (kq	== -1){
		// add this to the err log (along with date)
	    err(EXIT_FAILURE, "kqueue() failed");
	   	exit(EXIT_FAILURE);
	}
	EV_SET(&event, g_fd, EVFILT_VNODE, EV_ADD|EV_CLEAR, NOTE_WRITE, 0, NULL);	/* Add the folder to the queue (to monitor) */
	ret = kevent(kq, &event, 1, NULL, 0, NULL);	/* start monitoring the folder */
	if (ret == -1){
		// add this to the err log (along with date)
	    err(EXIT_FAILURE, "kevent register");
	    exit(EXIT_FAILURE);
	}
	if (event.flags & EV_ERROR)
		errx(EXIT_FAILURE,	"Event error: %s", strerror(event.data));

	while(1) {
		ret = kevent(kq, NULL, 0, &tevent, 1, NULL);	/* we don't want to store the event */
		if(ret == -1) {
			// add this to the err log (along with date)
			err(EXIT_FAILURE, "kevent wait");
		}else{
			printf("wferfeferf\n");
			handle_changes();
		}
	}
}