#include "Stdafx.h"
#include "Effect.h"

HRESULT Effect::init(void)
{
    _effectTick = 0.0f;

    IMAGEMANAGER->addFrameImage("Exp1", "Resources/Image/Effect/Effect_1.bmp", 0.0f, 0.0f,
        360, 27, 12, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Exp2", "Resources/Image/Effect/Effect_2.bmp", 0.0f, 0.0f,
        1462, 98, 15, 1, true, RGB(255, 0, 255));

    return S_OK;
}

void Effect::release(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        SAFE_DELETE(_viEffect->img);
    }
}

void Effect::update(void)
{
    animation();
}

void Effect::render(void)
{
    draw();
}

void Effect::fire(const char* fileName, float x, float y)
{
    tagEffect effect;
    ZeroMemory(&effect, sizeof(tagEffect));

    effect.img = new GImage;
    effect.img->init("Resources/Image/Effect/Effect_2.bmp", 0.0f, 0.0f,
        1462, 98, 15, 1, true, RGB(255, 0, 255));

    effect.x = x;
    effect.y = y;
    effect.fire = true;
    effect.count = 0;

    effect.rc = RectMakeCenter(effect.x, effect.y,
        effect.img->getFrameWidth(), effect.img->getFrameHeight());

    _vEffect.push_back(effect);
}

void Effect::draw(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        if (!_viEffect->fire) continue;

        _viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top,
            _viEffect->img->getFrameX(), _viEffect->img->getFrameY());
    }
}

void Effect::animation(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();++_viEffect)
    {
        if (!_viEffect->fire) continue;

        if (0.01 + _effectTick <= TIMEMANAGER->getWolrdTime())
        {
            _effectTick = TIMEMANAGER->getWolrdTime();
            _viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
            if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
            {
                _viEffect->fire = false;
            }
            
        }
    }
}
