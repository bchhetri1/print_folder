#include "save.h"
using namespace std;
using namespace boost::archive;

void save_map(off_t key, bool val){

}

void load_map(){
	//std::ifstream infile("data.bin",std::ios::binary)
}

// int main()
// {
//    std::map<int, int> map = {{1,2}, {2,1}};
//       cout<<__LINE__<<endl;

//    std::ofstream ss{"test.txt"};
//       cout<<__LINE__<<endl;

//    boost::archive::text_oarchive oarch{ss};
//       cout<<__LINE__<<endl;

//    oarch << map;
//    cout<<__LINE__<<endl;

//    std::map<int, int> new_map;
//    cout<<__LINE__<<endl;

//        std::ifstream ss2{"test.txt"};
//    cout<<__LINE__<<endl;
//    boost::archive::text_iarchive iarch{ss2};
//       cout<<__LINE__<<endl;

//    iarch >> new_map;
//    cout<<__LINE__<<endl;
//    std::cout << (map == new_map) << std::endl;
// }
 std::map<int, int> m = {{1,2}, {2,1}};
void save()
{
  std::ofstream file{"archive.txt"};
  text_oarchive oa{file};
 
  oa << m;
}

void load()
{
  std::ifstream file{"archive.txt"};
  text_iarchive ia{file};
  std::map<int, int> map2;// = {{1,2}, {2,1}};
  ia >> map2;
  std::cout << (m==map2)<< endl;
}

int main()
{
  save();
  load();
}