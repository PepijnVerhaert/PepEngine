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
	return dir == Direction::down || distance || point.x;
}
