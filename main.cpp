#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "scope.hpp"
int main(int argc,char *argv[])
{
Scope::Token_c ss_('{');
Scope::Token_c se_('}');

Scope::Token_c vs_('"');
Scope::Token_c ve_('"');


 //Scope::Detector<Scope::Token_c,Scope::Token_c> Object_scope_(ss_,se_);
 Scope::Detector<Scope::Token_c,Scope::Token_c> Value_scope_(vs_,ve_);
 

  std::ifstream is(argv[1]);
  while (is)
  {
    std::string test_;
    std::getline(is,test_);
   // printf(":scope_test:%d",static_cast<int>(Object_scope_.find(test_)));
   // printf(":str_test:%s",test_.c_str());

   // if (Object_scope_.find(test_))
   // {    
      printf(":value_test:%zd:[%s]\n",Value_scope_.find(test_),test_.c_str());
   // }
  }


}