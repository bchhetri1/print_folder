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
#include <map>
#include <sys/stat.h>
#include <sstream>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>


using namespace std;
using namespace boost::archive;

#define filename "archive.txt"


class PrintFolder{
	/* If a change has been detected on the folder (i.e. a file was added or removed) then
	we will look for a new file, thus making a distinction from a modification even.
	If the new file is present, it will be sent to the printer. */
public:
	void handle_changes();

	/* serialize the map*/

	void save();

	/* load the map from file */
	void load();

	/* add a (k,v) to map */
	void add_to_map(std::pair<dev_t,ino_t> key, bool val);

	/* getter */
	void get_from_map(std::pair<dev_t,ino_t> key){}
private:
	std::map<std::pair<dev_t,ino_t>,bool> data;

};

int main(){
	return 0;
}