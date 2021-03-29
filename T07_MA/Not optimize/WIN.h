#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <string>
#include <tchar.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include "compl.h"

struct timer {
  timer(void) : SyncTime(0),FPS(0), DeltaTime(0), GlobalDeltaTime(0), GlobalTime(0), Time(0),
  StartTime(-1), OldTime(0), FPSTime(0), FrameCounter(0), OldTimeFPS(0), TimePerSec(0) {

  }

  long long StartTime, OldTime, OldTimeFPS, FPSTime, FrameCounter, TimePerSec;
  double    SyncTime, FPS, DeltaTime;
  const int TimerInitID = 87, TimerRefreshID = 30;
  double    GlobalTime, GlobalDeltaTime, Time;
};

struct keyboard {
  BYTE  Keys[256] = {}, KeysClick[256] = {}, OldKeys[256] = {};
  double   Scale = 0.1;

  void Response_Keyboard(void) {
    GetKeyboardState(Keys);
    for (INT i = 0; i < 256; i++)
      KeysClick[i] = !OldKeys[i] && Keys[i];
    memcpy(OldKeys, Keys, 256);
  }

};
static class win {
  static char                  WND_CLASS_NAME[];
  static const int             R = 800;
  static PIXELFORMATDESCRIPTOR pfd;
  static HDC                   hDC;
  static HGLRC                 hGLRC;
  static int                   PixelFormat, W, H, HH, WW;
  static timer                 time;
  static keyboard              keyboard;
  static BYTE                  Pixels[R][R][3];
  static double                X_UP, X_DOWN, Y_UP, Y_DOWN;
  MSG                          msg = {};
  
  static HWND                  hWnd;
  
public:
  
  win(void);

  ~win(void){}
  win(const win& copy) = delete;
  win operator= (const win& copy) = delete;
  int run(void);


private:

  static void TimerInit(void);
  static void Timer(void);
  static LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};
