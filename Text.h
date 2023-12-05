#ifndef TEXT_H
#define TEXT_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Component.h"

class Text: public Component{
public:
    enum TextStyle { SOLID, SHADED, BLENDED };

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, Vec2 offset = Vec2(0.0, 0.0));
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    void SetOffset(float x, float y);

    Vec2 GetSize();

    std::string GetText();

    void RemakeTexture();

private:
    std::shared_ptr<TTF_Font> font;
    SDL_Texture *texture;

    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;

    Vec2 offset;

    float w;
    float h;
};

#endif // TEXT_H
