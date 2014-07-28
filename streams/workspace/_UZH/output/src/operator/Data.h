// eJx1kctugzAQRTW_1EnUN5qGqYkdJ0zaEPApIVTeRQyaKxcNobILI1xdouyBK5dVcnztzPVZ1YfAjrzWS5yXBNpYNZQhsPA7MDMPUXY3mMy5bij53XZzmKt7t_1MBVQWAb59mE6Wj9zpxEuE3UPdbhfLHpVHtNMlomT67dZVUUt6l_12lvtMpD3zNIJmavDXOkov2y69LoO2xd_1s21fg_1XAM7ChEPqBQbxdeV4jKu3YMErWVALzLEs0lSbkpeLHUlRmKylXNc_1Q3Kdfb_0aRaw6VrBBcqCVpmLawfif5WpM4NBoXhAgnSSUf0HnvXvwUDA6FzHIIGqVluRL9NnkBJAscWvY3qD_0GgoFCuiDdgKM5Fle8G8C6CcB6nYEcAv_0t4Z_1fgRKoh8dn9jMOwNg3_1_0maAE



#ifndef SPL_OPER_INSTANCE_DATA_H_
#define SPL_OPER_INSTANCE_DATA_H_

#include <SPL/Toolkit/TCPServer.h>
#include <SPL/Runtime/Common/Metric.h>
#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMXQySUksSQQAC4sCC2.h"
#include "../type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h"
#include "../type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.h"


#define MY_OPERATOR Data$OP
#define MY_BASE_OPERATOR Data_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMXQySUksSQQAC4sCC2 OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    SPL::uint32 lit$0;
    SPL::uint32 lit$1;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$format$0;
    SPL::rstring param$role$0;
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
  
    virtual void process(uint32_t index);
    
    virtual void allPortsReady();
 
    virtual void prepareToShutdown();
    
private:
   int _fd;
   uint64_t _tupleNumber;
   
   
   Metric& _numInvalidTuples;
   Metric& _numReconnects;
   Metric& _numConnections;
   Metric& _numWireFormatHandshakesFailed;
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_DATA_H_


