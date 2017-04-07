#include "Text.hpp"
#include "GameWindow.hpp"

Text::Text(SDL_Renderer *renderer, std::string msg, SDL_Color color, std::string fontPath, int fontSize)
{
    _textSurface = NULL;
    _textTexture = NULL;
    _font = NULL;
    
    _color = color;
    
    _font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    _textSurface = TTF_RenderText_Solid(_font, msg.c_str(), color);
    if (!_textSurface)
    {
        GameWindow::logTTFError("TTF_RenderText_Solid");
        
    }
    else
    {
        _textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
        if (!_textTexture)
        {
            GameWindow::logSDLError("SDL_CreateTextureFromSurfacce");
        }
        else
        {
            SDL_QueryTexture(_textTexture, NULL, NULL, &_textWidth, &_textHeight);
        }
        SDL_FreeSurface(_textSurface);
    }

}

Text::~Text()
{
    free();
}

void Text::free()
{
    SDL_DestroyTexture(_textTexture);
    TTF_CloseFont(_font);
}

void Text::renderText(SDL_Renderer *renderer, int xPos, int yPos, int w, int h)
{
    SDL_Rect dstrect = {xPos, yPos, w, h};
    SDL_RenderCopy(renderer, _textTexture, NULL, &dstrect);
}

void Text::renderTextFullScreen(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, _textTexture, NULL, NULL);
}

void Text::updateText(SDL_Renderer *renderer, std::string msg)
{
    free();
    _textSurface = TTF_RenderText_Solid(_font, msg.c_str(), _color);
    _textTexture = SDL_CreateTextureFromSurface(renderer, _textSurface);
    SDL_FreeSurface(_textSurface);
}

int Text::getTextWidth()
{
    return _textWidth;
}

int Text::getTextHeight()
{
    return _textHeight;
}


