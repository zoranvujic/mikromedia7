/*
 * tempWin.h
 *
 *  Created on: Nov 11, 2021
 *      Author: User
 */

#ifndef INC_WINDOWS_TEMPWIN_H_
#define INC_WINDOWS_TEMPWIN_H_

#include "DIALOG.h"

#define TEMP 0x02
#define ID_WINDOW_0        (GUI_ID_USER + 0x00+TEMP)
#define ID_BTN_NAZAD_TEMP        (GUI_ID_USER + 0x01+TEMP)
#define ID_LISTTEMP        (GUI_ID_USER + 0x02+TEMP)

WM_HWIN CreateTempWin(void);

#endif /* INC_WINDOWS_TEMPWIN_H_ */
