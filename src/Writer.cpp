#include "Writer.h"
#include "Presenter.h"

Writer::Writer()
{
}

Writer::~Writer()
{
}

void Writer::init()
{
   // m_fontLocation = FONT_FOLDER + "Oswald-Regular.ttf";
    m_fontLocation = FONT_FOLDER + "Young.ttf";

    TTF_Font* font;

    for (int i = 10; i < 70; i++) //Font size from 10 to 69
    {
        font = TTF_OpenFont(m_fontLocation.c_str(), i);
        m_font.insert(pair<int, TTF_Font*>(i, font));
    }

    SDL_Color color;

    color.a = (Uint8)255;

    //Light color
    color.r = (Uint8)255;
    color.g = (Uint8)255;
    color.b = (Uint8)255;

    m_colors.insert(pair<COLOR, SDL_Color>(LIGHT, color));

    //Dark color
    color.r = (Uint8)0;
    color.g = (Uint8)0;
    color.b = (Uint8)0;

    m_colors.insert(pair<COLOR, SDL_Color>(DARK, color));

    //Blue color
    color.r = (Uint8)60;
    color.g = (Uint8)35;
    color.b = (Uint8)215;

    m_colors.insert(pair<COLOR, SDL_Color>(BLUE, color));

    //Red color
    color.r = (Uint8)215;
    color.g = (Uint8)35;
    color.b = (Uint8)78;

    m_colors.insert(pair<COLOR, SDL_Color>(RED, color));

    //Orange color
    color.r = (Uint8)247;
    color.g = (Uint8)162;
    color.b = (Uint8)32;

    m_colors.insert(pair<COLOR, SDL_Color>(ORANGE, color));

    //Pink color
    color.r = (Uint8)248;
    color.g = (Uint8)111;
    color.b = (Uint8)226;

    m_colors.insert(pair<COLOR, SDL_Color>(PINK, color));

    //Yellow color
    color.r = (Uint8)255;
    color.g = (Uint8)237;
    color.b = (Uint8)70;

    m_colors.insert(pair<COLOR, SDL_Color>(YELLOW, color));

    //Light green color
    color.r = (Uint8)167;
    color.g = (Uint8)254;
    color.b = (Uint8)152;

    m_colors.insert(pair<COLOR, SDL_Color>(LIGHT_GREEN, color));

    //Dark cyan color
    color.r = (Uint8)20;
    color.g = (Uint8)81;
    color.b = (Uint8)81;

    m_colors.insert(pair<COLOR, SDL_Color>(DARK_CYAN, color));

    //Purple color
    color.r = (Uint8)101;
    color.g = (Uint8)0;
    color.b = (Uint8)117;

    m_colors.insert(pair<COLOR, SDL_Color>(PURPLE, color));
}

pair<int2, SDL_Texture*> Writer::getText(string text, COLOR color, int fontSize)
{
    TTF_Font* font = m_font.at(fontSize);

    const char* c = text.c_str(); //Pointer to the text

    SDL_Surface* surface = TTF_RenderText_Blended(font, c, m_colors.at(color)); //TTF_RenderUTF8_Shaded for Bulgarian text
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Presenter::m_mainRenderer, surface);

    int2 size = {surface->w, surface->h};

    pair<int2, SDL_Texture*> result = {size, texture};

    SDL_FreeSurface(surface);

    return result;
}
