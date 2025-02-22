/*
 * CvUniversalPrereqsGame.cpp
 *
 * UNIVERSAL_PREREQS 08/2017 lfgr
 */


// Obligatory include for precompiled headers (?)
#include "CvGameCoreDLL.h"


// implemented header
#include "CvUniversalPrereqsGame.h"


#include <sstream>

#include "CvGame.h"

//-----------------
// CvPrereq<CvGame>
//-----------------

template<>
CvPrereq<CvGame>* CvPrereq<CvGame>::readPrereq( CvXMLLoadUtility* pXml )
{
	const std::string sTagName = getCurrentTagName( pXml->GetXML() );

	TRY_READ_RETURN_PREREQ( sTagName, CvAndPrereq<CvGame> )
	TRY_READ_RETURN_PREREQ( sTagName, CvOrPrereq<CvGame> )
	TRY_READ_RETURN_PREREQ( sTagName, CvNotPrereq<CvGame> )
	TRY_READ_RETURN_PREREQ( sTagName, CvGameUnitCreatedPrereq )
	TRY_READ_RETURN_PREREQ( sTagName, CvGameCivilizationAlivePrereq )

	return NULL;
}

const std::string CvGameUnitCreatedPrereq::TAG = "UnitCreated";

CvGameUnitCreatedPrereq::CvGameUnitCreatedPrereq( const char* szUnit ) :
		m_zUnit( szUnit )
{
}

CvGameUnitCreatedPrereq::~CvGameUnitCreatedPrereq()
{
}

CvPrereqStruct* CvGameUnitCreatedPrereq::makeStruct() const
{
	return new CvPrereqStruct( TAG, m_zUnit.getInfoType() );
}

bool CvGameUnitCreatedPrereq::isValid( const CvGame* pGame ) const
{
	return pGame->getUnitCreatedCount( m_zUnit.getInfoType() ) > 0;
}

void CvGameUnitCreatedPrereq::readPass3() {
	m_zUnit.readPass3();
}

CvGameUnitCreatedPrereq* CvGameUnitCreatedPrereq::read( CvXMLLoadUtility* pXml )
{
	std::string sUnit;
	if( ! pXml->GetXmlVal( sUnit ) )
		return NULL;
	return new CvGameUnitCreatedPrereq( sUnit.c_str() );
}


const std::string CvGameCivilizationAlivePrereq::TAG = "CivilizationAlive";

CvGameCivilizationAlivePrereq::CvGameCivilizationAlivePrereq( const char* szCivilization ) :
	m_zCivilization( szCivilization ) {}

CvGameCivilizationAlivePrereq::~CvGameCivilizationAlivePrereq() {
}

CvPrereqStruct* CvGameCivilizationAlivePrereq::makeStruct() const {
	return new CvPrereqStruct( TAG, m_zCivilization.getInfoType() );
}

bool CvGameCivilizationAlivePrereq::isValid( const CvGame* pGame ) const {
	for( int ePlayer = 0; ePlayer < MAX_CIV_PLAYERS; ePlayer++ ) {
		if( GET_PLAYER( (PlayerTypes) ePlayer ).isAlive() && GET_PLAYER( (PlayerTypes) ePlayer ).getCivilizationType() == m_zCivilization.getInfoType() ) {
			return true;
		}
	}
	return false;
}

void CvGameCivilizationAlivePrereq::readPass3() {
	m_zCivilization.readPass3();
}

CvGameCivilizationAlivePrereq* CvGameCivilizationAlivePrereq::read( CvXMLLoadUtility* pXml ) {
	std::string sCivilization;
	if( ! pXml->GetXmlVal( sCivilization ) )
		return NULL;
	return new CvGameCivilizationAlivePrereq( sCivilization.c_str() );
}
