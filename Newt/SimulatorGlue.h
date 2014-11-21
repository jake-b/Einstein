//
//  TTask.h
//  Einstein
//
//  Created by Matthias Melcher on 7/11/14.
//
//

#ifndef EINSTEIN_NEWT_SIMULATOR_GLUE_H
#define EINSTEIN_NEWT_SIMULATOR_GLUE_H


#ifdef IS_NEWT_SIM

#include "NewtSim.h"

#else

#include <K/Defines/KDefinitions.h>
#include "TROMImage.h"
#include "TMemory.h"
#include "TARMProcessor.h"
#include "TJITGeneric_Macros.h"

#if 0
#define T_ROM_SIMULATION(addr, name) \
	T_ROM_INJECTION(addr, name) {\
		if (ioCPU->GetMode()==TARMProcessor::kUserMode) {\
			return ioUnit;\
		} else {\
			Func_##addr(ioCPU);\
			return 0;\
		}\
	}
#else
#define T_ROM_SIMULATION(addr, name) \
	T_ROM_INJECTION(addr, name) {\
		Func_##addr(ioCPU);\
		return 0;\
	}
#endif

#define RT_PANIC_UNEXPECTED_RETURN_ADDRESS \
	ioCPU->UnexpectedPC();

#endif


#include "SimHandcoded.h"

#endif /* EINSTEIN_NEWT_SIMULATOR_GLUE_H */
