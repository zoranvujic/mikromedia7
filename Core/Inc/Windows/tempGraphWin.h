#ifndef  INC_WINDOWS_TEMPGRAPHWIN_H_
#define  INC_WINDOWS_TEMPGRAPHWIN_H_

#include "DIALOG.h"

#define ID_WINDOW_GRAPH 	(GUI_ID_USER + 0x00 + 0x40)
#define ID_GRAPH_0 		(GUI_ID_USER + 0x01 + 0x40)
#define ID_TEXT_0 		(GUI_ID_USER + 0x02 + 0x40)
#define ID_BTN_NAZAD_GRAPH 	(GUI_ID_USER + 0x03 + 0x40)
#define ID_CHECKBOX_0 	(GUI_ID_USER + 0x04 + 0x40)

WM_HWIN CreateTempGraph(void);


#endif
