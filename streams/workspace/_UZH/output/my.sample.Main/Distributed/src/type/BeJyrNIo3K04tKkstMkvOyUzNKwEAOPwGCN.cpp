// y2_6server6client


#include "BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.h"

#define SELF BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN

using namespace SPL;

std::auto_ptr<EnumMappings> SELF::mappings_(SELF::initMappings());


SELF SELF::server(0);
SELF SELF::client(1);

SELF::SELF(const std::string & v)
: Enum(*mappings_)
{
    // initialize from a string value
    this->Enum::operator=(v);
}

SELF::SELF(const rstring & v)
: Enum(*mappings_)
{
    // initialize from a string value
    this->Enum::operator=(v);
}


EnumMappings* SELF::initMappings()
{
   EnumMappings* em = new EnumMappings();
   // initialize the mappings 
   {
      std::string s("server");
      em->nameToIndex_.insert(std::make_pair(s, 0));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("client");
      em->nameToIndex_.insert(std::make_pair(s, 1));
      em->indexToName_.push_back(s);
   }
   
   return em;
}
