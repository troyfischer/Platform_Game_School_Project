
#ifndef Text_hpp
#define Text_hpp

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class Text
{
private:
    SDL_Surface *_textSurface;
    SDL_Texture *_textTexture;
    SDL_Color _color;
    TTF_Font *_font;
    int _textWidth;
    int _textHeight;
    
    void free();
public:
    Text(SDL_Renderer *renderer, std::string msg, SDL_Color color, std::string fontPath, int fontSize);
    ~Text();
    void renderText(SDL_Renderer *renderer, int xPos, int yPos, int w, int h);
    void renderTextFullScreen(SDL_Renderer *renderer);
    void updateText(SDL_Renderer *renderer, std::string msg);
    int getTextWidth();
    int getTextHeight();
};

#endif /* Text_hpp */
