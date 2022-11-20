#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete particleMan;
	delete object;
	delete objectBillboard;
	delete(sprite1);
	delete(sprite2);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;
	scene = square;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	//テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	//座標{0,0}に、テクスチャ2番のスプライトを生成
	sprite1 = Sprite::Create(2, { 0,0 });
	//座標{500,500}に、テクスチャ2番のスプライトを生成
	sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// 3Dオブジェクト生成
	object = Object::Create();
	object->Update();

	objectBillboard = Object3dBillboard::Create();
	objectBillboard->Update();

	particleMan = ParticleManager::Create();
	//particleMan->Update();


}

void GameScene::Update()
{
	////スペースキーを押していたら
	//if (input->PushKey(DIK_SPACE))
	//{
	//	//現在の座標を取得
	//	XMFLOAT2 position = sprite1->GetPosition();
	//	//移動後の座標を計算
	//	position.x += 1.0f;
	//	//座標の変更を反映
	//	sprite1->SetPosition(position);
	//}

	if (input->PushKey(DIK_RETURN))
	{
		scene = particle;

	}

	if (scene == square)
	{
		// オブジェクト移動
		//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		//{
		//	// 現在の座標を取得
		//	XMFLOAT3 position = object->GetPosition();

		//	// 移動後の座標を計算
		//	if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//	else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//	if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//	else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		//	// 座標の変更を反映
		//	object->SetPosition(position);
		//}

		// カメラ移動
		if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{
			if (input->PushKey(DIK_W)) { Object::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
			else if (input->PushKey(DIK_S)) { Object::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
			if (input->PushKey(DIK_D)) { Object::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
			else if (input->PushKey(DIK_A)) { Object::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
		}
		// カメラ移動
		if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{
			if (input->PushKey(DIK_W)) { Object3dBillboard::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
			else if (input->PushKey(DIK_S)) { Object3dBillboard::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
			if (input->PushKey(DIK_D)) { Object3dBillboard::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
			else if (input->PushKey(DIK_A)) { Object3dBillboard::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
		}



		object->Update();
		objectBillboard->Update();
	}
	else if (scene == particle)
	{
		
		for (int i = 0; i < 50; i++)
		{
			//x,y,z全て[-5.0f,+5.0f]でランダムに分布
			const float md_pos = 10.0f;
			XMFLOAT3 pos{};
			pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			//x,y,z全て[-0.05f,+0.05f]でランダムに分布
			const float md_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			//重力に見立ててYのみ{-0.001f,0}でランダムに分布
			XMFLOAT3 acc{};
			const float md_acc = 0.001f;
			acc.y = (float)rand() / RAND_MAX * md_acc;
			//色を変化させる
			XMFLOAT4 colorSpeed{};
			colorSpeed.x += 0.01;

			//追加
			particleMan->Add(120, pos, vel, acc, colorSpeed, 1.0f, 0.0f);
			//particleMan->Add(120, pos, vel, acc, colorSpeed);

		}

		particleMan->Update();

		// カメラ移動
		if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{
			if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
			else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
			if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
			else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
		}

	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理

	/// <summary>
	// 3Dオブクジェクトの描画
	if (scene == square)
	{
		Object::PreDraw(cmdList);
		object->Draw();
		Object::PostDraw();
		Object3dBillboard::PreDraw(cmdList);
		objectBillboard->Draw();
		Object3dBillboard::PostDraw();
	}
	else if (scene == particle)
	{
		ParticleManager::PreDraw(cmdList);
		particleMan->Draw();
		ParticleManager::PostDraw();
	}
	/// </summary>

	// 3Dオブジェクト描画後処理

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/*sprite1->Draw();
	sprite2->Draw();*/

	/// </summary>

	// デバッグテキストの描画
	//debugText.Print("CameraMove  WASD", 0.0f, 0.0f, 3.0f);
	//debugText.Print("ObjectMove  Arrowkey", 0.0f, 100.0f,3.0f);

	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
