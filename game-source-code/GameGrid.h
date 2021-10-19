#pragma once
#include "GameEntity.h"

namespace GameGrid
{
	using GameEntity_ptr = shared_ptr<GameEntity>;

	const float CELL_SIZE = 8;
	const float HALF_CELL = CELL_SIZE / 2;
	const float PIXELS_PER_CELL = CELL_SIZE;

	const float GRID_X_CELLS = 30;
	const float GRID_Y_CELLS = 30;

	const float GRID_X_START = 0;
	const float GRID_Y_START = CELL_SIZE;

	const float X_MIN = GRID_X_START;
	const float X_MAX = GRID_X_START + (CELL_SIZE * GRID_X_CELLS);
	const float Y_MIN = GRID_Y_START;
	const float Y_MAX = GRID_Y_START + (CELL_SIZE * GRID_Y_CELLS);

	const float PLAYER_AREA_X_MIN = X_MIN;
	const float PLAYER_AREA_X_MAX = X_MAX;
	const float PLAYER_AREA_Y_MIN = Y_MAX - (6 * CELL_SIZE);
	const float PLAYER_AREA_Y_MAX = Y_MAX;

	// static const pair<int, int> locate(const GameEntity &entity)
	// {
	// 	sf::Vector2f position;
	// 	if (entity.originAtCenter())
	// 	{
	// 		position = entity.getPosition();
	// 	}
	// 	else
	// 	{
	// 		auto size = entity.getCurrentSize();
	// 		position.x = entity.getPosition().x + (size.x / 2);
	// 		position.y = entity.getPosition().y + (size.y / 2);
	// 	}

	// 	return make_pair<int, int>(round((position.x) / CELL_SIZE), round(position.y / CELL_SIZE));
	// }

}