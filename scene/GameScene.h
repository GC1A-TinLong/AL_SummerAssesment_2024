#pragma once
#include "Audio.h"
#include "CameraController.h"
#include "DangerSign.h"
#include "DeathParticles.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Fade.h"
#include "Goal.h"
#include "Input.h"
#include "MapChipField.h"
#include "MathFunction.h"
#include "Model.h"
#include "Player.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "PlayerHPmodel.h"
#include <vector>

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	/// <summary>
	/// Check all collisions
	/// </summary>
	void CheckAllCollisions();

	void CurrentPhase();

	// Getter
	bool IsFinished() const { return isFinished_; }

private: // メンバ変数
	enum class Phase {
		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut,
	};
	Phase phase_; // current phase
	static inline const float kFadeDuration = 1.0f;
	Fade* fade_ = nullptr;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// check if game scene is finished (for getter)
	bool isFinished_ = false;

#ifdef _DEBUG
	// Debug Camera
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;
#endif // DEBUG

	MapChipField* mapChipField_ = nullptr;

	// Block model
	Model* modelBlock_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// Skydome
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// Player
	Player* player_ = nullptr;
	uint32_t playerTexture_ = 0;
	CameraController::Rect playerMovableArea = {2.5f, 55.4f, 2.0f, 100.0f};
	Model* playerModel_ = nullptr;
	bool isPlayerHit = false;

	// Player HP icon
	std::vector<PlayerHPmodel*> playerHP_;
	Model* hpModel_ = nullptr;
	static inline const uint8_t kMaxHp = 5;
	uint8_t hp = kMaxHp;

	// Death Particles
	DeathParticles* deathParticles_ = nullptr;
	Model* deathParticlesModel_ = nullptr;

	// Spawn
	Vector2 spawnPosition{};

	// Enemy
	Enemy* enemy_ = nullptr;
	Model* enemyModel_ = nullptr;
	uint32_t enemyTexture_ = 0u;

	static inline const uint8_t kEnemyNum = 2;
	std::list<Enemy*> enemies_;

	// DangerSign
	//DangerSign* dangerSign_ = nullptr;
	std::vector<DangerSign*> dangerSign_;

	// Goal
	std::unique_ptr<Goal> goal_ = std::make_unique<Goal>();
	Model* goalModel_ = nullptr;

	// Camera
	CameraController* cameraController_ = nullptr;
	CameraController::Rect cameraMovableArea = {29.f, 29.f, 15.5f, 100.0f};
};
