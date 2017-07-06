#include "print_folder.h"
PrintFolder pf;

void savechanges(int signal){
	cout<<"In the sigint handler"<<endl;
	pf.save();
}
int main(int argc, char * argv[]){
	signal(SIGINT, savechanges);
	cout<<__LINE__<<endl;
	cout<<__LINE__<<endl;
	struct	kevent event;	 /* Event we want to monitor */
	struct	kevent tevent;	 /* Event triggered */
	int kq, ret;
	kq = kqueue();
	DIR* dir = opendir("/Users/Bhawesh/Documents/print_folder");
	int g_fd = 0;
	if (dir){
	    /* Directory exists. */
	    g_fd = open("/Users/Bhawesh/Documents/print_folder",O_RDONLY);
	    closedir(dir);
	}else{
		g_fd = mkdir("/Users/Bhawesh/Documents/print_folder", S_IRWXU|S_IRWXG|S_IRWXO);
	}
	if (kq	== -1){
		// add this to the err log (along with date)
	    err(EXIT_FAILURE, "kqueue() failed");
	   	exit(EXIT_FAILURE);
	}
	cout<<"The fd is "<<g_fd<<endl;
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
			cout<<"in the main\n";
			pf.handle_changes();
			//handle_changes();
		}
	}
}

