#include "TextLabel.h"


TextLabel::TextLabel(std::string _message, TTF_Font * _font, SDL_Color _color, SDL_Rect _rect)
{
	message = _message;
	font = _font;
	color = _color;

	position = Vector2
	{ 
		static_cast<float>(_rect.x),
		static_cast<float>(_rect.y)
	};

	dimension = Vector2
	{ 
		static_cast<float>(_rect.w),
		static_cast<float>(_rect.h)
	};
}

TextLabel::~TextLabel()
{

}

void TextLabel::Render(SDL_Renderer * renderer)
{
	surface = TTF_RenderText_Solid(font, message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect = SDL_Rect
	{ 
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(dimension.x),
		static_cast<int>(dimension.y)
	};

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void TextLabel::SetColor(SDL_Color _color)
{
	color = _color;
}

void TextLabel::SetPosition(Vector2 _position)
{
	position = _position;
}

void TextLabel::SetDimension(Vector2 _dimension)
{
	dimension = _dimension;
}
