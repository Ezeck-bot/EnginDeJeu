#include "SDL_ttf.h"
#include "SDLGfx.h"
#include "SDL_image.h"


int SDLGfx::Init(const char* title, int w, int h)
{
    //commencer par initialiser les sous système de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        ////SDL_INIT_VIDEO | SDL_INIT_EVENTS
        SDL_Log(SDL_GetError());
        return false;
    }
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    uint32_t flags = SDL_WINDOW_TOOLTIP;

    m_window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!m_window) {
        SDL_Log(SDL_GetError());
        return false;
    }

    //le renderer a besoin d'un windows donc on le crée après
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        SDL_Log(SDL_GetError());
        return false;
    }

    TTF_Init();

    return 1;
}

void SDLGfx::Shutdown()
{
    //détruit les textures alloué dans la vram sinon fuite de mémoire
    for (auto& _pair : m_cacheMap)
    {
        SDL_DestroyTexture(_pair.second);
    }
    m_cacheMap.clear();

    //font
    for (auto& _pair : m_fontCache)
    {
        TTF_CloseFont(_pair.second);
    }
    m_fontCache.clear();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();

    SDL_Quit();
}

void SDLGfx::SetColor(const Color& color)
{
}

void SDLGfx::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void SDLGfx::Present()
{
    SDL_RenderPresent(m_renderer);
}

Color::Color(uchar red, uchar green, uchar blue, uchar alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
{

}

void SDLGfx::DrawRect(float x, float y, float w, float h, const Color& color)
{
    SDL_Rect get_rekt = { 0 };
    get_rekt.x = x;
    get_rekt.y = y;
    get_rekt.w = w;
    get_rekt.h = h;
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawRect(m_renderer, &get_rekt);
}

void SDLGfx::DrawRect(const RectF& rect, const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);

    SDL_Rect _sdlRect{
        static_cast<int>(rect.x),
        static_cast<int>(rect.y),
        static_cast<int>(rect.w),
        static_cast<int>(rect.h)
    };

    SDL_RenderDrawRect(m_renderer, &_sdlRect);
}

void SDLGfx::Fillrect(float x, float y, float w, float h, const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);

    //SDL_FRect rect = { x, y, w, h };
    SDL_FRect get_rekt = { 0 };
    get_rekt.x = x;
    get_rekt.y = y;
    get_rekt.w = w;
    get_rekt.h = h;
    SDL_RenderFillRectF(m_renderer, &get_rekt);
}

void SDLGfx::Fillrect(const RectF& rect, const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);

    SDL_FRect _sdlRect{
        rect.x,
        rect.y,
        rect.w,
        rect.h
    };

    SDL_RenderFillRectF(m_renderer, &_sdlRect);
}

void SDLGfx::DrawLine(float x1, float y1, float x2, float y2, const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue, color.alpha);

    SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
}

size_t SDLGfx::LoadTexture(const std::string& filename)
{
    //homer::Engine::Get()->LoggerF()->Log("icic");

    const size_t _texId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map le retourne l'id
    if (m_cacheMap.find(_texId) != m_cacheMap.end())
    {
        return _texId;
    }


    SDL_Texture* _tex = IMG_LoadTexture(m_renderer, filename.c_str());
    if (_tex != NULL)
    {
        m_cacheMap[_texId] = _tex;

        return _texId;
    }

    return static_cast<size_t>(-1);
}

void SDLGfx::DrawTexture(size_t id, const RectI& src, const RectF& dst, double angle, const Flip& flip, const Color& color)
{

    if (m_cacheMap.find(id) == m_cacheMap.end()) {
        return;
    }

    SDL_Texture* _tex = m_cacheMap.find(id)->second;

    SDL_Rect _srcRect{
        src.x,
        src.y,
        src.w,
        src.h
    };

    SDL_FRect _dstRect{
        dst.x,
        dst.y,
        dst.w,
        dst.h
    };

    SDL_RendererFlip _flip;
    if (flip.h)
    {
        _flip = SDL_FLIP_HORIZONTAL;
    }
    else if (flip.v) {
        _flip = SDL_FLIP_VERTICAL;
    }
    else {
        _flip = SDL_FLIP_NONE;
    }

    SDL_SetTextureBlendMode(_tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(_tex, color.alpha);
    SDL_SetTextureColorMod(_tex, color.red, color.green, color.blue);

    

    SDL_RenderCopyExF(m_renderer, _tex, &_srcRect, &_dstRect, angle, nullptr, _flip);
}

void SDLGfx::DrawTexture(size_t id, const RectF& dst, const Color& color)
{
    int w = 0, h = 0;
    GetTextureSize(id, &w, &h); // taille réelle de la texture
    RectI src{ // toute la texture
        0, 
        0, 
        w, 
        h 
    };                 
    DrawTexture(id, src, dst, 0.0, Flip{}, color);
}

void SDLGfx::DrawTexture(size_t id, const Color& color) //ajout de variable pour le mouvement x et y
{
    int w = 0, h = 0;

    GetTextureSize(id, &w, &h); // taille réelle de la texture

    RectI src{ 
        0,
        0,
        w,
        h
    };

    RectF dst{
        0,
        0,
        w,
        h
    };

    DrawTexture(id, src, dst, 0.0, Flip{}, color);
}

//la taille de l'image
void SDLGfx::GetTextureSize(size_t id, int* w, int* h)
{
    if (m_cacheMap.count(id) > 0)
    {
        SDL_Texture* _tex = m_cacheMap[id];
        SDL_QueryTexture(_tex, nullptr, nullptr, w, h);
    }
    else
    {
        *w = 0;
        *h = 0;
    }
}

//------------------FONT--------------------//
size_t SDLGfx::LoadFont(const std::string& filename, int fontSize)
{


    const size_t _fontId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map le retourne l'id
    if (m_fontCache.find(_fontId) != m_fontCache.end())
    {
        return _fontId;
    }


    TTF_Font* _font = TTF_OpenFont(filename.c_str(), fontSize);
    if (_font != NULL)
    {
        m_fontCache[_fontId] = _font;

        return _fontId;
    }

    return static_cast<size_t>(-1);
}
SDL_Texture* g_TextureBuffer;
void SDLGfx::DrawString(const std::string& text, size_t fontId, float x, float y, const Color& color)
{

    if (m_fontCache.find(fontId) == m_fontCache.end()) {
        return;
    }

    if (m_fontCache.count(fontId) > 0)
    {
        TTF_Font* _font = m_fontCache[fontId];
        //SDL_Surface* _surface = TTF_RenderText_Solid(_font, text.c_str(), { color.red, color.green, color.blue, color.alpha });
        SDL_Surface* _surface = TTF_RenderUTF8_Blended_Wrapped(_font, text.c_str(), { color.red, color.green, color.blue, color.alpha }, 0);

        

        g_TextureBuffer = SDL_CreateTextureFromSurface(m_renderer, _surface);

        SDL_Rect _dst{ static_cast<int>(x), static_cast<int>(y), _surface->w, _surface->h };

        SDL_RenderCopy(m_renderer, g_TextureBuffer, nullptr, &_dst);
        SDL_FreeSurface(_surface);
    }
}

void SDLGfx::GetTextSize(const std::string& text, size_t fontId, int* w, int* h)
{
    if (m_fontCache.count(fontId) > 0)
    {
        TTF_Font* _tex = m_fontCache[fontId];
        TTF_SizeUTF8(_tex, text.c_str(), w, h);
    }
    else
    {
        *w = 0;
        *h = 0;
    }
}



