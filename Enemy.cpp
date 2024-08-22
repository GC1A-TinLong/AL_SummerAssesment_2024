#include "Enemy.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, DangerSign* dangerSign) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	SpawningFrom(dangerSign);
	if (spawnPoint_ == SpawnPoint::kRight) {
		worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f * 3.0f;
		velocity_ = {-kWalkSpeed, 0, 0};
	} else if (spawnPoint_ == SpawnPoint::kLeft) {
		worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.f;
		velocity_ = {kWalkSpeed, 0, 0};
	}
	walkTimer_ = 0.0f;
}

void Enemy::Update() {
	worldTransform_.translation_.x += velocity_.x;

	walkTimer_ += 1.0f / 60.0f;
	worldTransform_.rotation_.x = std::sin(2 * std::numbers::pi_v<float> * (walkTimer_ / kWalkMotionTime));
	float param = std::sin(2 * std::numbers::pi_v<float> * (walkTimer_ / kWalkMotionTime));
	float radian = kInitialWalkMotionAngle + (kFinalWalkMotionAngle * (param + 1.0f) / 2.0f);
	worldTransform_.rotation_.x = (std::numbers::pi_v<float> * radian) / 180.0f;

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void Enemy::OnCollision(const Player* player) { (void)player; }

void Enemy::SpawningFrom(DangerSign* dangerSign) {
	switch (dangerSign->GetSpawnPoint()) {
	case 0:
		spawnPoint_ = SpawnPoint::kLeft;
		break;
	case 1:
		spawnPoint_ = SpawnPoint::kLeft;
		break;
	case 2:
		spawnPoint_ = SpawnPoint::kRight;
		break;
	case 3:
		spawnPoint_ = SpawnPoint::kRight;
		break;
	default:
		break;
	}
}

const Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos{};
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

const AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb{};
	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

const Vector3 Enemy::GetSpawnPos(DangerSign* dangerSign) {
	Vector3 pos{};
	switch (dangerSign->GetSpawnPoint()) {
	case 0:
		spawnPos = SpawnPos::topLeft;
		pos = topLeftPos;
		break;
	case 1:
		spawnPos = SpawnPos::botLeft;
		pos = botLeftPos;
		break;
	case 2:
		spawnPos = SpawnPos::topRight;
		pos = topRightPos;
		break;
	case 3:
		spawnPos = SpawnPos::botRight;
		pos = botRightPos;
		break;
	default:
		break;
	}
	return pos;
}
