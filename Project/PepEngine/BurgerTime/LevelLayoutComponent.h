#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 4201)
#include <glm/glm.hpp>
#pragma warning (pop)

#include <vector>
#include <string>
#include "BinaryReader.h"

#include "Helper.h"

class LevelLayoutComponent final : public pep::BaseComponent
{
	LevelLayoutComponent(const std::weak_ptr<pep::Object>& object, size_t gridWidth, size_t gridHeight);
	~LevelLayoutComponent() = default;
	LevelLayoutComponent(const LevelLayoutComponent& other) = delete;
	LevelLayoutComponent(LevelLayoutComponent&& other) = delete;
	LevelLayoutComponent& operator=(const LevelLayoutComponent& other) = delete;
	LevelLayoutComponent& operator=(LevelLayoutComponent&& other) = delete;

	void Update() {};
	void AddWalkable(size_t idx);
	bool MoveDistanceInDirection(Direction dir, float distance, glm::vec2& point) const;

	bool GetTileId(const glm::vec2& pos, size_t x, size_t y) const;
	bool GetTilePos(glm::vec2& pos, size_t x, size_t y) const;
private:
	std::vector<std::vector<bool>> m_WalkableTiles;
	glm::vec2 m_TileSize;
	glm::vec2 m_GridOffset;
};

