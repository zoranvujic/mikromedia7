// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_GRAPH 	(GUI_ID_USER + 0x00 + 0x40)
#define ID_GRAPH_0 		(GUI_ID_USER + 0x01 + 0x40)
#define ID_TEXT_0 		(GUI_ID_USER + 0x02 + 0x40)
#define ID_BTN_NAZAD_GRAPH 	(GUI_ID_USER + 0x03 + 0x40)
#define ID_CHECKBOX_0 	(GUI_ID_USER + 0x04 + 0x40)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


// USER START (Optionally insert additional static data)
#define BK_COLOR_1       0x880000
#define COLOR_BK         GUI_DARKGRAY
#define COLOR_BORDER     BK_COLOR_1
#define COLOR_FRAME      GUI_BLACK
#define COLOR_GRID       GUI_DARKGRAY


#define GRAPH_DIV        9   // (2^9 = 512) If this value is changed _aWaves[] need to be changed too!
#define GRID_DIST_X      100
#define GRID_DIST_Y      25
#define GRID_OFF_Y       0

#define TICK_DIST_H      25
#define TICK_DIST_V      25
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Temp Grafik", ID_WINDOW_GRAPH, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Grafik temperature", ID_TEXT_0, 270, 7, 269, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Nazad", ID_BTN_NAZAD_GRAPH, 30, 15, 50, 30, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 40, 50, 700, 400, 0, 0x0, 0 },

  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;

  GRAPH_SCALE_Handle hScaleV;

  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Graph'
    //
	WINDOW_SetBkColor(pMsg->hWin, GUI_DARKGRAY);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
//    GRAPH_SetBorder(hItem, 30, 10, 10, 30);

   GRAPH_SetColor (hItem, GUI_WHITE,     GRAPH_CI_BK);

    //
    // Adjust grid
    //
    GRAPH_SetGridVis  (hItem, 1);
    GRAPH_SetGridDistX(hItem, GRID_DIST_X);
    GRAPH_SetGridDistY(hItem, GRID_DIST_Y);


    hScaleV = GRAPH_SCALE_Create(30>>1, GUI_TA_HCENTER, GRAPH_SCALE_CF_VERTICAL,   TICK_DIST_V);
    GRAPH_SCALE_SetTextColor(hScaleV, GUI_ORANGE);


	GRAPH_SCALE_SetNumDecs(hScaleV,2);
	GRAPH_SCALE_SetFactor(hScaleV,0.02);
	GRAPH_SCALE_SetOff(hScaleV,-1100);

	GRAPH_AttachScale(hItem, hScaleV);

     //Show some graphs

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextColor(hItem, GUI_ORANGE);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "Log");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BTN_NAZAD_GRAPH: // Notifications sent by 'Close'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateACCEL
*/
WM_HWIN CreateTempGraph(void);
WM_HWIN CreateTempGraph(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
