#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() {
	delete spriteBG_; // BG
	delete modelStage_;//ステージ
}


//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//BG(2Dスプライト)
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//ステージ
	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelStage_ = Model::Create();
	worldTransformStage_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
}
//更新
void GameScene::Update() {}

//表示
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	//背景
	spriteBG_->Draw();
	//ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
