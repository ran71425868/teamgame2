#include "all.h"
#include <sstream>

int easy_state;
int easy_timer;

float playerX1;
float playerY1;

int score1;
float comboscore2;
int combo1;

extern int player_state;
extern int enemy_state;
extern OBJ2D enemy[ENEMY_MAX];
extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack1;

std::ostringstream oss3;                                 // 文字列ストリーム
POINT point1;

// 現在のスクロール量
float scrollValue3 = 0.0f;

void easy_init() {
	easy_state = 0;
	easy_timer = 0;
	score1 = 0;
	combo1 = 0;
	comboscore2 = 1.0f;

	playerX1 = SCREEN_W / 2.0f;
	playerY1 = SCREEN_H / 2.0f;
}
void easy_deinit() {
	music::stop(0);
	player_deinit();
	/*enemy_deinit();
	obstacle_deinit();*/
	avalanche_deinit();
	flag_deinit();

}
void easy_update()
{
	switch (easy_state)
	{
	case 0:
		sprBack1 = sprite_load(L"./Data/Images/map_04.png");

		audio_init();
		player_init();
		enemy_init();
		obstacle_init();
		avalanche_init();
		flag_init();

		easy_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		easy_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_SELECT) {
			nextScene = SCENE_RESULT;
			break;
		}

		if (hp <= 0)
		{
			nextScene = SCENE_RESULT;
		}

		player_update();
		enemy_update();
		obstacle_update();
		avalanche_update();
		flag_update();


		game_over();
		judge();
		break;
	}

	scrollValue3 -= 3;

	easy_timer++;
}
void easy_render() {

	text_out(4, "Up:W Down:S Right: D Left: A", 0, 0, 1, 1);
	//text_out(4, "angle++:Up Key angle--:Down Key", 0, 30, 1, 1);
	text_out(0, "score", 1100, 0, 2, 2);
	text_out(0, std::to_string(score1), 1100, 50, 2, 2);
	text_out(0, "combo", 0, 150, 2, 2);
	text_out(0, std::to_string(combo1), 0, 200, 2, 2);



	sprite_render(sprBack1, 0.0f, scrollValue3); // 背景をカメラの位置に合わせて描画
	sprite_render(sprBack1, 0.0f, 10000.0f + scrollValue3); // 背景をカメラの位置に合わせて描画


	player_render();
	//enemy_render();
	//obstacle_render();
	avalanche_render();
	flag_render();

}
void easy_score()
{
	if (combo1 >= 30)
		comboscore2 = 2.5f;
	else if (combo1 >= 20)
		comboscore2 = 2.0f;
	else if (combo1 >= 10)
		comboscore2 = 1.5f;
	else
		comboscore2 = 1.0f;


	for (int i = 0; i < FLAG_MAX; i++) {
		if (enemy[i].moveAlg == -1)
			score1 += 100 * comboscore2;

	}
	combo1++;
}

void easy_clear()
{

}

void easy_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT;
	}
}
