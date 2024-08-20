#pragma once
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>

class PlayerHPmodel {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	const Vector3 GetWorldTranslation() const { return worldTransform_.translation_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
};