#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/MiniFB_cpp.h"
#include "include/MiniFB.h"
#include "include/FreeImage.h"

void key_press(struct mfb_window* window, mfb_key key, mfb_key_mod mod, bool isPressed);
int generate_RandomX(int upperx, int lowerx);
int generate_RandomY(int uppery, int lowery);

typedef struct
{
	//sprites
	int* x;
	int* x_old;
	int* y;
	int* y_old;
	int* s;
	//menus
	int* game_mode;
	int* ub;
	int* ub_x_off;
	int* ub_y_off;
	int* ub_next;
	int* direct;
	//upgrades
	int* u_select;
	int* speed_lvl;
	//bg or maps
	int* map_x;
	int* map_y;
	//int* room_no;
	int* m;
	int* map_ctr;
	int* upperx;
	int* lowerx;
	int* uppery;
	int* lowery;
	//cats
	int* a;
	int* dir;
	int* cat_type;
	////rats
	//int *rx_dir;
	//int *ry_dir;
	//int *rx;
	int* ry1;
	int* ry2;
	int* ry3;
	int* ry4;
	int* ry5;
	//int *rx_old;
	//int *ry_old;
	//int *rs;
	//int rat_hp[11];
	int* hp_pos;
	int* r1_hp;
	int* r2_hp;
	int* r3_hp;
	int* r4_hp;
	int* r5_hp;
	//kill count
	int* weapontaken;
	int* kill_count;
	int* currency;
	//cat health
	int* heart_3;
	int* heart_2;
	int* heart_1;
} user_data;

int randomizer = 1; // RANDOMIZE ONCE ONLY
int rand_xnum = 0; //-200
int rand_ynum = 0; //30
int rand_x[11] = {};
int rand_y[11] = {};

int dead = 0;
//int rand_weapon = rand() % (2 + 1 - 0) + 0; //need to improve on this since its too small ung range. also needs to randomize per wave
int rand_weapon;

int main()
{
	printf("Hello Framebuffer!");

	struct mfb_window* window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
	if (!window)
		return 0;

	user_data udata;

	uint32_t* buffer = (uint32_t*)malloc(800 * 600 * 4);  //1436 | 1293

	FIBITMAP* fi_ui1 = FreeImage_Load(FIF_JPEG, "assets_meow/Main_Menu.jpg");
	FreeImage_FlipVertical(fi_ui1);
	uint8_t* ui1 = FreeImage_GetBits(fi_ui1);

	FIBITMAP* fi_ui2 = FreeImage_Load(FIF_JPEG, "assets_meow/Upgrades_Menu.jpg");
	FreeImage_FlipVertical(fi_ui2);
	uint8_t* ui2 = FreeImage_GetBits(fi_ui2);

	FIBITMAP* fi_ui_btn1 = FreeImage_Load(FIF_PNG, "assets_meow/Main_Start.png");
	FreeImage_FlipVertical(fi_ui_btn1);
	uint8_t* ui_btn1 = FreeImage_GetBits(fi_ui_btn1);

	FIBITMAP* fi_ui_btn2 = FreeImage_Load(FIF_PNG, "assets_meow/Main_Upgrades.png");
	FreeImage_FlipVertical(fi_ui_btn2);
	uint8_t* ui_btn2 = FreeImage_GetBits(fi_ui_btn2);

	FIBITMAP* fi_ui_btn3 = FreeImage_Load(FIF_PNG, "assets_meow/Upgrades_Back.png");
	FreeImage_FlipVertical(fi_ui_btn3);
	uint8_t* ui_btn3 = FreeImage_GetBits(fi_ui_btn3);

	FIBITMAP* fi_ui_btn4 = FreeImage_Load(FIF_PNG, "assets_meow/Upgrades_Continue.png");
	FreeImage_FlipVertical(fi_ui_btn4);
	uint8_t* ui_btn4 = FreeImage_GetBits(fi_ui_btn4);

	FIBITMAP* fi_ui_btn5 = FreeImage_Load(FIF_PNG, "assets_meow/Upgrades_Buy.png");
	FreeImage_FlipVertical(fi_ui_btn5);
	uint8_t* ui_btn5 = FreeImage_GetBits(fi_ui_btn5);

	FIBITMAP* fi_ui_btn6 = FreeImage_Load(FIF_PNG, "assets_meow/Upgrades_Speed.png");
	FreeImage_FlipVertical(fi_ui_btn6);
	uint8_t* ui_btn6 = FreeImage_GetBits(fi_ui_btn6);

	FIBITMAP* fi_bg1 = FreeImage_Load(FIF_JPEG, "assets_meow/F1_LivingRoom.jpg");
	FreeImage_FlipVertical(fi_bg1);
	uint8_t* bg1 = FreeImage_GetBits(fi_bg1);

	FIBITMAP* fi_bg2 = FreeImage_Load(FIF_JPEG, "assets_meow/F2_Bedroom.jpg");
	FreeImage_FlipVertical(fi_bg2);
	uint8_t* bg2 = FreeImage_GetBits(fi_bg2);

	FIBITMAP* fi_bg3 = FreeImage_Load(FIF_JPEG, "assets_meow/F3_Bathroom.jpg");
	FreeImage_FlipVertical(fi_bg3);
	uint8_t* bg3 = FreeImage_GetBits(fi_bg3);

	FIBITMAP* fi_sprite2 = FreeImage_Load(FIF_PNG, "assets_meow/Bengal_Up.png");
	FreeImage_FlipVertical(fi_sprite2);
	uint8_t* sprite2 = FreeImage_GetBits(fi_sprite2);

	FIBITMAP* fi_sprite3 = FreeImage_Load(FIF_PNG, "assets_meow/Bengal_Down.png");
	FreeImage_FlipVertical(fi_sprite3);
	uint8_t* sprite3 = FreeImage_GetBits(fi_sprite3);

	FIBITMAP* fi_sprite4 = FreeImage_Load(FIF_PNG, "assets_meow/Bengal_Left.png");
	FreeImage_FlipVertical(fi_sprite4);
	uint8_t* sprite4 = FreeImage_GetBits(fi_sprite4);

	FIBITMAP* fi_sprite5 = FreeImage_Load(FIF_PNG, "assets_meow/Bengal_Right.png");
	FreeImage_FlipVertical(fi_sprite5);
	uint8_t* sprite5 = FreeImage_GetBits(fi_sprite5);

	FIBITMAP* fi_sprite6 = FreeImage_Load(FIF_PNG, "assets_meow/Burmilla_Up.png");
	FreeImage_FlipVertical(fi_sprite6);
	uint8_t* sprite6 = FreeImage_GetBits(fi_sprite6);

	FIBITMAP* fi_sprite7 = FreeImage_Load(FIF_PNG, "assets_meow/Burmilla_Down.png");
	FreeImage_FlipVertical(fi_sprite7);
	uint8_t* sprite7 = FreeImage_GetBits(fi_sprite7);

	FIBITMAP* fi_sprite8 = FreeImage_Load(FIF_PNG, "assets_meow/Burmilla_Left.png");
	FreeImage_FlipVertical(fi_sprite8);
	uint8_t* sprite8 = FreeImage_GetBits(fi_sprite8);

	FIBITMAP* fi_sprite9 = FreeImage_Load(FIF_PNG, "assets_meow/Burmilla_Right.png");
	FreeImage_FlipVertical(fi_sprite9);
	uint8_t* sprite9 = FreeImage_GetBits(fi_sprite9);

	FIBITMAP* fi_sprite10 = FreeImage_Load(FIF_PNG, "assets_meow/Persian_Up.png");
	FreeImage_FlipVertical(fi_sprite10);
	uint8_t* sprite10 = FreeImage_GetBits(fi_sprite10);

	FIBITMAP* fi_sprite11 = FreeImage_Load(FIF_PNG, "assets_meow/Persian_Down.png");
	FreeImage_FlipVertical(fi_sprite11);
	uint8_t* sprite11 = FreeImage_GetBits(fi_sprite11);

	FIBITMAP* fi_sprite12 = FreeImage_Load(FIF_PNG, "assets_meow/Persian_Left.png");
	FreeImage_FlipVertical(fi_sprite12);
	uint8_t* sprite12 = FreeImage_GetBits(fi_sprite12);

	FIBITMAP* fi_sprite13 = FreeImage_Load(FIF_PNG, "assets_meow/Persian_Right.png");
	FreeImage_FlipVertical(fi_sprite13);
	uint8_t* sprite13 = FreeImage_GetBits(fi_sprite13);

	FIBITMAP* fi_sprite14 = FreeImage_Load(FIF_PNG, "assets_meow/Siamese_Up.png");
	FreeImage_FlipVertical(fi_sprite14);
	uint8_t* sprite14 = FreeImage_GetBits(fi_sprite14);

	FIBITMAP* fi_sprite15 = FreeImage_Load(FIF_PNG, "assets_meow/Siamese_Down.png");
	FreeImage_FlipVertical(fi_sprite15);
	uint8_t* sprite15 = FreeImage_GetBits(fi_sprite15);

	FIBITMAP* fi_sprite16 = FreeImage_Load(FIF_PNG, "assets_meow/Siamese_Left.png");
	FreeImage_FlipVertical(fi_sprite16);
	uint8_t* sprite16 = FreeImage_GetBits(fi_sprite16);

	FIBITMAP* fi_sprite17 = FreeImage_Load(FIF_PNG, "assets_meow/Siamese_Right.png");
	FreeImage_FlipVertical(fi_sprite17);
	uint8_t* sprite17 = FreeImage_GetBits(fi_sprite17);

	FIBITMAP* fi_sprite18 = FreeImage_Load(FIF_PNG, "assets_meow/Sphynx_Up.png");
	FreeImage_FlipVertical(fi_sprite18);
	uint8_t* sprite18 = FreeImage_GetBits(fi_sprite18);

	FIBITMAP* fi_sprite19 = FreeImage_Load(FIF_PNG, "assets_meow/Sphynx_Down.png");
	FreeImage_FlipVertical(fi_sprite19);
	uint8_t* sprite19 = FreeImage_GetBits(fi_sprite19);

	FIBITMAP* fi_sprite20 = FreeImage_Load(FIF_PNG, "assets_meow/Sphynx_Left.png");
	FreeImage_FlipVertical(fi_sprite20);
	uint8_t* sprite20 = FreeImage_GetBits(fi_sprite20);

	FIBITMAP* fi_sprite21 = FreeImage_Load(FIF_PNG, "assets_meow/Sphynx_Right.png");
	FreeImage_FlipVertical(fi_sprite21);
	uint8_t* sprite21 = FreeImage_GetBits(fi_sprite21);

	FIBITMAP* fi_sprite22 = FreeImage_Load(FIF_PNG, "assets_meow/NoAttack.png");
	FreeImage_FlipVertical(fi_sprite22);
	uint8_t* NoAttack = FreeImage_GetBits(fi_sprite22);

	FIBITMAP* fi_sprite23 = FreeImage_Load(FIF_PNG, "assets_meow/Scratch.png");
	FreeImage_FlipVertical(fi_sprite23);
	uint8_t* light_attack = FreeImage_GetBits(fi_sprite23);

	FIBITMAP* fi_sprite24 = FreeImage_Load(FIF_PNG, "assets_meow/Bite.png");
	FreeImage_FlipVertical(fi_sprite24);
	uint8_t* bite = FreeImage_GetBits(fi_sprite24);

	FIBITMAP* fi_sprite25 = FreeImage_Load(FIF_PNG, "assets_meow/Furball_Spit.png");
	FreeImage_FlipVertical(fi_sprite25);
	uint8_t* furball_spit = FreeImage_GetBits(fi_sprite25);

	FIBITMAP* fi_sprite26 = FreeImage_Load(FIF_PNG, "assets_meow/Mega_Meow.png");
	FreeImage_FlipVertical(fi_sprite26);
	uint8_t* mega_meow = FreeImage_GetBits(fi_sprite26);

	FIBITMAP* fi_sprite27 = FreeImage_Load(FIF_PNG, "assets_meow/Tail_Whip.png");
	FreeImage_FlipVertical(fi_sprite27);
	uint8_t* tail_slap = FreeImage_GetBits(fi_sprite27);

	FIBITMAP* fi_sprite28 = FreeImage_Load(FIF_PNG, "assets_meow/Telekinesis.png");
	FreeImage_FlipVertical(fi_sprite28);
	uint8_t* telekinesis = FreeImage_GetBits(fi_sprite28);

	FIBITMAP* fi_sprite29 = FreeImage_Load(FIF_PNG, "assets_meow/Flamethrower_Attack.png");
	FreeImage_FlipVertical(fi_sprite29);
	uint8_t* flamethrower_attack = FreeImage_GetBits(fi_sprite29);

	FIBITMAP* fi_sprite30 = FreeImage_Load(FIF_PNG, "assets_meow/Taser_Attack.png");
	FreeImage_FlipVertical(fi_sprite30);
	uint8_t* taser_attack = FreeImage_GetBits(fi_sprite30);

	FIBITMAP* fi_sprite31 = FreeImage_Load(FIF_PNG, "assets_meow/Sword_Attack.png");
	FreeImage_FlipVertical(fi_sprite30);
	uint8_t* sword_attack = FreeImage_GetBits(fi_sprite31);

	FIBITMAP* fi_sprite32 = FreeImage_Load(FIF_PNG, "assets_meow/Easy_Up.png");
	FreeImage_FlipVertical(fi_sprite32);
	uint8_t* sprite32 = FreeImage_GetBits(fi_sprite32);

	FIBITMAP* fi_sprite33 = FreeImage_Load(FIF_PNG, "assets_meow/Easy_Down.png");
	FreeImage_FlipVertical(fi_sprite33);
	uint8_t* sprite33 = FreeImage_GetBits(fi_sprite33);

	FIBITMAP* fi_sprite34 = FreeImage_Load(FIF_PNG, "assets_meow/Easy_Left.png");
	FreeImage_FlipVertical(fi_sprite34);
	uint8_t* sprite34 = FreeImage_GetBits(fi_sprite34);

	FIBITMAP* fi_sprite35 = FreeImage_Load(FIF_PNG, "assets_meow/Easy_Right.png");
	FreeImage_FlipVertical(fi_sprite35);
	uint8_t* sprite35 = FreeImage_GetBits(fi_sprite35);

	FIBITMAP* fi_sprite36 = FreeImage_Load(FIF_PNG, "assets_meow/Medium_Up.png");
	FreeImage_FlipVertical(fi_sprite36);
	uint8_t* sprite36 = FreeImage_GetBits(fi_sprite36);

	FIBITMAP* fi_sprite37 = FreeImage_Load(FIF_PNG, "assets_meow/Medium_Down.png");
	FreeImage_FlipVertical(fi_sprite37);
	uint8_t* sprite37 = FreeImage_GetBits(fi_sprite37);

	FIBITMAP* fi_sprite38 = FreeImage_Load(FIF_PNG, "assets_meow/Medium_Left.png");
	FreeImage_FlipVertical(fi_sprite38);
	uint8_t* sprite38 = FreeImage_GetBits(fi_sprite38);

	FIBITMAP* fi_sprite39 = FreeImage_Load(FIF_PNG, "assets_meow/Medium_Right.png");
	FreeImage_FlipVertical(fi_sprite39);
	uint8_t* sprite39 = FreeImage_GetBits(fi_sprite39);

	FIBITMAP* fi_sprite40 = FreeImage_Load(FIF_PNG, "assets_meow/Hard_Up.png");
	FreeImage_FlipVertical(fi_sprite40);
	uint8_t* sprite40 = FreeImage_GetBits(fi_sprite40);

	FIBITMAP* fi_sprite41 = FreeImage_Load(FIF_PNG, "assets_meow/Hard_Down.png");
	FreeImage_FlipVertical(fi_sprite41);
	uint8_t* sprite41 = FreeImage_GetBits(fi_sprite41);

	FIBITMAP* fi_sprite42 = FreeImage_Load(FIF_PNG, "assets_meow/Hard_Left.png");
	FreeImage_FlipVertical(fi_sprite42);
	uint8_t* sprite42 = FreeImage_GetBits(fi_sprite42);

	FIBITMAP* fi_sprite43 = FreeImage_Load(FIF_PNG, "assets_meow/Hard_Right.png");
	FreeImage_FlipVertical(fi_sprite43);
	uint8_t* sprite43 = FreeImage_GetBits(fi_sprite43);

	FIBITMAP* fi_sprite44 = FreeImage_Load(FIF_PNG, "assets_meow/Portal.png");
	FreeImage_FlipVertical(fi_sprite44);
	uint8_t* sprite44 = FreeImage_GetBits(fi_sprite44);

	FIBITMAP* fi_sprite45 = FreeImage_Load(FIF_PNG, "assets_meow/Sword.png");
	FreeImage_FlipVertical(fi_sprite45);
	uint8_t* sword = FreeImage_GetBits(fi_sprite45);

	FIBITMAP* fi_sprite46 = FreeImage_Load(FIF_PNG, "assets_meow/Flamethrower.png");
	FreeImage_FlipVertical(fi_sprite46);
	uint8_t* flamethrower = FreeImage_GetBits(fi_sprite46);

	FIBITMAP* fi_sprite47 = FreeImage_Load(FIF_PNG, "assets_meow/Taser.png");
	FreeImage_FlipVertical(fi_sprite47);
	uint8_t* taser = FreeImage_GetBits(fi_sprite47);

	FIBITMAP* fi_sprite48 = FreeImage_Load(FIF_PNG, "assets_meow/Empty_Heart.png");
	FreeImage_FlipVertical(fi_sprite48);
	uint8_t* sprite48 = FreeImage_GetBits(fi_sprite48);

	FIBITMAP* fi_sprite49 = FreeImage_Load(FIF_PNG, "assets_meow/Full_Heart.png");
	FreeImage_FlipVertical(fi_sprite49);
	uint8_t* sprite49 = FreeImage_GetBits(fi_sprite49);

	//// Copies the full background to the framebuffer
	//for (int i = 0; i < map_x *  map_y * 3; i += 3)
	//	buffer[i / 3] = (bg2[i + 2] << 16) | (bg2[i + 1] << 8) | bg2[i];

	mfb_set_keyboard_callback(window, key_press);
	mfb_set_user_data(window, (void*)&udata);

	srand(time(0));

	do {
		static int map_x = 800; //1436 800
		static int map_y = 600; //1293 600
		//static int room_no = 1; //ROOM NUMBER
		static int m = 0;
		static int map_ctr = 0;

		static int upperx = 0;
		static int lowerx = 0;
		static int uppery = 0;
		static int lowery = 0;

		uint8_t* maps[5] = { ui1, ui2, bg1, bg2, bg3 };

		udata.map_x = &map_x;
		udata.map_y = &map_y;
		//udata.room_no = &room_no;
		udata.m = &m;
		udata.map_ctr = &map_ctr;

		udata.upperx = &upperx;
		udata.lowerx = &lowerx;
		udata.uppery = &uppery;
		udata.lowery = &lowery;

		if (map_ctr > 0 && map_ctr < 2) {
			buffer = (uint32_t*)malloc(map_x * map_y * 4);
			map_ctr = 0;
			printf("CHANGED MAP! = %d\n\n", map_ctr);
		}

		//udata.map_ctr = &map_ctr;

		for (int i = 0; i < map_x * map_y * 3; i += 3)
			buffer[i / 3] = (maps[m][i + 2] << 16) | (maps[m][i + 1] << 8) | maps[m][i];

		static int bg_x = 0;
		static int bg_y = 0;
		static int bg_x_old = bg_x;
		static int bg_y_old = bg_y;
		static int s = 1;

		static int game_mode = 0; //0 - start menu | 1 - game in map 1 | 2 - upgrade menu
		static int ub = 0;
		static int ub_x_off = 0;
		static int ub_y_off = 247;
		static int ub_next = 0;
		static int direct = 0; //0 - screen 1 to screen 2 | 1 - screen 2 to screen 1

		static int u_select = 0;
		static int speed_lvl = 0;

		static int a = 0;
		static int dir = 1;
		static int cat_type = 1;

		static int rx_dir1 = 2; //0 - left | 1 - right | 2 - no movement
		static int ry_dir1 = 0; //0 - up | 1 - down | 2 - no movement
		static int rx1 = 0;
		static int ry1 = 0;
		static int rx_old1 = rx1;
		static int ry_old1 = ry1;
		static int rs1 = 0;

		static int rx_dir2 = 2; //0 - left | 1 - right | 2 - no movement
		static int ry_dir2 = 0; //0 - up | 1 - down | 2 - no movement
		static int rx2 = 0;
		static int ry2 = 0;
		static int rx_old2 = rx2;
		static int ry_old2 = ry2;
		static int rs2 = 0;

		static int rx_dir3 = 2; //0 - left | 1 - right | 2 - no movement
		static int ry_dir3 = 0; //0 - up | 1 - down | 2 - no movement
		static int rx3 = 0;
		static int ry3 = 0;
		static int rx_old3 = rx3;
		static int ry_old3 = ry3;
		static int rs3 = 0;

		static int rx_dir4 = 2; //0 - left | 1 - right | 2 - no movement
		static int ry_dir4 = 0; //0 - up | 1 - down | 2 - no movement
		static int rx4 = 0;
		static int ry4 = 0;
		static int rx_old4 = rx4;
		static int ry_old4 = ry4;
		static int rs4 = 0;

		static int rx_dir5 = 2; //0 - left | 1 - right | 2 - no movement
		static int ry_dir5 = 0; //0 - up | 1 - down | 2 - no movement
		static int rx5 = 0;
		static int ry5 = 0;
		static int rx_old5 = rx5;
		static int ry_old5 = ry5;
		static int rs5 = 0;

		static int wave = 1; // change to test wave 1, wave 2, wave 3
		static int rat_hp[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		static int hp_pos = 10;

		static int kill_count = 0;
		static int weapontaken = 0;
		static int currency = 0;

		static int heart_1 = 1;
		static int heart_2 = 1;
		static int heart_3 = 1;

		//static int hp_val;
		static int r1_hp = 0, r2_hp = 0, r3_hp = 0, r4_hp = 0, r5_hp = 0, r6_hp = 0, r7_hp = 0, r8_hp = 0, r9_hp = 0, r10_hp = 0;

		uint8_t* ui_btns[6] = { ui_btn1, ui_btn2, ui_btn3, ui_btn4, ui_btn5, ui_btn6 };

		uint8_t* sprites[21] = { sprite2, sprite3, sprite4, sprite5, sprite6, sprite7, sprite8, sprite9, sprite10, sprite11, sprite12, sprite13, sprite14, sprite15, sprite16, sprite17, sprite18, sprite19, sprite20, sprite21, sprite44 };
		uint8_t* attacks[12] = { NoAttack , light_attack, bite, furball_spit, mega_meow, tail_slap, telekinesis, flamethrower_attack, sword_attack, taser_attack };
		uint8_t* weapons[3] = { flamethrower, sword, taser };

		uint8_t* easy[4] = { sprite32, sprite33, sprite34, sprite35 };
		uint8_t* medium[4] = { sprite36, sprite37, sprite38, sprite39 };
		uint8_t* hard[4] = { sprite40, sprite41, sprite42, sprite43 };

		uint8_t* health[2] = { sprite48, sprite49 };

		udata.x = &bg_x;
		udata.x_old = &bg_x_old;
		udata.y = &bg_y;
		udata.y_old = &bg_y_old;
		udata.s = &s;

		udata.game_mode = &game_mode;
		udata.ub = &ub;
		udata.ub_x_off = &ub_x_off;
		udata.ub_y_off = &ub_y_off;
		udata.ub_next = &ub_next;
		udata.direct = &direct;

		udata.u_select = &u_select;
		udata.speed_lvl = &speed_lvl;

		udata.a = &a;
		udata.dir = &dir;
		udata.cat_type = &cat_type;

		//udata.rx_dir = &rx_dir;
		//udata.ry_dir = &ry_dir;
		//udata.rx = &rx;
		udata.ry1 = &ry1;
		udata.ry2 = &ry2;
		udata.ry3 = &ry3;
		udata.ry4 = &ry4;
		udata.ry5 = &ry5;
		//udata.rx_old = &rx_old;
		//udata.ry_old = &ry_old;
		//udata.rs = &rs;
		////udata.rat_hp[10] = rat_hp[10];
		udata.hp_pos = &hp_pos;
		//udata.hp_val = &hp_val;
		udata.r1_hp = &r1_hp;
		udata.r2_hp = &r2_hp;
		udata.r3_hp = &r3_hp;
		udata.r4_hp = &r4_hp;
		udata.r5_hp = &r5_hp;

		udata.kill_count = &kill_count;
		udata.weapontaken = &weapontaken;
		udata.currency = &currency;

		udata.heart_3 = &heart_3;
		udata.heart_2 = &heart_2;
		udata.heart_1 = &heart_1;


		if (game_mode == 0) { //start menu
			//bg
			for (int i = 0; i < 106; i++)
			{
				for (int j = 0; j < 456; j++)
				{
					uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 24) + 3 * (bg_x_old + ub_x_off + j + 172) + 2];
					uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 24) + 3 * (bg_x_old + ub_x_off + j + 172) + 1];
					uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 24) + 3 * (bg_x_old + ub_x_off + j + 172)];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y_old + ub_y_off + 24) + (j + bg_x_old + ub_x_off + 172)] = pixel; //-- CENTER
				}
			}
			//btn sprite
			for (int i = 0; i < 106; i++)
			{
				for (int j = 0; j < 456; j++)
				{
					uint8_t r = ui_btns[ub][456 * 3 * i + 3 * j + 2];
					uint8_t g = ui_btns[ub][456 * 3 * i + 3 * j + 1];
					uint8_t b = ui_btns[ub][456 * 3 * i + 3 * j];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y + ub_y_off + 24) + (j + bg_x + ub_x_off + 172)] = pixel; //-- CENTER
				}
			}
		}

		if (game_mode == 1) { //upgrades menu
			if (speed_lvl == 1) {
				//bg
				for (int i = 0; i < 41; i++)
				{
					for (int j = 0; j < 48; j++)
					{
						uint8_t r = maps[m][map_x * 3 * (i + 299) + 3 * (j + 327) + 2];
						uint8_t g = maps[m][map_x * 3 * (i + 299) + 3 * (j + 327) + 1];
						uint8_t b = maps[m][map_x * 3 * (i + 299) + 3 * (j + 327)];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + 299) + (j + 327)] = pixel; //-- CENTER
					}
				}
				//btn sprite
				for (int i = 0; i < 41; i++)
				{
					for (int j = 0; j < 48; j++)
					{
						uint8_t r = ui_btns[5][48 * 3 * i + 3 * j + 2];
						uint8_t g = ui_btns[5][48 * 3 * i + 3 * j + 1];
						uint8_t b = ui_btns[5][48 * 3 * i + 3 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + 299) + (j + 327)] = pixel; //-- CENTER
					}
				}
			}
			if (ub_next == 0) {
				//bg
				for (int i = 0; i < 52; i++)
				{
					for (int j = 0; j < 260; j++)
					{
						uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 157) + 3 * (bg_x_old + ub_x_off + j + 143) + 2];
						uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 157) + 3 * (bg_x_old + ub_x_off + j + 143) + 1];
						uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 157) + 3 * (bg_x_old + ub_x_off + j + 143)];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y_old + ub_y_off + 157) + (j + bg_x_old + ub_x_off + 143)] = pixel; //-- CENTER
					}
				}
				//btn sprite
				for (int i = 0; i < 52; i++)
				{
					for (int j = 0; j < 260; j++)
					{
						uint8_t r = ui_btns[ub][260 * 3 * i + 3 * j + 2];
						uint8_t g = ui_btns[ub][260 * 3 * i + 3 * j + 1];
						uint8_t b = ui_btns[ub][260 * 3 * i + 3 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + ub_y_off + 157) + (j + bg_x + ub_x_off + 143)] = pixel; //-- CENTER
					}
				}
			}
			else if (ub_next == 1) {
				if (u_select == 1) {
					//bg
					for (int i = 0; i < 41; i++)
					{
						for (int j = 0; j < 48; j++)
						{
							uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 65) + 3 * (bg_x_old + ub_x_off + j + 71) + 2];
							uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 65) + 3 * (bg_x_old + ub_x_off + j + 71) + 1];
							uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 65) + 3 * (bg_x_old + ub_x_off + j + 71)];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + bg_y_old + ub_y_off - 65) + (j + bg_x_old + ub_x_off + 71)] = pixel; //-- CENTER
						}
					}
					//btn sprite
					for (int i = 0; i < 41; i++)
					{
						for (int j = 0; j < 48; j++)
						{
							uint8_t r = ui_btns[5][48 * 3 * i + 3 * j + 2];
							uint8_t g = ui_btns[5][48 * 3 * i + 3 * j + 1];
							uint8_t b = ui_btns[5][48 * 3 * i + 3 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + bg_y + ub_y_off - 65) + (j + bg_x + ub_x_off + 71)] = pixel; //-- CENTER
						}
					}
				}
				//bg
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 160; j++)
					{
						uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 100) + 3 * (bg_x_old + ub_x_off + j + 208) + 2];
						uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 100) + 3 * (bg_x_old + ub_x_off + j + 208) + 1];
						uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off + 100) + 3 * (bg_x_old + ub_x_off + j + 208)];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y_old + ub_y_off + 100) + (j + bg_x_old + ub_x_off + 208)] = pixel; //-- CENTER
					}
				}
				//btn sprite
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 160; j++)
					{
						uint8_t r = ui_btns[ub][160 * 3 * i + 3 * j + 2];
						uint8_t g = ui_btns[ub][160 * 3 * i + 3 * j + 1];
						uint8_t b = ui_btns[ub][160 * 3 * i + 3 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + ub_y_off + 100) + (j + bg_x + ub_x_off + 208)] = pixel; //-- CENTER
					}
				}
			}
			else if (ub_next == 2) {
				//bg
				for (int i = 0; i < 41; i++)
				{
					for (int j = 0; j < 48; j++)
					{
						uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 64) + 3 * (bg_x_old + ub_x_off + j + 71) + 2];
						uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 64) + 3 * (bg_x_old + ub_x_off + j + 71) + 1];
						uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + ub_y_off - 64) + 3 * (bg_x_old + ub_x_off + j + 71)];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y_old + ub_y_off - 64) + (j + bg_x_old + ub_x_off + 71)] = pixel; //-- CENTER
					}
				}
				//btn sprite
				for (int i = 0; i < 41; i++)
				{
					for (int j = 0; j < 48; j++)
					{
						uint8_t r = ui_btns[ub][48 * 3 * i + 3 * j + 2];
						uint8_t g = ui_btns[ub][48 * 3 * i + 3 * j + 1];
						uint8_t b = ui_btns[ub][48 * 3 * i + 3 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + ub_y_off - 64) + (j + bg_x + ub_x_off + 71)] = pixel; //-- CENTER
					}
				}
			}
		}

		//start playing the game
		if (game_mode == 2) {
			//bg
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 42; j++)
				{
					uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + 284) + 3 * (bg_x_old + j + 379) + 2];
					uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + 284) + 3 * (bg_x_old + j + 379) + 1];
					uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + 284) + 3 * (bg_x_old + j + 379)];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y_old + 284) + (j + bg_x_old + 379)] = pixel; //-- CENTER
				}
			}

			if (dead == 1) {
				//portal sprite
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 42; j++)
					{
						uint8_t r = sprites[20][42 * 4 * i + 4 * j + 2];
						uint8_t g = sprites[20][42 * 4 * i + 4 * j + 1];
						uint8_t b = sprites[20][42 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + 284) + (j + 379)] = pixel; //-- CENTER
					}
				}
			}

			//cat sprite
			//Change sprite used depending on direction
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 42; j++)
				{
					uint8_t r = sprites[s][42 * 4 * i + 4 * j + 2];
					uint8_t g = sprites[s][42 * 4 * i + 4 * j + 1];
					uint8_t b = sprites[s][42 * 4 * i + 4 * j];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y + 284) + (j + bg_x + 379)] = pixel; //-- CENTER
				}
			}

			if (dir == 3) {
				//attack
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						uint8_t r = attacks[a][20 * 4 * i + 4 * j + 2];
						uint8_t g = attacks[a][20 * 4 * i + 4 * j + 1];
						uint8_t b = attacks[a][20 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + 284) + (j + bg_x + 419)] = pixel; //-- RIGHT
					}
				}
			}
			else if (dir == 2) {
				//attack
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						uint8_t r = attacks[a][20 * 4 * i + 4 * j + 2];
						uint8_t g = attacks[a][20 * 4 * i + 4 * j + 1];
						uint8_t b = attacks[a][20 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + 284) + (j + bg_x + 357)] = pixel; //-- LEFT
					}
				}
			}
			else if (dir == 1) {
				//attack
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						uint8_t r = attacks[a][20 * 4 * i + 4 * j + 2];
						uint8_t g = attacks[a][20 * 4 * i + 4 * j + 1];
						uint8_t b = attacks[a][20 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + 312) + (j + bg_x + 388)] = pixel; //-- DOWN
					}
				}
			}
			else if (dir == 0) {
				//attack
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						uint8_t r = attacks[a][20 * 4 * i + 4 * j + 2];
						uint8_t g = attacks[a][20 * 4 * i + 4 * j + 1];
						uint8_t b = attacks[a][20 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + bg_y + 258) + (j + bg_x + 388)] = pixel; //-- UP
					}
				}
			}

			//update current hp of each rat
			//rat_hp[hp_pos] = hp_val;
			rat_hp[0] = r1_hp;
			rat_hp[1] = r2_hp;
			rat_hp[2] = r3_hp;
			rat_hp[3] = r4_hp;
			rat_hp[4] = r5_hp;
			rat_hp[5] = r6_hp;
			rat_hp[6] = r7_hp;
			rat_hp[7] = r8_hp;
			rat_hp[8] = r9_hp;
			rat_hp[9] = r10_hp;

			if (randomizer) {
				if (wave == 1) {
					rand_weapon = rand() % (2 + 1 - 0) + 0;
					r1_hp = 1;
					r2_hp = 1;
					r3_hp = 1;
					r4_hp = 1;
					r5_hp = 2;
					for (int i = 0; i < 4; i++)
						rat_hp[i] = 1;
					for (int i = 4; i < 5; i++)
						rat_hp[i] = 2;
					for (int i = 5; i < 10; i++)
						rat_hp[i] = 0;
				}

				for (int i = 0; i < 11; i++)
				{
					rand_xnum = generate_RandomX(upperx, lowerx);
					for (int j = 0; j < 11; j++)
					{
						if ((rand_x[j] >= rand_xnum) && (rand_xnum <= rand_x[j] + 30)) {
							rand_xnum = generate_RandomX(upperx, lowerx);
						}
						else {
							rand_x[i] = rand_xnum;
						}
					}
				}
				for (int i = 0; i < 11; i++)
				{
					rand_ynum = generate_RandomY(uppery, lowery);
					for (int j = 0; j < 11; j++) {
						if ((rand_y[j] >= rand_ynum) && (rand_ynum <= rand_y[j] + 30)) {
							rand_ynum = generate_RandomY(uppery, lowery);
						}
						else {
							rand_y[i] = rand_ynum;
						}
					}
				}
				randomizer = 0; // set randomizer 1 again after wave is done
			}

			if (rat_hp[0] <= 0 && rat_hp[1] <= 0 && rat_hp[2] <= 0 && rat_hp[3] <= 0 && rat_hp[4] <= 0 &&
				rat_hp[5] <= 0 && rat_hp[6] <= 0 && rat_hp[7] <= 0 && rat_hp[8] <= 0 && rat_hp[9] <= 0)
				dead = 1;

			for (int i = 0; i < 10; i++) {
				printf("rat_hp[%d] = %d\n", i, rat_hp[i]);
			}

			//for (int i = 0; i < 11; i++) {
			//	printf("X [%d] = %d\n", i, rand_x[i]);
			//}
			//for (int j = 0; j < 11; j++) {
			//	printf("Y [%d] = %d\n", j, rand_y[j]);
			//}
			//printf("X [%d] = %d\n", 11, rand_x[11]);
			//printf("Y [%d] = %d\n", 11, rand_y[11]);

			if (wave == 1) { // first wave, 5 rats
				if (weapontaken == 0) { //it just spawns

					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 44; j++)
						{
							uint8_t r = weapons[rand_weapon][44 * 4 * i + 4 * j + 2];
							uint8_t g = weapons[rand_weapon][44 * 4 * i + 4 * j + 1];
							uint8_t b = weapons[rand_weapon][44 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[10]) + (j + rand_x[10])] = pixel;
						}
					}

				}

				//no need to add else for weaponstaken
				if (dead == 0) {
					if (rat_hp[0] > 0) {
						for (int i = 0; i < 22; i++)
						{
							for (int j = 0; j < 28; j++)
							{
								uint8_t r = easy[rs1][28 * 4 * i + 4 * j + 2];
								uint8_t g = easy[rs1][28 * 4 * i + 4 * j + 1];
								uint8_t b = easy[rs1][28 * 4 * i + 4 * j];
								uint32_t pixel = (r << 16) | (g << 8) | b;
								if (pixel)
									buffer[map_x * (i + ry1 + rand_y[0]) + (j + rx1 + rand_x[0])] = pixel;
							}
						}
						rx_old1 = rx1;
						if (rx1 <= map_x - 309) {  //800
							if (rx_dir1 == 1)
								rx1 += 1;
							else if (rx_dir1 == 2)
								rx1 += 0;
							else
								rx1 -= 1;
						}
						ry_old1 = ry1;
						if (ry1 <= map_y - 326) {  //600
							if (ry_dir1 == 1)
								ry1 += 1;
							else if (ry_dir1 == 2)
								ry1 += 0;
							else
								ry1 -= 1;
						}
					}

					if (rat_hp[1] > 0) {
						for (int i = 0; i < 22; i++)
						{
							for (int j = 0; j < 28; j++)
							{
								uint8_t r = easy[rs2][28 * 4 * i + 4 * j + 2];
								uint8_t g = easy[rs2][28 * 4 * i + 4 * j + 1];
								uint8_t b = easy[rs2][28 * 4 * i + 4 * j];
								uint32_t pixel = (r << 16) | (g << 8) | b;
								if (pixel)
									buffer[map_x * (i + ry2 + rand_y[1]) + (j + rx2 + rand_x[1])] = pixel;
							}
						}
						rx_old2 = rx2;
						if (rx2 <= map_x - 309) {  //800
							if (rx_dir2 == 1)
								rx2 += 1;
							else if (rx_dir2 == 2)
								rx2 += 0;
							else
								rx2 -= 1;
						}
						ry_old2 = ry2;
						if (ry2 <= map_y - 326) {  //600
							if (ry_dir2 == 1)
								ry2 += 1;
							else if (ry_dir2 == 2)
								ry2 += 0;
							else
								ry2 -= 1;
						}
					}

					if (rat_hp[2] > 0) {
						for (int i = 0; i < 22; i++)
						{
							for (int j = 0; j < 28; j++)
							{
								uint8_t r = easy[rs3][28 * 4 * i + 4 * j + 2];
								uint8_t g = easy[rs3][28 * 4 * i + 4 * j + 1];
								uint8_t b = easy[rs3][28 * 4 * i + 4 * j];
								uint32_t pixel = (r << 16) | (g << 8) | b;
								if (pixel)
									buffer[map_x * (i + ry3 + rand_y[2]) + (j + rx3 + rand_x[2])] = pixel;
							}
						}
						rx_old3 = rx3;
						if (rx3 <= map_x - 309) {  //800
							if (rx_dir3 == 1)
								rx3 += 1;
							else if (rx_dir3 == 2)
								rx3 += 0;
							else
								rx3 -= 1;
						}
						ry_old3 = ry3;
						if (ry3 <= map_y - 326) {  //600
							if (ry_dir3 == 1)
								ry3 += 1;
							else if (ry_dir3 == 2)
								ry3 += 0;
							else
								ry3 -= 1;
						}
					}

					if (rat_hp[3] > 0) {
						for (int i = 0; i < 22; i++)
						{
							for (int j = 0; j < 28; j++)
							{
								uint8_t r = easy[rs4][28 * 4 * i + 4 * j + 2];
								uint8_t g = easy[rs4][28 * 4 * i + 4 * j + 1];
								uint8_t b = easy[rs4][28 * 4 * i + 4 * j];
								uint32_t pixel = (r << 16) | (g << 8) | b;
								if (pixel)
									buffer[map_x * (i + ry4 + rand_y[3]) + (j + rx4 + rand_x[3])] = pixel;
							}
						}
						rx_old4 = rx4;
						if (rx4 <= map_x - 309) {  //800
							if (rx_dir4 == 1)
								rx4 += 1;
							else if (rx_dir4 == 2)
								rx4 += 0;
							else
								rx4 -= 1;
						}
						ry_old4 = ry4;
						if (ry4 <= map_y - 326) {  //600
							if (ry_dir4 == 1)
								ry4 += 1;
							else if (ry_dir4 == 2)
								ry4 += 0;
							else
								ry4 -= 1;
						}
					}

					// 1 medium
					if (rat_hp[4] > 0) {
						for (int i = 0; i < 22; i++)
						{
							for (int j = 0; j < 28; j++)
							{
								uint8_t r = medium[rs5][28 * 4 * i + 4 * j + 2];
								uint8_t g = medium[rs5][28 * 4 * i + 4 * j + 1];
								uint8_t b = medium[rs5][28 * 4 * i + 4 * j];
								uint32_t pixel = (r << 16) | (g << 8) | b;
								if (pixel)
									buffer[map_x * (i + ry5 + rand_y[4]) + (j + rx5 + rand_x[4])] = pixel;
							}
						}
						rx_old5 = rx5;
						if (rx5 <= map_x - 309) {  //800
							if (rx_dir5 == 1)
								rx5 += 1;
							else if (rx_dir5 == 2)
								rx5 += 0;
							else
								rx5 -= 1;
						}
						ry_old5 = ry5;
						if (ry5 <= map_y - 326) {  //600
							if (ry_dir5 == 1)
								ry5 += 1;
							else if (ry_dir5 == 2)
								ry5 += 0;
							else
								ry5 -= 1;
						}
					}
				}
			}

			if (wave == 2) { // second wave, 7 rats
				for (int x = 0; x < 3; x++) { // 3 easy
					for (int i = 0; i < 22; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							uint8_t r = easy[x][28 * 4 * i + 4 * j + 2];
							uint8_t g = easy[x][28 * 4 * i + 4 * j + 1];
							uint8_t b = easy[x][28 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[x]) + (j + rand_x[x])] = pixel;
						}
					}
				}
				for (int x = 0; x < 3; x++) { // 3 medium
					for (int i = 0; i < 22; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							uint8_t r = medium[x][28 * 4 * i + 4 * j + 2];
							uint8_t g = medium[x][28 * 4 * i + 4 * j + 1];
							uint8_t b = medium[x][28 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[x + 3]) + (j + rand_x[x + 3])] = pixel;
						}
					}
				}
				// 1 hard
				for (int i = 0; i < 22; i++)
				{
					for (int j = 0; j < 28; j++)
					{
						uint8_t r = hard[0][28 * 4 * i + 4 * j + 2];
						uint8_t g = hard[0][28 * 4 * i + 4 * j + 1];
						uint8_t b = hard[0][28 * 4 * i + 4 * j];
						uint32_t pixel = (r << 16) | (g << 8) | b;
						if (pixel)
							buffer[map_x * (i + rand_y[6]) + (j + rand_x[6])] = pixel;
					}
				}
			}

			if (wave == 3) { // third wave, 10 rats
				for (int x = 0; x < 2; x++) { // 2 easy
					for (int i = 0; i < 22; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							uint8_t r = easy[x][28 * 4 * i + 4 * j + 2];
							uint8_t g = easy[x][28 * 4 * i + 4 * j + 1];
							uint8_t b = easy[x][28 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[x]) + (j + rand_x[x])] = pixel;
						}
					}
				}
				for (int x = 0; x < 4; x++) { // 4 medium
					for (int i = 0; i < 22; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							uint8_t r = medium[x][28 * 4 * i + 4 * j + 2];
							uint8_t g = medium[x][28 * 4 * i + 4 * j + 1];
							uint8_t b = medium[x][28 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[x + 2]) + (j + rand_x[x + 2])] = pixel;
						}
					}
				}
				for (int x = 0; x < 4; x++) { // 4 hard
					for (int i = 0; i < 22; i++)
					{
						for (int j = 0; j < 28; j++)
						{
							uint8_t r = hard[x][28 * 4 * i + 4 * j + 2];
							uint8_t g = hard[x][28 * 4 * i + 4 * j + 1];
							uint8_t b = hard[x][28 * 4 * i + 4 * j];
							uint32_t pixel = (r << 16) | (g << 8) | b;
							if (pixel)
								buffer[map_x * (i + rand_y[x + 6]) + (j + rand_x[x + 6])] = pixel;
						}
					}
				}
			}

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					uint8_t r = health[heart_1][20 * 4 * i + 4 * j + 2];
					uint8_t g = health[heart_1][20 * 4 * i + 4 * j + 1];
					uint8_t b = health[heart_1][20 * 4 * i + 4 * j];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y + 10) + (j + bg_x + 710)] = pixel;
				}
			}

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					uint8_t r = health[heart_2][20 * 4 * i + 4 * j + 2];
					uint8_t g = health[heart_2][20 * 4 * i + 4 * j + 1];
					uint8_t b = health[heart_2][20 * 4 * i + 4 * j];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y + 10) + (j + bg_x + 735)] = pixel;
				}
			}
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					uint8_t r = health[heart_3][20 * 4 * i + 4 * j + 2];
					uint8_t g = health[heart_3][20 * 4 * i + 4 * j + 1];
					uint8_t b = health[heart_3][20 * 4 * i + 4 * j];
					uint32_t pixel = (r << 16) | (g << 8) | b;
					if (pixel)
						buffer[map_x * (i + bg_y + 10) + (j + bg_x + 760)] = pixel;
				}
			}

			//Rat Borders			
			//Top and Bottom
			// [-rand_y + (1293 - uppery - cat width)]
			// [uppery - rand_y + rat height]
			if (ry1 == (-rand_y[0] + (map_y - uppery - 42))) {
				ry_dir1 = 1;
				rs1 = 1;
			}
			if (ry1 == (uppery - rand_y[0] + 22)) {
				ry_dir1 = 0;
				rs1 = 0;
			}

			if (ry2 == (-rand_y[1] + (map_y - uppery - 42))) {
				ry_dir2 = 1;
				rs2 = 1;
			}
			if (ry2 == (uppery - rand_y[1] + 22)) {
				ry_dir2 = 0;
				rs2 = 0;
			}

			if (ry3 == (-rand_y[2] + (map_y - uppery - 42))) {
				ry_dir3 = 1;
				rs3 = 1;
			}
			if (ry3 == (uppery - rand_y[2] + 22)) {
				ry_dir3 = 0;
				rs3 = 0;
			}

			if (ry4 == (-rand_y[3] + (map_y - uppery - 42))) {
				ry_dir4 = 1;
				rs4 = 1;
			}
			if (ry4 == (uppery - rand_y[3] + 22)) {
				ry_dir4 = 0;
				rs4 = 0;
			}

			if (ry5 == (-rand_y[4] + (map_y - uppery - 42))) {
				ry_dir5 = 1;
				rs5 = 1;
			}
			if (ry5 == (uppery - rand_y[4] + 22)) {
				ry_dir5 = 0;
				rs5 = 0;
			}

			//Left and Right
			printf("rx = %d\n", rx1);
			printf("ry = %d\n\n", ry1);

			//Currency
			currency = 10 * kill_count;
			printf("currency = %d\n\n", currency);

		}


		////will overload ur memory thats 
		////why key press to change maps nlg
		//if (bg_x > 100 && bg_y > 100) {
		//	map_x = 988;
		//	map_y = 1062;
		//	m = 1;
		//	map_ctr = 1;
		//	//map_ctr = 0;
		//}

		printf("bg_x = %d\n", bg_x);
		printf("bg_y = %d\n\n", bg_y);

		//printf("map_x = %d\n", map_x);
		//printf("map_y = %d\n", map_y);
		//printf("m = %d\n", m);
		//printf("map_ctr = %d\n\n", map_ctr);

		int state = mfb_update_crop(window, buffer + bg_x + (map_x * bg_y), 800, 600, map_x);

		if (state < 0) {
			window = NULL;
			break;
		}
	} while (mfb_wait_sync(window));

	return 0;
}

int generate_RandomX(int upperx, int lowerx)
{
	int num;

	//num = rand() % 1100; // should be less than map size - 30 (width of rat) 750
	num = (rand() % (upperx - lowerx + 1)) + lowerx; // (upper - lower + 1) + lower;
	return num;
}

int generate_RandomY(int uppery, int lowery)
{
	int num;

	//num = rand() % 1000; // should be less than map size - 30 (height of rat) 690
	num = (rand() % (uppery - lowery + 1)) + lowery; // (upper - lower + 1) + lower;
	return num;
}

void key_press(struct mfb_window* window, mfb_key key, mfb_key_mod mod, bool isPressed)
{
	static int type_i = 0;
	static int heavyattack_i = 0;
	static int specialattack_i = 0;
	static int speed_p[5] = { 50, 100, 150, 200, 250 };
	//static int strength_p[5] = { 50, 100, 150, 200, 250 };
	//static int health_p[5] = { 50, 100, 150, 200, 250 };
	user_data* udata = (user_data*)mfb_get_user_data(window);
	if (isPressed)
	{
		//MAPS
		//if (key == KB_KEY_M) {
		//	*(udata->map_x) = 988;
		//	*(udata->map_y) = 1062;
		//	//*(udata->map_change) = 1;
		//	*(udata->m) = 2;
		//	*(udata->map_ctr) += 1;
		//	printf("CHANGING MAP! = %d\n", *(udata->map_ctr));
		//}		

		//Menu Keys
		if (key == KB_KEY_ENTER && *(udata->game_mode) == 2) {
			if (*(udata->x) == 0 && *(udata->y) == 0) {
				*(udata->map_x) = 800;
				*(udata->map_y) = 600;
				//*(udata->map_change) = 1;
				*(udata->m) = 1;
				*(udata->map_ctr) += 1;
				//printf("CHANGING MAP! = %d\n", *(udata->map_ctr));
				*(udata->ub_y_off) += 200;
				//*(udata->ub_next) = 0;
				*(udata->ub) = 2; //back
				*(udata->game_mode) = 1;
				printf("game_mode = %d\n", *(udata->game_mode));
			}
		}

		if (key == KB_KEY_ENTER && *(udata->game_mode) == 1) {
			//if (*(udata->game_mode) == 1) {
				//printf("BACK NOW x= %d\n", *(udata->ub_x_off));
				//if (*(udata->direct) == 1) {
			if (*(udata->ub_x_off) == 0 && *(udata->ub_y_off) == 365) { //BACK BUTTON
				printf("BACKED\n");
				*(udata->map_x) = 800;
				*(udata->map_y) = 600;
				*(udata->m) = 0;
				*(udata->map_ctr) += 1;
				*(udata->ub) = 1; //upgrade
				*(udata->game_mode) = 0;
				*(udata->direct) = 2;
			}
			if (*(udata->ub_x_off) == 256 && *(udata->ub_y_off) == 365) { //CONTINUE BUTTON
				//*(udata->map_x) = 988;
				//*(udata->map_y) = 1062;
				//*(udata->m) = 4;
				*(udata->map_x) = 1468;
				*(udata->map_y) = 1216;
				*(udata->m) = 2;
				*(udata->upperx) = 1239;
				*(udata->lowerx) = 219;
				*(udata->uppery) = 874;
				*(udata->lowery) = 284;
				*(udata->map_ctr) += 1;
				*(udata->game_mode) = 2;
			}
			if (*(udata->ub) == 5) {
				if (*(udata->u_select) == 0) {
					*(udata->u_select) = 1;
				}
				else {
					*(udata->u_select) = 0;
				}
				printf("select5 = %d\n", *(udata->u_select));
			}
			if (*(udata->ub) == 4) {
				printf("select4 = %d\n", *(udata->u_select));
				if (*(udata->currency) >= speed_p[0]) {
					*(udata->speed_lvl) = 1;
					printf("speed1 = %d\n", *(udata->speed_lvl));
				}
			}
			//}
		//}
		}

		if (key == KB_KEY_ENTER && *(udata->game_mode) == 0) {
			if (*(udata->ub_y_off) == 247) { //START BUTTON
				*(udata->map_x) = 1436;
				*(udata->map_y) = 1293;
				*(udata->m) = 3;
				*(udata->upperx) = 1127;
				*(udata->lowerx) = 177;
				*(udata->uppery) = 967;
				*(udata->lowery) = 407;
				*(udata->map_ctr) += 1;
				*(udata->game_mode) = 2;
			}
			if (*(udata->ub_y_off) == 365 && *(udata->direct) != 2) { //UPGRADES BUTTON
				*(udata->map_x) = 800;
				*(udata->map_y) = 600;
				*(udata->m) = 1;
				*(udata->map_ctr) += 1;
				*(udata->ub) = 2;
				*(udata->game_mode) = 1;
			}
		}

		//MOVEMENT
		if (key == KB_KEY_LEFT)
		{
			if (*(udata->game_mode) == 1) {
				if (*(udata->ub) == 3) {
					*(udata->ub_x_off) -= 256;
					*(udata->ub) = 2;
					printf("Left game mode 1\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
			}
			else if (*(udata->game_mode) == 2) {
				*(udata->dir) = 2;
				*(udata->x_old) = *(udata->x);
				if (*(udata->speed_lvl) == 0)
					*(udata->x) -= 10;
				else if (*(udata->speed_lvl) == 1)
					*(udata->x) -= 12;
				*(udata->s) = 2 + type_i;
				*(udata->a) = 0;
				printf("Left\n");
				//Pick up Weapon
				//if (*(udata->x) >= (rand_x[10] - 379 - 44)) { 
				//	if (*(udata->y) >= (rand_y[10]) - 284 - 32 && *(udata->y) <= (rand_y[10]) - 284) {
				//		*(udata->weapontaken) = 1;
				//		specialattack_i = rand_weapon;

				//	}
				//}

				//HEALTH_LEFT
				/*if (*(udata->x) <= (rand_x[0] - 379)) {
					if (*(udata->y) >= (rand_y[0]) - 284 - 32 + *(udata->ry1) && *(udata->y) <= (rand_y[0]) - 284 + 32 + *(udata->ry1)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) <= (rand_x[1] - 379)) {
					if (*(udata->y) >= (rand_y[1]) - 284 - 32 + *(udata->ry2) && *(udata->y) <= (rand_y[1]) - 284 + 32 + *(udata->ry2)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) <= (rand_x[2] - 379)) {
					if (*(udata->y) >= (rand_y[2]) - 284 - 32 + *(udata->ry3) && *(udata->y) <= (rand_y[2]) - 284 + 32 + *(udata->ry3)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) <= (rand_x[3] - 379)) {
					if (*(udata->y) >= (rand_y[3]) - 284 - 32 + *(udata->ry4) && *(udata->y) <= (rand_y[3]) - 284 + 32 + *(udata->ry4)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) <= (rand_x[4] - 379)) {
					if (*(udata->y) >= (rand_y[4]) - 284 - 32 + *(udata->ry5) && *(udata->y) <= (rand_y[4]) - 284 + 32 + *(udata->ry5)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}*/

			}
		}
		else if (key == KB_KEY_RIGHT)
		{
			if (*(udata->game_mode) == 1) {
				if (*(udata->ub) == 2) {
					*(udata->ub_x_off) += 256;
					*(udata->ub) = 3;
					printf("Right game mode 1\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
			}
			else if (*(udata->game_mode) == 2) {
				*(udata->dir) = 3;
				*(udata->x_old) = *(udata->x);
				if (*(udata->speed_lvl) == 0)
					*(udata->x) += 10;
				else if (*(udata->speed_lvl) == 1)
					*(udata->x) += 12;
				*(udata->s) = 3 + type_i;
				*(udata->a) = 0;
				printf("Right\n");
				//Pick up Weapon
				//if (*(udata->x) >= (rand_x[10] - 379 - 44)) { 
				//	if (*(udata->y) >= (rand_y[10]) - 284 - 32 && *(udata->y) <= (rand_y[10]) - 284) {
				//		*(udata->weapontaken) = 1;
				//		specialattack_i = rand_weapon;

				//	}
				//}

				//HEALTH_RIGHT
				if (*(udata->x) >= (rand_x[0] - 379)) {
					if (*(udata->y) >= (rand_y[0]) - 284 - 32 + *(udata->ry1) && *(udata->y) <= (rand_y[0]) - 284 + 32 + *(udata->ry1)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379)) {
					if (*(udata->y) >= (rand_y[1]) - 284 - 32 + *(udata->ry2) && *(udata->y) <= (rand_y[1]) - 284 + 32 + *(udata->ry2)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379)) {
					if (*(udata->y) >= (rand_y[2]) - 284 - 32 + *(udata->ry3) && *(udata->y) <= (rand_y[2]) - 284 + 32 + *(udata->ry3)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379)) {
					if (*(udata->y) >= (rand_y[3]) - 284 - 32 + *(udata->ry4) && *(udata->y) <= (rand_y[3]) - 284 + 32 + *(udata->ry4)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379)) {
					if (*(udata->y) >= (rand_y[4]) - 284 - 32 + *(udata->ry5) && *(udata->y) <= (rand_y[4]) - 284 + 32 + *(udata->ry5)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}

			}
		}
		else if (key == KB_KEY_UP)
		{
			if (*(udata->game_mode) == 0) {
				*(udata->ub_y_off) -= 118;
				*(udata->ub) = 0;
				printf("Up\n");
				*(udata->direct) = 0;
			}
			else if (*(udata->game_mode) == 1) {
				if (*(udata->ub) == 4) {
					*(udata->ub_y_off) -= 1;
					*(udata->ub) = 5;
					*(udata->ub_next) = 2;
					printf("Up\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
				if (*(udata->ub) == 3) {
					*(udata->ub_y_off) -= 1;
					*(udata->ub) = 4;
					*(udata->ub_next) = 1;
					printf("Up\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
			}
			else if (*(udata->game_mode) == 2) {
				*(udata->dir) = 0;
				*(udata->y_old) = *(udata->y);
				if (*(udata->speed_lvl) == 0)
					*(udata->y) -= 10;
				else if (*(udata->speed_lvl) == 1)
					*(udata->y) -= 12;
				*(udata->s) = 0 + type_i;
				*(udata->a) = 0;
				printf("Up\n");
				//Pick up Weapon
				//if (*(udata->x) >= (rand_x[10] - 379 - 44)) { 
				//	if (*(udata->y) >= (rand_y[10]) - 284 - 32 && *(udata->y) <= (rand_y[10]) - 284) {
				//		*(udata->weapontaken) = 1;
				//		specialattack_i = rand_weapon;

				//	}
				//}

				//HEALTH_UP
				/*if (*(udata->x) >= (rand_x[0] - 379 && *(udata->x) <= (rand_x[0]) - 379)) {
					if (*(udata->y) >= (rand_y[0]) - 284 - 32 + *(udata->ry1) && *(udata->y) <= (rand_y[0]) - 284 + 32 + *(udata->ry1)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379 - 42 && *(udata->x) <= (rand_x[1]) - 379 + 42)) {
					if (*(udata->y) >= (rand_y[1]) - 284 - 32 + *(udata->ry2) && *(udata->y) <= (rand_y[1]) - 284 + 32 + *(udata->ry2)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379 - 42 && *(udata->x) <= (rand_x[2]) - 379 + 42)) {
					if (*(udata->y) >= (rand_y[2]) - 284 - 32 + *(udata->ry3) && *(udata->y) <= (rand_y[2]) - 284 + 32 + *(udata->ry3)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379 - 42 && *(udata->x) <= (rand_x[3]) - 379 + 42)) {
					if (*(udata->y) >= (rand_y[3]) - 284 - 32 + *(udata->ry4) && *(udata->y) <= (rand_y[3]) - 284 + 32 + *(udata->ry4)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379 - 42 && *(udata->x) <= (rand_x[4]) - 379 + 42)) {
					if (*(udata->y) >= (rand_y[4]) - 284 - 32 + *(udata->ry5) && *(udata->y) <= (rand_y[4]) - 284 + 32 + *(udata->ry5)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}*/

			}
		}
		else if (key == KB_KEY_DOWN)
		{
			if (*(udata->game_mode) == 0) {
				*(udata->ub_y_off) += 118;
				*(udata->ub) = 1;
				printf("Down\n");
			}
			else if (*(udata->game_mode) == 1) {
				if (*(udata->ub) == 4) {
					*(udata->ub_y_off) += 1;
					*(udata->ub) = 3;
					*(udata->ub_next) = 0;
					printf("Down\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
				if (*(udata->ub) == 5) {
					*(udata->ub_y_off) += 1;
					*(udata->ub) = 4;
					*(udata->ub_next) = 1;
					printf("Down\n");
					printf("ub_x_off = %d\n", *(udata->ub_x_off));
					printf("ub_y_off = %d\n", *(udata->ub_y_off));
				}
			}
			else if (*(udata->game_mode) == 2) {
				*(udata->dir) = 1;
				*(udata->y_old) = *(udata->y);
				if (*(udata->speed_lvl) == 0)
					*(udata->y) += 10;
				else if (*(udata->speed_lvl) == 1)
					*(udata->y) += 12;
				*(udata->s) = 1 + type_i;
				*(udata->a) = 0;
				printf("Down\n");
				//Pick up Weapon
				//if (*(udata->x) >= (rand_x[10] - 379 - 44)) { 
				//	if (*(udata->y) >= (rand_y[10]) - 284 - 32 && *(udata->y) <= (rand_y[10]) - 284) {
				//		*(udata->weapontaken) = 1;
				//		specialattack_i = rand_weapon;

				//	}
				//}

				//HEALTH_DOWN
				/*if (*(udata->x) >= (rand_x[0] - 379 && *(udata->x) <= (rand_x[0]) - 379)) {
					if (*(udata->y) >= (rand_y[0]) - 284 - 32 + *(udata->ry1) && *(udata->y) <= (rand_y[0]) - 284 + 32 + *(udata->ry1)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379 && *(udata->x) <= (rand_x[1]) - 379)) {
					if (*(udata->y) >= (rand_y[1]) - 284 - 32 + *(udata->ry2) && *(udata->y) <= (rand_y[1]) - 284 + 32 + *(udata->ry2)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379 && *(udata->x) <= (rand_x[2]) - 379)) {
					if (*(udata->y) >= (rand_y[2]) - 284 - 32 + *(udata->ry3) && *(udata->y) <= (rand_y[2]) - 284 + 32 + *(udata->ry3)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379 && *(udata->x) <= (rand_x[3]) - 379)) {
					if (*(udata->y) >= (rand_y[3]) - 284 - 32 + *(udata->ry4) && *(udata->y) <= (rand_y[3]) - 284 + 32 + *(udata->ry4)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379 && *(udata->x) <= (rand_x[4]) - 379)) {
					if (*(udata->y) >= (rand_y[4]) - 284 - 32 + *(udata->ry5) && *(udata->y) <= (rand_y[4]) - 284 + 32 + *(udata->ry5)) {
						if ((*(udata->heart_3) == 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_3) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) == 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_2) = 0;
						}
						else if ((*(udata->heart_3) != 1) && (*(udata->heart_2) != 1) && (*(udata->heart_1) == 1)) {
							*(udata->heart_1) = 0;
							//*(udata->game_mode) = 0;
						}
					}
				}*/

			}
		}

		//Pick Up Weapons
		if (key == KB_KEY_D) {
			if ((*udata->dir == 3)) { //LEFT SIDE
				//[rand x - cat x offset - (cat width/2) - set range]
				//[rand y - cat y offset - (cat height/2)] && [rand y - cat y offset]
				if (*(udata->x) >= (rand_x[10] - 379 - 21 - 50)) {
					if (*(udata->y) >= (rand_y[10]) - 284 - 16 && *(udata->y) <= (rand_y[10]) - 284) {
						*(udata->weapontaken) = 1;
						specialattack_i = rand_weapon;
					}
				}
			}
			if ((*udata->dir == 2)) { //RIGHT SIDE
				//[rand x - cat x offset + (cat width/2) + set range]
				//[rand y - cat y offset - (cat height/2)] && [rand y - cat y offset]
				if (*(udata->x) <= (rand_x[10]) - 379 + 21 + 50) {
					if (*(udata->y) >= (rand_y[10]) - 284 - 16 && *(udata->y) <= (rand_y[10]) - 284) {
						*(udata->weapontaken) = 1;
						specialattack_i = rand_weapon;
					}
				}
			}
			if ((*udata->dir == 1)) { //TOP SIDE
				//[rand x - cat x offset - (cat height/2)] && [rand x - cat x offset + (cat width/2)]
				//[rand y - cat y offset] && [rand y - cat y offset + (cat height/2) + set range]
				if (*(udata->x) >= (rand_x[10]) - 379 - 21 && *(udata->x) <= (rand_x[10]) - 379 + 21) {
					if (*(udata->y) >= (rand_y[10]) - 284 - 16 - 50 && *(udata->y) <= (rand_y[10]) - 284) {
						*(udata->weapontaken) = 1;
						specialattack_i = rand_weapon;
					}
				}
			}
			if ((*udata->dir == 0)) { //BOTTOM SIDE
				//[rand x - cat x offset - (cat width/2)] && [rand x - cat x offset + (cat width/2)]
				//[rand y - cat y offset] && [rand y - cat y offset + (cat height/2) + set range]
				if (*(udata->x) >= (rand_x[10]) - 379 - 21 && *(udata->x) <= (rand_x[10]) - 379 + 21) {
					if (*(udata->y) >= (rand_y[10]) - 284 && *(udata->y) <= (rand_y[10]) - 284 + 16 + 50) {
						*(udata->weapontaken) = 1;
						specialattack_i = rand_weapon;
					}
				}
			}
		}

		//Light Attack
		else if ((*udata->dir == 3) && (key == KB_KEY_A))
		{
			*(udata->s) = 3 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Right\n");

			////non-moving rats
			//if (*(udata->x) >= (rand_x[4] - 379 - 42)) {  //rand x - cat x offset - cat width
			//	if (*(udata->y) >= (rand_y[4]) - 284 - 32 && *(udata->y) <= (rand_y[4]) - 284) { //rand y - cat y offset - height && rand y - cat y offset
			//		*(udata->hp_pos) = 4;
			//		*(udata->r5_hp) -= 1;
			//		//printf("hop_pos = %d\n", *(udata->hp_pos));
			//		//printf("hp_val = %d\n", *(udata->hp_val));
			//	}
			//}

			//moving rats (up & down)
			//[rand x - cat x offset - cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) >= (rand_x[0] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 1;
					//Medium Rat counts as 2 kills
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}


		}
		else if ((*udata->dir == 2) && (key == KB_KEY_A))
		{
			*(udata->s) = 2 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Left\n");
			//[rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 1;
					//Medium Rat counts as 2 kills
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}
		else if ((*udata->dir == 1) && (key == KB_KEY_A))
		{
			*(udata->s) = 1 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Down\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r2_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r3_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r4_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 1;
					//Medium Rat counts as 2 kills
					if (*(udata->r5_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}
		else if ((*udata->dir == 0) && (key == KB_KEY_A))
		{
			*(udata->s) = 0 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Up\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset + ry] && [rand y - cat y offset + cat height + ry]
			*(udata->hp_pos) = 0;
			if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + 32 + *(udata->ry1))) {
					*(udata->r1_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + 32 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + 32 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + 32 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 1;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + 32 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 1;
					//Medium Rat counts as 2 kills
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}

		//Heavy Attacks
		else if ((*udata->dir == 3) && (key == KB_KEY_S))
		{
			*(udata->s) = 3 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Right\n");
			//[rand x - cat x offset - cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 2;
					//Medium Rat counts as 2 kills
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}
		else if ((*udata->dir == 2) && (key == KB_KEY_S))
		{
			*(udata->s) = 2 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Left\n");
			//[rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 2;
					//Medium Rat counts as 2 kills
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}
		else if ((*udata->dir == 1) && (key == KB_KEY_S))
		{
			*(udata->s) = 1 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Down\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->x) >= (rand_x[0] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r2_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r3_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r4_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 2;
					//Medium Rat counts as 2 kills
					if (*(udata->r5_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}
		else if ((*udata->dir == 0) && (key == KB_KEY_S))
		{
			*(udata->s) = 0 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Up\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset + ry] && [rand y - cat y offset + cat height + ry]
			if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[0] - 284 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + 32 + *(udata->ry1))) {
					*(udata->hp_pos) = 0;
					*(udata->r1_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r1_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[1] - 284 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + 32 + *(udata->ry2))) {
					*(udata->hp_pos) = 1;
					*(udata->r2_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r2_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[2] - 284 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + 32 + *(udata->ry3))) {
					*(udata->hp_pos) = 2;
					*(udata->r3_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r3_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[3] - 284 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + 32 + *(udata->ry4))) {
					*(udata->hp_pos) = 3;
					*(udata->r4_hp) -= 2;
					//Easy Rat counts as 1 kill
					if (*(udata->r4_hp) <= 0) {
						*(udata->kill_count) += 1;
					}
				}
			}
			if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
				if (*(udata->y) >= (rand_y[4] - 284 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + 32 + *(udata->ry5))) {
					*(udata->hp_pos) = 4;
					*(udata->r5_hp) -= 2;
					//Medium Rat counts as 2 kills
					if (*(udata->r5_hp) <= 0) {
						*(udata->kill_count) += 2;
					}
				}
			}

		}

		//Special Attacks
		else if ((*udata->dir == 3) && (key == KB_KEY_W))
		{
			*(udata->s) = 3 + type_i;
			if (*(udata->weapontaken) == 1) {
				if (specialattack_i >= 0) {
					*(udata->a) = 7 + specialattack_i;
				}
			}
			else *(udata->a) = 0 + specialattack_i;
			printf("Special Attack Right\n");
			//[rand x - cat x offset - cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->a) != 0) {
				if (*(udata->x) >= (rand_x[0] - 379 - 42)) {
					if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
						*(udata->hp_pos) = 0;
						*(udata->r1_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r1_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379 - 42)) {
					if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
						*(udata->hp_pos) = 1;
						*(udata->r2_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r2_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379 - 42)) {
					if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
						*(udata->hp_pos) = 2;
						*(udata->r3_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r3_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379 - 42)) {
					if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
						*(udata->hp_pos) = 3;
						*(udata->r4_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r4_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379 - 42)) {
					if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
						*(udata->hp_pos) = 4;
						*(udata->r5_hp) -= 2;
						//Medium Rat counts as 2 kills
						if (*(udata->r5_hp) <= 0) {
							*(udata->kill_count) += 2;
						}
					}
				}
			}

		}
		else if ((*udata->dir == 2) && (key == KB_KEY_W))
		{
			*(udata->s) = 2 + type_i;
			if (*(udata->weapontaken) == 1) {
				if (specialattack_i >= 0) {
					*(udata->a) = 7 + specialattack_i;
				}
			}
			else *(udata->a) = 0 + specialattack_i;
			printf("Special Attack Left\n");
			//[rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->a) != 0) {
				if (*(udata->x) <= (rand_x[0] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
						*(udata->hp_pos) = 0;
						*(udata->r1_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r1_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) <= (rand_x[1] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
						*(udata->hp_pos) = 1;
						*(udata->r2_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r2_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) <= (rand_x[2] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
						*(udata->hp_pos) = 2;
						*(udata->r3_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r3_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) <= (rand_x[3] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
						*(udata->hp_pos) = 3;
						*(udata->r4_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r4_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) <= (rand_x[4] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
						*(udata->hp_pos) = 4;
						*(udata->r5_hp) -= 2;
						//Medium Rat counts as 2 kills
						if (*(udata->r5_hp) <= 0) {
							*(udata->kill_count) += 2;
						}
					}
				}
			}

		}
		else if ((*udata->dir == 1) && (key == KB_KEY_W))
		{
			*(udata->s) = 1 + type_i;
			if (*(udata->weapontaken) == 1) {
				if (specialattack_i >= 0) {
					*(udata->a) = 7 + specialattack_i;
				}
			}
			else *(udata->a) = 0 + specialattack_i;
			printf("Special Attack Down\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset - cat height + ry] && [rand y - cat y offset + ry]
			if (*(udata->a) != 0) {
				if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[0] - 284 - 32 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + *(udata->ry1))) {
						*(udata->hp_pos) = 0;
						*(udata->r1_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r1_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[1] - 284 - 32 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + *(udata->ry2))) {
						*(udata->hp_pos) = 1;
						*(udata->r2_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r2_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[2] - 284 - 32 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + *(udata->ry3))) {
						*(udata->hp_pos) = 2;
						*(udata->r3_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r3_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[3] - 284 - 32 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + *(udata->ry4))) {
						*(udata->hp_pos) = 3;
						*(udata->r4_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r4_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[4] - 284 - 32 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + *(udata->ry5))) {
						*(udata->hp_pos) = 4;
						*(udata->r5_hp) -= 2;
						//Medium Rat counts as 2 kills
						if (*(udata->r5_hp) <= 0) {
							*(udata->kill_count) += 2;
						}
					}
				}
			}

		}
		else if ((*udata->dir == 0) && (key == KB_KEY_W))
		{
			*(udata->s) = 0 + type_i;
			if (*(udata->weapontaken) == 1) {
				if (specialattack_i >= 0) {
					*(udata->a) = 7 + specialattack_i;
				}
			}
			else *(udata->a) = 0 + specialattack_i;
			printf("Special Attack Up\n");
			//[rand x - cat x offset - cat width] && [rand x - cat x offset + cat width]
			//[rand y - cat y offset + ry] && [rand y - cat y offset + cat height + ry]
			if (*(udata->a) != 0) {
				if (*(udata->x) >= (rand_x[0] - 379 - 42) && *(udata->x) <= (rand_x[0] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[0] - 284 + *(udata->ry1)) && *(udata->y) <= (rand_y[0] - 284 + 32 + *(udata->ry1))) {
						*(udata->hp_pos) = 0;
						*(udata->r1_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r1_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[1] - 379 - 42) && *(udata->x) <= (rand_x[1] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[1] - 284 + *(udata->ry2)) && *(udata->y) <= (rand_y[1] - 284 + 32 + *(udata->ry2))) {
						*(udata->hp_pos) = 1;
						*(udata->r2_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r2_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[2] - 379 - 42) && *(udata->x) <= (rand_x[2] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[2] - 284 + *(udata->ry3)) && *(udata->y) <= (rand_y[2] - 284 + 32 + *(udata->ry3))) {
						*(udata->hp_pos) = 2;
						*(udata->r3_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r3_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[3] - 379 - 42) && *(udata->x) <= (rand_x[3] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[3] - 284 + *(udata->ry4)) && *(udata->y) <= (rand_y[3] - 284 + 32 + *(udata->ry4))) {
						*(udata->hp_pos) = 3;
						*(udata->r4_hp) -= 2;
						//Easy Rat counts as 1 kill
						if (*(udata->r4_hp) <= 0) {
							*(udata->kill_count) += 1;
						}
					}
				}
				if (*(udata->x) >= (rand_x[4] - 379 - 42) && *(udata->x) <= (rand_x[4] - 379 + 42)) {
					if (*(udata->y) >= (rand_y[4] - 284 + *(udata->ry5)) && *(udata->y) <= (rand_y[4] - 284 + 32 + *(udata->ry5))) {
						*(udata->hp_pos) = 4;
						*(udata->r5_hp) -= 2;
						//Medium Rat counts as 2 kills
						if (*(udata->r5_hp) <= 0) {
							*(udata->kill_count) += 2;
						}
					}
				}
			}

		}

		//Change Cats
		else if (key == KB_KEY_1)
		{
			type_i = 0;
			heavyattack_i = 0;
			*(udata->cat_type) = 1;
			*(udata->dir) = 1;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Bengal\n");
		}
		else if (key == KB_KEY_2)
		{
			type_i = 4;
			heavyattack_i = 3;
			*(udata->cat_type) = 2;
			*(udata->dir) = 1;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Burmilla\n");
		}
		else if (key == KB_KEY_3)
		{
			type_i = 8;
			heavyattack_i = 1;
			*(udata->cat_type) = 3;
			*(udata->dir) = 1;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Persian\n");
		}
		else if (key == KB_KEY_4)
		{
			type_i = 12;
			heavyattack_i = 2;
			*(udata->cat_type) = 4;
			*(udata->dir) = 1;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Siamese\n");
		}
		else if (key == KB_KEY_5)
		{
			type_i = 16;
			heavyattack_i = 4;
			*(udata->cat_type) = 5;
			*(udata->dir) = 1;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Sphynx\n");
		}

		//Weapons
		else if (key == KB_KEY_Z)
		{
			specialattack_i = 7;
			printf("Flamethrower\n");
		}
		else if (key == KB_KEY_X)
		{
			specialattack_i = 8;
			printf("Taser\n");
		}
		else if (key == KB_KEY_C)
		{
			specialattack_i = 9;
			printf("Sword\n");
		}

		//Start Menu Boundaries
		if (*(udata->m) == 0) {
			if (*(udata->ub_y_off) < 247)
				*(udata->ub_y_off) = 247;
			else if (*(udata->ub_y_off) > 365)
				*(udata->ub_y_off) = 365;
		}

		//Upgrades Menu Boundaries
		if (*(udata->m) == 1) {
			if (*(udata->ub_x_off) < 0)
				*(udata->ub_x_off) = 0;
			else if (*(udata->ub_x_off) > 256)
				*(udata->ub_x_off) = 256;
		}

		// For Map 1 Object Collision
		if (*(udata->m) == 3) {
			//F2_Bedroom Walls
			//Top
			if (*(udata->y) < 0)
				*(udata->y) = 0;
			if (*(udata->x) < 0 && *(udata->y) == 0)
				*(udata->x) = 0;
			//Bottom
			if (*(udata->y) > 690)
				*(udata->y) = 690;
			//Left
			if (*(udata->x) < -200)
				*(udata->x) = -200;
			//Right
			if (*(udata->x) > 750)
				*(udata->x) = 750;
			// table
			if ((*(udata->y) < 40 && *(udata->x) < -50) && (*(udata->y) < 40 && *(udata->x) > -140)) {
				if (*(udata->y) == 30) {
					*(udata->y) = 40;
					*(udata->x) = *(udata->x);
				}
				else {
					if (*(udata->x) == -60)
						*(udata->x) = -50;
					else if (*(udata->x) == -130)
						*(udata->x) = -140;
					*(udata->y) = *(udata->y);
				}
			}
			// tree
			if (*(udata->y) < 10 && *(udata->x) < -190) {
				if (*(udata->y) == 0) {
					*(udata->y) = 10;
					*(udata->x) = *(udata->x);
				}
				else {
					if (*(udata->x) == -180)
						*(udata->x) = -190;
					*(udata->y) = *(udata->y);
				}
			}
			// shelf
			if ((*(udata->y) > 30 && *(udata->x) < -180) && (*(udata->y) < 330 && *(udata->x) < -180)) {
				if (*(udata->x) == -190) {
					*(udata->y) = *(udata->y);
					*(udata->x) = -180;
				}
				else {
					if (*(udata->y) == 40)
						*(udata->y) = 30;
					else if (*(udata->y) == 320)
						*(udata->y) = 330;
					*(udata->x) = *(udata->x);
				}
			}
			// workstation
			if ((*(udata->y) > 330 && *(udata->x) < -70) && (*(udata->y) < 410 && *(udata->x) < -70)) {
				if (*(udata->x) == -80) {
					*(udata->y) = *(udata->y);
					*(udata->x) = -70;
				}
				else {
					if (*(udata->y) == 340)
						*(udata->y) = 330;
					else if (*(udata->y) == 400)
						*(udata->y) = 410;
					*(udata->x) = *(udata->x);
				}
			}
			// drawer top
			if ((*(udata->y) > 460 && *(udata->x) < -40) && (*(udata->y) < 510 && *(udata->x) < -40)) {
				if (*(udata->x) == -50) {
					*(udata->y) = *(udata->y);
					*(udata->x) = -40;
				}
				else {
					if (*(udata->y) == 470)
						*(udata->y) = 460;
					else if (*(udata->y) == 500)
						*(udata->y) = 510;
					*(udata->x) = *(udata->x);
				}
			}
			// drawer middle
			if ((*(udata->y) > 500 && *(udata->x) < -170) && (*(udata->y) < 600 && *(udata->x) < -170)) {
				if (*(udata->x) == -180) {
					*(udata->y) = *(udata->y);
					*(udata->x) = -170;
				}
			}
			// drawer bottom
			if ((*(udata->y) > 590 && *(udata->x) < -70) && (*(udata->y) < 640 && *(udata->x) < -70)) {
				if (*(udata->x) == -80) {
					*(udata->y) = *(udata->y);
					*(udata->x) = -70;
				}
				else {
					if (*(udata->y) == 630)
						*(udata->y) = 640;
					else if (*(udata->y) == 600)
						*(udata->y) = 590;
					*(udata->x) = *(udata->x);
				}
			}
			// table
			if ((*(udata->y) > 590 && *(udata->y) < 660 && *(udata->x) < -140) && (*(udata->y) > 590 && *(udata->y) < 660 && *(udata->x) > -180)) {
				if (*(udata->y) == 650) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 660;
				}
				else {
					if (*(udata->x) == -150)
						*(udata->x) = -140;
					else if (*(udata->x) == -170)
						*(udata->x) = -180;
					*(udata->y) = *(udata->y);
				}
			}
			// more shelves
			if ((*(udata->y) > 490 && *(udata->x) > 330) && (*(udata->y) > 490 && *(udata->x) < 410)) {
				if (*(udata->y) == 500) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 490;
				}
				else {
					if (*(udata->x) == 340)
						*(udata->x) = 330;
					else if (*(udata->x) == 400)
						*(udata->x) = 410;
					*(udata->y) = *(udata->y);
				}
			}
			if ((*(udata->y) > 490 && *(udata->y) < 590 && *(udata->x) > 110) && (*(udata->y) > 490 && *(udata->y) < 590 && *(udata->x) < 410)) {
				if (*(udata->y) == 500) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 490;
				}
				else if (*(udata->y) == 580) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 590;
				}
				else {
					if (*(udata->x) == 120)
						*(udata->x) = 110;
					else if (*(udata->x) == 400)
						*(udata->x) = 410;
					*(udata->y) = *(udata->y);
				}
			}
			// dining
			if ((*(udata->y) > 330 && *(udata->y) < 420 && *(udata->x) > 190) && (*(udata->y) > 330 && *(udata->y) < 420 && *(udata->x) < 290)) {
				if (*(udata->y) == 340) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 330;
				}
				else if (*(udata->y) == 410) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 420;
				}
				else {
					if (*(udata->x) == 200)
						*(udata->x) = 190;
					else if (*(udata->x) == 280)
						*(udata->x) = 290;
					*(udata->y) = *(udata->y);
				}
			}
			// dividers
			if ((*(udata->y) > 150 && *(udata->y) < 210 && *(udata->x) > 50) && (*(udata->y) > 150 && *(udata->y) < 210 && *(udata->x) < 400)) {
				if (*(udata->y) == 160) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 150;
				}
				else if (*(udata->y) == 200) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 210;
				}
				else {
					if (*(udata->x) == 60)
						*(udata->x) = 50;
					else if (*(udata->x) == 390)
						*(udata->x) = 400;
					*(udata->y) = *(udata->y);
				}
			}
			if ((*(udata->y) > 180 && *(udata->y) < 240 && *(udata->x) > 110) && (*(udata->y) > 180 && *(udata->y) < 240 && *(udata->x) < 340)) {
				if (*(udata->y) == 190) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 180;
				}
				else if (*(udata->y) == 230) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 240;
				}
				else {
					if (*(udata->x) == 120)
						*(udata->x) = 110;
					else if (*(udata->x) == 330)
						*(udata->x) = 340;
					*(udata->y) = *(udata->y);
				}
			}
			// harp
			if ((*(udata->y) > 220 && *(udata->y) < 270 && *(udata->x) > 200) && (*(udata->y) > 220 && *(udata->y) < 270 && *(udata->x) < 250)) {
				if (*(udata->y) == 230) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 220;
				}
				else if (*(udata->y) == 260) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 270;
				}
				else {
					if (*(udata->x) == 210)
						*(udata->x) = 200;
					else if (*(udata->x) == 240)
						*(udata->x) = 250;
					*(udata->y) = *(udata->y);
				}
			}
			// bed
			if ((*(udata->y) < 100 && *(udata->x) < 260) && (*(udata->y) < 100 && *(udata->x) > 160)) {
				if (*(udata->y) == 90) {
					*(udata->y) = 100;
					*(udata->x) = *(udata->x);
				}
				else {
					if (*(udata->x) == 250)
						*(udata->x) = 260;
					else if (*(udata->x) == 170)
						*(udata->x) = 160;
					*(udata->y) = *(udata->y);
				}
			}
			// drawer
			if ((*(udata->y) < 20 && *(udata->x) < 420) && (*(udata->y) < 20 && *(udata->x) > 320)) {
				if (*(udata->y) == 10) {
					*(udata->y) = 20;
					*(udata->x) = *(udata->x);
				}
				else {
					if (*(udata->x) == 410)
						*(udata->x) = 420;
					else if (*(udata->x) == 330)
						*(udata->x) = 320;
					*(udata->y) = *(udata->y);
				}
			}
			// right side
			if ((*(udata->y) > 40 && *(udata->y) < 180 && *(udata->x) > 470) && (*(udata->y) > 40 && *(udata->y) < 180 && *(udata->x) < 570)) {
				if (*(udata->y) == 50) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 40;
				}
				else if (*(udata->y) == 170) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 180;
				}
				else {
					if (*(udata->x) == 480)
						*(udata->x) = 470;
					else if (*(udata->x) == 560)
						*(udata->x) = 570;
					*(udata->y) = *(udata->y);
				}
			}
			if ((*(udata->y) > 150 && *(udata->y) < 210 && *(udata->x) > 490) && (*(udata->y) > 150 && *(udata->y) < 210 && *(udata->x) < 540)) {
				if (*(udata->y) == 160) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 150;
				}
				else if (*(udata->y) == 200) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 210;
				}
				else {
					if (*(udata->x) == 500)
						*(udata->x) = 490;
					else if (*(udata->x) == 530)
						*(udata->x) = 540;
					*(udata->y) = *(udata->y);
				}
			}
			if ((*(udata->y) > 80 && *(udata->x) > 470) && (*(udata->y) < 180 && *(udata->x) > 470)) {
				if (*(udata->x) == 480) {
					*(udata->y) = *(udata->y);
					*(udata->x) = 470;
				}
				else {
					if (*(udata->y) == 90)
						*(udata->y) = 80;
					else if (*(udata->y) == 170)
						*(udata->y) = 180;
					*(udata->x) = *(udata->x);
				}
			}
			if (*(udata->y) < 180 && *(udata->x) > 720) {
				if (*(udata->x) == 730) {
					*(udata->y) = *(udata->y);
					*(udata->x) = 720;
				}
			}
			if (*(udata->y) < 10 && *(udata->x) > 580) {
				if (*(udata->x) == 590) {
					*(udata->y) = *(udata->y);
					*(udata->x) = 580;
				}
				else {
					*(udata->y) = 10;
					*(udata->x) = *(udata->x);
				}
			}
			if ((*(udata->y) > 190 && *(udata->x) > 580) && (*(udata->y) < 290 && *(udata->x) > 580)) {
				if (*(udata->x) == 590) {
					*(udata->y) = *(udata->y);
					*(udata->x) = 580;
				}
				else {
					if (*(udata->y) == 200)
						*(udata->y) = 190;
					else if (*(udata->y) == 280)
						*(udata->y) = 290;
					*(udata->x) = *(udata->x);
				}
			}
			if ((*(udata->y) > 490 && *(udata->y) < 650 && *(udata->x) > 480) && (*(udata->y) > 490 && *(udata->y) < 650 && *(udata->x) < 670)) {
				if (*(udata->y) == 500) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 490;
				}
				else if (*(udata->y) == 640) {
					*(udata->x) = *(udata->x);
					*(udata->y) = 650;
				}
				else {
					if (*(udata->x) == 490)
						*(udata->x) = 480;
					else if (*(udata->x) == 660)
						*(udata->x) = 670;
					*(udata->y) = *(udata->y);
				}
			}
		}
	}
}
