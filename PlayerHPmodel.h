#pragma once
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>
#include <random>

class Player;

class PlayerHPmodel {
public:
	PlayerHPmodel() : seed(), eng(seed()), distribution(-randDistance, randDistance) {}
	~PlayerHPmodel();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw();

	float RandomOutput() { return distribution(eng); }

	const Vector3 GetWorldTranslation() const { return worldTransform_.translation_; }
	bool GetIsFinsihed() const { return isFinished; }

	void HpFallMotion();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	bool isFalling = false;
	bool isFinished = false;

	static inline const float kFallSpeed = 0.5f;
	float randDistance = kFallSpeed;
	std::random_device seed; // random device
	std::default_random_engine eng;
	std::uniform_real_distribution<float> distribution;
	Vector3 shakeDistance{};
};