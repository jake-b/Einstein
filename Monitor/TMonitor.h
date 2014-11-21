// ==============================
// File:			TMonitor.h
// Project:			Einstein
//
// Copyright 2003-2007 by Paul Guyot (pguyot@kallisys.net).
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// ==============================
// $Id$
// ==============================

#ifndef _TMONITOR_H
#define _TMONITOR_H

#include <K/Defines/KDefinitions.h>

#include "Emulator/Log/TBufferLog.h"

class TEmulator;
class TMemory;
class TARMProcessor;
class TInterruptManager;
class TSymbolList;
class TJITGenericRetarget;

///
/// Class for the monitor (in monitor mode).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 113 $
///
/// \test	aucun test d�fini.
///
class TMonitor
{
public:
	///
	/// Constructor from the emulator.
	///
	TMonitor(
			TBufferLog* inLog,
			TEmulator* inEmulator,
			TSymbolList* inSymbolList,
			const char* inROMPath);

	///
	/// Destructor.
	///
	virtual ~TMonitor( void );

	///
	/// Draw screen.
	/// Return true if the screen was erased.
	///
	Boolean		DrawScreen( void );

	///
	/// Determine if the machine is halted.
	///
	Boolean		IsHalted( void ) const
		{
			return mHalted;
		}

	///
	/// Monitor loop.
	///
	void		Run( void );

	///
	/// Exit from monitor loop.
	///
	void		Stop( void );

	///
	/// Print help for the available commands.
	///
	void		PrintHelp( void );
	
	///
	/// Print help for the log commands.
	///
	void		PrintLoggingHelp( void );
	
	///
	/// Print help for the script commands.
	///
	void		PrintScriptingHelp( void );
	
	///
	/// Print help for the watchpoint commands.
	///
	void		PrintWatchpointHelp( void );
	
	///
	/// Print help for the retargeting commands.
	///
	void		PrintRetargetHelp( void );
	
	///
	/// Output a line.
	///
	void		PrintLine( const char* inLine )
		{
			mLog->LogLine( inLine );
		}

	///
	/// Get monitor socket (notified of state changes).
	///
	int			GetMonitorSocket( void ) const
		{
			return mSocketPair[0];
		}
	
	///
	/// Execute a script.
	///
	/// \return false, if the script file was not found, or the result of
	///         the script operations.
	///
	Boolean		ExecuteScript( const char* inScriptFile );
	
	///
	/// Execute startup script.
	///
	/// \return true if /ROMPath/monitorrc was found and run.
	///
	Boolean		ExecuteStartupScript();
	
	///
	/// Execute a command.
	///
	/// \return true if the command was known.
	///
	Boolean		ExecuteCommand( const char* inCommand );
	
	///
	/// Execute the help command.
	///
	/// \return true if the command was known.
	///
	Boolean		ExecuteHelpCommand( const char* inCommand );
	
	///
	/// Execute a retargeting command.
	///
	/// \return true if the command was known.
	///
	Boolean		ExecuteRetargetCommand( const char* inCommand );
	
	///
	/// Save the current state of the Emulator to a file.
	///
	void		SaveEmulatorState( const char *inFilename=0L );
	
	///
	/// Read the current emulator state from a file.
	///
	void		LoadEmulatorState( const char *inFilename=0L );
	
	///
	/// Save the current state of the Emulator to a file.
	///
	void		SnapEmulatorState( const char *inFilename=0L );
	
	///
	/// Read the current emulator state from a file.
	///
	void		RevertEmulatorState( const char *inFilename=0L );
	
protected:
	/// Constants.
	static const char* kEraseLine;
	static const char* const kRegisterNames[16];
	static const char* const kModesNames[32];
	
	enum ECommand {
		kNop,
		kRun,
		kStep,
		kExit,
		kSaveState,
		kLoadState
	};
	
	enum {
		kPermanentBP	= 0,
		kTemporaryBP	= 1,
		kWatch0BP		= 2,
		kWatch1BP		= 3,
		kWatch2BP		= 4,
		kWatch3BP		= 5
	};

	///
	/// Draw screen when the emulator is halted.
	///
	void		DrawScreenHalted( void );

	///
	/// Draw screen when the emulator is running.
	///
	void		DrawScreenRunning( void );

	///
	/// Output current instruction (to the log).
	///
	void		PrintCurrentInstruction( void );

	///
	/// Output instruction at a given address.
	///
	void		PrintInstruction( KUInt32 inAddr );
	
	///
	/// Output the contents of the current stack.
	///
	void		PrintBacktrace(KSInt32 inNWords=0);
	
public:
	///
	/// Run the emulator (handle breakpoint if we're on a BP).
	///
	void		RunEmulator( void );

	///
	/// Step the emulator (handle breakpoint if we're on a BP).
	///
	void		StepEmulator( void );
	
	///
	/// Process a breakpoint.
	///
	/// \param inBPID		ID of the breakpoint.
	/// \param inBPAddr		address of the breakpoint.
	/// \return true if the machine should be stopped.
	///
	Boolean		ProcessBreakpoint( KUInt16 inBPID, KUInt32 inBPAddr );

	/// \name Platform threading primitives

	///
	/// Create the condition variable and the mutex.
	///
	void		CreateCondVarAndMutex( void );

	///
	/// Delete the condition variable and the mutex.
	///
	void		DeleteCondVarAndMutex( void );
	
	///
	/// Signal the condition varaible.
	///
	void		SignalCondVar( void );

	///
	/// Wait (forever) on the emulator condition varaible.
	///
	void		WaitOnCondVar( void );

	///
	/// Acquire the mutex.
	///
	void		AcquireMutex( void );

	///
	/// Release the mutex.
	///
	void		ReleaseMutex( void );

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TMonitor( const TMonitor& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TMonitor& operator = ( const TMonitor& inCopy );

	/// \name Variables
	TEmulator*				mEmulator;			///< Emulator.
	TMemory*				mMemory;			///< Memory.
	TARMProcessor*			mProcessor;			///< CPU.
	TInterruptManager*		mInterruptManager;	///< Interrupt manager.
	TBufferLog*				mLog;				///< Interface to the log.
	TSymbolList*			mSymbolList;		///< List of symbols.
	Boolean					mHalted;			///< If the emulator is halted.
#if TARGET_OS_WIN32
	// FIXME: we must still implement this
#else
	pthread_cond_t			mCondVar;			///< Condition variable
	pthread_mutex_t			mMutex;				///< Mutex for the loop.
#endif
	ECommand				mCommand;			///< Next command for the
												///< monitor thread.
	char*					mFilename;			///< Argument for next command.
	int						mSocketPair[2];		///< Socket pair for monitor
												///< state changes.
	Boolean					mLastScreenHalted;	///< If last screen was halted.
	TJITGenericRetarget*	mRetarget;			///< retargeting source code generator
	char*					mROMPath;			///< path to the ROM fle directory
};

#endif
		// _TMONITOR_H

// ============================ //
// All constants are variables. //
// ============================ //
