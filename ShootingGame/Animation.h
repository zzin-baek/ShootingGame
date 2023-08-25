#pragma once
class Animation
{
private:
	// 프레임
	typedef vector<POINT> _vFrameList;
	// 프레임 플레이
	typedef vector<int> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;
	int _frameWidth;
	int _frameHeight;
	int _frameNumWidth;
	int _frameNumHeight;

	float _frameUpdateSec;
	float _elapsedSec;

	bool _isPlay;
	bool _loop;

	DWORD _nowPlayIdx;

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrlen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	void AniStart(void);
	void AniStop(void);
	void AniPause(void);
	void AniResume(void);

	//= 인라인 함수 ==
	inline bool isPlay(void) { return _isPlay; }
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX * frameY * _frameNumWidth;
	}

	// 프레임에 대한 가로 + 세로 크기 + 현재 몇번째 프레임 순서인지
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }

	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }



	Animation(void);
	~Animation() {}
};

