// eJx9j80KwjAQhNlXEc9NUvWSWwV_1URBqL14k2qUN2qQkW0p9ekOrBS_0ypx1mZ7719TNqSD81dVIuUd2tAd6PgEkUMepqZEvct_06YtvGLczo8FsdzmyWbzXyViKicBG8MIWDKIT0dpGy0oVkMvSQGyXly2hQAwEpbIQsrqsqrvNKGtdY9fK3uyK7ZZctyRQqMNRgINKFTpK3xIH7CxacwoRB8awjXDrGH5mBr60aYP_0igwYWDCr1XBcKXUSR_0N9aN4vANfwMX_1FsS

#include <SPL/Runtime/Utility/Mutex.h>

#ifndef SPL_OPER_INSTANCE_HI_H_
#define SPL_OPER_INSTANCE_HI_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMSw2z00tLk5MTwUAGG4EA1.h"


#define MY_OPERATOR Hi$OP
#define MY_BASE_OPERATOR Hi_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2z00tLk5MTwUAGG4EA1 OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    
    
    SPL::uint32 lit$0;
    SPL::rstring lit$1;
    
    
protected:
    Mutex $svMutex;
    void checkpointStateVariables(NetworkByteBuffer & opstate) const {
    }
    void restoreStateVariables(NetworkByteBuffer & opstate) {
    }
private:
    static bool globalInit_;
    static bool globalIniter();
    ParameterMapType paramValues_;
    ParameterMapType& getParameters() { return paramValues_;}
    void addParameterValue(std::string const & param, ConstValueHandle const& value)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create(value));
    }
    void addParameterValue(std::string const & param)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create());
    }
};


class MY_OPERATOR : public MY_BASE_OPERATOR 
{
public:
   MY_OPERATOR();
  
   void allPortsReady();
   void process(uint32_t index);
   virtual void getCheckpoint(NetworkByteBuffer & opstate);
   virtual void restoreCheckpoint(NetworkByteBuffer & opstate);
private:
   SPL::BeJwrMSw2z00tLk5MTwUAGG4EA1 _tuple;
   SPL::uint32 _iters;
   Mutex _mutex;
   uint64_t _iterationCount;
   uint64_t IterationCount() const { return _iterationCount;}
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_HI_H_


