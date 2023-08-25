#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    _f22 = IMAGEMANAGER->addFrameImage("F22", "Resources/Image/Plane/f22(2).bmp", 320 * 2, 40 * 2, 10, 1, true, RGB(255, 0, 255));

    _anim = new Animation;
    _anim->init(320 *2, 40 * 2, 64, 80);
    _anim->setDefPlayFrame(true, true);
    _anim->AniStart();

    _plPos = { WINSIZE_X / 2, 600 };
    _plRect = RectMakeCenter( _plPos.x, _plPos.y, _f22->getFrameWidth(), _f22->getFrameHeight());

    return S_OK;
}

void Player::release(void)
{
    SAFE_DELETE(_f22);
}

void Player::update(void)
{
    _anim->setPlayFrame(4, 5, true, true);
    _anim->frameUpdate(TIMEMANAGER->getElpasedTime());

    _plRect = RectMakeCenter(_plPos.x, _plPos.y, _f22->getFrameWidth(), _f22->getFrameHeight());

    if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _plRect.left >= 0)
    {
        _plPos.x -= 2;
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _plRect.right < WINSIZE_X)
    {
        _plPos.x += 2;
    }
    if (KEYMANAGER->isStayKeyDown(VK_UP) && _plRect.top >= 0)
    {
        _plPos.y -= 2;
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _plRect.bottom < WINSIZE_Y)
    {
        _plPos.y += 2;
    }
}

void Player::render(void)
{
    //_f22->aniRender(getMemDC(), WINSIZE_X / 2, 600, _anim);
    //_f22->frameRender(getMemDC(), _plPos.left, _plPos.top, _f22->getFrameX(), _f22->getFrameY());
    IMAGEMANAGER->findImage("F22")->aniRender(getMemDC(), _plRect.left, _plRect.top, _anim);
    //IMAGEMANAGER->findImage("F22")->frameRender(getMemDC(), _plRect.left, _plRect.top, 0, 0);
}
