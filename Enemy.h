#pragma once
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <numbers>

class Player;
class DangerSign;

class Enemy {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, DangerSign* dangerSign);
	void Update(Model* model, ViewProjection* viewProjection, const Vector3& position, DangerSign* dangerSign);
	void Draw();

	void OnCollision(const Player* player);

	void SpawningFrom(DangerSign* dangerSign);

	// Getter
	const Vector3 GetWorldPosition();
	const AABB GetAABB();
	const Vector3 GetSpawnPos(DangerSign* dangerSign);
	const bool GetIsStart() const { return isStart; }
	// Setter
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;

	enum class SpawnPoint {
		kRight,
		kLeft,
	};

	bool isStart = false;

	// Size
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;

	// Walking speed
	static inline const float kWalkSpeed = 0.3f;
	static inline const float kInitialWalkMotionAngle = -60.0f; // Initial angle
	static inline const float kFinalWalkMotionAngle = 120.0f;   // Final angle
	static inline const float kWalkMotionTime = 1.0f;           // Animation loop time
	float walkTimer_ = 0.0f;
	// Velocity
	Vector3 velocity_ = {};

	SpawnPoint spawnPoint_ = SpawnPoint::kLeft;

	enum class SpawnPos {
		topLeft,
		botLeft,
		topRight,
		botRight,

		kSpawnPointNum,
	};
	SpawnPos spawnPos;
	Vector3 topLeftPos = mapChipField_->GetMapChipPositionByIndexInt(-6, 16);
	Vector3 botLeftPos = mapChipField_->GetMapChipPositionByIndexInt(-6, 18);
	Vector3 topRightPos = mapChipField_->GetMapChipPositionByIndexInt(35, 16);
	Vector3 botRightPos = mapChipField_->GetMapChipPositionByIndexInt(35, 18);
};
