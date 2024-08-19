#include "DangerSign.h"

DangerSign::~DangerSign() { delete sprite_; }

void DangerSign::Initialize(ViewProjection* viewProjection, const Vector2& position) {
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;

	sprite_ = Sprite::Create(texture_, position);
}

void DangerSign::Update() {
	drawCount++;
	if (drawCount >= kMaxDrawCount) {
		drawCount = 0;
	}
	worldTransform_.UpdateMatrix();
}

void DangerSign::Draw() {
	if (drawCount <= kMaxDrawCount / 2) {
		sprite_->Draw();
	}
}