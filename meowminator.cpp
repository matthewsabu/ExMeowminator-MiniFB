#include <stdlib.h>
#include "include/MiniFB_cpp.h"
#include "include/MiniFB.h"
#include "include/FreeImage.h"

void key_press(struct mfb_window* window, mfb_key key, mfb_key_mod mod, bool isPressed);

typedef struct
{
	int *x;
	int *x_old;
	int *y;
	int *y_old;
	int *s;

	int *map_x; 
	int *map_y; 
	//int *map_change;
	int *m;
	int *map_ctr;

	int* a;
	int* dir;
	int* cat_type;
} user_data;

int main()
{
	printf("Hello Framebuffer!");

	struct mfb_window* window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
	if (!window)
		return 0;

	user_data udata;

	uint32_t* buffer = (uint32_t*)malloc(1100 * 833 * 4);

	//FIBITMAP* fi_bg = FreeImage_Load(FIF_JPEG, "assets/bg.jpg");
	//FreeImage_FlipVertical(fi_bg);
	//uint8_t* bg = FreeImage_GetBits(fi_bg);

	FIBITMAP* fi_bg1 = FreeImage_Load(FIF_JPEG, "assets_meow/f2_bedroom_new.jpg");
	FreeImage_FlipVertical(fi_bg1);
	uint8_t* bg1 = FreeImage_GetBits(fi_bg1);

	FIBITMAP* fi_bg2 = FreeImage_Load(FIF_JPEG, "assets_meow/f3_bathroom.jpg");
	FreeImage_FlipVertical(fi_bg2);
	uint8_t* bg2 = FreeImage_GetBits(fi_bg2);

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

	//// Copies the full background to the framebuffer
	//for (int i = 0; i < map_x *  map_y * 3; i += 3)
	//	buffer[i / 3] = (bg2[i + 2] << 16) | (bg2[i + 1] << 8) | bg2[i];

	mfb_set_keyboard_callback(window, key_press);
	mfb_set_user_data(window, (void *)& udata);

	do {
		static int map_x = 1100; //988
		static int map_y = 833; //1062
		//static int map_change = 0;
		static int m = 0;
		static int map_ctr = 0;

		uint8_t* maps[2] = { bg1, bg2 };

		udata.map_x = &map_x;
		udata.map_y = &map_y;
		//udata.map_change = &map_change;
		udata.m = &m;
		udata.map_ctr = &map_ctr;
		
		// Copies the full background to the framebuffer
		//if (map_change == 0) {
		//	if (map_ctr > 0 && map_ctr < 2) {
		//		buffer = (uint32_t*)malloc(map_x * map_y * 4);
		//		printf("CHANGING MAP! = %d\n", map_ctr);
		//		map_ctr = 0;
		//		printf("CHANGED MAP! = %d\n\n", map_ctr);
		//	}

		//	for (int i = 0; i < map_x * map_y * 3; i += 3)
		//		buffer[i / 3] = (maps[m][i + 2] << 16) | (maps[m][i + 1] << 8) | maps[m][i];
		//}
		//else if (map_change == 1) {
		//	if (map_ctr > 0 && map_ctr < 2) {
		//		buffer = (uint32_t*)malloc(map_x * map_y * 4);
		//		printf("CHANGING MAP! = %d\n", map_ctr);
		//		map_ctr = 0;
		//		printf("CHANGED MAP! = %d\n\n", map_ctr);
		//	}

		//	for (int i = 0; i < map_x * map_y * 3; i += 3)
		//		buffer[i / 3] = (maps[m][i + 2] << 16) | (maps[m][i + 1] << 8) | maps[m][i];
		//}

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
		static int a = 0;
		static int dir = 1;
		static int cat_type = 1;
		uint8_t* sprites[20] = { sprite2, sprite3, sprite4, sprite5, sprite6, sprite7, sprite8, sprite9, sprite10, sprite11, sprite12, sprite13, sprite14, sprite15, sprite16, sprite17, sprite18, sprite19, sprite20, sprite21 };
		uint8_t* attacks[12] = { NoAttack , light_attack, bite, furball_spit, mega_meow, tail_slap, telekinesis, flamethrower_attack, taser_attack, sword_attack };

		udata.x = &bg_x;
		udata.x_old = &bg_x_old;

		udata.y = &bg_y;
		udata.y_old = &bg_y_old;

		udata.s = &s;

		udata.a = &a;
		udata.dir = &dir;
		udata.cat_type = &cat_type;

		// Redraw the background 
		// 10k pixels
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 42; j++)
			{
				uint8_t r = maps[m][map_x * 3 * (i + bg_y_old + 277) + 3 * (bg_x_old + j + 377) + 2];
				uint8_t g = maps[m][map_x * 3 * (i + bg_y_old + 277) + 3 * (bg_x_old + j + 377) + 1];
				uint8_t b = maps[m][map_x * 3 * (i + bg_y_old + 277) + 3 * (bg_x_old + j + 377)];
				uint32_t pixel = (r << 16) | (g << 8) | b;
				if (pixel)
					buffer[map_x * (i + bg_y_old + 277) + (j + bg_x_old + 377)] = pixel; //-- CENTER
			}
		}

		// Change sprite used depending on direction
		// Draws the sprite over the background in the framebuffer
		// 10k pixels
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 42; j++)
			{
				uint8_t r = sprites[s][42 * 4 * i + 4 * j + 2];
				uint8_t g = sprites[s][42 * 4 * i + 4 * j + 1];
				uint8_t b = sprites[s][42 * 4 * i + 4 * j];
				uint32_t pixel = (r << 16) | (g << 8) | b;
				if (pixel)
					buffer[map_x * (i + bg_y + 277) + (j + bg_x + 377)] = pixel; //-- CENTER
			}
		}

		if (dir == 3) {
			// Draws the attack over the background in the framebuffer
			// 10k pixels
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
			// Draws the attack over the background in the framebuffer
			// 10k pixels
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
			// Draws the attack over the background in the framebuffer
			// 10k pixels
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
			// Draws the attack over the background in the framebuffer
			// 10k pixels
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

void key_press(struct mfb_window* window, mfb_key key, mfb_key_mod mod, bool isPressed)
{
	static int type_i = 0;
	static int heavyattack_i = 0;
	static int specialattack_i = 0;
	user_data* udata = (user_data *)mfb_get_user_data(window);
	if (isPressed)
	{
		//MAPS
		if (key == KB_KEY_N) {
			*(udata->map_x) = 1100;
			*(udata->map_y) = 833;
			//*(udata->map_change) = 0;
			*(udata->m) = 0;
			*(udata->map_ctr) += 1;
			printf("CHANGING MAP! = %d\n", *(udata->map_ctr));
		}
		
		if (key == KB_KEY_M) {
			*(udata->map_x) = 988;
			*(udata->map_y) = 1062;
			//*(udata->map_change) = 1;
			*(udata->m) = 1;
			*(udata->map_ctr) += 1;
			printf("CHANGING MAP! = %d\n", *(udata->map_ctr));
		}

		//MOVEMENT
		if (key == KB_KEY_LEFT)
		{
			*(udata->dir) = 2;
			*(udata->x_old) = *(udata->x);
			*(udata->x) -= 10;
			*(udata->s) = 2 + type_i;
			*(udata->a) = 0;
			printf("Left\n");
		}
		else if (key == KB_KEY_RIGHT)
		{
			*(udata->dir) = 3;
			*(udata->x_old) = *(udata->x);
			*(udata->x) += 10;
			*(udata->s) = 3 + type_i;
			*(udata->a) = 0;
			printf("Right\n");
		}
		else if (key == KB_KEY_UP)
		{
			*(udata->dir) = 0;
			*(udata->y_old) = *(udata->y);
			*(udata->y) -= 10;
			*(udata->s) = 0 + type_i;
			*(udata->a) = 0;
			printf("Up\n");
		}
		else if (key == KB_KEY_DOWN)
		{
			*(udata->dir) = 1;
			*(udata->y_old) = *(udata->y);
			*(udata->y) += 10;
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0;
			printf("Down\n");
		}

		//Light Attack
		else if ((*udata->dir == 3) && (key == KB_KEY_A))
		{
			*(udata->s) = 3 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Right\n");
		}
		else if ((*udata->dir == 2) && (key == KB_KEY_A))
		{
			*(udata->s) = 2 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Left\n");
		}
		else if ((*udata->dir == 1) && (key == KB_KEY_A))
		{
			*(udata->s) = 1 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Down\n");
		}
		else if ((*udata->dir == 0) && (key == KB_KEY_A))
		{
			*(udata->s) = 0 + type_i;
			*(udata->a) = 1;
			printf("Light Attack Up\n");
		}

		//Heavy Attacks
		else if ((*udata->dir == 3) && (key == KB_KEY_S))
		{
			*(udata->s) = 3 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Right\n");
		}
		else if ((*udata->dir == 2) && (key == KB_KEY_S))
		{
			*(udata->s) = 2 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Left\n");
		}
		else if ((*udata->dir == 1) && (key == KB_KEY_S))
		{
			*(udata->s) = 1 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Down\n");
		}
		else if ((*udata->dir == 0) && (key == KB_KEY_S))
		{
			*(udata->s) = 0 + type_i;
			*(udata->a) = 2 + heavyattack_i;
			printf("Heavy Attack Up\n");
		}

		//Special Attacks
		else if ((*udata->dir == 3) && (key == KB_KEY_W))
		{
			*(udata->s) = 3 + type_i;
			*(udata->a) = 0 + specialattack_i;
			printf("Special Attack Right\n");
		}
		else if ((*udata->dir == 2) && (key == KB_KEY_W))
		{
			*(udata->s) = 2 + type_i;
			*(udata->a) = 0 + specialattack_i;
			printf("Special Attack Left\n");
		}
		else if ((*udata->dir == 1) && (key == KB_KEY_W))
		{
			*(udata->s) = 1 + type_i;
			*(udata->a) = 0 + specialattack_i;
			printf("Special Attack Down\n");
		}
		else if ((*udata->dir == 0) && (key == KB_KEY_W))
		{
			*(udata->s) = 0 + type_i;
			*(udata->a) = 0 + specialattack_i;
			printf("Special Attack Up\n");
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

		//if (*(udata->x) < -(*(mdata->map_x))) //left border
		//	*(udata->x) = -(*(mdata->map_x));
		//else if (*(udata->x) >= (*(mdata->map_x))) //right border
		//	*(udata->x) = (*(mdata->map_x));

		//if (*(udata->y) < -(*(mdata->map_y))) //top border
		//	*(udata->y) = (*(mdata->map_y));
		//else if (*(udata->y) >= (*(mdata->map_y))) //bottom border
		//	*(udata->y) = (*(mdata->map_y));
	}
}