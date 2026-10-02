#pragma once
#include "IGfx.h"
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

//il faut mettre public pour que toutes les fonction soit accessible
class SDLGfx final : public IGfx {
public:

	virtual int Init(const char* title, int w, int h) override;
	virtual void Shutdown() override;

	virtual void SetColor(const Color& color) override;

	//effacer
	virtual void Clear() override;

	//presenter
	virtual void Present() override;

	//dessiner les lignes autour d'un rectangle
	virtual void DrawRect(float x, float y, float w, float h, const Color& color) override;
	virtual void DrawRect(const RectF& rect, const Color& color) override;

	//dessiner un rectangles plein
	virtual void Fillrect(float x, float y, float w, float h, const Color& color) override;
	virtual void Fillrect(const RectF& rect, const Color& color) override;

	//dessiner une ligne
	virtual void DrawLine(float x1, float y1, float x2, float y2, const Color& color) override;

	//Load une image que je mettre mettre dans un cache
	virtual size_t LoadTexture(const std::string& filename) override;
	virtual void DrawTexture(size_t id, const RectI& src, const RectF& dst, double angle, const Flip& flip, const Color& color) override;
	virtual void DrawTexture(size_t id, const RectF& dst, const Color& color) override;
	virtual void DrawTexture(size_t id, const Color& color) override;
	virtual void GetTextureSize(size_t id, int* w, int* h) override;
	virtual size_t LoadFont(const std::string& filename, int fontSize) override;
	virtual void DrawString(const std::string& text, size_t fontId, float x, float y, const Color& color) override;
	virtual void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) override;

	//destructeur
	virtual ~SDLGfx() = default;
private:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;

	//Cache
	std::map<size_t, SDL_Texture*> m_cacheMap;
	std::map<size_t, _TTF_Font*> m_fontCache;
};