
/* File generated by gen_cfile.py. Should not be modified. */

#include "TestMaster.h"

/**************************************************************************/
/* Declaration of the mapped variables                                    */
/**************************************************************************/
UNS8 DO = 0x0;		/* Mapped at index 0x2000, subindex 0x00 */
UNS8 DI1 = 0x0;		/* Mapped at index 0x200F, subindex 0x00 */
UNS8 DI2 = 0x0;		/* Mapped at index 0x2010, subindex 0x00 */
UNS8 DI3 = 0x0;		/* Mapped at index 0x2011, subindex 0x00 */
UNS8 DI4 = 0x0;		/* Mapped at index 0x2012, subindex 0x00 */
UNS8 DI5 = 0x0;		/* Mapped at index 0x2013, subindex 0x00 */
UNS8 DI6 = 0x0;		/* Mapped at index 0x2014, subindex 0x00 */
UNS8 DI7 = 0x0;		/* Mapped at index 0x2015, subindex 0x00 */
UNS8 DI8 = 0x0;		/* Mapped at index 0x2016, subindex 0x00 */

/**************************************************************************/
/* Declaration of the value range types                                   */
/**************************************************************************/

UNS32 TestMaster_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestMaster_bDeviceNodeId = 0x01;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestMaster_iam_a_slave = 0;

TIMER_HANDLE TestMaster_heartBeatTimers[1] = {TIMER_NONE,};

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 TestMaster_obj1000 = 0x191;	/* 401 */
                    subindex TestMaster_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 TestMaster_obj1001 = 0x0;	/* 0 */
                    subindex TestMaster_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_obj1001 }
                     };

/* index 0x1005 :   SYNC COB ID. */
                    UNS32 TestMaster_obj1005 = 0x40000080;	/* 1073741952 */
                    ODCallback_t TestMaster_Index1005_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestMaster_Index1005[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1005 }
                     };

/* index 0x1006 :   Communication / Cycle Period. */
                    UNS32 TestMaster_obj1006 = 0xC350;	/* 50000 */
                    ODCallback_t TestMaster_Index1006_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestMaster_Index1006[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1006 }
                     };

/* index 0x1016 :   Consumer Heartbeat Time. */
                    UNS8 TestMaster_highestSubIndex_obj1016 = 1; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1016[] = 
                    {
                      0x4005DC	/* 4195804 */
                    };
                    subindex TestMaster_Index1016[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1016 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1016[0] }
                     };

/* index 0x1017 :   Producer Heartbeat Time */ 
                    UNS16 TestMaster_obj1017 = 0x0;   /* 0 */

/* index 0x1018 :   Identity. */
                    UNS8 TestMaster_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex TestMaster_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Serial_Number }
                     };

/* index 0x1280 :   Client SDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1280 = 3; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO = 0x640;	/* 1600 */
                    UNS32 TestMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO = 0x5C0;	/* 1472 */
                    INTEGER32 TestMaster_obj1280_Node_ID_of_the_SDO_Server = 0x40;	/* 64 */
                    subindex TestMaster_Index1280[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1280 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO },
                       { RW, int32, sizeof (INTEGER32), (void*)&TestMaster_obj1280_Node_ID_of_the_SDO_Server }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1400 = 5; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1400_COB_ID_used_by_PDO = 0x1C0;	/* 448 */
                    UNS8 TestMaster_obj1400_Transmission_Type = 0x1;	/* 1 */
                    UNS16 TestMaster_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestMaster_obj1400_Event_Timer = 0x0;	/* 0 */
                    subindex TestMaster_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1400 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1400_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1400_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1400_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1400_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1400_Event_Timer }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 TestMaster_highestSubIndex_obj1600 = 8; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1600[] = 
                    {
                      0x200F0001,	/* 537853953 */
                      0x20100001,	/* 537919489 */
                      0x20110001,	/* 537985025 */
                      0x20120001,	/* 538050561 */
                      0x20130001,	/* 538116097 */
                      0x20140001,	/* 538181633 */
                      0x20150001,	/* 538247169 */
                      0x20160001	/* 538312705 */
                    };
                    subindex TestMaster_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1600 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[7] }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1800 = 5; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1800_COB_ID_used_by_PDO = 0x240;	/* 576 */
                    UNS8 TestMaster_obj1800_Transmission_Type = 0x1;	/* 1 */
                    UNS16 TestMaster_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestMaster_obj1800_Event_Timer = 0x0;	/* 0 */
                    subindex TestMaster_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1800_Event_Timer }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 TestMaster_highestSubIndex_obj1A00 = 1; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1A00[] = 
                    {
                      0x20000008	/* 536870920 */
                    };
                    subindex TestMaster_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1A00[0] }
                     };

/* index 0x2000 :   Mapped variable DO */
                    subindex TestMaster_Index2000[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&DO }
                     };

/* index 0x200F :   Mapped variable DI1 */
                    subindex TestMaster_Index200F[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI1 }
                     };

/* index 0x2010 :   Mapped variable DI2 */
                    subindex TestMaster_Index2010[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI2 }
                     };

/* index 0x2011 :   Mapped variable DI3 */
                    subindex TestMaster_Index2011[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI3 }
                     };

/* index 0x2012 :   Mapped variable DI4 */
                    subindex TestMaster_Index2012[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI4 }
                     };

/* index 0x2013 :   Mapped variable DI5 */
                    subindex TestMaster_Index2013[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI5 }
                     };

/* index 0x2014 :   Mapped variable DI6 */
                    subindex TestMaster_Index2014[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI6 }
                     };

/* index 0x2015 :   Mapped variable DI7 */
                    subindex TestMaster_Index2015[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI7 }
                     };

/* index 0x2016 :   Mapped variable DI8 */
                    subindex TestMaster_Index2016[] = 
                     {
                       { RW, boolean, sizeof (UNS8), (void*)&DI8 }
                     };

const indextable TestMaster_objdict[] = 
{
  { (subindex*)TestMaster_Index1000,sizeof(TestMaster_Index1000)/sizeof(TestMaster_Index1000[0]), 0x1000},
  { (subindex*)TestMaster_Index1001,sizeof(TestMaster_Index1001)/sizeof(TestMaster_Index1001[0]), 0x1001},
  { (subindex*)TestMaster_Index1005,sizeof(TestMaster_Index1005)/sizeof(TestMaster_Index1005[0]), 0x1005},
  { (subindex*)TestMaster_Index1006,sizeof(TestMaster_Index1006)/sizeof(TestMaster_Index1006[0]), 0x1006},
  { (subindex*)TestMaster_Index1016,sizeof(TestMaster_Index1016)/sizeof(TestMaster_Index1016[0]), 0x1016},
  { (subindex*)TestMaster_Index1018,sizeof(TestMaster_Index1018)/sizeof(TestMaster_Index1018[0]), 0x1018},
  { (subindex*)TestMaster_Index1280,sizeof(TestMaster_Index1280)/sizeof(TestMaster_Index1280[0]), 0x1280},
  { (subindex*)TestMaster_Index1400,sizeof(TestMaster_Index1400)/sizeof(TestMaster_Index1400[0]), 0x1400},
  { (subindex*)TestMaster_Index1600,sizeof(TestMaster_Index1600)/sizeof(TestMaster_Index1600[0]), 0x1600},
  { (subindex*)TestMaster_Index1800,sizeof(TestMaster_Index1800)/sizeof(TestMaster_Index1800[0]), 0x1800},
  { (subindex*)TestMaster_Index1A00,sizeof(TestMaster_Index1A00)/sizeof(TestMaster_Index1A00[0]), 0x1A00},
  { (subindex*)TestMaster_Index2000,sizeof(TestMaster_Index2000)/sizeof(TestMaster_Index2000[0]), 0x2000},
  { (subindex*)TestMaster_Index200F,sizeof(TestMaster_Index200F)/sizeof(TestMaster_Index200F[0]), 0x200F},
  { (subindex*)TestMaster_Index2010,sizeof(TestMaster_Index2010)/sizeof(TestMaster_Index2010[0]), 0x2010},
  { (subindex*)TestMaster_Index2011,sizeof(TestMaster_Index2011)/sizeof(TestMaster_Index2011[0]), 0x2011},
  { (subindex*)TestMaster_Index2012,sizeof(TestMaster_Index2012)/sizeof(TestMaster_Index2012[0]), 0x2012},
  { (subindex*)TestMaster_Index2013,sizeof(TestMaster_Index2013)/sizeof(TestMaster_Index2013[0]), 0x2013},
  { (subindex*)TestMaster_Index2014,sizeof(TestMaster_Index2014)/sizeof(TestMaster_Index2014[0]), 0x2014},
  { (subindex*)TestMaster_Index2015,sizeof(TestMaster_Index2015)/sizeof(TestMaster_Index2015[0]), 0x2015},
  { (subindex*)TestMaster_Index2016,sizeof(TestMaster_Index2016)/sizeof(TestMaster_Index2016[0]), 0x2016},
};

const indextable * TestMaster_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1005: i = 2;*callbacks = TestMaster_Index1005_callbacks; break;
		case 0x1006: i = 3;*callbacks = TestMaster_Index1006_callbacks; break;
		case 0x1016: i = 4;break;
		case 0x1018: i = 5;break;
		case 0x1280: i = 6;break;
		case 0x1400: i = 7;break;
		case 0x1600: i = 8;break;
		case 0x1800: i = 9;break;
		case 0x1A00: i = 10;break;
		case 0x2000: i = 11;break;
		case 0x200F: i = 12;break;
		case 0x2010: i = 13;break;
		case 0x2011: i = 14;break;
		case 0x2012: i = 15;break;
		case 0x2013: i = 16;break;
		case 0x2014: i = 17;break;
		case 0x2015: i = 18;break;
		case 0x2016: i = 19;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestMaster_objdict[i];
}

/* To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
UNS8 TestMaster_count_sync[1] = {0,};

quick_index TestMaster_firstIndex = {
  0, /* SDO_SVR */
  6, /* SDO_CLT */
  7, /* PDO_RCV */
  8, /* PDO_RCV_MAP */
  9, /* PDO_TRS */
  10 /* PDO_TRS_MAP */
};

quick_index TestMaster_lastIndex = {
  0, /* SDO_SVR */
  6, /* SDO_CLT */
  7, /* PDO_RCV */
  8, /* PDO_RCV_MAP */
  9, /* PDO_TRS */
  10 /* PDO_TRS_MAP */
};

UNS16 TestMaster_ObjdictSize = sizeof(TestMaster_objdict)/sizeof(TestMaster_objdict[0]); 

CO_Data TestMaster_Data = CANOPEN_NODE_DATA_INITIALIZER(TestMaster);

