#include "PepEnginePCH.h"
#include "Texture2D.h"

using namespace pep;

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
