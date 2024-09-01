#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "MapChipField.h"
#include <TextureManager.h>

class DangerSign {
public:
	~DangerSign();

	void Initialize(ViewProjection* viewProjection, const Vector2& position);
	void Update(ViewProjection* viewProjection, const Vector2& position);
	void Draw();

	Vector2 RollSpawnPoint();
	const int GetSpawnPoint() const { return randSpawnPoint; }
	const Vector3 GetPos() const { return worldTransform_.translation_; }

	void SetIsStart(bool boolean) { isStart = boolean; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;

	Sprite* sprite_ = nullptr;
	uint32_t texture_ = TextureManager::Load("sprite/dangerSign.png");

	enum class SpawnPos {
		topLeft,
		botLeft,
		topRight,
		botRight,

		kSpawnPointNum,
	};
	SpawnPos spawnPos;
	Vector2 topLeftPos = {36, 520};
	Vector2 botLeftPos = {36, 610};
	Vector2 topRightPos = {1180, 520};
	Vector2 botRightPos = {1180, 610};

	int randSpawnPoint = 0;

	bool isStart = false;
	int totalDuration = 0;

	static inline const int kMaxDrawCount = 50;
	int drawCount = 0;
	static inline const int kMaxDuration = 90;
	int duration = 0;
};
