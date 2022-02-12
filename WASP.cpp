#include "WASP.h"

#define MAX_LOADSTRING 128

HINSTANCE hINSTANCE;
WCHAR     TITLE[MAX_LOADSTRING];
WCHAR     WINDOWCLASS[MAX_LOADSTRING];

ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

HBITMAP hBACKGROUND  = nullptr;
HWND    hWND         = nullptr;

float   mRatio = 1.0f;
CRect   mRect;
UINT    mFramesPerSec = 25;
size_t  mFrame        = (size_t) (mFramesPerSec * (GetTickCount64() / 1000));;

CSpriteOpenDoor      mOpenDoor;
CSpritePantsFallDown mPantsFallDown;
CSpriteChocolate     mChooseChoc;
CSpriteCoffee        mChooseCoffee;

CSprite* mpCurrentSprite = &mOpenDoor;

CImage* Add(UINT resID, LPCTSTR type);
bool Load(CImage* pIMage, UINT resID, LPCTSTR type);
IStream* CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
  {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  LoadStringW(hINSTANCE, IDS_APP_TITLE, TITLE, MAX_LOADSTRING);
  LoadStringW(hINSTANCE, IDC_WASP, WINDOWCLASS, MAX_LOADSTRING);
  MyRegisterClass(hINSTANCE);

  if (!InitInstance (hINSTANCE, nCmdShow))
    return FALSE;

  HACCEL hAccelTable = LoadAccelerators(hINSTANCE, MAKEINTRESOURCE(IDC_WASP));
  MSG msg;

  // MAIN MESSAGE LOOP
  while (TRUE)
    {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT) break;
        }
      }

    // DO TIMEKEEPING
    double currentSecs  = (double) GetTickCount64() / 1000;
    size_t currentFrame = (size_t) (mFramesPerSec * currentSecs);

    // ONLY NEED TO UPDATE THE SCREEN ON FRAME CHANGE
    if (mFrame != currentFrame)
      {
      InvalidateRect(hWND, NULL, true);
      mFrame = currentFrame;
      }
    }

  return (int) msg.wParam;
  }

ATOM MyRegisterClass(HINSTANCE hInstance)
  {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style          = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc    = WndProc;
  wcex.cbClsExtra     = 0;
  wcex.cbWndExtra     = 0;
  wcex.hInstance      = hInstance;
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WASP));
  wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WASP);
  wcex.lpszClassName  = WINDOWCLASS;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
  }

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
  {
  hINSTANCE = hInstance;

  hWND = CreateWindowW(WINDOWCLASS, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWND) return FALSE;

  hBACKGROUND = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BACKGROUND));

  mOpenDoor.InitInstance(&Add);
  mPantsFallDown.InitInstance(&Add);
  mChooseChoc.InitInstance(&Add);
  mChooseCoffee.InitInstance(&Add);

  ShowWindow(hWND, nCmdShow);
  UpdateWindow(hWND);

  return TRUE;
  }

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
  switch (message)
    {
    case WM_COMMAND:
      {
      switch (LOWORD(wParam))
        {
        case IDM_ABOUT: DialogBox(hINSTANCE, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); break;
        case IDM_EXIT:  DestroyWindow(hWnd); break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
      } break;

    case WM_ERASEBKGND:
      {
      CRect rect;
      GetClientRect(hWND, &rect);

      HDC hDC = GetDC(hWnd);
      FillRect(hDC, &rect, CreateSolidBrush(RGB(64, 128, 128)));
      ReleaseDC(hWnd, hDC);
      } break;

    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      BITMAP      bm;

      HDC         hDC    = BeginPaint(hWnd, &ps);
      HDC         hDCMem = CreateCompatibleDC(hDC);
      HBITMAP     hbmOld = (HBITMAP) SelectObject(hDCMem, hBACKGROUND);

      GetObject(hBACKGROUND, sizeof(bm), &bm);
      StretchBlt(hDC, mRect.left, mRect.top, mRect.Width(), mRect.Height(), hDCMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

      // CURRENT SPRITE WILL RETURN FALSE WHEN FINISHED ANIMATING
      if (!mpCurrentSprite->Draw(mFrame, hDC, hDCMem, mRatio, &mRect))
        {
        CSprite* nextSprite = nullptr;

        // CHOOSE NEXT ANIMATION (BASED ON CURRENT ONE)
        float ChanceOfPantsFailure = 0.2f;
        float ChocOrCoffee         = 0.5f;

        if (mpCurrentSprite == &mChooseChoc || mpCurrentSprite == &mChooseCoffee)
          {
          nextSprite = &mOpenDoor;
          }

        if (mpCurrentSprite == &mOpenDoor || mpCurrentSprite == &mPantsFallDown)
          {
          float random = (float) rand() / RAND_MAX;
          nextSprite = (random < ChocOrCoffee ? (CSprite*) &mChooseChoc : (CSprite*) &mChooseCoffee);
          }

        if (mpCurrentSprite == &mOpenDoor)
          {
          if (((float) rand() / RAND_MAX) < ChanceOfPantsFailure)
            nextSprite = &mPantsFallDown;
          }

        mpCurrentSprite = nextSprite;
        }

      SelectObject(hDCMem, hbmOld);
      DeleteDC(hDCMem);

      EndPaint(hWnd, &ps);
      } break;

    case WM_SIZE:
      {
      BITMAP bm;
      CRect  rect;

      GetObject(hBACKGROUND, sizeof(bm), &bm);
      GetClientRect(hWND, &rect);

      float ratioX  = (float) rect.Width()  / bm.bmWidth;
      float ratioY  = (float) rect.Height() / bm.bmHeight;

      mRatio = (ratioX < ratioY ? ratioX : ratioY);

      mRect.SetRect(0, 0, (int) (mRatio * bm.bmWidth), (int) (mRatio * bm.bmHeight));

      CPoint wndCentre = rect.CenterPoint();
      CPoint bmpCentre = mRect.CenterPoint();

      mRect.OffsetRect(wndCentre.x - bmpCentre.x, wndCentre.y - bmpCentre.y);
      } break;

    case WM_DESTROY:
      DeleteObject(hBACKGROUND);
      PostQuitMessage(0);
      break;

    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }

  return 0;
  }

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
  {
  UNREFERENCED_PARAMETER(lParam);
  switch (message)
    {
    case WM_INITDIALOG: return (INT_PTR)TRUE;

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
        }
      break;
    }

  return (INT_PTR)FALSE;
  }

CImage* Add(UINT resID, LPCTSTR type)
  {
  IStream *pStream = CreateStreamOnResource(MAKEINTRESOURCE(resID), type);

  if (pStream != nullptr)
    {
    CImage* pImage = new CImage();

    pImage->Load(pStream);
    pImage->SetHasAlphaChannel(true);
    pStream->Release();

    return pImage;
    }

  return nullptr;
  }

IStream* CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType)
  {
  IStream * ipStream = NULL;

  HRSRC hrsrc = FindResource(NULL, lpName, lpType);
  if (hrsrc == NULL) return ipStream;

  DWORD   dwResourceSize = SizeofResource(NULL, hrsrc);
  HGLOBAL hglbImage      = LoadResource(NULL, hrsrc);
  if (hglbImage == NULL) return ipStream;

  LPVOID pvSourceResourceData = LockResource(hglbImage);
  if (pvSourceResourceData == NULL) return ipStream;

  HGLOBAL hgblResourceData = GlobalAlloc(GMEM_MOVEABLE, dwResourceSize);
  if (hgblResourceData == NULL) return ipStream;

  LPVOID pvResourceData = GlobalLock(hgblResourceData);

  if (pvResourceData == NULL)
    {
    GlobalFree(hgblResourceData);
    return ipStream;
    }

  CopyMemory(pvResourceData, pvSourceResourceData, dwResourceSize);

  GlobalUnlock(hgblResourceData);

  if (SUCCEEDED(CreateStreamOnHGlobal(hgblResourceData, TRUE, &ipStream))) return ipStream;

  GlobalFree(hgblResourceData);
  return ipStream;
  }
