#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

MainGame* _mg;

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdParam,
    int nCmdShow)
{
    _mg = new MainGame();

    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WINNAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;


    RegisterClass(&wndClass);

#ifdef FULLSCREEN

    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));

    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;
    dm.dmPanningWidth = 1980;
    dm.dmPelsHeight = 1020;
    dm.dmDisplayFrequency = 60;

    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }
#endif
    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL

    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TIMEMANAGER->update(60.0f);
            _mg->update();
            _mg->render();
        }
    }
    // 메시지 루프
    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    return message.wParam;
}

// 윈도우 프로시져
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}
