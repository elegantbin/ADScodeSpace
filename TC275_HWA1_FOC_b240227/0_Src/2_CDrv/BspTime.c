/*
 *
 * $Date: $2013-06-24 18:38:11 GMT
 * $Revision: $0.3
 */
#include "BspTime.h"

TTime TimeConst[TIMER_COUNT];

/** \brief Initialize the time constants.
 *
 * Initialize the time constants TimeConst_0s, TimeConst_100ns, TimeConst_1us,
 * TimeConst_10us, TimeConst_100us, TimeConst_1ms, TimeConst_10ms, TimeConst_100ms,
 * TimeConst_1s, TimeConst_10s
 * \return None.
 */
void initTime(void)
{
    sint32 Fsys = IfxStm_getFrequency(BSP_DEFAULT_TIMER);

    TimeConst[TIMER_INDEX_10NS]  = Fsys / (1000000000 / 10);
    TimeConst[TIMER_INDEX_100NS] = Fsys / (1000000000 / 100);
    TimeConst[TIMER_INDEX_1US]   = Fsys / (1000000 / 1);
    TimeConst[TIMER_INDEX_10US]  = Fsys / (1000000 / 10);
    TimeConst[TIMER_INDEX_100US] = Fsys / (1000000 / 100);
    TimeConst[TIMER_INDEX_1MS]   = Fsys / (1000 / 1);
    TimeConst[TIMER_INDEX_10MS]  = Fsys / (1000 / 10);
    TimeConst[TIMER_INDEX_100MS] = Fsys / (1000 / 100);
    TimeConst[TIMER_INDEX_1S]    = Fsys * (1);
    TimeConst[TIMER_INDEX_10S]   = Fsys * (10);
    TimeConst[TIMER_INDEX_100S]  = Fsys * (100);
}
