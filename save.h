#include <map>
#include <sstream>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <iostream>
#include <fstream>
#include "save.h"


#define filename "archive.txt"

using namespace std;
using namespace boost::archive;

// store whether a given file was printed
std::map<int,bool> data;

// serialize the map
void save();

// load the map
void load();

void add_to_map(off_t key, bool val);