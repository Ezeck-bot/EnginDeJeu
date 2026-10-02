#pragma once
#include <string>


struct RectI {
	int x;
	int y;
	int w;
	int h;
};

struct RectF {
	float x;
	float y;
	float w;
	float h;
};

struct Flip {
	bool h;
	bool v;
};

typedef unsigned char uchar;

class Color {
public:
	Color(uchar red, uchar green, uchar blue, uchar alpha);

	static const Color& Red;
	static const Color& Green;
	static const Color& Blue;

	uchar red = 255;
	uchar green = 255;
	uchar blue = 255;
	uchar alpha = 255;
};

class IGfx {
public:
	virtual ~IGfx() = default;

	virtual int Init(const char* title, int w, int h) = 0; //ok
	virtual void Shutdown() = 0; //ok

	virtual void SetColor(const Color& color) = 0; //ok
	virtual void Clear() = 0; //ok
	virtual void Present() = 0; //ok
	virtual void DrawRect(float x, float y, float w, float h, const Color& color) = 0; //ok
	
	virtual void DrawRect(const RectF& rect, const Color& color) = 0;
	virtual void Fillrect(float x, float y, float w, float h, const Color& color) = 0;
	virtual void Fillrect(const RectF& rect, const Color& color) = 0;
	virtual void DrawLine(float x1, float y1, float x2, float y2, const Color& color) = 0;
	virtual size_t LoadTexture(const std::string& filename) = 0;
	virtual void DrawTexture(size_t id, const RectI& src, const RectF& dst, double angle, const Flip& flip, const Color& color) = 0;
	virtual void DrawTexture(size_t id, const RectF& dst, const Color& color) = 0;
	virtual void DrawTexture(size_t id, const Color& color) = 0;
	virtual void GetTextureSize(size_t id, int* w, int* h) = 0;
	virtual size_t LoadFont(const std::string& filename, int fontSize) = 0;
	virtual void DrawString(const std::string& text, size_t fontId, float x, float y, const Color& color) = 0;
	virtual void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) = 0;



	//pour que ce soit une interface faut mettre égale 0
};