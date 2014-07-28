// eJwzYHQsLclnNGR0SU0qTXfLzEkNzszLBgBGhwb6


#include "BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>


using namespace SPL;

extern int PE_Version;

#define MYPE BeJwzNHZJTSpNd8vMSQ3OzMuOBwAtbQXA



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   PE_Version = 3100;
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}



MAKE_PE(SPL::MYPE);

