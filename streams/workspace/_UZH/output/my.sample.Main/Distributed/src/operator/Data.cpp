// eJx1UE1rwkAQZf6K9JxNYiglNxsJrdW2EoXSi2ziWBeTnTA7IcRf3_1UDqYey7GHevHnvzbi2DvRWt4KcprmpsaCOK4Tw_1GIYBYGSoUX1jLOeF1_1LoVgfXLFcTrLEZVkc7Ed3nIHfX8PxyiTdYnhs36b5x_0D646ri2eopiYfKLop_0Pdlton6W0Wn4ZFIbeQih_0JynKTthY3_1gjEUXrDNWxjEAqD01qDwDdeP0tjFW9cQH1_0oK1Wb9_1aK2WjRYsggJ7Pw2EN3LRlevifi67ARzRoQdcaPFN6d_0PL8UIZQ1VQfIOifUzI0_1kK4vWGGON_0Frtuia9153T5L_1CVES1aitlxbuEDKyTrQ9WUX_0U0t8O8M_114YG2JPPW_1ooJYThL1ZvItW




#include "./Data.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Data_Base
#define MY_OPERATOR Data$OP


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <signal.h>

#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>


    #include <SPL/Runtime/Serialization/StreamByteBuffer.h>

#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Toolkit/IOHelper.h>
#include <SPL/Toolkit/RuntimeException.h>

#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>

using namespace std;
using namespace streams_boost::iostreams;

#define DEV_NULL "/dev/null"


// defines for error checking conditions
#define CHECK_FAIL      \
    if (failedRead)                                   \
        _numInvalidTuples.incrementValueNoLock()

    #define DO_ERROR(msg)                             \
        do { _numInvalidTuples.incrementValueNoLock();   \
          const FormattableMessage& $msg = msg;       \
          SPLTRACEMSG (L_ERROR, $msg, SPL_OPER_DBG);  \
          THROW (SPLRuntimeFileSourceOperator, $msg);} while (0)
    #define DO_ERROR_FILESOURCE(msg) DO_ERROR(msg)
    #define CHECK_ERROR(msg)                          \
        if (fs.fail() && !getPE().getShutdownRequested()) \
            DO_ERROR(msg)


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
    : MY_BASE_OPERATOR(), _fd(-1),
         
         
        
        
        
        
        _numFilesOpenedMetric(getContext().getMetrics().getCustomMetricByName("nFilesOpened")),
        _numInvalidTuples(getContext().getMetrics().getCustomMetricByName("nInvalidTuples"))
{
    _numFilesOpenedMetric.setValueNoLock(0);
    _numInvalidTuples.setValueNoLock(0);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::initialize()
{
    
}



void MY_OPERATOR_SCOPE::MY_OPERATOR::punctAndStatus(const string& pathName)
{

    submit (Punctuation::WindowMarker, 0);


}

void MY_OPERATOR_SCOPE::MY_OPERATOR::processOneFile (const string& pathName)
{
    SPL::BeJwrMXQySUksSQQAC4sCC2 tuple$;
    
    namespace bf = streams_boost::filesystem;
    SPLAPPTRC(L_DEBUG, "Using '" << pathName << "' as the workload file...", SPL_OPER_DBG);

    int32_t fd = ::open (pathName.c_str(), O_RDONLY | O_LARGEFILE);
    if (fd < 0) {
        
        
        const FormattableMessage& m = 
                  SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(
                      pathName, RuntimeUtility::getErrorNoStr());
        SPLLOGMSG(L_ERROR, m, SPL_OPER_DBG);
        SPLTRACEMSG(L_ERROR, m, SPL_OPER_DBG);
        THROW (SPLRuntimeFileSourceOperator, m);
    }
    
        SPL::HotFile fd_src (getPE(), *this, fd);
    
    _numFilesOpenedMetric.incrementValueNoLock();
    filtering_streambuf<input> filt_str;
    
    
    filt_str.push (fd_src);
    
        iostream fs (&filt_str);
        SPL::StreamByteBuffer sbfs(fs);
    
    fs.imbue(locale::classic());

    _fd = fd;
    _tupleNumber = 0; 
    





bool failedRead = false;
while(!getPE().getShutdownRequested() && !fs.eof()) {
    _tupleNumber++;
    if (SPL::safePeek(fs) == EOF) break;
    bool doSubmit = true;
    try {
        
            SPL::blob& b = tuple$.get_data();
            unsigned rSize;
            std::auto_ptr<char>data (new char[lit$1]);
            sbfs.getFixedCharSequence(data.get(), lit$1, rSize);
            b.adoptData(reinterpret_cast<unsigned char*>(data.release()), rSize);
        



    } catch (const SPLRuntimeException& e) {
        // Add the filename & tuple number
        DO_ERROR_FILESOURCE(
            SPL_APPLICATION_RUNTIME_FILE_SOURCE_SINK_FILENAME_TUPLE(_tupleNumber, pathName, e.getExplanation()));

    } catch (const std::exception& e) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()));
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    } catch (...) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION);
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    }
    if (doSubmit)
        submit (tuple$, 0);
}

    if (_fd < 0) {
        // We closed it already.  Prevent an error message
        int newFd = ::open (DEV_NULL, O_RDONLY);
        ::dup2 (newFd, _fd);
        ::close(newFd);
    }
    _fd = -1; // no longer using this



    punctAndStatus(pathName);
}


void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "FileSource startup...", SPL_OPER_DBG);
    initialize();
    processOneFile (lit$0);
    SPLAPPTRC(L_DEBUG, "FileSource exiting...", SPL_OPER_DBG);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}



static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("Data",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    PE & pe = PE::instance();
    uint32_t index = getIndex();
    initRTC(*this, lit$0, "lit$0");
    initRTC(*this, lit$1, "lit$1");
    addParameterValue ("file", SPL::ConstValueHandle(lit$0));
    param$format$0 = "block";
    addParameterValue ("format", SPL::ConstValueHandle(param$format$0));
    addParameterValue ("blockSize", SPL::ConstValueHandle(lit$1));
    param$hotFile$0 = true;
    addParameterValue ("hotFile", SPL::ConstValueHandle(param$hotFile$0));
    (void) getParameters(); // ensure thread safety by initializing here
}
MY_BASE_OPERATOR::~MY_BASE_OPERATOR()
{
    for (ParameterMapType::const_iterator it = paramValues_.begin(); it != paramValues_.end(); it++) {
        const ParameterValueListType& pvl = it->second;
        for (ParameterValueListType::const_iterator it2 = pvl.begin(); it2 != pvl.end(); it2++) {
            delete *it2;
        }
    }
}




