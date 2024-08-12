#ifndef _0_APPSW_DOORSYS_POS_H_
#define _0_APPSW_DOORSYS_POS_H_


#include <OsTypedefs.h>
#include "DoorSysDef.h"
#include "DoorSys.h"


boolean DoorSys_OpeningPosCheck(DoorControl_t *door);


boolean DoorSys_ClosingPosCheck(DoorControl_t *door);

void DoorSys_PosLearn(DoorControl_t *door);


#endif /* _0_APPSW_DOORSYS_POS_H_ */
