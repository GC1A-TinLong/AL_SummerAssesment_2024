#pragma once
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>

class Player;

class Goal 
{
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	void OnCollision(const Player* player);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
};
