#include "print_folder.h"

int main(){
	struct	kevent event;	 /* Event we want to monitor */
	struct	kevent tevent;	 /* Event triggered */
	int kq, ret;
	g_fd = open(argv[2], O_RDONLY); /* Get the dir from argv */
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
		ret = kevent(kq, NULL, 0, &tevent, 1, NULL);	/* we don't want to store > 1 event */
		if(ret == -1) {
			// add this to the err log (along with date)
			err(EXIT_FAILURE, "kevent wait");
		}else{
			handle_changes();
		}
	}
}

