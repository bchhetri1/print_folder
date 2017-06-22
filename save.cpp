#include "save.h"



void save()
{
	std::ofstream file{filename};
	text_oarchive oa{file};
	oa << data;
}

void load(){

	std::ifstream file{filename};
	file.seekg (0, file.end);
    int length = file.tellg();
    if(!length)
    	return;
    file.seekg(0, file.beg);
	text_iarchive ia{file};
	ia >> data;
}

void add_to_map(off_t key, bool val){
	data[key] = val;
}