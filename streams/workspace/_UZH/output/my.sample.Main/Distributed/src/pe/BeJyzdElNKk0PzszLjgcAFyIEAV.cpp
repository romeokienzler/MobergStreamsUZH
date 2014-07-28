// eJwzYHQsLclnNGR0SU0qTQ_1OzMsGAC1jAV6


#include "BeJyzdElNKk0PzszLjgcAFyIEAV.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>


using namespace SPL;

extern int PE_Version;

#define MYPE BeJyzdElNKk0PzszLjgcAFyIEAV



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   PE_Version = 3100;
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}



MAKE_PE(SPL::MYPE);

