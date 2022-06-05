#include "LevelLayoutComponent.h"
#include "BinaryReader.h"

LevelLayoutComponent::LevelLayoutComponent(const std::weak_ptr<pep::Object>& object, size_t gridWidth, size_t gridHeight)
	:pep::BaseComponent(object)
	,m_WalkableTiles{}
	,m_TileSize{}
	,m_GridOffset{}
{
	std::vector<bool> fillVector{};
	fillVector.resize(gridHeight, false);
	m_WalkableTiles.resize(gridWidth);
}



void LevelLayoutComponent::AddWalkable(size_t idx)
{
	size_t x = idx % m_WalkableTiles.size();
	size_t y = idx / m_WalkableTiles.size();

	m_WalkableTiles[x][y] = true;
}

bool LevelLayoutComponent::MoveDistanceInDirection(Direction dir, float distance, glm::vec2& point) const
{
	float epsilon = 0.01f;
	glm::vec2 destination = point;
	switch (dir)
	{
	case Direction::Up:
		size_t destX{};
		size_t destY{};
		if (GetTileId(point, destX, destY))
		{
			if (m_WalkableTiles[destX][destY])
			{

			}
		}
		break;
	case Direction::down:
		break;
	case Direction::left:
		break;
	case Direction::right:
		break;
	default:
		break;
	}

	return dir == Direction::down || distance || point.x;
}

bool LevelLayoutComponent::GetTileId(const glm::vec2& pos, size_t x, size_t y) const
{
	float gridSizeX = static_cast<float>(m_WalkableTiles.size());
	float gridSizeY = static_cast<float>(m_WalkableTiles[0].size());
	glm::vec2 posInGrid = pos;
	posInGrid -= m_GridOffset;
	if (posInGrid.x >= 0.f && posInGrid.x <= m_TileSize.x * gridSizeX)
	{
		x = static_cast<size_t>(posInGrid.x / m_TileSize.x);
	}
	else
	{
		return false;
	}

	if (posInGrid.y >= 0.f && posInGrid.y <= m_TileSize.y * gridSizeY)
	{
		y = static_cast<size_t>(posInGrid.y / m_TileSize.y);
	}
	else
	{
		return false;
	}

	if (x > m_WalkableTiles.size() || y > m_WalkableTiles[0].size())
	{
		return false;
	}
	return true;
}

bool LevelLayoutComponent::GetTilePos(glm::vec2& pos, size_t x, size_t y) const
{
	if (x > m_WalkableTiles.size() || y > m_WalkableTiles[0].size())
	{
		return false;
	}

	pos.x = static_cast<float>(x) * m_TileSize.x;
	pos.y = static_cast<float>(y) * m_TileSize.y;

	pos += m_GridOffset;

	return true;
}
