// ==============================
// Fichier:			tests.h
// Projet:			Einstein
// Ecrit par:		Paul Guyot (pguyot@kallisys.net)
// 
// Cr�� le:			31/1/2004
// Tabulation:		4 espaces
// 
// Copyright:		� 2004 by Paul Guyot.
// 					Tous droits r�serv�s pour tous pays.
// Licence:			Licence R�flexive Kallisys
// 					http://www.kallisys.org/reflexive/
// ===========
// $Id: tests.h 107 2005-01-05 10:20:39Z paul $
// ===========

#ifndef __TESTS__
#define __TESTS__

///
/// Effectue un test donn�.
/// Si ce test n'existe pas, retourne une erreur.
///
/// \param inTestName	nom du test � effectuer.
/// \param inArgument	argument suppl�mentaire (ou \c null)
///
void test( const char* inTestName, const char* inArgument );

#endif
		// _TESTS_H

// ============================================================================ //
// "The bad reputation UNIX has gotten is totally undeserved, laid on by people //
// who don't understand, who have not gotten in there and tried anything."      //
//                 -- Jim Joyce, owner of Jim Joyce's UNIX Bookstore            //
// ============================================================================ //
