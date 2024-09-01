#include "DangerSign.h"
#include <random>

std::random_device seed; // random device
std::default_random_engine eng(seed());
std::uniform_int_distribution<int> randOutput(0, 3);

DangerSign::~DangerSign() { delete sprite_; }

void DangerSign::Initialize(ViewProjection* viewProjection, const Vector2& position) {
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;

	sprite_ = Sprite::Create(texture_, position);

	drawCount = 0;
	duration = 0;
}

void DangerSign::Update(ViewProjection* viewProjection, const Vector2& position) {
	totalDuration++;
	if (totalDuration >= 250) {
		Initialize(viewProjection, position);
		totalDuration = 0;
	}

	drawCount++;
	if (duration < kMaxDuration) {
		duration++;
	}
	if (drawCount >= kMaxDrawCount) {
		drawCount = 0;
	}
	worldTransform_.UpdateMatrix();
}

void DangerSign::Draw() {
	if (drawCount <= kMaxDrawCount / 2 && duration < kMaxDuration) {
		sprite_->Draw();
	}
}

Vector2 DangerSign::RollSpawnPoint() {
	randSpawnPoint = randOutput(eng);
	Vector2 pos{};
	switch (randSpawnPoint) {
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
