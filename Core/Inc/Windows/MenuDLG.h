/*
 * MenuDLG.h
 *
 *  Created on: Aug 13, 2021
 *      Author: User
 */

#ifndef WINDOWS_MENUDLG_H_
#define WINDOWS_MENUDLG_H_

#include "DIALOG.h"

#define ID_MENU_WINDOW     (GUI_ID_USER + 0x00)
#define ID_BTN_TEMP     (GUI_ID_USER + 0x01)
#define ID_BTN_ACC     (GUI_ID_USER + 0x02)
#define ID_BTN_AUTO 	(GUI_ID_USER + 0x10)
#define ID_BTN_TEMP_GRAPH 	(GUI_ID_USER + 0x11)

WM_HWIN CreateMenu(void);


#endif /* WINDOWS_MENUDLG_H_ */
