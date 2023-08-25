#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	float _setTime, _worldTime;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion();
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }

	EnemyManager();
	~EnemyManager();
};

/*
����1. �� ��Ʈ������ PPT ��ǥ �غ�
�� ��ǥ��: ����
�� ��ǥ�� �غ�

����2. ���� ��Ʈ������ (�帣: ���ð���)
�� 27�� (��)����
�� ���ο� �̹��� �ʼ�(1945, ����ø���, �ٰ���)
�� ��ŸƮ ���� ���� �� + �÷��̾� ���� ��
�� ���� ���̸� ���� ȹ��
�� �÷��̾� -> ü�� / ������
�� ���� ��� ���̸� ������ ���� ( ���� ������ ���ؼ��� �ڿ�������)
�� �� 2 + @ + �߰� ����
�� ������ ���̸� ���� ������ �ٽ� ������ ������
*/