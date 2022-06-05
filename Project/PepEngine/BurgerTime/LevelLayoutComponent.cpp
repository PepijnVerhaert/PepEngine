#include "LevelLayoutComponent.h"
#include "BinaryReader.h"

LevelLayoutComponent::LevelLayoutComponent(const std::weak_ptr<pep::Object>& object, size_t gridWidth, size_t gridHeight, const glm::vec2& tileSize, const glm::vec2& offset)
	:pep::BaseComponent(object)
	,m_WalkableTiles{}
	,m_TileSize{ tileSize }
	,m_GridOffset{ offset }
{
	std::vector<bool> fillVector{};
	fillVector.resize(gridHeight, true);
	m_WalkableTiles.resize(gridWidth, fillVector);
}



void LevelLayoutComponent::Update()
{
}

void LevelLayoutComponent::Render() const
{
}

void LevelLayoutComponent::AddWalkable(size_t idx)
{
	size_t x = idx % m_WalkableTiles.size();
	size_t y = idx / m_WalkableTiles.size();

	m_WalkableTiles[x][y] = true;
}

bool LevelLayoutComponent::MoveDistanceInDirection(Direction dir, float distance, glm::vec2& point) const
{
	float leftDistance = distance;
	float epsilon = 0.0001f;
	glm::vec2 destination = point;
	size_t destX{};
	size_t destY{};
	//set destination
	switch (dir)
	{
	case Direction::Up:
		if (!GetTileId(point, destX, destY))
			return false;
		if (destY == 0)
			return false;
		--destY;
		if (!m_WalkableTiles[destX][destY])
			return false;
		if (!GetTilePos(destination, destX, destY))
			return false;
		break;
	case Direction::down:
		if (!GetTileId(point, destX, destY))
			return false;
		if (destY >= m_WalkableTiles[0].size()-1)
			return false;
		++destY;
		if (!m_WalkableTiles[destX][destY])
			return false;
		if (!GetTilePos(destination, destX, destY))
			return false;
		break;
	case Direction::left:
		if (!GetTileId(point, destX, destY))
			return false;
		if (destX == 0)
			return false;
		--destX;
		if (!m_WalkableTiles[destX][destY])
			return false;
		if (!GetTilePos(destination, destX, destY))
			return false;
		break;
	case Direction::right:
		if (!GetTileId(point, destX, destY))
			return false;
		if (destX >= m_WalkableTiles.size() - 1)
			return false;
		++destX;
		if (!m_WalkableTiles[destX][destY])
			return false;
		if (!GetTilePos(destination, destX, destY))
			return false;
		break;
	default:
		return false;
		break;
	}

	//move point to destination
	glm::vec2 distanceToDestination = destination - point;
	switch (dir)
	{
	case Direction::Up:
	case Direction::down:
		//move along x to center
		if (glm::abs(distanceToDestination.x) > epsilon)
		{
			if (leftDistance >= glm::abs(distanceToDestination.x))
			{
				leftDistance -= glm::abs(distanceToDestination.x);
				point.x = destination.x;
			}
			else
			{
				if (distanceToDestination.x > 0.f)
				{
					point.x += leftDistance;
				}
				else
				{
					point.x -= leftDistance;
				}
				return true;
			}
		}
		else
		{
			point.x = destination.x;
		}
		//move along y
		if (glm::abs(distanceToDestination.y) < leftDistance)
		{
			point.y = destination.y;
			return true;
		}
		else
		{
			if (distanceToDestination.y > 0.f)
			{
				point.y += leftDistance;
			}
			else
			{
				point.y -= leftDistance;
			}
			return true;
		}
		break;
	case Direction::left:
	case Direction::right:
		//move along y to center
		if (glm::abs(distanceToDestination.y) > epsilon)
		{
			if (leftDistance >= glm::abs(distanceToDestination.y))
			{
				leftDistance -= glm::abs(distanceToDestination.y);
				point.y = destination.y;
			}
			else
			{
				if (distanceToDestination.y > 0.f)
				{
					point.y += leftDistance;
				}
				else
				{
					point.y -= leftDistance;
				}
				return true;
			}
		}
		else
		{
			point.y = destination.y;
		}
		//move along x
		if (glm::abs(distanceToDestination.x) < leftDistance)
		{
			point.x = destination.x;
			return true;
		}
		else
		{
			if (distanceToDestination.x > 0.f)
			{
				point.x += leftDistance;
			}
			else
			{
				point.x -= leftDistance;
			}
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

bool LevelLayoutComponent::GetTileId(const glm::vec2& pos, size_t& x, size_t& y) const
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

bool LevelLayoutComponent::GetTilePos(glm::vec2& pos, size_t idx) const
{
	size_t x = idx % m_WalkableTiles.size();
	size_t y = idx / m_WalkableTiles.size();
	return GetTilePos(pos, x, y);
}
