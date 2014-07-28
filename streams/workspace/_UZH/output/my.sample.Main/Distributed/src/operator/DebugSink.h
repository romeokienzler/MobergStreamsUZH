// eJx9kL1ug0AQhLWvYqVIGu4MTkNHECIJP0bBNGmik9mYE3CH7tYm_0OkDlizFLqKtVpr9dmbs0DmiFgOh8f1dWJRStcAv48LKcRhNA7IXfB9NVo7umXNK2_0dsN1ZBHG_0iYO00qxvdZPI37SV8Q0lrKWtP26k658kYBdtijMN80XNYQyfpgUNZpL5_1lIo8FwBYo3tklgyK3oq6l4qN2rR2EHtkX9XnK6sFCVBaIXgwaEMz6C_1iio1_0BoPWSq3A6A4Xld63SB_1LwsGiOaGB8GhJ96mcs4sOvrujbe54NwYfefUEoVaWhFoec5CLhWuKfzoCCeZSKcxn_1WxMHBDMnFOqA_1BfY4x0DC



#ifndef SPL_OPER_INSTANCE_DEBUGSINK_H_
#define SPL_OPER_INSTANCE_DEBUGSINK_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>
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

#include "../type/BeJwrMSw2z00tLk5MTwUAGG4EA1.h"
#include "../type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.h"


#define MY_OPERATOR DebugSink$OP
#define MY_BASE_OPERATOR DebugSink_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2z00tLk5MTwUAGG4EA1 IPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    
    
    
    SPL::uint32 lit$0;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$role$0;
    SPL::uint32 param$flush$0;
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


    virtual void prepareToShutdown();

    virtual void process(Tuple const & tuple, uint32_t port);
    bool processInternal(Tuple const & tuple, uint32_t port);

    virtual void process(Punctuation const & punct, uint32_t port);
    bool processInternal(Punctuation const & punct, uint32_t port);

    
        virtual void allPortsReady();
        virtual void process(uint32_t index);
    

private:
    inline void setupLocked (int32_t fd);
    void setup (int32_t fd);
    void cleanup();
    void closeConnection ();
    bool isDisconnected();
    void reconnectToNewConnection();
    inline bool canReconnect();

    std::auto_ptr<streams_boost::iostreams::file_descriptor_sink> _fd_sink;
    std::auto_ptr<SPL::TCPServer> _connector;
    std::auto_ptr<streams_boost::iostreams::filtering_streambuf<streams_boost::iostreams::output> > _filt_str;
    std::auto_ptr<std::ostream> _fs;
    
    
    
        CV _cv;
    
    Mutex _mutex;
    
    
    volatile bool _connected, _connectionClosed;
    
    Metric& _numReconnects;
    Metric& _numConnections;
    Metric& _numWireFormatHandshakesFailed;
    
    
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_DEBUGSINK_H_


