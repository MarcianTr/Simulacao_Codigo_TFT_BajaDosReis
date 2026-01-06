//<File !Start!>
// FILE: [Baja_GSLC.h]
// Created by GUIslice Builder version: [0.17.b41]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Num.h"
#include "elem/XProgress.h"
#include "elem/XRamp.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
#include "NotoSerif14pt7b.h"
#include "NotoSerif8pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
extern "C" const unsigned short Baja[] PROGMEM;
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG2,E_POP_KEYPAD_NUM};
enum {E_DRAW_LINE2,E_ELEM_BOX4,E_ELEM_BOX5,E_ELEM_BOX6,E_ELEM_BOX7
      ,E_ELEM_BOX8,E_ELEM_BOX9,E_ELEM_IMAGE1,E_ELEM_NUMINPUT1
      ,E_ELEM_NUMINPUT3,E_ELEM_NUMINPUT4,E_ELEM_PROGRESS1
      ,E_ELEM_RAMPGAUGE2,E_ELEM_TEXT10,E_ELEM_TEXT11,E_ELEM_TEXT12
      ,E_ELEM_TEXT13,E_ELEM_TEXT14,E_ELEM_TEXT15,E_ELEM_TEXT21
      ,E_ELEM_TEXT22,E_ELEM_TEXT23,E_ELEM_KEYPAD_NUM};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN25X40,E_BUILTIN5X8
      ,E_NOTOSERIF14,E_NOTOSERIF8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                3

#define MAX_ELEM_PG_MAIN 5 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG2 17 // # Elems total on page
#define MAX_ELEM_PG2_RAM MAX_ELEM_PG2 // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG2_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG2];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXProgress                m_sXBarGauge1;
gslc_tsXRamp                    m_sXRampGauge2;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemBox7;
extern gslc_tsElemRef* m_pElemBox8;
extern gslc_tsElemRef* m_pElemBox9;
extern gslc_tsElemRef* m_pElemProgress1;
extern gslc_tsElemRef* m_pElemRamp2;
extern gslc_tsElemRef* m_pElemVal1_2;
extern gslc_tsElemRef* m_pElemVal3;
extern gslc_tsElemRef* m_pElemVal4;
extern gslc_tsElemRef* m_pElemKeyPadNum;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN25X40,GSLC_FONTREF_PTR,NULL,5)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSERIF14,GSLC_FONTREF_PTR,&NotoSerif14pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSERIF8,GSLC_FONTREF_PTR,&NotoSerif8pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG2,m_asPage2Elem,MAX_ELEM_PG2_RAM,m_asPage2ElemRef,MAX_ELEM_PG2);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
 
  // Create E_ELEM_IMAGE1 using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_IMAGE1,E_PG_MAIN,(gslc_tsRect){0,0,320,240},
    gslc_GetImageFromProg((const unsigned char*)Baja,GSLC_IMGREF_FMT_BMP24));

  // Create progress bar E_ELEM_PROGRESS1 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS1,E_PG_MAIN,&m_sXBarGauge1,
    (gslc_tsRect){199,217,108,10},0,100,0,GSLC_COL_GREEN,false);
  m_pElemProgress1 = pElemRef;
  
  // Create E_ELEM_TEXT21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT21,E_PG_MAIN,(gslc_tsRect){205,197,97,16},
    (char*)"Carregando...",0,E_NOTOSERIF8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT22,E_PG_MAIN,(gslc_tsRect){178,114,57,20},
    (char*)"Bem",0,E_NOTOSERIF14);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT23,E_PG_MAIN,(gslc_tsRect){214,142,77,21},
    (char*)"Vindo",0,E_NOTOSERIF14);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG2
  
   
  // Create E_ELEM_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX4,E_PG2,(gslc_tsRect){0,0,275,80});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_BOX5 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX5,E_PG2,(gslc_tsRect){0,80,275,80});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
   
  // Create E_ELEM_BOX6 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX6,E_PG2,(gslc_tsRect){0,160,275,80});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG2,(gslc_tsRect){12,11,132,16},
    (char*)"Temperatura",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_NUMINPUT1 numeric input field
  static char m_sInputNumber2[6] = "00.00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT1,E_PG2,(gslc_tsRect){2,36,160,42},
    (char*)m_sInputNumber2,6,E_BUILTIN25X40);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal1_2 = pElemRef;
  
  // Create E_ELEM_NUMINPUT3 numeric input field
  static char m_sInputNumber3[6] = "00.00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT3,E_PG2,(gslc_tsRect){5,101,160,42},
    (char*)m_sInputNumber3,6,E_BUILTIN25X40);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){255,178,53}));
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal3 = pElemRef;
  
  // Create E_ELEM_NUMINPUT4 numeric input field
  static char m_sInputNumber4[6] = "00.00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT4,E_PG2,(gslc_tsRect){4,168,160,42},
    (char*)m_sInputNumber4,6,E_BUILTIN25X40);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal4 = pElemRef;
  
  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG2,(gslc_tsRect){163,44,23,23},
    (char*)"C",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT12,E_PG2,(gslc_tsRect){158,30,24,26},
    (char*)"o",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT13,E_PG2,(gslc_tsRect){183,31,90,24},
    (char*)"BR-01",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG2,(gslc_tsRect){189,108,72,24},
    (char*)"Km/h",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){255,178,53}));
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){255,140,0}),GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT15,E_PG2,(gslc_tsRect){199,173,54,24},
    (char*)"RPM",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){255,140,0}),GSLC_COL_BLACK,GSLC_COL_BLACK);

  // Create E_DRAW_LINE2 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE2,E_PG2,177,0,177,80);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_WHITE,GSLC_COL_WHITE);
   
  // Create E_ELEM_BOX7 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX7,E_PG2,(gslc_tsRect){276,0,44,240});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK4,GSLC_COL_GREEN,GSLC_COL_GREEN);
  m_pElemBox7 = pElemRef;
   
  // Create E_ELEM_BOX8 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX8,E_PG2,(gslc_tsRect){276,120,44,120});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){193,193,0}),GSLC_COL_YELLOW,GSLC_COL_YELLOW);
  m_pElemBox8 = pElemRef;
   
  // Create E_ELEM_BOX9 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX9,E_PG2,(gslc_tsRect){276,192,44,48});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_DK3,GSLC_COL_RED,GSLC_COL_RED);
  m_pElemBox9 = pElemRef;

  // Create progress bar E_ELEM_RAMPGAUGE2 
  pElemRef = gslc_ElemXRampCreate(&m_gui,E_ELEM_RAMPGAUGE2,E_PG2,&m_sXRampGauge2,
    (gslc_tsRect){4,219,267,20},0,100,
    0,GSLC_COL_YELLOW,false);
  m_pElemRamp2 = pElemRef;

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
