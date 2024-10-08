#pragma once

#define NOMINMAX
#include "CameraController.h"
#include "MathFunction.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "cassert"
#include <algorithm>
#include <numbers>
#include "PlayerHPmodel.h"

class MapChipField;
class Enemy;

enum class LRDirection {
	kRight,
	kLeft,
};

enum Corner { kBottomRight, kBottomLeft, kTopRight, kTopLeft, kNumCorner };

struct CollisionMapInfo {
	bool isHitCeiling = false;
	bool isHitGround = false;
	bool isHitWall = false;
	Vector3 velocity;
};

class Player {
public:
	Player();

	~Player();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, CameraController::Rect movableArea);
	void Update();
	void Draw();

	void PlayerMovement();
	void MovementInput();
	void PlayerDirection();

	Vector3 CornerPosition(const Vector3& center, Corner corner);
	void MovementByMapCollision(CollisionMapInfo& info);
	void WhenHitCeiling(const CollisionMapInfo& info);
	void SwitchToOnGround(const CollisionMapInfo& info);
	void WhenHitWall(const CollisionMapInfo& info);

	// Collision
	void OnCollision(const Enemy* enemy);
	void CollisionBuffer();

	// Getter
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	const Vector3& GetVelocity() const { return velocity_; };
	const Vector3 GetWorldPosition();
	const AABB GetAABB();
	const uint8_t GetPlayerHP() { return hp; }
	bool IsHit() const { return isHit_; }
	bool IsDead() const { return isDead_; }
	bool GetIsPressedR() const { return isPressedR; }
	// Setter
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

private:
	void IsCollideMapTop(CollisionMapInfo& info);
	void IsCollideMapBottom(CollisionMapInfo& info);
	void IsCollideMapLeft(CollisionMapInfo& info);
	void IsCollideMapRight(CollisionMapInfo& info);
	void MapCollision(CollisionMapInfo& info);

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};
	CameraController::Rect movableArea_ = {};
	LRDirection lrDirection_ = LRDirection::kRight;
	MapChipField* mapChipField_ = nullptr;

	// Player Size
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	// Airborne
	static inline const float kGravityAcceleration = 0.07f;
	static inline const float kLimitFallSpeed = 1.8f;
	static inline const float kJumpAcceleration = 1.1f;
	// OnGround
	static inline const float kAcceleration = 0.015f;
	static inline const float kAttenuation = 0.15f;
	static inline const float kMaxVelocity = 0.6f;
	bool onGround_ = true;
	// MapChip Adjustment
	static inline const float kBlank = 1.0f;
	static inline const float kLeftWallBlank = 0.9f;
	static inline const float kRightWallBlank = 1.1f;
	static inline const float kAboveGroundDistance = 0.2f;
	static inline const float kAdjustWallDistance = 0.2f;
	static inline const float kAttenuationLanding = 0.2f;
	static inline const float kAttenuationWall = 0.2f;
	// Player Rotation
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0;
	static inline const float kTimeTurn = 0.3f;
	// Player HP icon
	static inline const uint8_t kMaxHp = 5;
	uint8_t hp = kMaxHp;
	// Collide with enemy
	uint8_t collideBuffer = 0;
	static inline const int kMaxDrawCount = 30;
	int drawCount = 0;
	bool isHit_ = false;
	bool isDead_ = false;
	bool isPressedR = false;
};