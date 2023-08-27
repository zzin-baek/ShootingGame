#include "Stdafx.h"
#include "SelectPlayer.h"

HRESULT SelectPlayer::init(void)
{
    IMAGEMANAGER->addFrameImage("Select", "Resources/Image/UI/character.bmp",
        WINSIZE_X * 6, WINSIZE_Y, 6, 1);

    _select = 0;
    _next = false;

    return S_OK;
}

void SelectPlayer::release(void)
{
}

void SelectPlayer::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _select--;

        if (_select < 0)
            _select = 5;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        _select++;

        if (_select > 5)
            _select = 0;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        _next = true;
    }
}

void SelectPlayer::render(void)
{
    IMAGEMANAGER->frameRender("Select", getMemDC(), 0, 0, _select, 0);
}
