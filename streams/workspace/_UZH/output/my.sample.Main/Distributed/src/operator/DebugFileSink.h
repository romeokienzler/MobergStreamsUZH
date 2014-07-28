// eJx1j8EKwjAMQMmvDM9tFU_096VBEFBxlIF6kuujKurY0hbm_1twwUPEgOISF5L6FgmW50SBil3BqLyrgOxBRzKBjjaQzI17gf4vFcjaruSFXVqlxSWS5YW0xz1qSZAHU6SBkpReOeAMBb3yPPJeqedNMbxwcfOwr6jvxaX3a80UmD8w4z4pHdOf0wPuDNK0QkMt7llgATfPz6_1lwGBuL0BOSVyXOz_1gbiDXmYEdr





#ifndef SPL_OPER_INSTANCE_DEBUGFILESINK_H_
#define SPL_OPER_INSTANCE_DEBUGFILESINK_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <SPL/Runtime/Common/Metric.h>
#include <streams_boost/iostreams/device/file_descriptor.hpp>
#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMXQySUksSQQAC4sCC2.h"


#define MY_OPERATOR DebugFileSink$OP
#define MY_BASE_OPERATOR DebugFileSink_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMXQySUksSQQAC4sCC2 IPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    
    
    
    SPL::rstring lit$0;
    
    
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

    virtual void prepareToShutdown();

    void process(Tuple const & tuple, uint32_t port);
    
    
        void process(Punctuation const & punct, uint32_t port);
    
  private:
    class Helper {
        public:
            Helper (const std::string& fName
                    );
            
                std::ostream& fs() { return _fs; }
                std::ostream& writeTo() { return _fs; }
            
            void flush() { _fs.flush(); }
            int fd() { return _fd; }
            streams_boost::iostreams::filtering_streambuf<streams_boost::iostreams::output>& filt_str()
                { return _filt_str; }
        private:
            std::auto_ptr<streams_boost::iostreams::file_descriptor_sink> _fd_sink;
            std::ostream _fs;
            streams_boost::iostreams::filtering_streambuf<streams_boost::iostreams::output> _filt_str;
            
            
            int _fd;
    };


    

    void closeAndReopen();
    std::string genFilename();
    void openFile();
    void closeFile();
    Mutex _mutex;
    volatile bool _shutdown;
    std::string _pathName;
    std::string _pattern;
    Metric& _numFilesOpenedMetric;
    Metric& _numTupleWriteErrorsMetric;
    std::auto_ptr<Helper> _f;
    uint32_t _fileGeneration;
    
    
    
    
    
    
    
    
    
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_DEBUGFILESINK_H_

