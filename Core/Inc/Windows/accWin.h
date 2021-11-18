/*
 * accWin.h
 *
 *  Created on: Nov 9, 2021
 *      Author: User
 */

#ifndef INC_WINDOWS_ACCWIN_H_
#define INC_WINDOWS_ACCWIN_H_

#include "DIALOG.h"

#define ID_WINDOW_0        (GUI_ID_USER + 0x04)
#define ID_LISTACC       (GUI_ID_USER + 0x05)
#define ID_BTN_NAZAD        (GUI_ID_USER + 0x06)
#define ID_TEXT_TEST        (GUI_ID_USER + 0x07)
#define ID_TEXT_ACC        (GUI_ID_USER + 0x08)

WM_HWIN CreateAccWin(void);

#endif /* INC_WINDOWS_ACCWIN_H_ */
