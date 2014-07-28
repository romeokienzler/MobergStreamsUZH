// eJx9kL1ug0AQhLWvYqVIGu4MTkNHECIJP0bBNGmik9mYE3CH7tYm_0OkDlizFLqKtVpr9dmbs0DmiFgOh8f1dWJRStcAv48LKcRhNA7IXfB9NVo7umXNK2_0dsN1ZBHG_0iYO00qxvdZPI37SV8Q0lrKWtP26k658kYBdtijMN80XNYQyfpgUNZpL5_1lIo8FwBYo3tklgyK3oq6l4qN2rR2EHtkX9XnK6sFCVBaIXgwaEMz6C_1iio1_0BoPWSq3A6A4Xld63SB_1LwsGiOaGB8GhJ96mcs4sOvrujbe54NwYfefUEoVaWhFoec5CLhWuKfzoCCeZSKcxn_1WxMHBDMnFOqA_1BfY4x0DC




#include "./DebugSink.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR DebugSink_Base
#define MY_OPERATOR DebugSink$OP


#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Toolkit/Utility.h>
#include <signal.h>

using namespace std;
using namespace streams_boost::iostreams;


void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
        createThreads (1);
}


void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    AutoMutex am (_mutex);
    if (_fd_sink.get())
        _filt_str.reset();
    _connected = false;
    _numConnections.setValueNoLock(0);
    
        _cv.broadcast();
    
    if (_connector.get())
        _connector->terminate();
}

// we have the mutex, already
void MY_OPERATOR_SCOPE::MY_OPERATOR::cleanup()
{
    
    _fs.reset(NULL);
    _filt_str.reset(NULL);
    _fd_sink.reset(NULL);
    _connected = false;
    _numConnections.setValueNoLock(0);
    
        _cv.broadcast();
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::setup (int32_t fd)
{
    AutoMutex am (_mutex);
    setupLocked(fd);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::setupLocked (int32_t fd)
{
    if (!_connector.get() || !_connector->connected())
        return;
    shutdown (fd, SHUT_RD);
    _fd_sink.reset (new file_descriptor_sink(fd));
    _filt_str.reset (new filtering_streambuf<output>);
    
    _filt_str->push (*_fd_sink);
    _fs.reset(new ostream(_filt_str.get()));
    _fs->imbue(locale::classic());
    
    _connected = true;
    _numConnections.setValueNoLock(1);
    
        _cv.broadcast();
    
    SPLAPPTRC(L_DEBUG, "TCPSink: file descriptor: " << fd, SPL_OPER_DBG);
}


void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "TCPSink Connector startup...", SPL_OPER_DBG);
    _connector.reset(new SPL::TCPServer(getPE()));
    
    
        
        
            _connector->setup(lit$0);
        
    
    if (_connector->connected()) {
        setup (_connector->fileDescriptor());
        SPLAPPTRC(L_DEBUG, "TCPSink connected...", SPL_OPER_DBG);
    }

    
        while (!_connectionClosed && 
                !getPE().getShutdownRequested() ) {
            if (!_connected) {
                {
                    // Check to see if we are already finished working (Final seen)
                    AutoMutex am(_mutex);
                    if (_connectionClosed)
                        break; // We are all done here.
                }
                int fd = _connector->reconnect();
                _numReconnects.incrementValueNoLock();
                
                SPLAPPTRC(L_DEBUG, "TCPSink reconnected...", SPL_OPER_DBG);
                setup (fd);
            } else {
                timespec ts = { 1, 0 };
                AutoMutex am(_mutex);
                if(_connected)
                    _cv.waitFor(_mutex, ts);
            }
        }
    

    SPLAPPTRC(L_DEBUG, "TCPSink Connector exitting...", SPL_OPER_DBG);
}


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
: 
    _connected(false), _connectionClosed(false),
    
    _numReconnects(getContext().getMetrics().getCustomMetricByName("nReconnections")),
    _numConnections(getContext().getMetrics().getCustomMetricByName("nConnections")),
    _numWireFormatHandshakesFailed(getContext().getMetrics().getCustomMetricByName("nConfirmWireFormatFailures"))

{
    SPLAPPTRC(L_DEBUG, "TCPSink startup...", SPL_OPER_DBG);
    
    
    signal (SIGPIPE, SIG_IGN);
    _numReconnects.setValueNoLock(0);
    _numConnections.setValueNoLock(0);
    _numWireFormatHandshakesFailed.setValueNoLock(0);
    
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::closeConnection()
{
    _connectionClosed = true;
    cleanup();
    if (_connector.get())
        _connector->terminate();
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port) {
    AutoMutex am(_mutex);
    
        if(_connected)         
            processInternal(punct, port);
    
    // Ensure that we close the connection when we see the Final punctuation
    if (punct == Punctuation::FinalMarker)
        closeConnection();
}

bool MY_OPERATOR_SCOPE::MY_OPERATOR::processInternal(Punctuation const & punct, uint32_t port) {
    try {
        
        
        
            if (_fs.get()) {
                _fs->flush();
            }
            
        
        if (punct == Punctuation::FinalMarker) {
            SPLAPPTRC(L_DEBUG, "TCPSink received FinalMarker...", SPL_OPER_DBG);
            
            cleanup();
        }
    } catch (const std::exception& e) {
        SPLAPPTRC(L_ERROR, SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()), SPL_OPER_DBG);
        cleanup();
        return false;
    } catch (...) {
        SPLAPPTRC(L_ERROR, SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION, SPL_OPER_DBG);
        cleanup();
        return false;
    }
    return true;
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port)
{
    AutoMutex am(_mutex);
    
        if(_connected)
            processInternal(tuple, port);
    
}

bool MY_OPERATOR_SCOPE::MY_OPERATOR::processInternal(Tuple const & tuple$, uint32_t port)
{
    // Write to output
    const IPort0Type& tuple = static_cast<const IPort0Type&>(tuple$);
    try {
        
        
        	    SPL::serializeWithPrecision((*_fs), tuple.get_message()) << '\n';

        if (_fs->fail()) {
            SPLAPPTRC(L_WARN, SPL_APPLICATION_RUNTIME_TCPSINK_LOST_CONNECTION, SPL_OPER_DBG);
            cleanup();
            return false;
        }
        
    } catch (const std::exception& e) {
        SPLAPPTRC(L_ERROR, SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()), SPL_OPER_DBG);
        cleanup();
        return false;
    } catch (...) {
        SPLAPPTRC(L_ERROR, SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION, SPL_OPER_DBG);
        cleanup();
        return false;
    }
    return true;
}



static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("DebugSink",&initer));
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
    addParameterValue ("port", SPL::ConstValueHandle(lit$0));
    param$role$0 = "server";
    addParameterValue ("role", SPL::ConstValueHandle(param$role$0));
    param$flush$0 = SPL::uint32(0U);
    addParameterValue ("flush", SPL::ConstValueHandle(param$flush$0));
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

void MY_BASE_OPERATOR::tupleLogic(Tuple const & tuple, uint32_t port) {
}


void MY_BASE_OPERATOR::processRaw(Tuple const & tuple, uint32_t port) {
    tupleLogic (tuple, port);
    static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
}

void MY_BASE_OPERATOR::processRaw(Punctuation const & punct, uint32_t port) {
    punctLogic (punct, port);
    
    process(punct, port);
}




