#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "scope.hpp"
int main(int argc,char *argv[])
{
Scope::StartTokens_c ss_('{');
Scope::EndTokens_c se_('}');

 Scope::Detector<Scope::StartTokens_c,Scope::EndTokens_c> scope_(ss_,se_);

 //Scope::Scope<Scope::StartTokens_c,Scope::EndTokens_c> scope_('{','}');
 /* FILE *f = fopen(argv[1],"r+");
    if (f!=NULL)
    {
        printf("opened...\n");
        fclose(f);
    }
*/
  std::ifstream is(argv[1]);
  while (is)
  {
    std::string test_;
    std::getline(is,test_);
    printf("is=%s\n",test_.c_str());

  }


}