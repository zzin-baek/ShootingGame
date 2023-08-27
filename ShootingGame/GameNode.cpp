#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
    SetTimer(_hWnd, 1, 10, NULL);

    RND->init();
    KEYMANAGER->init();
    IMAGEMANAGER->init();
    return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;
    if (managerInit)
    {
        setlocale(LC_ALL, "korean");

        SetTimer(_hWnd, 1, 10, NULL);

        RND->init();
        KEYMANAGER->init();
        IMAGEMANAGER->init();
        SOUNDMANAGER->init();
        TIMEMANAGER->init();
    }

    return S_OK;
}

void GameNode::release(void)
{
    if (_managerInit)
    {
        KillTimer(_hWnd, 1);
        RND->releaseSingleton();
        KEYMANAGER->releaseSingleton();
        IMAGEMANAGER->release();
        IMAGEMANAGER->releaseSingleton();
        SOUNDMANAGER->releaseSingleton();
        TIMEMANAGER->releaseSingleton();
    }

    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
    //! Do Nothing
}

// ���� ���ν���
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
    {
        this->render();
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
