#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color): Component(associated){
    this->texture = nullptr;

    this->text = text;
    this->style = style;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->color = color;

    this->font = Resources::GetFont(this->fontFile, this->fontSize);

    RemakeTexture();
}

Text::~Text(){
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt){

}

void Text::Render(){
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.w;
    clipRect.h = associated.box.h;

    SDL_Rect dstRect;
    dstRect.x = associated.box.x - Camera::pos.x;
    dstRect.y = associated.box.y - Camera::pos.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(std::string type){
    if (type.compare("Text") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int font255Size){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
    if(texture){
        SDL_DestroyTexture(texture);
    }

    std::shared_ptr<TTF_Font> newFont = Resources::GetFont(this->fontFile, this->fontSize);
    if(newFont){
        SDL_Surface* tempSurface;
        font = newFont;
        switch(style){
        case SOLID:
            tempSurface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;

        case SHADED:
            tempSurface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, SDL_Color{0, 0, 0, 255});
            break;

        case BLENDED:
            tempSurface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
        }
        texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), tempSurface);
        associated.box.w = tempSurface->w;
        associated.box.h = tempSurface->h;
        SDL_FreeSurface(tempSurface);
    }

}
