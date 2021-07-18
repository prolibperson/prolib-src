#include "stdafx.h"
#include "ZCommandTable.h"
#include "MSharedCommandTable.h"
#include "MCommandManager.h"

void ZAddCommandTable(MCommandManager* pCommandManager)
{
	BEGIN_CMD_DESC(pCommandManager);

	// �ܼ� ���ɾ�
	C(ZC_CON_CLEAR, "Con.Clear", "Clear Console", MCDT_LOCAL);
	C(ZC_CON_SIZE, "Con.Size", "Resize Console", MCDT_LOCAL)
		P(MPT_INT, "width")
		P(MPT_INT, "height");
	C(ZC_CON_HIDE, "Con.Hide", "Hide Console", MCDT_LOCAL);

	// Test �ڵ� - �ֿܼ��� Ÿ������ �����Ƽ�...
	C(ZC_CON_CONNECT, "con", "Test Command for connection", MCDT_LOCAL);
	C(ZC_CON_DISCONNECT, "dis", "Test Command for disconnection", MCDT_LOCAL);

	// ������ �˾ƺ��� ���� �׽�Ʈ�Լ�
	C(ZC_TEST_INFO, "t", "Get Test Info", MCDT_LOCAL);

	C(ZC_BEGIN_PROFILE, "bp" , "Begin Profile", MCDT_LOCAL);
	C(ZC_END_PROFILE, "ep" , "End Profile", MCDT_LOCAL);




	C(ZC_CHANGESKIN, "ChangeSkin", "Change Interface Skin", MCDT_LOCAL);
		P(MPT_STR, "SkinName");
	C(ZC_REPORT_119, "Report119", "Report 119", MCDT_LOCAL);
	C(ZC_MESSAGE, "Message", "Message", MCDT_LOCAL);
		P(MPT_INT, "nMessageID")
	C(ZC_EVENT_OPTAIN_SPECIAL_WORLDITEM, "Local.Event.Optain.Special.WorldItem", "Event Optain Special WorldItem", MCDT_LOCAL);
		P(MPT_INT, "WorldItemID")


	C(MC_QUEST_NPC_LOCAL_SPAWN,	"Quest.NPCLocalSpawn", "Npc Local Spawn", MCDT_LOCAL)
		P(MPT_UID,		"uidChar")				// NPC ������
		P(MPT_UID,		"nNpcUID")				// �Ҵ�� NPC ID
		P(MPT_UCHAR,	"nNpcType")				// NPC ����
		P(MPT_UCHAR,	"PositionIndex")		// NPC ���� ��ġ �ε���


	END_CMD_DESC();
}