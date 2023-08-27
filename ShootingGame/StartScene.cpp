#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    _startScene = IMAGEMANAGER->addImage("Main", "Resources/Image/UI/logo.bmp", WINSIZE_X, WINSIZE_Y);
    _startButton = IMAGEMANAGER->addImage("Button", "Resources/Image/UI/StartButton.bmp", WINSIZE_X / 2, 500,
        305, 57, true, RGB(255, 0, 255));

    _flikering = 0;
    _next = false;

    return S_OK;
}

void StartScene::release(void)
{
    SAFE_DELETE(_startScene);
    SAFE_DELETE(_startButton);
}

void StartScene::update(void)
{
    _flikering++;

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        _next = true;
    }
}

void StartScene::render(void)
{
    _startScene->render(getMemDC());

    if (_flikering % 50 >= 25)
    {
        _startButton->render(getMemDC(), WINSIZE_X / 2 - _startButton->getWidth() / 2, 580);
    }
}
