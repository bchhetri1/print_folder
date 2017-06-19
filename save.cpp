#include <map>
#include <sstream>
#include <map>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <iostream>
int main()
{
   std::map<int, int> map = {{1,2}, {2,1}};
   std::stringstream ss;
   boost::archive::text_oarchive oarch(ss);
   oarch << map;
   std::map<int, int> new_map;
   boost::archive::text_iarchive iarch(ss);
   iarch >> new_map;
   std::cout << (map == new_map) << std::endl;
}