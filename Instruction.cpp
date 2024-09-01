#include "Instruction.h"

Instruction::Instruction() {}

Instruction::~Instruction() {
	delete fade_;
	delete sprite_;
}

void Instruction::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = position_;
	viewProjection_.Initialize();
	sprite_ = Sprite::Create(texture_, {0, 0});

	fade_ = new Fade;
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, kFadeDuration);
}

void Instruction::Update() {
	worldTransform_.UpdateMatrix();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		fade_->Start(Fade::Status::FadeOut, kFadeDuration);
		fade_->Initialize();
		startChange = true;
	}
	if (fade_->IsFinished() && startChange) {
		isFinished_ = true;
	}

	fade_->Update();
}

void Instruction::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	//model_->Draw(worldTransform_, viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	if (fade_) {
		fade_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
