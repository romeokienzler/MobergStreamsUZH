// eJx1UE1rwkAQZf6K9JxNYiglNxsJrdW2EoXSi2ziWBeTnTA7IcRf3_1UDqYey7GHevHnvzbi2DvRWt4KcprmpsaCOK4Tw_1GIYBYGSoUX1jLOeF1_1LoVgfXLFcTrLEZVkc7Ed3nIHfX8PxyiTdYnhs36b5x_0D646ri2eopiYfKLop_0Pdlton6W0Wn4ZFIbeQih_0JynKTthY3_1gjEUXrDNWxjEAqD01qDwDdeP0tjFW9cQH1_0oK1Wb9_1aK2WjRYsggJ7Pw2EN3LRlevifi67ARzRoQdcaPFN6d_0PL8UIZQ1VQfIOifUzI0_1kK4vWGGON_0Frtuia9153T5L_1CVES1aitlxbuEDKyTrQ9WUX_0U0t8O8M_114YG2JPPW_1ooJYThL1ZvItW



#ifndef SPL_OPER_INSTANCE_DATA_H_
#define SPL_OPER_INSTANCE_DATA_H_

namespace streams_boost { namespace iostreams { class file_descriptor_source; } }
#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>
#include <SPL/Toolkit/HotFile.h>
#include <SPL/Runtime/Common/Metric.h>
#include <streams_boost/filesystem/path.hpp>
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
    
    
    
    SPL::rstring lit$0;
    SPL::uint32 lit$1;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$format$0;
    SPL::boolean param$hotFile$0;
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
    void initialize();
    inline void punctAndStatus(const std::string& pathName);
    void processOneFile (const std::string& pathName);
    

    int32_t _fd;
    uint64_t _tupleNumber;
    
    
    
    
    
    
    Metric& _numFilesOpenedMetric;
    Metric& _numInvalidTuples;
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_DATA_H_


