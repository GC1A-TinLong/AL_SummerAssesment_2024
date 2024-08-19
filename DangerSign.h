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

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	MapChipField* mapChipField_ = nullptr;

	Sprite* sprite_ = nullptr;
	uint32_t texture_ = TextureManager::Load("sprite/dangerSign.png");

	static inline const int kMaxDrawCount = 50;
	int drawCount = 0;
};
