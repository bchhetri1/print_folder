#include "print_folder.h"


int exists(char * c){
	int i = 0;
	while(i < idx){
		if(!strcmp(inodes[i],c))
			return 1;
		i++;
	}
	return 0;
}
void handle_changes(){
	DIR * dirp = fdopendir(g_fd);
	struct dirent *dp;
	while((dp = readdir(dirp))){
		if(dp->d_type == DT_REG && dp->d_name[0]!='.'){
			if(!exists(dp->d_name)){
				printf("Added %s\n",dp->d_name);
				inodes[idx] = strdup(dp->d_name);
				idx++; 	
				char * s = malloc(1024);
				strcat(strcat(strcpy(s,"/Users/Bhawesh/Desktop/print_folder"),"/"),dp->d_name);
				printf("%s\n",s );
				printf("%s\n", cupsGetDefault());
				cups_dest_t *dests;
				int num_dests = cupsGetDests(&dests);
				cups_dest_t *dest = cupsGetDest(NULL, NULL, num_dests, dests);
				if(cupsPrintFile(dest->name, s, "cairo PS", dest->num_options,dest->options)==0){
					printf("error!!!\n");;
					puts(ippErrorString(cupsLastError()));//<< endl;  

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
	g_fd = open("/Users/Bhawesh/Desktop/print_folder", O_RDONLY);
	if (g_fd == -1)
	    err(EXIT_FAILURE, "Failed to open '%s'", argv[1]);
	kq = kqueue();
	if (kq	== -1)
	    err(EXIT_FAILURE, "kqueue() failed");
	EV_SET(&event, g_fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE, 0, NULL);	/* Add the folder to the queue (to monitor) */
	ret = kevent(kq, &event, 1, NULL, 0, NULL);	/* start monitoring the folder */
	if (ret == -1)
	    err(EXIT_FAILURE, "kevent register");
	if (event.flags & EV_ERROR)
		errx(EXIT_FAILURE,	"Event error: %s", strerror(event.data));
	while(1) {
		ret = kevent(kq, NULL, 0, NULL, 0, NULL);
		if(ret == -1) {
			err(EXIT_FAILURE, "kevent wait");
		}else if (ret > 0) {
			 handle_changes();
		}
	}
}