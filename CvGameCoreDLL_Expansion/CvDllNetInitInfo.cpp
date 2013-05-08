/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */

#include "CvGameCoreDLLPCH.h"
#include "CvDllNetInitInfo.h"
#include "CvDllContext.h"

CvDllNetInitInfo::CvDllNetInitInfo()
	: m_uiRefCount(1)
{
	m_szLoadFileName = CvPreGame::loadFileName();
	m_eLoadFileStorage = CvPreGame::loadFileStorage();
	m_szMapScriptName = CvPreGame::mapScriptName();
	m_bIsEarthMap = CvPreGame::isEarthMap();
	m_bIsRandomMapScript = CvPreGame::randomMapScript();
	m_bIsRandomWorldSize = CvPreGame::randomWorldSize();
	m_bWBMapNoPlayers = CvPreGame::mapNoPlayers();
	m_eWorldSize = CvPreGame::worldSize();
	m_eClimate = CvPreGame::climate();
	m_eSeaLevel = CvPreGame::seaLevel();
	m_eEra = CvPreGame::era();
	m_eCalendar = CvPreGame::calendar();
	m_iGameTurn = CvPreGame::gameTurn();
	m_eGameSpeed = CvPreGame::gameSpeed();
	m_eTurnTimer = CvPreGame::turnTimer();
	m_szGameName = CvPreGame::gameName();
	m_uiSyncRandSeed = CvPreGame::syncRandomSeed();
	m_uiMapRandSeed = CvPreGame::mapRandomSeed();

	m_abVictories = CvPreGame::victories();

	m_aGameOptions = CvPreGame::GetGameOptions();
	m_aMapOptions = CvPreGame::GetMapOptions();
	m_abMPOptions = CvPreGame::multiplayerOptions();

	m_iMaxTurns = CvPreGame::maxTurns();
	m_iMaxCityElimination = CvPreGame::maxCityElimination();
	m_iNumMinorCivs = CvPreGame::numMinorCivs();
	m_iNumAdvancedStartPoints = CvPreGame::advancedStartPoints();
	m_eMode = CvPreGame::gameMode();

	ZeroMemory(m_szDebugString, sizeof m_szDebugString);
}
//------------------------------------------------------------------------------
CvDllNetInitInfo::~CvDllNetInitInfo()
{
}
//------------------------------------------------------------------------------
void* CvDllNetInitInfo::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
	        guidInterface == ICvNetInitInfo1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}
//------------------------------------------------------------------------------
unsigned int CvDllNetInitInfo::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
unsigned int CvDllNetInitInfo::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}
	else
	{
		--m_uiRefCount;
		return m_uiRefCount;
	}
}
//------------------------------------------------------------------------------
unsigned int CvDllNetInitInfo::GetReferenceCount()
{
	return m_uiRefCount;
}
//------------------------------------------------------------------------------
void CvDllNetInitInfo::Destroy()
{
	DecrementReference();
}
//------------------------------------------------------------------------------
void CvDllNetInitInfo::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}
//------------------------------------------------------------------------------
void* CvDllNetInitInfo::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}
//------------------------------------------------------------------------------
const char* CvDllNetInitInfo::GetDebugString()
{
	sprintf(m_szDebugString, "NetInitInfo : m_szLoadFileName=\"%s\", "\
	        "m_szMapScriptName=\"%s\", "\
	        "m_bWBMapNoPlayers=\"%s\", "\
	        "m_eWorldSize=%d, "\
	        "m_eClimate=%d "\
	        "m_eSeaLevel=%d "\
	        "m_eEra=%d "\
	        "m_eCalendar=%d "\
	        "m_iGameTurn=%d "\
	        "m_eGameSpeed=%d "\
	        "m_eTurnTimer=%d "\
	        "m_szGameName=\"%s\" "\
	        "m_uiSyncRandSeed=%d "\
	        "m_uiMapRandSeed=%d"
	        , CvPreGame::loadFileName().c_str()
	        , CvPreGame::mapScriptName().c_str()
	        , CvPreGame::mapNoPlayers() ? "true" : "false"
	        , static_cast<int>(CvPreGame::worldSize())
	        , static_cast<int>(CvPreGame::climate())
	        , static_cast<int>(CvPreGame::seaLevel())
	        , static_cast<int>(CvPreGame::era())
	        , static_cast<int>(CvPreGame::calendar())
	        , CvPreGame::gameTurn()
	        , static_cast<int>(CvPreGame::gameSpeed())
	        , static_cast<int>(CvPreGame::turnTimer())
	        , CvPreGame::gameName().c_str()
	        , CvPreGame::syncRandomSeed()
	        , CvPreGame::mapRandomSeed()
	       );

	return m_szDebugString;
}
//------------------------------------------------------------------------------
bool CvDllNetInitInfo::Read(FDataStream& kStream)
{
	kStream >> m_szLoadFileName;
	kStream >> m_eLoadFileStorage;
	kStream >> m_szMapScriptName;
	kStream >> m_bIsEarthMap;
	kStream >> m_bIsRandomMapScript;
	kStream >> m_bIsRandomWorldSize;
	kStream >> m_bWBMapNoPlayers;
	kStream >> m_eWorldSize;
	kStream >> m_eClimate;
	kStream >> m_eSeaLevel;
	kStream >> m_eEra;
	kStream >> m_eCalendar;
	kStream >> m_iGameTurn;
	kStream >> m_eGameSpeed;
	kStream >> m_eTurnTimer;
	kStream >> m_szGameName;
	kStream >> m_uiSyncRandSeed;
	kStream >> m_uiMapRandSeed;

	kStream >> m_iNumVictories;
	kStream >> m_abVictories;

	kStream >> m_aGameOptions;
	kStream >> m_aMapOptions;
	kStream >> m_abMPOptions;
	kStream >> m_iMaxTurns;
	kStream >> m_iPitbossTurnTime;
	kStream >> m_iMaxCityElimination;
	kStream >> m_iNumMinorCivs;
	kStream >> m_iNumAdvancedStartPoints;
	kStream >> m_eMode;
	kStream >> m_bStatReporting;

	return true;
}
//------------------------------------------------------------------------------
bool CvDllNetInitInfo::Write(FDataStream& kStream)
{
	kStream << m_szLoadFileName;
	kStream << m_eLoadFileStorage;
	kStream << m_szMapScriptName;
	kStream << m_bIsEarthMap;
	kStream << m_bIsRandomMapScript;
	kStream << m_bIsRandomWorldSize;
	kStream << m_bWBMapNoPlayers;
	kStream << m_eWorldSize;
	kStream << m_eClimate;
	kStream << m_eSeaLevel;
	kStream << m_eEra;
	kStream << m_eCalendar;
	kStream << m_iGameTurn;
	kStream << m_eGameSpeed;
	kStream << m_eTurnTimer;
	kStream << m_szGameName;
	kStream << m_uiSyncRandSeed;
	kStream << m_uiMapRandSeed;
	kStream << m_iNumVictories;
	kStream << m_abVictories;
	kStream << m_aGameOptions;
	kStream << m_aMapOptions;
	kStream << m_abMPOptions;
	kStream << m_iMaxTurns;
	kStream << m_iPitbossTurnTime;
	kStream << m_iMaxCityElimination;
	kStream << m_iNumMinorCivs;
	kStream << m_iNumAdvancedStartPoints;
	kStream << m_eMode;
	kStream << m_bStatReporting;

	return true;
}
//------------------------------------------------------------------------------
bool CvDllNetInitInfo::Commit()
{
	// Copy the settings into our initialization data structure
	CvPreGame::setMapScriptName(m_szMapScriptName);
	CvPreGame::setRandomMapScript(m_bIsRandomMapScript);
	CvPreGame::setEarthMap(m_bIsEarthMap);
	CvPreGame::setTransferredMap(false);		// We'll always set this manually
	CvPreGame::setLoadFileName(m_szLoadFileName, m_eLoadFileStorage);
	CvPreGame::setMapNoPlayers(m_bWBMapNoPlayers);
	CvPreGame::setWorldSize(m_eWorldSize,false);
	CvPreGame::setRandomWorldSize(m_bIsRandomWorldSize);
	CvPreGame::setClimate(m_eClimate);
	CvPreGame::setSeaLevel(m_eSeaLevel);
	CvPreGame::setEra(m_eEra);
	CvPreGame::setCalendar(m_eCalendar);
	CvPreGame::setGameTurn(m_iGameTurn);
	CvPreGame::setGameSpeed(m_eGameSpeed);
	CvPreGame::setTurnTimer(m_eTurnTimer);
	CvPreGame::setGameName(m_szGameName);
	CvPreGame::setSyncRandomSeed(m_uiSyncRandSeed);
	CvPreGame::setMapRandomSeed(m_uiMapRandSeed);
	CvPreGame::setVictories(m_abVictories);
	CvPreGame::SetGameOptions(m_aGameOptions);
	CvPreGame::SetMapOptions(m_aMapOptions);
	CvPreGame::setMultiplayerOptions(m_abMPOptions);
	CvPreGame::setMaxTurns(m_iMaxTurns);
	CvPreGame::setMaxCityElimination(m_iMaxCityElimination);
	CvPreGame::setNumMinorCivs(m_iNumMinorCivs);
	CvPreGame::setAdvancedStartPoints(m_iNumAdvancedStartPoints);
	CvPreGame::setGameMode(m_eMode);

	return true;
}