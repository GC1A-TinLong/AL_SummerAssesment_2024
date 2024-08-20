#include "PlayerHPmodel.h"

void PlayerHPmodel::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void PlayerHPmodel::Update() { worldTransform_.UpdateMatrix(); }

void PlayerHPmodel::Draw() { model_->Draw(worldTransform_, *viewProjection_); }