# NOTE: This makefile is designed to be run from one level up in the directory
# hierarchy compared to where it resides. For instance, if this makefile is
# located at 'output/build/Makefile', then it can be launched as:
# 'make -f build/Makefile' from the 'output' directory.

ifeq ($(CXX),)
  CXX=g++
endif
PKGCONFIG := /opt/ibm/InfoSphereStreams/bin/dst-pe-pkg-config.sh
PE_INCLUDE := $(shell $(PKGCONFIG) --cflags dst-spl-pe-install)
PE_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install)
PE_STAND_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install-standalone)
SPL_CXXFLAGS = -Wall -Wno-unused -Wno-sign-compare
SPL_CXXFLAGS += -D_REENTRANT -fPIC -finline-functions -fmessage-length=0
SPL_CXXFLAGS += $(PE_INCLUDE) 
SPL_LDFLAGS = $(PE_LIB)

SPL_TYPES = build/type/BeJwrMXQySUksSQQAC4sCC2.o \
            build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
            build/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.o 
SPL_FUNCTIONS = 
SPL_OPERATORS = build/operator/Data.o \
                build/operator/DebugFileSink.o 
SPL_PE_OBJS = build/pe/BeJwzcUksSYwHAAaTAIO.o \
              build/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.o 
SPL_PE_BINS = bin/Main-a.dpe \
              bin/Main-b.dpe 

.PHONY: distclean clean all types functions operators pes svar

all: bin types functions operators pes svar standalone

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/pe build/svar build/standalone

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o: \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{csv,txt,bin,block,line}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp

build/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.o: \
	    src/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.h \
	    src/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{server,client}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.cpp

build/type/BeJwrMXQySUksSQQAC4sCC2.o: \
	    src/type/BeJwrMXQySUksSQQAC4sCC2.h \
	    src/type/BeJwrMXQySUksSQQAC4sCC2.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<blob data>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMXQySUksSQQAC4sCC2.cpp

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

-include build/operator/Data.d
build/operator/Data.o: \
	    src/operator/Data.h \
	    src/operator/Data.cpp\
	    build/dep/operator/Data.dep \
	    src/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Data'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Main.adl\" -c $(SPL_CXXFLAGS) src/operator/Data.cpp

-include build/operator/DebugFileSink.d
build/operator/DebugFileSink.o: \
	    src/operator/DebugFileSink.h \
	    src/operator/DebugFileSink.cpp\
	    build/dep/operator/DebugFileSink.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] DebugFileSink'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Main.adl\" -c $(SPL_CXXFLAGS) src/operator/DebugFileSink.cpp

build/operator:
	-@mkdir -m 775 -p build/operator

functions: $(SPL_FUNCTIONS)

pes: $(SPL_PE_BINS)

build/pe/BeJwzcUksSYwHAAaTAIO.o: \
	    src/pe/BeJwzcUksSYwHAAaTAIO.h \
	    src/pe/BeJwzcUksSYwHAAaTAIO.cpp  \
	    build/cppOptions \
	    | build/pe
	@echo ' [CXX-pe] pe Main-a'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/pe/BeJwzcUksSYwHAAaTAIO.cpp

PEMain-a = \
	    build/pe/BeJwzcUksSYwHAAaTAIO.o \
	    build/operator/Data.o \
	    build/type/BeJwrMXQySUksSQQAC4sCC2.o \
	    build/type/BeJyrNIo3K04tKkstMkvOyUzNKwEAOPwGCN.o \
	    build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o 

bin/Main-a.dpe: \
	$(PEMain-a) \
	build/dep/Main-a.dep \
	build/ldOptions
	@echo ' [LD-pe] pe Main-a'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/Main-a.dpe -fPIC -shared $(PEMain-a) -lstreams-stdtk-runtime $(SPL_LDFLAGS)

build/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.o: \
	    src/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.h \
	    src/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.cpp  \
	    build/cppOptions \
	    | build/pe
	@echo ' [CXX-pe] pe Main-b'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.cpp

PEMain-b = \
	    build/pe/BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.o \
	    build/operator/DebugFileSink.o \
	    build/type/BeJwrMXQySUksSQQAC4sCC2.o 

bin/Main-b.dpe: \
	$(PEMain-b) \
	build/dep/Main-b.dep \
	build/ldOptions
	@echo ' [LD-pe] pe Main-b'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/Main-b.dpe -fPIC -shared $(PEMain-b) -lstreams-stdtk-runtime $(SPL_LDFLAGS)

build/pe:
	-@mkdir -m 775 build/pe

standalone: 
	@rm -f bin/standalone

