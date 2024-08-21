#pragma once
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>

class Player;

class PlayerHPmodel {
public:
	~PlayerHPmodel();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw();

	const Vector3 GetWorldTranslation() const { return worldTransform_.translation_; }

	void HpFallMotion();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	bool isFalling = false;
};