#pragma once
#include "DirectXCommon.h"
#include "Fade.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
#include <cmath>
#include <imgui.h>
#include <iostream>
#include <numbers>

class Instruction {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	Instruction();
	~Instruction();

	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Sprite* sprite_ = nullptr;
	uint32_t texture_ = TextureManager::Load("sprite/instruction.png");

	Fade* fade_ = nullptr;
	static inline const float kFadeDuration = 1.0f;
	Phase phase_ = Phase::kFadeIn;

	static inline const Vector3 position_ = {0, 3.0f, 0};

	bool isFinished_ = false;
	bool startChange = false;
};
