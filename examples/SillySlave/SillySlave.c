
/* File generated by gen_cfile.py. Should not be modified. */

#include "SillySlave.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS8 LifeSignal = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 SillySlave_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 SillySlave_bDeviceNodeId = 0x00;

/**************************************************************************/
/* Array of message processing information */

const UNS8 SillySlave_iam_a_slave = 1;

TIMER_HANDLE SillySlave_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 SillySlave_obj1000 = 0x2000000;	/* 33554432 */
                    subindex SillySlave_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 SillySlave_obj1001 = 0x0;	/* 0 */
                    subindex SillySlave_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&SillySlave_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 SillySlave_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 SillySlave_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    ODCallback_t SillySlave_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                     };
                    subindex SillySlave_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&SillySlave_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1003[0] }
                     };

/* index 0x1005 :   SYNC COB ID */
                    UNS32 SillySlave_obj1005 = 0x0;   /* 0 */

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 SillySlave_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 SillySlave_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 SillySlave_obj100D = 0x0;   /* 0 */

/* index 0x1012 :   TIME COB ID. */
                    UNS32 SillySlave_obj1012 = 0x80000100;	/* 2147483904 */
                    subindex SillySlave_Index1012[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&SillySlave_obj1012 }
                     };

/* index 0x1013 :   High Resolution Timestamp. */
                    UNS32 SillySlave_obj1013 = 0x0;	/* 0 */
                    subindex SillySlave_Index1013[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&SillySlave_obj1013 }
                     };

/* index 0x1014 :   Emergency COB ID */
                    UNS32 SillySlave_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 SillySlave_highestSubIndex_obj1016 = 0;
                    UNS32 SillySlave_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time */ 
                    UNS16 SillySlave_obj1017 = 0x0;   /* 0 */

/* index 0x1018 :   Identity. */
                    UNS8 SillySlave_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 SillySlave_obj1018_Vendor_ID = 0x4321;	/* 17185 */
                    UNS32 SillySlave_obj1018_Product_Code = 0x12;	/* 18 */
                    UNS32 SillySlave_obj1018_Revision_Number = 0x1;	/* 1 */
                    UNS32 SillySlave_obj1018_Serial_Number = 0x1;	/* 1 */
                    subindex SillySlave_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&SillySlave_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1018_Serial_Number }
                     };

/* index 0x1200 :   Server SDO Parameter. */
                    UNS8 SillySlave_highestSubIndex_obj1200 = 2; /* number of subindex - 1*/
                    UNS32 SillySlave_obj1200_COB_ID_Client_to_Server_Receive_SDO = 0x600;	/* 1536 */
                    UNS32 SillySlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO = 0x580;	/* 1408 */
                    ODCallback_t SillySlave_Index1200_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex SillySlave_Index1200[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&SillySlave_highestSubIndex_obj1200 },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1200_COB_ID_Client_to_Server_Receive_SDO },
                       { RO, uint32, sizeof (UNS32), (void*)&SillySlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 SillySlave_highestSubIndex_obj1800 = 5; /* number of subindex - 1*/
                    UNS32 SillySlave_obj1800_COB_ID_used_by_PDO = 0x180;	/* 384 */
                    UNS8 SillySlave_obj1800_Transmission_Type = 0x1;	/* 1 */
                    UNS16 SillySlave_obj1800_Inhibit_Time = 0x64;	/* 100 */
                    UNS8 SillySlave_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 SillySlave_obj1800_Event_Timer = 0x0;	/* 0 */
                    ODCallback_t SillySlave_Index1800_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex SillySlave_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&SillySlave_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&SillySlave_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&SillySlave_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&SillySlave_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&SillySlave_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&SillySlave_obj1800_Event_Timer }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 SillySlave_highestSubIndex_obj1A00 = 1; /* number of subindex - 1*/
                    UNS32 SillySlave_obj1A00[] = 
                    {
                      0x20010008	/* 536936456 */
                    };
                    subindex SillySlave_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&SillySlave_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&SillySlave_obj1A00[0] }
                     };

/* index 0x2001 :   Mapped variable LifeSignal */
                    subindex SillySlave_Index2001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&LifeSignal }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable SillySlave_objdict[] = 
{
  { (subindex*)SillySlave_Index1000,sizeof(SillySlave_Index1000)/sizeof(SillySlave_Index1000[0]), 0x1000},
  { (subindex*)SillySlave_Index1001,sizeof(SillySlave_Index1001)/sizeof(SillySlave_Index1001[0]), 0x1001},
  { (subindex*)SillySlave_Index1012,sizeof(SillySlave_Index1012)/sizeof(SillySlave_Index1012[0]), 0x1012},
  { (subindex*)SillySlave_Index1013,sizeof(SillySlave_Index1013)/sizeof(SillySlave_Index1013[0]), 0x1013},
  { (subindex*)SillySlave_Index1018,sizeof(SillySlave_Index1018)/sizeof(SillySlave_Index1018[0]), 0x1018},
  { (subindex*)SillySlave_Index1200,sizeof(SillySlave_Index1200)/sizeof(SillySlave_Index1200[0]), 0x1200},
  { (subindex*)SillySlave_Index1800,sizeof(SillySlave_Index1800)/sizeof(SillySlave_Index1800[0]), 0x1800},
  { (subindex*)SillySlave_Index1A00,sizeof(SillySlave_Index1A00)/sizeof(SillySlave_Index1A00[0]), 0x1A00},
  { (subindex*)SillySlave_Index2001,sizeof(SillySlave_Index2001)/sizeof(SillySlave_Index2001[0]), 0x2001},
};

const indextable * SillySlave_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1012: i = 2;break;
		case 0x1013: i = 3;break;
		case 0x1018: i = 4;break;
		case 0x1200: i = 5;*callbacks = SillySlave_Index1200_callbacks; break;
		case 0x1800: i = 6;*callbacks = SillySlave_Index1800_callbacks; break;
		case 0x1A00: i = 7;break;
		case 0x2001: i = 8;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &SillySlave_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status SillySlave_PDO_status[1] = {s_PDO_status_Initializer};

const quick_index SillySlave_firstIndex = {
  5, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  6, /* PDO_TRS */
  7 /* PDO_TRS_MAP */
};

const quick_index SillySlave_lastIndex = {
  5, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  6, /* PDO_TRS */
  7 /* PDO_TRS_MAP */
};

const UNS16 SillySlave_ObjdictSize = sizeof(SillySlave_objdict)/sizeof(SillySlave_objdict[0]); 

CO_Data SillySlave_Data = CANOPEN_NODE_DATA_INITIALIZER(SillySlave);

