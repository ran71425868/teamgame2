#include "all.h"
#include <sstream>

int easy_state;
int easy_timer;

float playerX1;
float playerY1;

extern int score;
extern float comboscore;
extern int combo;

extern OBJ2D flag[FLAG_MAX];

extern int hp;
extern int gameflug;

Sprite* sprBack1;

std::ostringstream oss3;                                 // 文字列ストリーム
POINT point1;

// 現在のスクロール量
float scrollValue3 = 0.0f;

void easy_init() {
	easy_state = 0;
	easy_timer = 0;

	playerX1 = SCREEN_W / 2.0f;
	playerY1 = SCREEN_H / 2.0f;
}
void easy_deinit() {
	music::stop(0);
	player_deinit();
	flag_deinit();
	obstacle_deinit();
	goal_deinit();
	avalanche_deinit();
	

}
void easy_update()
{
	switch (easy_state)
	{
	case 0:
		sprBack1 = sprite_load(L"./Data/Images/map_04.png");

		audio_init();
		player_init();
		flag_init();
		obstacle_init();
		goal_init();
		avalanche_init();

		easy_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		score = 0;

		easy_state++;
		/*fallthrough*/

	case 2:
		gameflug = 1;
		if (hp <= 0)
		{
			nextScene = SCENE_RESULT_OVER;
		}

		player_update();
		flag_update();
		obstacle_update();
		goal_update();
		avalanche_update();


		game_over();
		judge();
		
		break;
	}

	scrollValue3 -= 5;
	if (scrollValue3 < -9000)
	{
		scrollValue3 = 0;
	}
	easy_timer++;
}
void easy_render() {

	sprite_render(sprBack1, 0.0f, scrollValue3); // 背景をカメラの位置に合わせて描画
	sprite_render(sprBack1, 0.0f, 10000.0f + scrollValue3); // 背景をカメラの位置に合わせて描画
	sprite_render(sprBack1, 0.0f, 20000.0f + scrollValue3); // 背景をカメラの位置に合わせて描画


	player_render();
	flag_render();
	obstacle_render();
	goal_render();
	avalanche_render();
	
	text_out(0, "score", 1700, 450, 2, 2);
	text_out(0, std::to_string(score), 1700, 500, 2, 2);
	text_out(0, "combo", 1700, 550, 2, 2);
	text_out(0, std::to_string(combo), 1700, 600, 2, 2);
	
}