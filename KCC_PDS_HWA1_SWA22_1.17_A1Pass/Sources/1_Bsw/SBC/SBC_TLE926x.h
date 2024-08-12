/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2018, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **********************************************************************************************************************/
#ifndef SBC_TLE926X_H
#define SBC_TLE926X_H

/* XML Version 0.0.1 */
#define SBC_XML_VERSION (00001)

#define CW_BUS_CTRL_1 (0x2F) /*decimal 41*/

#define CW_BUS_CTRL_2 (0x0) /*decimal 0*/

#define CW_GPIO_CTRL (0xE4) /*decimal 32*/

#define CW_HS_CTRL1 (0x11) /*decimal 17*/

#define CW_HS_CTRL2 (0x11) /*decimal 17*/

#define CW_HW_CTRL (0x0) /*decimal 32*/

#define CW_M_S_CTRL (0xC) /*decimal 28*/

#define CW_PWM1_CTRL (0x7F) /*decimal 127*/

#define CW_PWM2_CTRL (0x0) /*decimal 0*/

#define CW_PWM_FREQ_CTRL (0x1) /*decimal 1*/

#define CW_SWK_BTL1_CTRL (0x50) /*decimal 80*/

#define CW_SWK_BTL2_CTRL (0x0) /*decimal 0*/

#define CW_SWK_CAN_FD_CTRL (0x0) /*decimal 0*/

#define CW_SWK_CDR_CTRL2 (0x1) /*decimal 1*/

#define CW_SWK_CDR_LIMIT_HIGH_CTRL (0x54) /*decimal 84*/

#define CW_SWK_CDR_LIMIT_LOW_CTRL (0x4C) /*decimal 76*/

#define CW_SWK_DATA_H_CTRL 0x00000000

#define CW_SWK_DATA_L_CTRL 0x00000000

#define CW_SWK_DLC_CTRL (0x0) /*decimal 0*/

#define CW_SWK_ID0_CTRL (0x0) /*decimal 0*/

#define CW_SWK_ID1_CTRL (0x0) /*decimal 0*/

#define CW_SWK_ID2_CTRL (0x0) /*decimal 0*/

#define CW_SWK_ID3_CTRL (0x0) /*decimal 0*/

#define CW_SWK_MASK_ID0_CTRL (0x0) /*decimal 0*/

#define CW_SWK_MASK_ID1_CTRL (0x0) /*decimal 0*/

#define CW_SWK_MASK_ID2_CTRL (0x0) /*decimal 0*/

#define CW_SWK_MASK_ID3_CTRL (0x0) /*decimal 0*/

#define CW_SW_SD_CTRL (0x0) /*decimal 0*/

#define CW_TIMER1_CTRL (0x11) /*decimal 17*/

#define CW_TIMER2_CTRL (0x11) /*decimal 17*/

#define CW_WD_CTRL (0x3) /*decimal 3*/

#define CW_WK_CTRL_1 (0xC0) /*decimal 192*/

#define CW_WK_CTRL_2 (0x3) /*decimal 3*/

#define CW_WK_FLT_CTRL (0xA) /*decimal 10*/

#define CW_WK_PUPD_CTRL (0x5) /*decimal 5*/

#define LED_EXTENDED_ID (0x1) /*decimal 1*/

#define LED_EXTENDED_ID_MASK (0x1) /*decimal 1*/

#define MATH_BAUDRADE (0x2) /*decimal 2*/

#define MATH_DOUBLE_CDR_FREQ (0x0) /*decimal 0*/

#define MATH_EN_PN (0x0) /*decimal 0*/

#define UI_PWM1_DC (0.0)

#define UI_PWM2_DC (0.0)

#define UI_SWK_IDx_CTRL 0x00000000

#define UI_SWK_MASK_IDx_CTRL 0x00000000

#define UI_VARIANT (0x2) /*decimal 2*/

#endif /* SBC_TLE926X_H */
