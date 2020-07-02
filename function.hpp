#include <string>
#include <stdio.h>
#include <regex>


template
<
    typename T
>
void for_each_(typename T::iterator beg_,
	typename T::iterator end_)
{
 while (beg_!=end_)
  {
    printf("%zd:%zd\n",*beg_,*end_);
    ++beg_;
    --end_;
  }

}


int main(int argc,char *argv[])
{
  std::vector<size_t> v;
  
for (size_t i = 0;i<1000;++i)
{
  v.push_back(i);
} 
// std::vector<size_t>::iterator b= v.begin();
for_each_< std::vector<size_t> >(v.begin(),v.end()); 
 return (0);
}