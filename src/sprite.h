#pragma once

#include <SDL2/SDL.h>

#include <stdint.h>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

class Sprite
{
	public:
	explicit Sprite(SDL_BlendMode blendMode);
	Sprite();
	virtual ~Sprite();
	
	virtual void draw(SDL_Renderer *renderer) = 0;
	//enum Type {LINE, LINES, POINT, POINTS, RECT, RECTS, FILLRECT}; 
	//SDL_RenderCopyEx, SDL_RenderCopy
	//SDL_RenderDrawLine, SDL_RenderDrawLines
	//SDL_RenderDrawPoint, SDL_RenderDrawPoints

	SDL_BlendMode blending; //SDL_BLENDMODE_BLEND for objects with alpha channel, SDL_BLENDMODE_NONE for no blending/overwrite (IE, UI)
	//SDL_SetRenderDrawBlendMode

};

class Nothing : public Sprite
{
	public:
	explicit Nothing(SDL_BlendMode blendMode);
	virtual ~Nothing();
	virtual void draw(SDL_Renderer *renderer) override;
};

class Background : public Sprite
{
	public:
	explicit Background(SDL_BlendMode blendMode, SDL_Texture *t);
	virtual ~Background();
	
	SDL_Texture *texture;
	
	virtual void draw(SDL_Renderer *renderer) override;
};

class Line : public Sprite
{
	public:
	explicit Line(SDL_BlendMode blendMode, Color c, int X1, int Y1, int X2, int Y2);
	virtual ~Line();
	virtual void draw(SDL_Renderer *renderer) override;
	
	Color color;
	int x1, y1, x2, y2;
	
};

class Box : public Sprite
{
	public:
	explicit Box(SDL_BlendMode blendMode, Color c, int X, int Y, int width, int height);
	virtual ~Box();
	virtual void draw(SDL_Renderer *renderer) override;
	
	Color color;
	SDL_Rect rect;
	
};

class Points: public Sprite
{
	public:
	explicit Points(SDL_BlendMode blendMode, Color c, SDL_Point *p, int ct);
	virtual ~Points();
	virtual void draw(SDL_Renderer *renderer) override;
	
	Color color;
	SDL_Point *points;
	int count;
};

//TODO: This name is terrible. This class represents a texture to be rendered in whole or part to the window.
/* A sprite that represents a subpart of a texture to render onto the screen. 
class Figure : public Sprite
{
	public:
	void draw(SDL_Renderer *renderer);
	//! A non-unique handle on the texture that we are rendering from
	SDL_Texture *texture;
	
	//! Where the subpart of the texture comes from
	SDL_Rect source;
	
	//! Where in the window to render to
	SDL_Rect destination;
};*/
