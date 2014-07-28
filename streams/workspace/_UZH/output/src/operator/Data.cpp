// eJx1kctugzAQRTW_1EnUN5qGqYkdJ0zaEPApIVTeRQyaKxcNobILI1xdouyBK5dVcnztzPVZ1YfAjrzWS5yXBNpYNZQhsPA7MDMPUXY3mMy5bij53XZzmKt7t_1MBVQWAb59mE6Wj9zpxEuE3UPdbhfLHpVHtNMlomT67dZVUUt6l_12lvtMpD3zNIJmavDXOkov2y69LoO2xd_1s21fg_1XAM7ChEPqBQbxdeV4jKu3YMErWVALzLEs0lSbkpeLHUlRmKylXNc_1Q3Kdfb_0aRaw6VrBBcqCVpmLawfif5WpM4NBoXhAgnSSUf0HnvXvwUDA6FzHIIGqVluRL9NnkBJAscWvY3qD_0GgoFCuiDdgKM5Fle8G8C6CcB6nYEcAv_0t4Z_1fgRKoh8dn9jMOwNg3_1_0maAE




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


#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>
#include <SPL/Runtime/Serialization/StreamByteBuffer.h>
#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Toolkit/IOHelper.h>
#include <SPL/Toolkit/RuntimeException.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>

using namespace std;
using namespace streams_boost::iostreams;


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
    : MY_BASE_OPERATOR(), _fd(0), _tupleNumber(0), 
        
        
        
        
        _numInvalidTuples( getContext().getMetrics().getCustomMetricByName("nInvalidTuples")),
        _numReconnects(getContext().getMetrics().getCustomMetricByName("nReconnections")),
        _numConnections(getContext().getMetrics().getCustomMetricByName("nConnections")),
        _numWireFormatHandshakesFailed(getContext().getMetrics().getCustomMetricByName("nConfirmWireFormatFailures"))
{
    _numInvalidTuples.setValueNoLock(0);
    _numReconnects.setValueNoLock(0);
    _numConnections.setValueNoLock(0);
    _numWireFormatHandshakesFailed.setValueNoLock(0);
}


void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    if (_fd) {
        shutdown (_fd, SHUT_RDWR); // try to clean things up nicely
        _fd = 0;
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "TCPSource startup...", SPL_OPER_DBG);
    SPL::BeJwrMXQySUksSQQAC4sCC2 tuple$;
    
    
    try {
        SPL::TCPServer conn (getPE());
        
        
            
            
            
                conn.setup (lit$0);
            
        

        _fd = conn.fileDescriptor();
        SPLAPPTRC(L_DEBUG, "TCPSource connected.  File descriptor = " << _fd, SPL_OPER_DBG);
        _numConnections.setValueNoLock(1);

        
            while (!getPE().getShutdownRequested()) {
        
                // We might have failed due to handshake failure
                if (conn.connected()) {
                    _tupleNumber = 0; 
                    file_descriptor_source fd_src (_fd, false);
                    filtering_streambuf<input> filt_str;
                    
                    filt_str.push (fd_src);
                    
                        iostream fs (&filt_str);
                        SPL::StreamByteBuffer sbfs(fs);
                    
                    fs.imbue(locale::classic());





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

                    
                        submit (Punctuation::WindowMarker, 0);
                    
                }
                _numConnections.setValueNoLock(0);

                
        
                _fd = conn.reconnect();
                _numConnections.setValueNoLock(1);
                _numReconnects.incrementValueNoLock();
            }
        
        conn.terminate();
    } catch (...) {
        // If we get here, we had an exception, and the throw will destruct conn.
        // Ensure that we don't try to do it twice.
        _fd = 0; // no longer using this
        throw;
    }
    _fd = 0; // no longer using this
    
    SPLAPPTRC(L_DEBUG, "TCPSource exiting...", SPL_OPER_DBG);
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
    addParameterValue ("port", SPL::ConstValueHandle(lit$0));
    param$format$0 = "block";
    addParameterValue ("format", SPL::ConstValueHandle(param$format$0));
    param$role$0 = "server";
    addParameterValue ("role", SPL::ConstValueHandle(param$role$0));
    addParameterValue ("blockSize", SPL::ConstValueHandle(lit$1));
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




