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
double win::X_RIGHT(2), win::X_LEFT(-2), win::Y_UP(2), win::Y_DOWN(-2);
const double Speed = 0.5;
const int NUM_ITER = 190;
const float koef = 256 / 190.0 ;

void win::Mandelbrot(void) {
  int counter = 0;
  //Маски для обсчета количества итераций на каждый пиксель
  __m128i mask32_pixel_1 = { 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
  __m128i mask32_pixel_2 = { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF };
  __m128i mask32_pixel_3 = { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF };
  __m128i mask32_pixel_4 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };

  //Адинъ
  __m128i ONE = _mm_set1_epi32(1);
  //Радиус мандельброта
  __m128  RADIUS = _mm_set1_ps(4);
  
  for (int ys(0); ys < HH; ys++) {
    float y0 = ys * (Y_UP - Y_DOWN) / HH + Y_DOWN;

    __m128 image = _mm_set1_ps(y0);

    for (int xs(0); xs < WW; xs += 4) {
      __m128i iterations = _mm_set1_epi32(0);
      __m128i iter_mask = _mm_set1_epi32(0xFFFFFFFF);

      //Шаг до следующего пикселя в координатах множества
      float deltaX = (X_RIGHT - X_LEFT) / WW;

      //Считываем положение по X, переводя из координат экрана на координаты множества Мандельброта
      float x0 = xs * deltaX + X_LEFT;

      //Считаем координаты вещественной части для 4 пикселей
      __m128 real = _mm_set_ps(x0, x0 + deltaX, x0 + deltaX * 2, x0 + deltaX * 3);

      __m128 working_real = real;
      __m128 working_image = image;

      //Сам цикл Мандельброта
      for (int i_count(1); i_count < NUM_ITER; i_count++) {
        //Квадраты вещественной и мнимой частей
        __m128 square_real = _mm_mul_ps(working_real, working_real);
        __m128 square_image = _mm_mul_ps(working_image, working_image);

        //Квадраты длины векторов
        __m128 working_len = _mm_add_ps(square_real, square_image);

        //Сравниваем длину векторов с теми, что даны
        __m128i comparing_len = _mm_add_epi32(_mm_cvtps_epi32(_mm_cmpge_ps(working_len, RADIUS)), ONE);
        //1 - если внутри, 0 - если снаружи

        //Проверяем результаты сравнения для каждого радиуса
        //И зануляем, если получилось меньшу нуля
        if (*((int32_t*)&comparing_len) < 0)
          *((int32_t*)&comparing_len) = 0;
        if (*((int32_t*)&comparing_len + 1) < 0)
          *((int32_t*)&comparing_len + 1) = 0;
        if (*((int32_t*)&comparing_len + 2) < 0)
          *((int32_t*)&comparing_len + 2) = 0;
        if (*((int32_t*)&comparing_len + 3) < 0)
          *((int32_t*)&comparing_len + 3) = 0;

        //Применяем маску для подсчета
        //Если он уже в кругу, то он прибавит 0, а если больше, то 1
        iterations = _mm_add_epi32(iterations, _mm_and_si128(iter_mask, comparing_len));

        //Проверяем является ли нулем 
        if (*((int32_t*)&comparing_len) == 0)
          iter_mask = _mm_and_si128(iter_mask, mask32_pixel_1);
        if (*((int32_t*)&comparing_len + 1) == 0)
          iter_mask = _mm_and_si128(iter_mask, mask32_pixel_2);
        if (*((int32_t*)&comparing_len + 2) == 0)
          iter_mask = _mm_and_si128(iter_mask, mask32_pixel_3);
        if (*((int32_t*)&comparing_len + 3) == 0)
          iter_mask = _mm_and_si128(iter_mask, mask32_pixel_4);


        //Если у нас все длинны меньше радиусы, то выходим из цикла, т.к. обсчет для всех 4-х закончен
        if (_mm_test_all_zeros(iter_mask, iter_mask))
          break;

        //Пересчитываем координаты для следующей точки
        working_image = _mm_add_ps(working_image, working_image);
        working_image = _mm_mul_ps(working_image, working_real);
        working_image = _mm_add_ps(working_image, image);

        working_real = _mm_sub_ps(square_real, square_image);
        working_real = _mm_add_ps(working_real, real);
      }
      

      Pixels[ys][xs + 3][0] = 255 - koef * 2 * (BYTE)(*((int32_t*)&iterations + 0)) ;
      Pixels[ys][xs + 3][1] = 255 - koef * 128 * abs(sin((BYTE)(*((int32_t*)&iterations + 0))));
      Pixels[ys][xs + 3][2] = 255 - koef * (BYTE)(*((int32_t*)&iterations + 0))* 3;
                                    
      Pixels[ys][xs + 2][0] = 255 - koef * 2 * (BYTE)(*((int32_t*)&iterations + 1));
      Pixels[ys][xs + 2][1] = 255 - koef * 128 * abs(sin((BYTE)(*((int32_t*)&iterations + 1))));
      Pixels[ys][xs + 2][2] = 255 - koef * (BYTE)(*((int32_t*)&iterations + 1)) * 3;
                                    
      Pixels[ys][xs + 1][0] = 255 - koef * 2 * (BYTE)(*((int32_t*)&iterations + 2)) ;
      Pixels[ys][xs + 1][1] = 255 - koef * 128 * abs(sin((BYTE)(*((int32_t*)&iterations + 2)))) ;
      Pixels[ys][xs + 1][2] = 255 - koef * (BYTE)(*((int32_t*)&iterations + 2)) * 3 ;
                                    
      Pixels[ys][xs + 0][0] = 255 - koef * 2 * (BYTE)(*((int32_t*)&iterations + 3));
      Pixels[ys][xs + 0][1] = 255 - koef * 128 * abs(sin((BYTE)(*((int32_t*)&iterations + 3)))) ;
      Pixels[ys][xs + 0][2] = 255 - koef * (BYTE)(*((int32_t*)&iterations + 3)) * 3 ;
    }
  }
}

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
      X_RIGHT += keyboard.Scale;
      X_LEFT -= keyboard.Scale;
      Y_UP += keyboard.Scale;
      Y_DOWN -= keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_PRIOR]) {
      X_RIGHT -= keyboard.Scale;
      X_LEFT += keyboard.Scale;
      Y_UP -= keyboard.Scale;
      Y_DOWN += keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_RIGHT]) {
      X_RIGHT += keyboard.Scale;
      X_LEFT += keyboard.Scale;
    }
    else if (keyboard.KeysClick[VK_LEFT]) {
      X_RIGHT -= keyboard.Scale;
      X_LEFT -= keyboard.Scale;
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
  {
    glViewport(0, 0, W, H);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Mandelbrot();

    glPixelZoom(1, 1);
    glDrawPixels(WW, HH, GL_RGB, GL_UNSIGNED_BYTE, Pixels);

    SwapBuffers(hDC);
    glFinish();
    break;
    //Clean background
  }
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
  time.Time = (double)(t.QuadPart - time.StartTime) / time.TimePerSec;

  time.OldTime = t.QuadPart;

  /* FPS */
  if (t.QuadPart - time.OldTimeFPS > time.TimePerSec)
  {
    time.FPS = time.FrameCounter * time.TimePerSec / (double)(t.QuadPart - time.OldTimeFPS);

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