#include "print_folder.h"

//g++ save.cpp save.h -std=c++0x -lboost_serialization

void print_file(char * name){
	char * s = malloc(1024);
	strcat(strcat(strcpy(s,"/Users/Bhawesh/Documents/print_folder"),"/"),name);
 	cups_dest_t *dests;
 	int num_dests = cupsGetDests(&dests);
 	cups_dest_t *dest = cupsGetDest(NULL, NULL, num_dests, dests);
 	if(!cupsPrintFile(dest->name, s, "cairo PS", dest->num_options,dest->options)){
 		puts(ippErrorString(cupsLastError()));  
 	}
}
/* Traverses the list of file names to see if a new file was added
 or just a old file was modified. If an old file was modified, nothing is
 done, else the new file is sent to the printed.

 A better implementation would keep track of the number of files previously,
 if there was a change, only then go through the array.
 
 */

void PrintFolder::handle_changes( ){
	DIR * dirp = opendir("/Users/Bhawesh/Documents/print_folder");
	struct dirent *dp;
	struct stat s;
	while((dp = readdir(dirp))){
		if(dp->d_type == DT_REG && dp->d_name[0]!='.'){
			char path[1024];
			stat(strcat(strcpy(path,"/Users/Bhawesh/Documents/print_folder/"),dp->d_name),&s);
			pair<dev_t,ino_t> p(s.st_dev,s.st_ino);
			if(!data[p]){
				cout<<"Adding files...\n";
				stat(dp->d_name,&s);
				data[p] = true;
				print_file(dp->d_name)
			}
		}
	}
}

void PrintFolder::save()
{
	cout<<"Saving data.."<<endl;
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
PrintFolder::PrintFolder(){
	cout<<"Loading the file...."<<endl;
	PrintFolder::load();
}
