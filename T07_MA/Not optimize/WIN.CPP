#include "WIN.h"

PIXELFORMATDESCRIPTOR win::pfd = {0};
HDC win::hDC;
HGLRC win::hGLRC;
HWND win::hWnd;
timer win::time;
keyboard win::keyboard;
INT  win::PixelFormat, win::W, win::H, win::HH(R), win::WW(R);
BYTE win::Pixels[win::R][win::R][3] = {};
char win::WND_CLASS_NAME[] = "klass hardbass";
double win::X_UP(2), win::X_DOWN(-2), win::Y_UP(2), win::Y_DOWN(-2);
const double Speed = 0.5;
const double const_time = 0.8;
double X_conf = 0, Y_conf = 0;
double Re_Jul = 0, Im_Jul = 0;
LRESULT CALLBACK win::MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
  switch (Msg) {

  case WM_CREATE:
    hDC = GetDC(hWnd);

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    PixelFormat = ChoosePixelFormat(hDC, &pfd);
    DescribePixelFormat(hDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    SetPixelFormat(hDC, PixelFormat, &pfd);

    hGLRC = wglCreateContext(hDC);

    wglMakeCurrent(hDC, hGLRC);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3, 0.5, 0.7, 1);
    SetTimer(hWnd, time.TimerInitID, 1, nullptr);
    TimerInit();

    break;

    //Exit from the application
  case WM_DESTROY:
    PostQuitMessage(0);
    KillTimer(hWnd, time.TimerRefreshID);
    return 0;
  case WM_TIMER:
   
    keyboard.Response_Keyboard();
    
    if (keyboard.KeysClick[VK_NEXT]) {
      X_UP += keyboard.Scale;
      X_DOWN -= keyboard.Scale;
      Y_UP += keyboard.Scale;
      Y_DOWN -= keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_PRIOR]) {
      X_UP -= keyboard.Scale;
      X_DOWN += keyboard.Scale;
      Y_UP -= keyboard.Scale;
      Y_DOWN += keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_RIGHT]) {
      X_UP += keyboard.Scale;
      X_DOWN += keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_LEFT]) {
      X_UP -= keyboard.Scale;
      X_DOWN -= keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_DOWN]) {
      Y_UP += keyboard.Scale;
      Y_DOWN += keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_UP]) {
      Y_UP -= keyboard.Scale;
      Y_DOWN -= keyboard.Scale;
    }
    else if (keyboard.KeysClick['+'])
      keyboard.Scale += Speed;
    else if (keyboard.KeysClick['-'])
      keyboard.Scale += Speed;
    //else if (keyboard.Keys[VK_ESCAPE]) {
    //  PostQuitMessage(0);
    //  KillTimer(hWnd, time.TimerRefreshID);
    //  return 0;
    //}

    Timer();
    //break;
  //Function for paint
  case WM_PAINT:
    glViewport(0, 0, W, H);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int n;
    X_conf = (X_UP - X_DOWN) / WW;
    Y_conf = (Y_UP - Y_DOWN) / HH;
    
    Re_Jul = 1 * sin(clock() / (double)CLOCKS_PER_SEC);
    Im_Jul = 1 * cos(clock() / (double)CLOCKS_PER_SEC);
    for (int ys(0); ys < HH; ys++)
      for (int xs(0); xs < WW; xs++)
      {

        mk5::complex Z(xs * X_conf + X_DOWN, ys * Y_conf + Y_DOWN);
        n = Z.MandelBrot();
        //n = Z.Julia(Re_Jul, Im_Jul);

        Pixels[ys][xs][0] = 255 - 2 * n;
        Pixels[ys][xs][1] = 255 - 128 * abs(sin(n));
        Pixels[ys][xs][2] = 255 - n * 3;
      }

    glPixelZoom(1, 1);
    glDrawPixels(WW, HH, GL_RGB, GL_UNSIGNED_BYTE, Pixels);

    SwapBuffers(hDC);
    glFinish();
    break;
    //Clean background
  case WM_ERASEBKGND:
    break;
    //Change size of screen
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void win::Timer(void)
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  time.GlobalTime = (double)(t.QuadPart - time.StartTime) / time.TimePerSec;
  time.GlobalDeltaTime = (double)(t.QuadPart - time.OldTime) / time.TimePerSec;

  time.DeltaTime = time.GlobalDeltaTime;
  time.Time = (double)(t.QuadPart - time.StartTime) / time.TimePerSec ;

  time.OldTime = t.QuadPart;
  
  /* FPS */
  if (t.QuadPart - time.OldTimeFPS > time.TimePerSec)
  {
    time.FPS = time.FrameCounter * time.TimePerSec / (double)(t.QuadPart - time.OldTimeFPS) * const_time;

    SetWindowText(hWnd, (std::to_string(time.FPS)).c_str());
    time.OldTimeFPS = t.QuadPart;
    time.FrameCounter = 0;
  }

  /* Increment frame counter */
  time.FrameCounter++;
}

win::win(void) {
  WNDCLASS wc;

  for (int i = 0; i < R; i++)
    for (int j = 0; j < R; j++)
      Pixels[i][j][0] = Pixels[i][j][1] = Pixels[i][j][2] = 127;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = "MIPT";

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return;
  }

  hWnd =
    CreateWindow("MIPT",
      "MIPT",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      R, R,
      NULL,
      NULL,
      GetModuleHandle(NULL),
      NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
}

int win::run(void) {
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

void win::  TimerInit(void) {

  LARGE_INTEGER t;
  QueryPerformanceFrequency(&t);
  time.TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  time.StartTime = time.OldTime = t.QuadPart;
}