#include "print_folder.h"

//g++ save.cpp save.h -std=c++0x -lboost_serialization


/* Traverses the list of file names to see if a new file was added
 or just a old file was modified. If an old file was modified, nothing is
 done, else the new file is sent to the printed.

 A better implementation would keep track of the number of files previously,
 if there was a change, only then go through the array.
 
 */

void PrintFolder::handle_changes( ){
	DIR * dirp = opendir("dw");
	struct dirent *dp;
	struct stat s;
	pair<dev_t,ino_t> p;
	while((dp = readdir(dirp))){
		if(dp->d_type == DT_REG && dp->d_name[0]!='.'){
			// stat("strcat(strcat(filename,/)",dp->d_name),&s);
			// if(!data[p(s.st_dev,st_ino)]){
			// 	data[p(s.st_dev,st_ino)] = true;
			// }
		}
	}
}

void PrintFolder::save()
{
	std::ofstream file{filename};
	text_oarchive oa{file};
	oa << data;
}

void PrintFolder::load(){

	std::ifstream file{filename};
	file.seekg (0, file.end);
    int length = file.tellg();
    if(!length)
    	return;
    file.seekg(0, file.beg);
	text_iarchive ia{file};
	ia >> data;
}

void PrintFolder::add_to_map(std::pair<dev_t,ino_t> key, bool val){
	data[key] = val;
}

