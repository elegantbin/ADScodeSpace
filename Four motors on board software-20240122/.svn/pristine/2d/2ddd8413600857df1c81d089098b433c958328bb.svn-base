/**
 * \file PosIf.h
 * \brief Position sensor interface
 * \ingroup library_srvsw_if_posif
 *
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without
 * modification, provided that all copyright notices are retained;
 * that all modifications to this file are prominently noted in the
 * modified file; and that this paragraph is not modified.
 *
 *
 * $Revision: $1368.4
 * $Date: $2013-07-12 16:20:31 GMT
 *
 * \defgroup library_srvsw_if_pos Position sensor interface
 * \ingroup library_srvsw_if
 *
 * \defgroup library_srvsw_if_posif Position sensor interface
 * This module implements the basic of position sensor interface
 * \ingroup library_srvsw_if_pos
 *
 */
#ifndef POSIF_H
#define POSIF_H

#include "Arith.StdReal.h"
#include "IfxStdIf_Pos.h"
/**\addtogroup library_srvsw_if_posif
 * \{ */

#ifndef POSIF_DEBUG
#define POSIF_DEBUG       (1)
#endif

#ifndef POSIF_DATA_BITS
/**\brief Default number of bits representing 0 .. 360 degree */
#define POSIF_DATA_BITS   (10)
#endif

#ifndef POSIF_ANGLE_RANGE
/**\brief Default range representing 0 .. 360 degree */
#define POSIF_ANGLE_RANGE (1UL << POSIF_DATA_BITS)
#endif

typedef sint32 PosIf_Raw;       /**< \brief Raw position value as given by sensor */
typedef sint32 PosIf_Angle;     /**< \brief Position value used for electrical or mechanical angle, \ref POSIF_ANGLE_RANGE */

/** \brief Position sensor Types */
typedef enum
{
    PosIf_Types_encoder,
    PosIf_Types_hall,
    PosIf_Types_resolver,
    PosIf_Types_angletrk
} PosIf_Types;

/** \brief Position sensor direction definition */
typedef enum
{
    PosIf_Dir_forward,          /**< \brief Forward direction */
    PosIf_Dir_backward,         /**< \brief Backward direction */
    PosIf_Dir_unknown           /**< \brief Unknown direction */
} PosIf_Dir;

/** \brief Position sensor status definition */
typedef union
{
    uint32 U;
    struct
    {
        uint32 notSynchronised : 1;
        uint32 signalLoss : 1;
        uint32 signalDegradation : 1;
        uint32 trackingLoss : 1;
        uint32 commError : 1;
    } B;
} PosIf_Status;

/** \brief Position sensor diagnostic/statistic */
typedef union
{
    uint32 byIndex[5];
    struct
    {
        uint32 signalLoss;
        uint32 signalDegradation;
        uint32 trackingLoss;
        uint32 noError;
        uint32 commError;
    } byType;
} PosIf_Diag;

/** \brief Forward declaration */
typedef struct PosIf_s PosIf;

typedef PosIf_Raw    (*PosIf_ResetOffset)(PosIf *handle);
typedef void         (*PosIf_SetOffset)(PosIf *handle, PosIf_Raw offset);
typedef void         (*PosIf_SetupElAngleConst)(PosIf *handle, sint32 motorPolePairs);
typedef void         (*PosIf_SetupSpeedConst)(PosIf *handle);
typedef PosIf_Raw    (*PosIf_UpdatePosition)(PosIf *handle);
typedef StdReal      (*PosIf_UpdateSpeed)(PosIf *handle, boolean update);

/** \brief Pointers to function implementations */
typedef struct
{
    PosIf_ResetOffset       resetOffset;
    PosIf_SetOffset         setOffset;
    PosIf_SetupElAngleConst setupElAngleConst;
    PosIf_SetupSpeedConst   setupSpeedConst;
    PosIf_UpdatePosition    updatePosition;
    PosIf_UpdateSpeed       updateSpeed;
} PosIf_Calls;

/** \brief Configuration structure for position sensor interface */
typedef struct
{
    PosIf_Raw offset;               /**< \brief raw position offset */
    boolean   reversed;             /**< \brief reversed direction */
    sint32    periodPerRotation;    /**< \brief 'electrical' periods per mechanical rotation */
    PosIf_Raw resolution;           /**< \brief resolution of this position sensor interface */
    sint32    motorPolePairs;    	/**< \brief Number of motor pole pairs */

} PosIf_Config0;


/** \brief Position interface configuration */
typedef struct
{
    sint32                        offset;                    /**< \brief Position sensor offset */
    boolean                       reversed;                  /**< \brief If true, the sensor direction is reversed */
    sint32                        resolution;                /**< \brief Sensor resolution. For encoder with 1024 pulse per revolution, the value should be 1024 */
    uint16                        periodPerRotation;         /**< \brief Number of period per rotation. Is usually 1 for encoder */
    sint32                        motorPolePairs;            /**< \brief Number of motor pole pairs */


    IfxStdIf_Pos_ResolutionFactor resolutionFactor;          /**< \brief Resolution multiplier for encoder interface, valid is 2, 4. */
    float32                       updatePeriod;              /**< \brief period in seconds, at which the application calls IfxStdIf_Pos_update() */
    float32                       speedModeThreshold;        /**< \brief Speed threshold used for the speed calculation mode. For encoder, above the threshold the pulse count mode is used, below the threshold, the time delta is used */
    float32                       minSpeed;                  /**< \brief Absolute minimal allowed speed. below speed is recognized as 0rad/s */
    float32                       maxSpeed;                  /**< \brief Absolute maximal allowed speed. Above speed is recognized as error */
    boolean                       speedFilterEnabled;        /**< \brief Enable / disable the speed low pass filter */
    float32                       speedFilerCutOffFrequency; /**< \brief Speed low pass filter cut off frequency */
} PosIf_Config; //IfxStdIf_Pos_Config;

/** \brief Position sensor interface data structure */
struct PosIf_s
{
    /* status */
    PosIf_Raw    position;                /**< \brief raw position in ticks. \note: the value already contains the offset */
    StdReal      speed;                   /**< \brief mechanical speed in rad/s */
    sint32       turn;                    /**< \brief number of mechanical turns */
    PosIf_Dir    direction;               /**< \brief rotation direction */
    PosIf_Status status;                  /**< \brief error code (0 = no error) */
#if POSIF_DEBUG
    PosIf_Diag   diag;                    /**< \brief diagnostic and statistic */
#endif
    /* configuration */
    PosIf_Raw          offset;            /**< \brief raw position offset */
    boolean            reversed;          /**< \brief reverse direction */
    sint32             periodPerRotation; /**< \brief 'electrical' periods per mechanical rotation */
    sint32             motorPolePairs;    /**< \brief Number of motor pole pairs */
    PosIf_Raw          resolution;        /**< \brief resolution of this position sensor interface */
    StdReal            elAngleConst;      /**< \brief constant for calculating elAngle (in ticks) from raw position */
    StdRealLong        speedConst;        /**< \brief constant for calculating mechanical speed (in rad/s) from raw speed */
    const PosIf_Calls *functions;         /**< \brief Pointer to functions implementation */
};

//----------------------------------------------------------------------------------------
/** \name Base functions
 * When PosIf* handle is required, the function is usable only after a driver is initialised.
 * \{ */
IFX_INLINE void        PosIf_clearFaults(PosIf *handle);
IFX_INLINE PosIf_Angle PosIf_getElAngle(PosIf *handle);
IFX_INLINE StdReal     PosIf_getElSpeed(PosIf *handle, sint32 motorPolePairs);
IFX_INLINE PosIf_Raw   PosIf_getOffset(PosIf *handle);
IFX_INLINE sint32      PosIf_getPeriodPerRotation(PosIf *handle);
IFX_INLINE PosIf_Raw   PosIf_getResolution(PosIf *handle);
IFX_INLINE StdReal     PosIf_getSpeed(PosIf *handle);
IFX_INLINE sint32      PosIf_getTurn(PosIf *handle);
IFX_INLINE boolean     PosIf_isFault(PosIf *handle);
IFX_INLINE void        PosIf_setPeriodPerRotation(PosIf *handle, sint32 value);  /* FIXME move as virtual */
IFX_INLINE void        PosIf_setResolution(PosIf *handle, PosIf_Raw resolution); /* FIXME move as virtual */
IFX_INLINE boolean     PosIf_reset(PosIf *handle);
IFX_INLINE float32     Rad_s_To_Rpm(float32 speed);
IFX_INLINE float32     Rpm_To_Rad_s(float32 speed);
/** \} */

/** \name Virtual functions
 * These functions are implemented by a driver.
 * \{ */
IFX_INLINE PosIf_Raw PosIf_resetOffset(PosIf *handle);
IFX_INLINE void      PosIf_setOffset(PosIf *handle, PosIf_Raw offset);
IFX_INLINE void      PosIf_setupElAngleConst(PosIf *handle, sint32 motorPolePairs);
IFX_INLINE StdReal   PosIf_updateSpeed(PosIf *handle, boolean update);
IFX_INLINE PosIf_Raw PosIf_updatePosition(PosIf *handle);
/** \} */

/** \name Protected functions
 * Only the driver may use these functions.
 * \{ */
IFX_EXTERN void PosIf_init(PosIf *handle, const PosIf_Config *config);
IFX_EXTERN void PosIf_setupSpeedConst_base(PosIf *handle);
/** \} */

/** \} */

//----------------------------------------------------------------------------------------
// INLINE FUNCTION IMPLEMENTATIONS

/** \brief Clear fault flags */
IFX_INLINE void PosIf_clearFaults(PosIf *handle)
{
    handle->status.U                      = 0;
#if POSIF_DEBUG
    handle->diag.byType.signalLoss        = 0;
    handle->diag.byType.signalDegradation = 0;
    handle->diag.byType.trackingLoss      = 0;
    handle->diag.byType.commError         = 0;
    handle->diag.byType.noError           = 0;
#endif
}


/** \brief Reset the position sensor interface */
IFX_INLINE boolean PosIf_reset(PosIf *handle)
{
    handle->position  = 0;
    handle->speed     = 0;
    handle->direction = PosIf_Dir_unknown;
    handle->turn      = 0;
    PosIf_clearFaults(handle);

    return TRUE;
}


/** \brief Reset the angle offset */
IFX_INLINE PosIf_Raw PosIf_resetOffset(PosIf *handle)
{
    return handle->functions->resetOffset(handle);
}


/** \brief Set the angle offset */
IFX_INLINE void PosIf_setOffset(PosIf *handle, PosIf_Raw offset)
{
    handle->functions->setOffset(handle, offset);
}


/** \brief Setup the elAngle constant */
IFX_INLINE void PosIf_setupElAngleConst(PosIf *handle, sint32 motorPolePairs)
{
    handle->motorPolePairs = motorPolePairs;
    handle->functions->setupElAngleConst(handle, motorPolePairs);
}


/** Set the sensor period per revolution
 * FIXME add call back function to PosIf, then remove setupSpeedConst
 */
IFX_INLINE void PosIf_setPeriodPerRotation(PosIf *handle, sint32 value)
{
    handle->periodPerRotation = value;
    handle->functions->setupSpeedConst(handle);
    handle->functions->setupElAngleConst(handle, handle->motorPolePairs);
}


/** Set the resolution field
 * FIXME add call back function to PosIf, then remove setupSpeedConst
 */
IFX_INLINE void PosIf_setResolution(PosIf *handle, PosIf_Raw resolution)
{
    handle->resolution = resolution;
    /* FIXME call to custom setResolution required  */
    // handle->functions->setResolution(handle, resolution);
    handle->functions->setupSpeedConst(handle);
    handle->functions->setupElAngleConst(handle, handle->motorPolePairs);
}


//----------------------------------------------------------------------------------------

/** \brief Get the electrical angle [0 .. POSIF_ANGLE_MAX - 1] */
IFX_INLINE PosIf_Angle PosIf_getElAngle(PosIf *handle)
{                               //TODO: using StdReal multiplication */
    PosIf_Angle elAngle = (PosIf_Angle)(handle->elAngleConst * (StdReal)handle->position);

    return elAngle & (POSIF_ANGLE_RANGE - 1);
}


/** \brief Get the electrical speed in rad/s */
IFX_INLINE StdReal PosIf_getElSpeed(PosIf *handle, sint32 motorPolePairs)
{                               //TODO: using StdReal multiplication */
    return handle->speed * (StdReal)motorPolePairs;
}


/** \brief Get the mechanical speed in rad/s */
IFX_INLINE StdReal PosIf_getSpeed(PosIf *handle)
{
    return handle->speed;
}


/** \brief Check whether the sensor is faulty */
IFX_INLINE boolean PosIf_isFault(PosIf *handle)
{
    return (handle->status.U != 0) ? TRUE : FALSE;
}


/** \brief Return the number of sensor rotations since last call to PosIf_init() or PosIf_reset() */
IFX_INLINE sint32 PosIf_getTurn(PosIf *handle)
{
    return handle->turn;
}


/** \brief Return the original sensor resolution */
IFX_INLINE PosIf_Raw PosIf_getResolution(PosIf *handle)
{
    return handle->resolution;
}


/** \brief Return the sensor offset */
IFX_INLINE PosIf_Raw PosIf_getOffset(PosIf *handle)
{
    return handle->offset;
}


/** \brief Return the sensor period per revolution*/
IFX_INLINE sint32 PosIf_getPeriodPerRotation(PosIf *handle)
{
    return handle->periodPerRotation;
}


/** \brief Update the speed reading */
IFX_INLINE StdReal PosIf_updateSpeed(PosIf *handle, boolean update)
{
    return handle->functions->updateSpeed(handle, update);
}


/** \brief Update the position reading
 * \return the raw position in original sensor resolution */
IFX_INLINE PosIf_Raw PosIf_updatePosition(PosIf *handle)
{
    return handle->functions->updatePosition(handle);
}


/** \brief Converts from rad/s to rpm
 *
 * \param speed Specifies the speed in rad/s.
 *
 * \return returns the converted speed in rpm.
 * \see Rpm_To_Rad_s()
 */
IFX_INLINE float32 Rad_s_To_Rpm(float32 speed)
{
    return (float32)((60 / (2 * PI)) * speed);
}


/** \brief Converts from rpm to rad/s
 *
 * \param speed Specifies the speed in rpm.
 *
 * \return returns the converted speed in rad/s.
 * \see Rad_s_To_Rpm()
 */
IFX_INLINE float32 Rpm_To_Rad_s(float32 speed)
{
    return (float32)(speed * ((2 * PI) / 60));
}


void initPosIf(void);
//----------------------------------------------------------------------------------------
/** \} */
#endif /* POSIF_H */
