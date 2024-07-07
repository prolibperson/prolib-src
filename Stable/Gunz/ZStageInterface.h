/***********************************************************************
  ZStageInterface.h
  
  용  도 : 스테이지 인터페이스를 관리하는 클래스. 코드 관리상의 편리를 위해
           분리했음(사실 아직 완전히 다 분리 못했음. -_-;).
  작성일 : 11, MAR, 2004
  작성자 : 임동환
************************************************************************/


#ifndef _ZSTAGEINTERFACE_H
#define _ZSTAGEINTERFACE_H

#define SACRIFICEITEM_SLOT0		0
#define SACRIFICEITEM_SLOT1		1

class MNewQuestScenarioManager;


// 아이템 슬롯에 있는 아이템 정보
class SacrificeItemSlotDesc
{
protected:
	MUID		m_uidUserID;
	int			m_nItemID;
	MBitmap*	m_pIconBitmap;
	char		m_szItemName[25];
	int			m_nQL;
	bool		m_bExist;
    

public:
	SacrificeItemSlotDesc()
	{
		m_nItemID = 0;
		m_pIconBitmap = NULL;
		m_szItemName[ 0] = 0;
		m_nQL = 0;
		m_bExist = false;
	}

public:
	void SetSacrificeItemSlot( const MUID& uidUserID, const unsigned long int nItemID, MBitmap* pBitmap, const char* szItemName, const int nQL);
	void RemoveItem( void)						{ m_bExist = false; }

	MUID GetUID( void)							{ return m_uidUserID; }
	MBitmap* GetIconBitmap( void)				{ return m_pIconBitmap; }
	unsigned long int GetItemID( void)			{ return m_nItemID; }
	const char* GetName( void)					{ return m_szItemName; }
	int GetQL( void)							{ return m_nQL; }
	bool IsExist( void)							{ return m_bExist; }
};


// 희생 아이템박스 리스트 아이템
class SacrificeItemListBoxItem : public MListItem
{
protected:
	unsigned long		m_nItemID;
	MBitmap*			m_pBitmap;
	char				m_szName[ 128];
	int					m_nCount;
	char				m_szDesc[ 256];

public:
	SacrificeItemListBoxItem( const unsigned long nItemID, MBitmap* pBitmap, const char* szName, int nCount, const char* szDesc)
	{
		m_nItemID = nItemID;
		m_pBitmap = pBitmap;
		m_nCount  = nCount;
		strcpy( m_szName, szName);
		strcpy( m_szDesc, szDesc);
	}
	virtual const char* GetString( void)
	{
		return m_szName;
	}
	virtual const char* GetString( int i)
	{
		if ( i == 1)
			return m_szName;

		return NULL;
	}
	virtual MBitmap* GetBitmap( int i)
	{
		if ( i == 0)
			return m_pBitmap;

		return NULL;
	}
	virtual bool GetDragItem(MBitmap** ppDragBitmap, char* szDragString, char* szDragItemString)
	{
		*ppDragBitmap = GetBitmap(0);
		strcpy( szDragString, m_szName);
		strcpy( szDragItemString, m_szName);

		return true;
	}

	unsigned long GetItemID( void)		{ return m_nItemID; }
	const char* GetItemName( void)		{ return m_szName; }
	int GetItemCount( void)				{ return m_nCount; }
	const char* GetItemDesc( void)		{ return m_szDesc; }
};

// 릴레이맵 일시 맵 리스트
class RelayMapList : public MListItem
{
protected:
	char				m_szName[ 128];
	MBitmap*			m_pBitmap;

public:
	RelayMapList();
	RelayMapList( const char* szName, MBitmap* pBitmap)
	{
		strcpy( m_szName, szName);
		m_pBitmap = pBitmap;
	}

	virtual void SetString(const char *szText)
	{
		strcpy(m_szName, szText);
	}
	virtual const char* GetString( void)
	{
		return m_szName;
	}
	virtual const char* GetString( int i)
	{
		if ( i == 1)
			return m_szName;

		return NULL;
	}
	virtual MBitmap* GetBitmap( int i)
	{
		if ( i == 0)
			return m_pBitmap;

		return NULL;
	}

	const char* GetItemName( void)		{ return m_szName; }
};

class SpyMapList : public MListItem
{
protected:
	char				m_szName[128];
	MBitmap*			m_pBitmap;
	MCOLOR				m_textColor;
public:
//	SpyMapList();
	SpyMapList(const char* szName, MBitmap* pBitmap,MCOLOR color)
	{
		strcpy_s(m_szName,sizeof(m_szName), szName);
		m_pBitmap = pBitmap;
		m_textColor = color;
	}

	virtual void SetString(const char *szText)
	{
		strcpy_s(m_szName, sizeof(m_szName), szText);
	}
	virtual const char* GetString(void)
	{
		return m_szName;
	}
	virtual const char* GetString(int i)
	{
		if (i == 1)
			return m_szName;

		return NULL;
	}
	virtual MBitmap* GetBitmap(int i)
	{
		if (i == 0)
			return m_pBitmap;

		return NULL;
	}

	virtual const MCOLOR GetColor(void) { return m_textColor; }
	virtual const MCOLOR GetColor(int i) {
		return m_textColor;
	}
	const char* GetItemName(void) { return m_szName; }
};


enum SCENARIOTYPE
{
	ST_STANDARD		= 0,
	ST_SPECIAL		= 1,
};

// 퀘스트 시나리오 이름 리스트
struct MSenarioList
{
	SCENARIOTYPE	m_ScenarioType;								// 시나리오 타입
	char			m_szName[ 32];								// 퀘스트 시나리오 이름
	char			m_szMapSet[ 32];							// 퀘스트 맵 셋 이름

	MSenarioList()
	{
		m_ScenarioType	= ST_STANDARD;
		m_szName[ 0]	= 0;
		m_szMapSet[ 0]	= 0;
	}
};

typedef map<int,MSenarioList>	LIST_SCENARIONAME;

// Class : ZStageInterface
class ZStageInterface
{
protected:	// protected varialbes
	bool			m_bDrawStartMovieOfQuest;
	DWORD			m_dwClockOfStartMovie;
	int				m_nPosOfItem0, m_nPosOfItem1;
	MMATCH_GAMETYPE		m_nGameType;
	bool			m_bPrevQuest;								// 이전 게임 타입이 퀘스트였는지 아닌지...
	MBitmapR2*		m_pTopBgImg;								// 상단 맵 이미지
	MBitmapR2*		m_pStageFrameImg;							// 프레임 이미지
	MBitmapR2*		m_pItemListFrameImg;						// 아이템 리스트 프레임 이미지
	MBitmapR2*		m_pRelayMapListFrameImg;					// 릴레이맵 리스트 프레임 이미지
	//Custom: spymode
	MBitmapR2*		m_spyMapList;
	LIST_SCENARIONAME	 m_SenarioDesc;							// 퀘스트 시나리오 이름 리스트
	MNewQuestScenarioManager* m_pChallengeQuestScenario;		// 챌린지 퀘스트 시나리오 명세
	bool			m_bRelayMapRegisterComplete;				// 릴레이맵 확인(등록)버튼 여부
	bool			m_bEnableWidgetByRelayMap;					// 릴레이맵경우 위젯활성화 세팅(게임시작버튼 포함)



protected:	// protected functions
	void UpdateSacrificeItem( void);
	void UpdateStageGameInfo(const int nQL, const int nMapsetID, const int nScenarioID);

public:		// public variables
	SacrificeItemSlotDesc	m_SacrificeItem[ 2];				// 각각의 아이템 슬롯에 있는 아이템에 대한 정보를 저장
	
	int				m_nListFramePos;							// 아이템 리스트 프레임 위치
	int				m_nStateSacrificeItemBox;					// 아이템 리스트 프레임 상태

	int				m_nRelayMapListFramePos;					// 릴레이맵 리스트 프레임 위치
	int				m_spyMapListFramePos;

public:		// public functions
	// Initialize
	ZStageInterface( void);										// Constructor
	virtual ~ZStageInterface( void);							// Destructor
	void OnCreate( void);										// On create
	void OnDestroy( void);										// On destroy
	void OpenSacrificeItemBox( void);
	void CloseSacrificeItemBox( void);
	void HideSacrificeItemBox( void);
	void GetSacrificeItemBoxPos( void);
	LIST_SCENARIONAME* GetSenarioDesc()							{ return &m_SenarioDesc;		}
	MNewQuestScenarioManager* GetChallengeQuestScenario() { return m_pChallengeQuestScenario; }

	// 릴레이맵 인터페이스
	void OpenRelayMapBox( void);
	void CloseRelayMapBox( void);
	void HideRelayMapBox( void);
	void SetRelayMapBoxPos( int nBoxPos);
	void PostRelayMapElementUpdate( void);
	void PostRelayMapTurnCount( void);
	void PostRelayMapInfoUpdate( void);
	void RelayMapCreateMapList( void);
	bool GetIsRelayMapRegisterComplete()		{ return m_bRelayMapRegisterComplete; }
	void SetIsRelayMapRegisterComplete(bool b)	{ m_bRelayMapRegisterComplete = b; }
	bool GetEnableWidgetByRelayMap()			{ return m_bEnableWidgetByRelayMap; }
	void SetEnableWidgetByRelayMap(bool b);
	void SetStageRelayMapImage();									// 화면 상단의 맵 이미지 설정하기

	//Custom: spymode
	void OpenSpyBanBox(void);
	void CLoseSpyBanBox(void);
	void HideSpyBanBox(void);
	void SetSpyBanBoxPos(int nBoxPos);
	void CreateSpyBanMapList(void);
	///TODO: make spymode packet to send playable maps n shit of that nature

	// Game stage interface
	void ChangeStageButtons( bool bForcedEntry, bool bMaster, bool bReady);
	void ChangeStageGameSetting( const MSTAGE_SETTING_NODE* pSetting);
	void ChangeStageEnableReady( bool bReady);
	void SetMapName(const char* szMapName);
	//Custom: map time of day
	void SetMapTOD(int const& index);

	void OnStageInterfaceSettup( void);							// Change map combobox
	void OnStageCharListSettup( void);							// Change map combobox
	void OnSacrificeItem0( void);								// Push a button : sacrifice item 0
	void OnSacrificeItem1( void);								// Push a button : sacrifice item 1
	void OnDropSacrificeItem( int nSlotNum);					// Drop sacrifice item
	void OnRemoveSacrificeItem( int nSlotNum);					// Remove sacrifice item

	// Start Movie
	void OnDrawStartMovieOfQuest( void);
	void StartMovieOfQuest( void);
	bool IsShowStartMovieOfQuest( void);


	// Sacrifice item list box
	void SerializeSacrificeItemListBox( void);					// 아이템 박스 업데이트
	bool ReadSenarioNameXML( void);

	void OnStartFail( const int nType, const MUID& uidParam );

#ifdef _QUEST_ITEM
	bool OnResponseDropSacrificeItemOnSlot( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
	bool OnResponseCallbackSacrificeItem( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
	bool OnResponseQL( const int nQL );
	bool OnResponseSacrificeSlotInfo( const MUID& uidOwner1, const unsigned long int nItemID1, 
									  const MUID& uidOwner2, const unsigned long int nItemID2 );
	bool OnNotAllReady();
	bool OnQuestStartFailed( const int nState );
	bool OnStageGameInfo( const int nQL, const int nMapsetID, const unsigned int nScenarioID );
	bool OnNewQuestGameInfo(int const& maxPlayers, int const& minLevel);
#endif

	bool OnStopVote();
};

void OnDropCallbackRemoveSacrificeItem( void* pSelf, MWidget* pSender, MBitmap* pBitmap, const char* szString, const char* szItemString);

// Listner
MListener* ZGetSacrificeItemListBoxListener( void);
MListener* ZGetRelayMapListBoxListener( void);
MListener* ZGetMapListBoxListener( void);


#endif
