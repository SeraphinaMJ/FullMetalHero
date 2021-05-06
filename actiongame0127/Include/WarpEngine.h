/******************************************************************************/
/*!
\file   WarpEngine.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    Version: 1.11
\date   2012/12/14

*/
/******************************************************************************/
#ifndef WARPENGINE_H
#define WARPENGINE_H

/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h> /*Many Windows things*/
#include <stdio.h>   /*printf, FILE*/

#include "WEGameData.h"

/******************************************************************************/
/*Debug helper functions*/
/*This is the draw text function prototyped from Graphics.*/
void WEGraphicsDrawText(const char* text, float x, float y);

/*These functions should NOT be called!!!!
USE THE MACROS!!!! */
int WEDebugAssert(int expression, const char* outputMessage, 
                  const char* fucntionName,const char* fileName, 
                  unsigned lineNumber);
void WEDebugCreateConsole(void);
void WEDebugDestroyConsole(void);

/*This should only be called for IMPORTANT MESSAGES to the user
Really STUDENTS probably don't need it!!! */
int  WEDebugMessageBox(const char* outputMessage);

/*Use this for unused parameters.*/
#define WEUNUSED_PARAM(p) (p)

/*Macros for debug only!!!*/
#if defined(DEBUG) | defined(_DEBUG)
#include <stdio.h>
#include <stdlib.h>
/*! Use this macro instead of the function to print to the console in debug 
only*/
#define WEDEBUG_PRINT(...) printf(__VA_ARGS__)
/*! Use this macro instead of the function to clear the console in debug only*/
#define WEDEBUG_CLEAR() system("cls")
/*! Use this macro instead of the function to ASSERT in debug only*/
#define WEDEBUG_ASSERT(exp, str) if(WEDebugAssert((exp),(str),      \
  __FUNCTION__,__FILE__, __LINE__))     \
{DebugBreak();}         
/*!Use this macro instead of the function to create a console in debug only*/
#define WEDEBUG_CREATE_CONSOLE() WEDebugCreateConsole();
/*!Use this macro instead of the function to destroy a console in debug only*/
#define WEDEBUG_DESTROY_CONSOLE() WEDebugDestroyConsole();
/*! Use this macro to draw debug text on the screen*/
#define WEDEBUG_DRAW_TEXT(text, tranform)    \
  WEGraphicsDrawText((text),(transform))
#else
/*! Use this macro instead of the function to print to the console in debug 
only*/
#define WEDEBUG_PRINT(...)
/*! Use this macro instead of the function to clear the console in debug only*/
#define WEDEBUG_CLEAR()
/*! Use this macro instead of the function to ASSERT in debug only*/
#define WEDEBUG_ASSERT(expression, outputMessage)
/*!Use this macro instead of the function to create a console in debug only*/
#define WEDEBUG_CREATE_CONSOLE()
/*!Use this macro instead of the function to destroy a console in debug only*/
#define WEDEBUG_DESTROY_CONSOLE()
/*! Use this macro to draw debug text on the screen*/
#define WEDEBUG_DRAW_TEXT(text, tranform) 
#endif

/******************************************************************************/


/*!The smallest value between two floats*/
#define WE_MATH_EPSILON 0.00001f
/*!The value of PI*/
#define WE_MATH_PI      3.1415926535897932384626433832795f
/*!The Value of PI/2*/
#define WE_MATH_HALF_PI (WE_MATH_PI * .5f)
/*!The value of 2PI*/
#define WE_MATH_TWO_PI  (WE_MATH_PI * 2.0f)

/*! The number of rows in the matrix*/
#define WE_ROWS 4
/*! The number of columns in the matrix*/
#define WE_COLS 4

/*! A 2D vector for a 2D game, use a separate variable for Z-Order. */
typedef struct  
{
  float x;/*!< The x coordinate of the vector*/
  float y;/*!< The y coordinate of the vector*/
}WEVec2;

/*! A 4D Matrix for a 2D game, z is used for Z-order.
\verbatim
    |Xx Xy Xz 0 |
    |Yx Yy Yz 0 |
    |Zx Zy Zz 0 |
    |Tx Ty Tz 1 |
\endverbatim
*/
typedef struct  
{
  float m[WE_ROWS][WE_COLS];/*!< Array of 16 floats to represent a 4x4 matrix*/
}WEMtx44;

/******************************************************************************/
/*Math helper functions*/
float WEMathRadianToDegree(float radians);
float WEMathDegreeToRadian(float degrees);
float WEMathClamp(float x, float low, float high);
float WEMathWrap(float x, float low, float high);
float WEMathMin(float x, float y);
float WEMathMax(float x, float y);
int   WEMathInRange(float x, float low, float high);
int   WEMathFloatIsEqual(float x, float y);
int   WEMathIsPowerOf2(int x);
int   WEMathGetNextPowerOf2(int x);

/******************************************************************************/
/*Vector2D Functions uses x y*/
void WEVec2Set(WEVec2* pResult, float x, float y);
void WEVec2Copy(WEVec2* pResult, const WEVec2* pToCopy);

void WEVec2Negate(WEVec2* pResult, const WEVec2* toNegate);
void WEVec2Add(WEVec2* pResult, const WEVec2* pVec1, const WEVec2* pVec2);
void WEVec2Sub(WEVec2* pResult,const WEVec2* pVec1,const WEVec2* pVec2);
void WEVec2Scale(WEVec2* pResult, const WEVec2* pToScale, float scale);

void WEVec2Normalize(WEVec2* pResult, const WEVec2* pToNormalize);
void WEVec2Project(WEVec2* pResult, const WEVec2* pVec1, const WEVec2* pVec2);
void WEVec2PerpProject(WEVec2*pResult,const WEVec2*pVec1,const WEVec2*pVec2);
void WEVec2Lerp(WEVec2* pResult, const WEVec2* pVec1, const WEVec2* pVec2, 
                float time);
float WEVec2CrossZ(const WEVec2* pVec1, const WEVec2* pVec2);
float WEVec2Dot(const WEVec2* pVec1, const WEVec2* pVec2);
/*Get the Length or length squared of a vector*/
float WEVec2Length(const WEVec2* pVec);
float WEVec2LengthSquared(const WEVec2* pVec);
/*Get the Distance or distance squared between tw0 points.*/
float WEVec2Distance(const WEVec2* pVec1, const WEVec2* pVec2);
float WEVec2DistanceSquared(const WEVec2* pVec1, const WEVec2* pVec2);
/*Use these to test*/
int WEVec2Equal(const WEVec2* pVec1, const WEVec2* pVec2);
int WEVec2NotEqual(const WEVec2* pVec1, const WEVec2* pVec2);
int WEVec2IsZero(const WEVec2* pVec);

/******************************************************************************/
/*Matrix 4x4 functions*/
void WEMtx44MakeZero(WEMtx44* pResult);
void WEMtx44MakeIdentity(WEMtx44* pResult);
void WEMtx44Copy(WEMtx44* pResult, const WEMtx44* pToCopy);

void WEMtx44Mult(WEMtx44* pResult, const WEMtx44* pFirst, WEMtx44* pSecond);

void WEMtx44MakeTranslate(WEMtx44* pResult, 
                          float transX, float transY, float zOrder);
void WEMtx44MakeScale(WEMtx44* pResult, float scaleX, float scaleY);
void WEMtx44MakeRotateZ(WEMtx44* pResult, float radians);

void WEMtx44MakeTransform(WEMtx44* pResult, float scaleX, float scaleY, 
                          float radians,
                          float transX, float transY, 
                          float zOrder);
int WEMtx44Equal(const WEMtx44* pMtx1, const WEMtx44* pMtx2);
/******************************************************************************/

/*Distance and Intersection tests*/
float WEDistancePointCircle(const WEVec2* pPoint, const WEVec2* pCircleCenter,
                            float radius);
float WEDistancePointRect(const WEVec2* pPoint, const WEVec2* pRectCenter,
                          float width, float height);
float WEDistancePointLine(const WEVec2* pPoint, const WEVec2*pLineStart,
                        const WEVec2* pLineEnd);
float WEDistanceCircleCircle(const WEVec2* pCircleCenter0, float radius0,
                             const WEVec2* pCircleCenter1, float radius1);
float WEDistanceCircleRect(const WEVec2* pCircleCenter, float radius,
                           const WEVec2* pRectCenter, float width, 
                           float height);
float WEDistanceCircleLine(const WEVec2* pCircleCenter, float radius,
                           const WEVec2* pLineStart, 
                           const WEVec2* pLineEnd);
float WEDistanceRectRect(const WEVec2* pRectCenter0, 
                         float width0, float height0,
                         const WEVec2* pRectCenter1,
                         float width1, float height1);
int WEIntersectionPointCircle(const WEVec2* pPoint, 
                                const WEVec2* pCircleCenter, float radius);
int WEIntersectionPointRect(const WEVec2* pPoint, const WEVec2* pRectCenter,
                          float width, float height);
int WEIntersectionCircleCircle(const WEVec2* pCircleCenter0, float radius0,
                             const WEVec2* pCircleCenter1, float radius1);
int WEIntersectionCircleRect(const WEVec2* pCircleCenter, float radius,
                           const WEVec2* pRectCenter, float width, 
                           float height);
int WEIntersectionCircleLine(const WEVec2* pCircleCenter, float radius,
                           const WEVec2* pLineStart, 
                           const WEVec2* pLineEnd);
int WEIntersectionRectRect(const WEVec2* pRectCenter0, 
                         float width0, float height0,
                         const WEVec2* pRectCenter1,
                         float width1, float height1);

/******************************************************************************/

/*Random numbers*/
void  WERandSeed(int seed);
int   WERandInt(void);
int   WERandIntMinMax(int min, int max);
float WERandFloat(void);
float WERandFloatMinMax(float min, float max);

/******************************************************************************/
/*Input definitions and functions*/
typedef enum 
{
    WE_INVALID,
    WE_BACKSPACE,
    WE_TAB,
    WE_RETURN,
    WE_SHIFT,
    WE_CONTROL,
    WE_CAPS_LOCK,
    WE_ESCAPE,
    WE_SPACE,
    WE_ARROW_UP,
    WE_ARROW_DOWN,
    WE_ARROW_LEFT,
    WE_ARROW_RIGHT,
    WE_0,
    WE_1,
    WE_2,
    WE_3,
    WE_4,
    WE_5,
    WE_6,
    WE_7,
    WE_8,
    WE_9,
    WE_A,
    WE_B,
    WE_C,
    WE_D,
    WE_E,
    WE_F,
    WE_G,
    WE_H,
    WE_I,
    WE_J,
    WE_K,
    WE_L,
    WE_M,
    WE_N,
    WE_O,
    WE_P,
    WE_Q,
    WE_R,
    WE_S,
    WE_T,
    WE_U,
    WE_V,
    WE_W,
    WE_X,
    WE_Y,
    WE_Z,
    WE_F1,
    WE_F2,
    WE_F3,
    WE_F4,
    WE_F5,
    WE_F6,
    WE_F7,
    WE_F8,
    WE_F9,
    WE_F10,
    WE_F11,
    WE_F12,
    WE_SHIFT_LEFT,
    WE_SHIFT_RIGHT,
    WE_CONTROL_LEFT,
    WE_CONTROL_RIGHT,
    WE_MOUSE_LEFT,
    WE_MOUSE_RIGHT,
    WE_MOUSE_MIDDLE,
    WE_MOUSE_MIDDLE_UP,
    WE_MOUSE_MIDDLE_DOWN,
    WE_GAMEPAD_DPAD_UP,
    WE_GAMEPAD_DPAD_DOWN,
    WE_GAMEPAD_DPAD_LEFT,
    WE_GAMEPAD_DPAD_RIGHT,
    WE_GAMEPAD_START,
    WE_GAMEPAD_BACK,
    WE_GAMEPAD_LEFT_THUMB,
    WE_GAMEPAD_RIGHT_THUMB,
    WE_GAMEPAD_LEFT_SHOULDER,
    WE_GAMEPAD_RIGHT_SHOULDER,
    WE_GAMEPAD_A,
    WE_GAMEPAD_B,
    WE_GAMEPAD_X,
    WE_GAMEPAD_Y,
    WE_LAST
}WEKeyCode;

int WEInputIsPressed(WEKeyCode key);
int WEInputIsTriggered(WEKeyCode key);
int WEInputIsRepeating(WEKeyCode key);
int WEInputIsAnyPressed(void);
int WEInputIsAnyTriggered(void);
int WEInputGetMouseX(void);
int WEInputGetMouseY(void);
void WEInputGetMouse(WEVec2* pMouse);
float WEInputGetLeftThumbX(void);
float WEInputGetLeftThumbY(void);
float WEInputGetRightThumbX(void);
float WEInputGetRightThumbY(void);
float WEInputGetLeftTrigger(void);
float WEInputGetRightTrigger(void);
int WEInputGamePadIsConnected(void);
/******************************************************************************/
/*State manager functions*/

/*!A pointer type for State Initialize functions */
typedef void (*WEInitFunc)(WEGameData* pGameData);
/*! A pointer type for State Update Functions.*/
typedef void (*WEUpdateFunc)(WEGameData* pGameData, float dt);
/*!A pointer type for State Shutdown functions.*/
typedef void (*WEShutdownFunc)(WEGameData* pGameData);
/*!A pointer type for State Load functions.*/
typedef void (*WELoadFunc)(WEGameData* pGameData);
/*!A pointer type for State Unload functions.*/
typedef void (*WEUnloadFunc)(WEGameData* pGameData);

/*! A struct to hold the function pointers for states.*/
typedef struct 
{
    WELoadFunc     pLoadFunc;    /*!< A states Load function pointer*/
    WEInitFunc     pInitFunc;    /*!< A states Init function pointer*/
    WEUpdateFunc   pUpdateFunc;  /*!< A states update function pointer*/
    WEShutdownFunc pShutdownFunc;/*!< A states Shutdown function pointer*/
    WEUnloadFunc   pUnloadFunc;  /*!< A states unload function pointer*/
}WEState;

/*Functions to initialize the State Manager*/
int  WESMAddState(const WEState* pState);
void WESMSetStartState(int startState);

/*Allows the user to get information about the State Manager*/
int  WESMGetQuit(void);
int  WESMGetRestart(void);
int  WESMGetPreviousState(void);
int  WESMGetCurrentState(void);
int  WESMGetNextState(void);

/*Allows the user to Set information about he State Manager*/
void WESMSetNextState(int nextState);
void WESMSetQuit(int quit);
void WESMSetRestart(int restart);

/******************************************************************************/
/*Application functions used to control the window and application creation*/


/*! A Struct used to initialize the system. Students should create one of these
and pass it to InitializeSystem*/
typedef struct
{
    HINSTANCE instance;/*!< The Instance from WinMain*/
    const char* title; /*!< The title of the window in windowed mode*/
    WEGameData* pGData;/*!< A pointer that contains the intial game values*/
    int gameDataSize;  /*!< The size of the WEGameData struct*/
    int height;        /*!< The height of the client area of the screen*/
    int width;         /*!< The width of the client area of the screen*/
    int fullScreen;    /*!< If the game should begin in fullscreen or not*/


}WEInitData;

/*This must be called first*/
void WEApplicationInit(const WEInitData* initStruct); 
void WEApplicationUpdate(void); /*This must be called every frame*/
void WEApplicationShutdown(void);/*This must be called last*/

/*Allows the user to control The application*/
void WEApplicationSetFullScreen(int fullScreen);
void WEApplicationSetShow(int show);
void WEApplicationSetShowCursor(int showCursor);
void WEApplicationChangeResolution(int width, int height);

/*Allows the user to get information about the application.*/
int  WEApplicationGetHeight(void);
int  WEApplicationGetWidth(void);

/************************************************************************/
/* Graphics Classes*/



/*Graphics Functions*/

/*Students Must call these functions if they want to draw*/

/*This should be called once before drawing all objects*/
void WEGraphicsStartDraw(void); 
/*This should be called once after drawing all objects*/
void WEGraphicsEndDraw(void);   

int  WEGraphicsLoadTexture(const char* fileName);
void WEGraphicsUnloadTexture(int textureID);
void WEGraphicsSetTexture(int textureID);
void WEGraphicsSetTextureCoords(float scaleX, float scaleY, float radians,
                                float transX, float transY);
void WEGraphicsSetCamera(float cameraX, float cameraY, float cameraZ,
                         float cameraRot);
void WEGraphicsSetToPerspective(void);
void WEGraphicsSetToOrtho(void);

void WEGraphicsDraw(const WEMtx44* pWorldMatrix);
void WEGraphicsDrawText(const char* text, float x, float y);

void WEGraphicsSetBackGroundColor(float red, float green, float blue);
void WEGraphicsSetAttributeColor(unsigned color);
void WEGraphicsSetAttributeColor4(unsigned char alpha, unsigned char blue,
  unsigned char green, unsigned char red);
void WEGraphicsConvertScreenToWorld(float* x, float* y);
void WEGraphicsConvertWorldToScreen(float* x, float* y);
void WEGraphicsSetViewport(int xStart, int yStart, int width, int height);

WEVec2 WEGraphicsGetWorldTopLeft(void);
WEVec2 WEGraphicsGetWorldTopRight(void);
WEVec2 WEGraphicsGetWorldBotLeft(void);
WEVec2 WEGraphicsGetWorldBotRight(void);


#endif /*WARPENGINE_H*/