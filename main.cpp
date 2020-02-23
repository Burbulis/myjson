#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "scope.hpp"
int main(int argc,char *argv[])
{
Scope::Token_c ss_('{');
Scope::Token_c se_('}');

 Scope::Detector<Scope::Token_c,Scope::Token_c> scope_(ss_,se_);

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

    printf(":scope_test:%d",scope_.find(test_));

  }


}