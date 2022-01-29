#include <sprite.h>
#include <iostream>

//######## BASE CLASS
Sprite::Sprite(SDL_BlendMode blendMode)
:blending{blendMode}
{}

Sprite::Sprite()
{}

Sprite::~Sprite() 
{}

//######## BACKGROUND
Background::~Background()
{}

void Background::draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

Background::Background(SDL_BlendMode blendMode, SDL_Texture *t)
:Sprite(blendMode), texture{t}
{}

//######## Nothing, used for testing
Nothing::~Nothing()
{}

void Nothing::draw(SDL_Renderer *renderer)
{
	(void)(renderer); //suppress unused warning - draw still needs an implementation.

}

Nothing::Nothing(SDL_BlendMode blendMode)
:Sprite(blendMode)
{}

//######## Line
Line::Line(SDL_BlendMode blendMode, Color c, int X1, int Y1, int X2, int Y2)
:Sprite(blendMode), color{c}, x1{X1}, y1{Y1}, x2{X2}, y2{Y2}
{}

Line::~Line()
{}

void Line::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

