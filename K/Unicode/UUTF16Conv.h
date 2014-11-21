// ==============================
// Fichier:			UUTF16Conv.h
// Projet:			K
//
// Cr�� le:			1/09/2001
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
// The Original Code is UUTF16Conv.h.
//
// The Initial Developer of the Original Code is Paul Guyot.
// Portions created by the Initial Developer are Copyright (C) 2001-2004
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========

#ifndef __UUNICODE__
#define __UUNICODE__

#include <K/Unicode/UnicodeDefinitions.h>

///
/// Classe pour convertir vers/depuis UTF-16.
///
/// Les encodages impl�ment�s pour le moment sont:
/// - ISO-8859-1
/// - ISO-8859-2
/// - ASCII
/// - x-mac-roman
/// - UCS-4
/// - UTF-8
///
/// Format UTF-16:
/// - UTF-16 est, pour le Basic Multilingual Plan, comme UCS-2 (utilis� dans NewtonOS), i.e. un caract�re
///   est repr�sent� sur 16 bits. La plupart des ensembles de caract�res g�r�s ici sont inclus dans le
///   BMP. Par cons�quent, pour les encodages avec des caract�res de taille fixe, les fonctions de
///   conversion peuvent �tre grandement simplifi�es.
/// - UTF-16 est du grand indien. Ceci est g�r� par UByteSex si KDefinition.h a su deviner le sexe des
///   octets sur votre plateforme.
///
/// Utilisation de EToOpt:
/// Si un caract�re dans une cha�ne unicode ne peut pas �tre repr�sent� dans l'encodage de destination,
/// deux comportements sont possibles: 
/// - mettre le caract�re de substitution (\c kSubstituteChar)
/// - arr�ter la conversion.
/// EToOpt permet de d�cider quel comportement adopter.
///
/// Cha�nes invalides en entr�e:
/// Si une cha�ne invalide est fournie en entr�e (e.g. 0x80 dans une cha�ne US ASCII), le comportement
/// n'est pas d�fini (il peut y avoir des exceptions, cf la documentation des m�thodes de conversion).
/// Si la cha�ne en entr�e est dans un codage � taille de caract�re variable (e.g. UTF, Shift, etc.)
/// et que le(s) dernier(s) octet(s)/mot(s) sont le d�but d'une suite de caract�res plus longue (ou
/// d'une s�quence d'�chapement) la conversion ne se termine pas correctement. Ces derniers octets ne
/// sont pas marqu�s comme lus (ioInputCount ne les comptera pas) et le r�sultat sera kMiddleOfMultiChar.
/// Ceci signifie que la m�moire tampon doit pouvoir contenir tous les caract�res multi-octets ou les
/// s�quences d'�chapement de la cha�ne fournie en entr�e.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
class UUTF16Conv
{
public:
	///
	/// Indique la politique � suivre lorsqu'un caract�re non repr�sentable est trouv�.
	///
	enum EToOpt {
		kRepCharOnUnrepChar,	///< Utilise le caract�re de remplacement.
		kStopOnUnrepChar		///< Arr�te la conversions.
	};
	
	///
	/// R�sultat des m�thodes de conversion
	///
	enum EResult {
		kInputExhausted = 0,	///< La conversion est termin�e (tous les caract�res en entr�e ont �t� convertis).
								///< Ne signifie pas que la m�moire tampon de sortie est pleine.
		kOutputExhausted,		///< Il n'y a plus de place dans la m�moire tampon de sortie (et la cha�ne en
								///< entr�e n'a pas �t� enti�rement convertie)
		kUnrepCharEncountered,	///< Un caract�re non repr�sentable a �t� trouv� (et l'option est \c kStopOnUnrepChar)
		kMiddleOfMultiChar		///< Les derniers octets de la m�moire tampon d'entr�e/de sortie constituent le d�but
								///< d'un caract�re ou d'une s�quence d'�chappement.
	};
	
	///
	/// Convertit une cha�ne UTF-16 en ISO-8859-1
	///
	/// \param inInputBuffer	cha�ne unicode � convertir.
	/// \param ioInputCount		en entr�e: nombre de caract�res (16 bits) dans la cha�ne unicode.
	///							en sortie: nombre de caract�res (16 bits) convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne ISO-8859-1.
	/// \param ioOutputCount	en entr�e: taille en octets/caract�res de cette m�moire tampon.
	///							en sortie: nombre d'octets/caract�res �crits dans cette m�moire tampon.
	/// \param inConvertToOpt	option pour la conversion. Cf le commentaire sur la classe.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToISO88591(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt8*			outOutputBuffer,
		size_t*			ioOutputCount,
		EToOpt			inConvertToOpt
		);

	///
	/// Convertit une cha�ne ISO-8859-1 en UTF-16
	///
	/// \param inInputBuffer	cha�ne ISO-8859-1 � convertir.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param inCount			taille en octets (entr�e) / mots (sortie) de chaque m�moire tampon.
	///
	static void		FromISO88591(
		const KUInt8*	inInputBuffer,
		KUInt16*		outOutputBuffer,
		size_t			inCount
		);
	
	///
	/// Convertit une cha�ne UTF-16 en ISO-8859-2
	///
	/// \param inInputBuffer	cha�ne unicode � convertir.
	/// \param ioInputCount		en entr�e: nombre de caract�res (16 bits) dans la cha�ne unicode.
	///							en sortie: nombre de caract�res (16 bits) convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne ISO-8859-2.
	/// \param ioOutputCount	en entr�e: taille en octets/caract�res de cette m�moire tampon.
	///							en sortie: nombre d'octets/caract�res �crits dans cette m�moire tampon.
	/// \param inConvertToOpt	option pour la conversion. Cf le commentaire sur la classe.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToISO88592(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt8*			outOutputBuffer,
		size_t*			ioOutputCount,
		EToOpt			inConvertToOpt
		);

	///
	/// Convertit une cha�ne ISO-8859-2 en UTF-16
	///
	/// \param inInputBuffer	cha�ne ISO-8859-2 � convertir.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param inCount			taille en octets (entr�e) / mots (sortie) de chaque m�moire tampon.
	///
	static void		FromISO88592(
		const KUInt8*	inInputBuffer,
		KUInt16*		outOutputBuffer,
		size_t			inCount
		);

	///
	/// Convertit une cha�ne UTF-16 en US-ASCII
	///
	/// \param inInputBuffer	cha�ne unicode � convertir.
	/// \param ioInputCount		en entr�e: nombre de caract�res (16 bits) dans la cha�ne unicode.
	///							en sortie: nombre de caract�res (16 bits) convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne US-ASCII.
	/// \param ioOutputCount	en entr�e: taille en octets/caract�res de cette m�moire tampon.
	///							en sortie: nombre d'octets/caract�res �crits dans cette m�moire tampon.
	/// \param inConvertToOpt	option pour la conversion. Cf le commentaire sur la classe.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToASCII(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt8*			outOutputBuffer,
		size_t*			ioOutputCount,
		EToOpt			inConvertToOpt
		);
	
	///
	/// Convertit une cha�ne US-ASCII en UTF-16
	///
	/// \param inInputBuffer	cha�ne US-ASCII � convertir.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param inCount			taille en octets (entr�e) / mots (sortie) de chaque m�moire tampon.
	///
	static void		FromASCII(
		const KUInt8*	inInputBuffer,
		KUInt16*			outOutputBuffer,
		size_t			inCount
		);

	///
	/// Convertit une cha�ne UTF-16 en MacRoman.
	///
	/// \param inInputBuffer	cha�ne unicode � convertir.
	/// \param ioInputCount		en entr�e: nombre de caract�res (16 bits) dans la cha�ne unicode.
	///							en sortie: nombre de caract�res (16 bits) convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne MacRoman.
	/// \param ioOutputCount	en entr�e: taille en octets/caract�res de cette m�moire tampon.
	///							en sortie: nombre d'octets/caract�res �crits dans cette m�moire tampon.
	/// \param inConvertToOpt	option pour la conversion. Cf le commentaire sur la classe.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToMacRoman(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt8*			outOutputBuffer,
		size_t*			ioOutputCount,
		EToOpt			inConvertToOpt
		);
	
	///
	/// Convertit une cha�ne MacRoman en UTF-16
	///
	/// \param inInputBuffer	cha�ne US-ASCII � convertir.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param inCount			taille en octets (entr�e) / mots (sortie) de chaque m�moire tampon.
	///
	static void		FromMacRoman(
		const KUInt8*	inInputBuffer,
		KUInt16*		outOutputBuffer,
		size_t			inCount
		);

	///
	/// Convertit une cha�ne UTF-16 en UCS-4.
	///
	/// Si tous les caract�res sont dans le BMP, cela revient � �tendre les caract�res de 16 � 32 bits.
	///
	/// \param inInputBuffer	cha�ne UTF-16 � convertir.
	/// \param ioInputCount		en entr�e: nombre de mots de 16 bits dans la cha�ne UTF-16.
	///							en sortie: nombre de mots de 16 bits convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UCS-4.
	/// \param ioOutputCount	en entr�e: taille en mots de 32 bits/caract�res de cette m�moire tampon.
	///							en sortie: nombre de mots de 32 bits/caract�res �crits dans cette m�moire tampon.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToUCS4(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt32*		outOutputBuffer,
		size_t*			ioOutputCount
		);

	///
	/// Convertit une cha�ne UCS-4 en UTF-16.
	///
	/// Si tous les caract�res sont dans le BMP, cela revient � r�duire les caract�res de 32 � 16 bits.
	///
	/// \param inInputBuffer	cha�ne UCS-4 � convertir.
	/// \param ioInputCount		en entr�e: nombre de mots de 32 bits/caract�res dans la cha�ne UCS-4.
	///							en sortie: nombre de mots de 32 bits/caract�res convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param ioOutputCount	en entr�e: taille en mots de 16 bits de cette m�moire tampon.
	///							en sortie: nombre de mots de 16 bits �crits dans cette m�moire tampon.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	FromUCS4(
		const KUInt32*	inInputBuffer,
		size_t*			ioInputCount,
		KUInt16*		outOutputBuffer,
		size_t*			ioOutputCount
		);

	///
	/// Convertit une cha�ne UTF-16 en UTF-8.
	///
	/// La cha�ne UTF-8 fait au plus 3 fois la taille de la cha�ne UTF-16 (en nombre de caract�res).
	///
	/// \param inInputBuffer	cha�ne UTF-16 � convertir.
	/// \param ioInputCount		en entr�e: nombre de mots de 16 bits dans la cha�ne UTF-16.
	///							en sortie: nombre de mots de 16 bits convertis dans cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-8.
	/// \param ioOutputCount	en entr�e: taille en caract�res (8 bits) de cette m�moire tampon.
	///							en sortie: nombre de caract�res �crits dans cette m�moire tampon.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	ToUTF8(
		const KUInt16*	inInputBuffer,
		size_t*			ioInputCount,
		void*			outOutputBuffer,
		size_t*			ioOutputCount
		);

	///
	/// Convertit une cha�ne UTF-8 en UTF-16.
	///
	/// La cha�ne UTF-16 fait au plus 1 fois la taille de la cha�ne UTF-8 (en nombre de caract�res).
	///
	/// \param inInputBuffer	cha�ne UTF-8 � convertir.
	/// \param ioInputCount		en entr�e: taille en caract�res (8 bits) de la cha�ne UTF-8.
	///							en sortie: nombre de caract�res (8 bits) convertis de cette cha�ne.
	/// \param outOutputBuffer	m�moire tampon pour la cha�ne UTF-16.
	/// \param ioOutputCount	en entr�e: taille en mots de 16 bits de cette m�moire tampon.
	///							en sortie: nombre de mots de 16 bits �crits dans cette m�moire tampon.
	/// \return un code indiquant comment la conversion a pris fin. (Cf le commentaire sur la classe et
	///			sur EResult)
	///
	static EResult	FromUTF8(
		const void*		inInputBuffer,
		size_t*			ioInputCount,
		KUInt16*		outOutputBuffer,
		size_t*			ioOutputCount
		);

	///
	/// Convertit un caract�re ISO-8859-2 en UTF-16 via la table.
	///
	/// \param inISOChar	caract�re ISO-8859-2
	/// \return un caract�re UTF-16 �quivalent.
	///
	inline static KUInt16	FromISO88592( const KUInt8 inISOChar )
		{
			if (inISOChar > 0xA0)
			{
				// 0x00A0 et toutes les valeurs inf�rieures sont les m�mes en UTF-16
				return kFromISO88592Table[inISOChar - 0xA0];
			} else {
				return (KUInt16) inISOChar;
			}
		}

	///
	/// Convertit un caract�re MacRoman en UTF-16 via la table.
	///
	/// \param inMacRomanChar	caract�re MacRoman
	/// \return un caract�re UTF-16 �quivalent.
	///
	inline static KUInt16	FromMacRoman( const KUInt8 inMacRomanChar )
		{
			if (inMacRomanChar >= 0x80)
			{
				// 0x0080 et toutes les valeurs inf�rieures sont les m�mes en UTF-16
				return kFromISO88592Table[inMacRomanChar - 0x80];
			} else {
				return (KUInt16) inMacRomanChar;
			}
		}

private:
	static const KUInt16	kToISO88592Table[58][2];	///< Table pour la conversion vers ISO-8859-2.
	static const KUInt16	kFromISO88592Table[0x60];	///< Table pour la conversion depuis ISO-8859-2.
	static const KUInt16	kToMacRomanTable[129][2];	///< Table pour la conversion vers MacRoman.
	static const KUInt16	kFromMacRomanTable[0x80];	///< Table pour la conversion depuis MacRoman.
#if !ARMCPP
	static const KUInt16 	kSubstituteChar;			///< Caract�re de substitution.
#endif
};

#endif
		// __UUNICODE__

// ============================================================================ //
// Mac Airways:                                                                 //
// The cashiers, flight attendants and pilots all look the same, feel the same  //
// and act the same. When asked questions about the flight, they reply that you //
// don't want to know, don't need to know and would you please return to your   //
// seat and watch the movie.                                                    //
// ============================================================================ //
