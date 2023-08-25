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
과제1. 팀 포트폴리오 PPT 발표 준비
ㄴ 발표일: 명일
ㄴ 발표자 준비

과제2. 세미 포트폴리오 (장르: 슈팅게임)
ㄴ 27일 (일)까지
ㄴ 새로운 이미지 필수(1945, 동방시리즈, 텐가이)
ㄴ 스타트 씬과 게임 씬 + 플레이어 선택 씬
ㄴ 적을 죽이면 점수 획득
ㄴ 플레이어 -> 체력 / 라이프
ㄴ 적을 모두 죽이면 보스가 출현 ( 보스 출현에 대해서는 자연스럽게)
ㄴ 적 2 + @ + 중간 보스
ㄴ 보스를 죽이면 게임 루프를 다시 가능한 구조로
*/