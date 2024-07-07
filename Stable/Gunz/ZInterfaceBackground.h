#ifndef ZINTERFACEBACKGROUND_H
#define ZINTERFACEBACKGROUND_H




#include "RBspObject.h"
using namespace RealSpace2;

#ifdef _CHURCH

#define BLOCK_SIZE			4000.0f
#define END_BLOCK_OFFSET	3000
#define CHURCH_BLOCK_COUNT		4
#define TIME_PER_DISTANCE		20000
#define END_TIME_PER_DISTANCE	2000

#define LOGIN_SCENE_FIXEDSKY	0			// 하늘에 카메라 고정
#define LOGIN_SCENE_FALLDOWN	1			// 카메라 내려오면서 로고 보임

class RPigeonVisualMesh :public RVisualMesh {
public:
	RPigeonVisualMesh() {
		m_fMoveSpeed = 0.f;
		m_vPos = rvector(0, 0, 0);
		m_back_time = timeGetTime();
	}
	~RPigeonVisualMesh() {

	}

	void SetPos(rvector& pos) {
		m_vPos = pos;
	}

	void SetMoveSpeed(float s) {
		m_fMoveSpeed = s;
	}

	void Move() {

		DWORD this_time = timeGetTime();

		float f = (this_time - m_back_time) / 30.f;//30fps 정도의 속도에서 정상속도

		m_vPos.y -= m_fMoveSpeed * f;

		m_back_time = this_time;
	}

	rmatrix GetMoveMatrix() {
		rmatrix m;
		MakeWorldMatrix(&m, m_vPos, rvector(0, -1, 0), rvector(0, 0, 1));
		return m;
	}

public:

	DWORD	m_back_time;
	rvector m_vPos;

	float m_fMoveSpeed;
};

class ZInterfaceBackground {
private:
	RBspObject* m_pChurch;
	RBspObject* m_pChurchEnd;
	ZMapDesc*   m_pMapDesc;
	RMesh*		m_pPigeonMesh;
	RVisualMeshMgr m_VMeshMgr;
	RVisualMesh* m_pVMesh;
	bool		m_bReverseCam;
	bool		m_bForcedChange;
	int			m_nSceneNumber;
	int			m_nPrevSceneNumber;
	DWORD		m_nSceneChangedTime;
	DWORD		m_nReverseCamTime;
	rvector		m_vCamPos;
	rvector		m_vCharPos;
	rvector		m_vCharDir;
	rvector 	m_EndCamPos;
	rvector		m_EndCamDir;
	rmatrix		m_matWorld;
	float		m_elapsedTime;
protected:
	void SetFogState(float fStart, float fEnd, unsigned long int nColor);
public:
	ZInterfaceBackground();
	virtual ~ZInterfaceBackground();
	void SetScene(int nSceneNumber);
	void Reload(void);
	void LoadMesh();
	void Free();
	void SetRenderState();
	void OnInvalidate();
	void OnRestore();
	void ReverseCam();
	void SetForcedChange(bool bForcedChange);
	void Draw();
	void OnUpdate(float fElapsed);
	bool  CreatePigeon(int nNumPigeon);
	void UpdatePigeon();
	int  SetRandomPigeon(RPigeonVisualMesh* pVMesh, float fAdd = 0.f);
	RBspObject* const	GetChurchEnd() { return m_pChurchEnd; }
	rvector& GetCharPos() { return m_vCharPos; }
	rvector& GetCharDir() { return m_vCharDir; }

};
#else

#define LOGIN_SCENE_FIXEDSKY	0			// 하늘에 카메라 고정
#define LOGIN_SCENE_FALLDOWN	1			// 카메라 내려오면서 로고 보임
#define LOGIN_SCENE_FIXEDCHAR	2			// 캐릭터한테 카메라 고정
#define LOGIN_SCENE_SELECTCHAR	3			// 캐릭터 선택 후
//#define LOGIN_SCENE_MAIN		4

class ZInterfaceBackground{
private:
	RBspObject*	m_pLogin;					// 배경
	ZMapDesc* m_pMapDesc;

	rmatrix		m_matWorld;					// 월드 맵

	int			m_nSceneNumber;				// 장면 번호
	
	rvector		m_vCamPosSt;				// 카메라 시작 위치
	rvector		m_vCamPosEd;				// 카메라 종료 위치
	rvector		m_vCamDirSt;				// 카메라 시작 방향
	rvector		m_vCamDirEd;				// 카메라 종료 위치
	rvector		m_vCharPos;					// 캐릭터 위치
	rvector		m_vCharDir;					// 캐릭터 방향

	DWORD		m_dwClock;

//	bool		m_bShowMaietLogo;			// Maiet logo 보임


protected:
	void SetFogState( float fStart, float fEnd, unsigned long int color);


public:
	ZInterfaceBackground( void);
	virtual ~ZInterfaceBackground( void);

	RBspObject*	const GetChurchEnd() { return m_pLogin; }
	int GetScene() { return m_nSceneNumber; }
	void SetScene(int nSceneNumber);

	void LoadMesh( void);
	void Free(void);
	void Draw(void);

	void OnUpdate(float fElapsed);
	void OnInvalidate();
	void OnRestore();

	rvector& GetCharPos() { return m_vCharPos; }
	rvector& GetCharDir() { return m_vCharDir; }
};

#endif

#endif
