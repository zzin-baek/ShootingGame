#include "Stdafx.h"
#include "Player.h"
#include "Boss.h"

HRESULT Player::init(void)
{
    _f22 = IMAGEMANAGER->addFrameImage("F22", "Resources/Image/Plane/f22(2).bmp", 320 * 2, 40 * 2, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Skill1", "Resources/Image/Plane/skill1.bmp", 6815 * 2, 131 * 2, 47, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Attack", "Resources/Image/Plane/F22_Bullet3.bmp", 0.0f, 0.0f,
        124, 53, 4, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("Score", "Resources/Image/Etc/Score.bmp",
        470, 47, 10, 1, true, RGB(255, 0, 255));
    
    _anim = new Animation;
    _anim->init(320 *2, 40 * 2, 64, 80);
    _anim->setDefPlayFrame(true, true);
    _anim->AniStart();

    _bullet = new Bullet;
    _bullet->init("Attack", 60);

    _effect = new Effect;
    _effect->init();

    _plPos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
    _plRect = RectMakeCenter( _plPos.x, _plPos.y, _f22->getFrameWidth(), _f22->getFrameHeight());

    _hpBar = new ProgressBar;
    _hpBar->init(_plPos.x, _plPos.y, 60, 6);

    _currentHp = 100;
    _maxHp = 100;

    _cnt = _score = _scoreCopy = 0;

    return S_OK;
}

void Player::release(void)
{
    SAFE_DELETE(_f22);
    SAFE_DELETE(_anim);
}

void Player::update(void)
{
    _anim->setPlayFrame(4, 5, true, true);
    _anim->frameUpdate(TIMEMANAGER->getElpasedTime() * 4);

    _bullet->update();
    _effect->update();
    collision();

    _plRect = RectMakeCenter(_plPos.x, _plPos.y, _f22->getFrameWidth(), _f22->getFrameHeight());

    if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _plRect.left >= 0)
    {
        _anim->setPlayFrame(0, 1, true, true);
        _plPos.x -= 2;
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _plRect.right < WINSIZE_X)
    {
        _anim->setPlayFrame(8, 9, true, true);
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

    _cnt++;
    if (KEYMANAGER->isStayKeyDown(VK_SPACE))
    {

        if (_cnt % 12 == 0)
        {
            SOUNDMANAGER->playSoundWithKey("Missile");
            _bullet->fire(_plRect.left + (_plRect.right - _plRect.left) / 2, _plRect.top, 90, 5);
        }
    }

    _hpBar->setX(_plPos.x - (_plRect.right - _plRect.left) / 2);
    _hpBar->setY(_plPos.y + (_plRect.bottom - _plRect.top) / 2);
    _hpBar->update();
    _hpBar->setGauge(_currentHp, _maxHp);
    
    _scoreCopy = _score;
}

void Player::render(void)
{
    IMAGEMANAGER->findImage("F22")->aniRender(getMemDC(), _plRect.left, _plRect.top, _anim);

    _bullet->render();
    _effect->render();
    _hpBar->render();

    
    for (int i = 0; i < 4; i++)
    {
        IMAGEMANAGER->frameRender("Score", getMemDC(),             150 - 40 * i, 10, (_scoreCopy % 10), 0);

        _scoreCopy /= 10;
    }
}

void Player::collision(void)
{
    for (int i = 0; i < _bullet->getBullet().size(); i++)
    {
        for (int j = 0; j < _em->getMinions().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
                &CollisionAreaResizing(_em->getMinions()[j]->getRect(), 20, 20)))
            {              
                removeMissile(i);
                _em->removeMinion(AIR, j);
                _effect->fire("Exp2", rc.left, rc.top);
                upScore(10);

                break;
            }
        }
    }

    for (int i = 0; i < _bullet->getBullet().size(); i++)
    {
        for (int j = 0; j < _em->getFallMonster().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
                &CollisionAreaResizing(_em->getFallMonster()[j]->getRect(), 30, 30)))
            {
                removeMissile(i);
                _em->removeMinion(FALL, j);
                _effect->fire("Exp2", rc.left, rc.top);
                upScore(10);
                break;
            }
        }
    }
    /*if (_boss)  
    {
        for (int i = 0; i < _bullet->getBullet().size(); i++)
        {
            RECT rc;
            if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
                &_boss->getRect()))
            {
                removeMissile(i);
                _boss->hitDamage(10);
                _effect->fire("Exp1", rc.left, rc.top);
                upScore(10);
                break;
            }
        }
    }*/
}

void Player::removeMissile(int arrNum)
{
    _bullet->removeBullet(arrNum);
}
