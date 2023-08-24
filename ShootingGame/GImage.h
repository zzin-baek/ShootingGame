#pragma once

class Animation;

class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,	
		LOAD_EMPTY, LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		// 복사를 전제
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;			
		float		y;			
		int			width;		
		int			height;		
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;	
		int			maxFrameY;	
		int			frameWidth;	
		int			frameHeight;
		BYTE		loadType;	

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char* _fileName;
	bool			_isTrans;	
	COLORREF		_transColor;

	BLENDFUNCTION	_blendFunc;	
	LPIMAGE_INFO	_blendImage;

public:
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	// 배경과 같이 중첩 배경이 필요할 때
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);
	// 투명 컬러키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 해제
	void release(void);

	// 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 이미지 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY);

	// 루프 렌더
	// ㄴ 반복 / 이미지를 밀고 당기는 방식
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	// ##인라인 함수##
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 X 좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// 이미지 Y 좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2); \
	}

	//  이미지 가로 / 세로 크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}

	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage() {}
};