/*
 * accWinDLG.h
 *
 *  Created on: Aug 13, 2021
 *      Author: User
 */

#ifndef WINDOWS_ACCWINDLG_H_
#define WINDOWS_ACCWINDLG_H_

#include "DIALOG.h"

#define ID_ACC_WINDOW        (GUI_ID_USER + 0x04)
#define ID_TEXT        (GUI_ID_USER + 0x05)
#define ID_LIST        (GUI_ID_USER + 0x06)
#define ID_BTN_NAZAD        (GUI_ID_USER + 0x07)

WM_HWIN CreateaccWin(void);



#endif /* WINDOWS_ACCWINDLG_H_ */
