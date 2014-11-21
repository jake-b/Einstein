// ==============================
// Fichier:			TMonitorMethodClient.h
// Projet:			K
//
// Cr�� le:			05/09/2002
// Tabulation:		4 espaces
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is TMonitorMethodClient.h.
//
// The Initial Developer of the Original Code is Paul Guyot.
// Portions created by the Initial Developer are Copyright (C) 2002-2004
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========

#ifndef __TMONITORMETHODCLIENT__
#define __TMONITORMETHODCLIENT__

#include <K/Defines/KDefinitions.h>

class TFunctionMonitor;

///
/// Classe pour noter le d�but et la fin d'une m�thode.
/// S'utilise normalement avec des macros, par exemple:
///
///	MONITOR_METHOD;
/// ou
/// MONITOR_FUNCTION;
/// ou encore
/// MONITOR_CONSTRUCTOR;
///
/// La premi�re macro prend l'objet monitor dans un des champs
/// de l'objet, la seconde dans une variable globale (ou via
/// une fonction). La troisi�me r�cup�re/cr�e l'objet et le
/// stocke dans un champ (pour utiliser la premi�re macro).
/// Etc.
///
/// L'objet moniteur est pr�venu de la fin de la fonction/m�thode
/// lorsque l'objet TMonitorMethodClient est d�truit (i.e. lors
/// de la fin normale ou pas de la m�thode).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version 1.0
///
/// \test	aucun test d�fini.
///
class TMonitorMethodClient
{
public:
	///
	/// Constructeur � partir d'un nom de fichier et d'un num�ro de ligne.
	/// Le pointeur sur le nom du fichier doit �tre le m�me � chaque appel
	/// pour le profilage.
	///
	/// \param	inMonitor		objet pr�venu du d�but et de la fin de la
	///							m�thode
	/// \param	inFileName		nom du fichier
	/// \param	inLineNumber	num�ro de ligne
	///
	TMonitorMethodClient(
					TFunctionMonitor* inMonitor,
					const char* inFileName,
					unsigned int inLineNumber );

	///
	/// Destructeur.
	///
	~TMonitorMethodClient( void );

private:
	TFunctionMonitor*	mMonitor;		///< objet moniteur, pr�venu du
										///< d�but et de la fin
	const char*			mFileName;		///< nom du fichier
	const unsigned int	mLineNumber;	///< num�ro de ligne
};

#endif
		// __TMONITORMETHODCLIENT__

// ======================================================================= //
// Around computers it is difficult to find the correct unit of time to    //
// measure progress.  Some cathedrals took a century to complete.  Can you //
// imagine the grandeur and scope of a program that would take as long?    //
//                 -- Epigrams in Programming, ACM SIGPLAN Sept. 1982      //
// ======================================================================= //