#include "scope.hpp"
int main(int argc,char **argv)
{
Scope::StartTokens_c ss_('{');
Scope::EndTokens_c se_('}');

 Scope::Detector<Scope::StartTokens_c,Scope::EndTokens_c> scope_(ss_,se_);

}