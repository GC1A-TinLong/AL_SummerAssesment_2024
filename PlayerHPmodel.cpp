#include "PlayerHPmodel.h"

PlayerHPmodel::~PlayerHPmodel() {}

void PlayerHPmodel::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void PlayerHPmodel::Update() {
	worldTransform_.UpdateMatrix();
}

void PlayerHPmodel::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void PlayerHPmodel::HpFallMotion() {
	if (worldTransform_.translation_.y < 750.f) {
		isFalling = true;
	}
	if (isFalling) {
		worldTransform_.translation_.y -= 0.8f;
		if (worldTransform_.translation_.y >= 750.f) {
			isFalling = false;
		}
	}
}
