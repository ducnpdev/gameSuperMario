#pragma once
// define number config
#define number_square_scene_1  48
#define ID_TEXTURE_BACKGROUND_SCENE_1   100
// windown console -- main.cpp
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Game Mario"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(176, 244, 248) 
#define SCREEN_WIDTH 270
#define SCREEN_HEIGHT 262
#define MAX_FRAME_RATE 120
#define STATE_NUMBER_DIE 9999
#define STATE_GOOMBA_DIE 10000
#define STATE_MONEY_DIE 10001
#define STATE_MUSHROOM_DIE 10002
#define STATE_LEAF_DIE 10003
// define number
#define NUMBER_AM_1 -1
#define NUMBER_0 0
#define NUMBER_1 1
#define NUMBER_2 2
#define NUMBER_3 3
#define NUMBER_4 4
#define NUMBER_5 5
#define NUMBER_6 6
#define NUMBER_7 7
#define NUMBER_8 8
#define NUMBER_9 9
#define NUMBER_10 10
#define NUMBER_16 16
#define NUMBER_70 70
#define NUMBER_100 100
#define NUMBER_150 150
#define NUMBER_250 250
#define NUMBER_300 300
#define NUMBER_1000 1000

// time all item 
#define LEAF_TIME 5000
// define Untouchable; 0 is touchable, 1 is untouchable
#define Touchable 0
#define UnTouchable 1
#define NumberZero 0
#define Modify_BBOX 12
#define GRAVITY 0.0005f
#define TIME_DIE 500
// setting start screen game and background -- Game.cpp
#define MAX_GAME_LINE 1024
#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2

// define Number
#define NUMBER_BBOX_WIDTH  10
#define NUMBER_BBOX_HEIGHT 10
#define NUMBER_POSITION_MOVEMENT 40
#define NUMBER_FLY_SPEED 0.05f

#define NUMBER_STATE_FLY 100
#define NUMBER_ANI_DISAPPEAR 0

// define Brick
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_ANIMATION 100
#define BRICK_STATE_DIE 200
#define BRICK_STATE_DONE 999

#define BRICK_ANI_ANIMATION 0
#define BRICK_ANI_DIE 1

#define BRICK_ITEM_RENDER_MONEY 1
#define BRICK_ITEM_RENDER_NUMBER 2
#define BRICK_ITEM_RENDER_MUSHROOM 3
#define BRICK_ITEM_RENDER_LEAF 4

// Define Common 
#define COMMON_GRAVITY			0.0005f
// setting animation id in animation_set
#define MARIO_ANI_DIE				        0
#define MARIO_ANI_IDLE_RIGHT		        1
#define MARIO_ANI_IDLE_LEFT			        2
#define MARIO_ANI_WALKING_RIGHT			    3
#define MARIO_ANI_WALKING_LEFT			    4
#define MARIO_ANI_SIT_DOWN_RIGHT            5
#define MARIO_ANI_SIT_DOWN_LEFT             6
#define MARIO_ANI_ATTACT_RIGHT              7
#define MARIO_ANI_ATTACT_LEFT               8
#define MARIO_ANI_JUMP_RIGHT                9
#define MARIO_ANI_JUMP_LEFT                 10

#define MARIO_BIG_ANI_IDLE_RIGHT		    11
#define MARIO_BIG_ANI_IDLE_LEFT			    12
#define MARIO_BIG_ANI_WALKING_RIGHT			13
#define MARIO_BIG_ANI_WALKING_LEFT			14
#define MARIO_BIG_ANI_JUMP_RIGHT            15
#define MARIO_BIG_ANI_JUMP_LEFT             16
#define MARIO_ANI_LEVEL_1_TO_2_RIGHT             17

#define MARIO_BIG_ATTACT_ANI_IDLE_RIGHT		    18
#define MARIO_BIG_ATTACT_ANI_IDLE_LEFT			    19
#define MARIO_BIG_ATTACT_ANI_WALKING_RIGHT			20
#define MARIO_BIG_ATTACT_ANI_WALKING_LEFT			21
#define MARIO_BIG_ATTACT_ANI_JUMP_RIGHT            22
#define MARIO_BIG_ATTACT_ANI_JUMP_LEFT             23
#define MARIO_BIG_ANI_SIT_DOWN_RIGHT            24
#define MARIO_BIG_ANI_SIT_DOWN_LEFT             25
#define MARIO_BIG_ATTACT_ANI_SIT_DOWN_RIGHT            26
#define MARIO_BIG_ATTACT_ANI_SIT_DOWN_LEFT             27
#define MARIO_ANI_LEVEL_3_ATTAT_RIGHT            28
#define MARIO_ANI_LEVEL_3_ATTAT_LEFT             29
#define MARIO_ANI_LEVEL_1_TO_2_LEFT             30
#define MARIO_ANI_LEVEL_2_TO_3_RIGHT             31
#define MARIO_ANI_SWING_TAIL_RIGHT             32
#define MARIO_ANI_SWING_TAIL_LEFT             33
#define MARIO_ANI_FLY_LEFT             34
#define MARIO_ANI_FLY_RIGHT             35

#define MARIO_WITH_TAIL_ATTACK_TIME		300

// define type object and scene session 
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP	10 

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1

#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_MORNINGSTAR  4
#define OBJECT_TYPE_FIRE  5
#define OBJECT_TYPE_GOOMBA	6
#define OBJECT_TYPE_MONEY	8
#define OBJECT_TYPE_BRICK_FLOOR	9
#define OBJECT_TYPE_NUMBER	10
#define OBJECT_TYPE_CLOUD 11
#define OBJECT_TYPE_MUSHROOM 12
#define OBJECT_TYPE_TURTLE 13
#define OBJECT_TYPE_SQUARE 14
#define OBJECT_TYPE_GOOMBA_FLY 15
#define OBJECT_TYPE_LEAF	16
#define OBJECT_TYPE_TURTLE_JUMP	17
#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_HOLD	57
#define OBJECT_TYPE_TAIL	58
#define OBJECT_TYPE_FLOWER	150
// type intro 70 -> 90
#define OBJECT_TYPE_INTRO_PLAYER 70
#define OBJECT_TYPE_INTRO_PLAYER_SECOND 71
#define OBJECT_TYPE_INTRO_NUMBER_THREE 73
#define OBJECT_TYPE_INTRO_LEAF 74
#define OBJECT_TYPE_INTRO_TURTLE 75
#define OBJECT_TYPE_INTRO_DOOR 76
#define OBJECT_TYPE_INTRO_MUSHROOM 77
#define OBJECT_TYPE_INTRO_STAR 78
#define OBJECT_TYPE_INTRO_GOOMBA 79
#define OBJECT_TYPE_INTRO_TURTLE_BLACK 80
#define OBJECT_TYPE_INTRO_TURTLE_ANIMATION 81
#define OBJECT_TYPE_INTRO_BACKGROUND 82
#define OBJECT_TYPE_INTRO_BACKGROUND_SUPER 83

#define OBJECT_TYPE_WORLD_MAP_ANIMATION 84
#define OBJECT_TYPE_WORLD_MAP_MARIO_PLAYER 85

#define OBJECT_TYPE_HUD 86

// type = 151 la bong hoa di chuyen ma ko ban dan
#define OBJECT_TYPE_FLOWER_TYPE2	151
#define OBJECT_TYPE_FLOWER_COLLISION_BROKENT	153

#define OBJECT_TYPE_BULLET	21
#define OBJECT_TYPE_WALL_HEIGHT	23

#define MAX_SCENE_LINE 1024

// define scene id 
#define ID_SCENE_1  1
#define ID_SCENE_2  2
#define ID_SCENE_3  3

// define morning star
#define mstar_level_1   1
#define mstar_level_2   2
#define mstar_level_3   3

#define MSTAR_ANI_ATTACT_RIGHT_LEVEL_1      0
#define MSTAR_ANI_ATTACT_LEFT_LEVEL_1       1
#define MSTAR_ANI_ATTACT_RIGHT_LEVEL_2      2
#define MSTAR_ANI_ATTACT_LEFT_LEVEL_2       3
#define MSTAR_ANI_ATTACT_RIGHT_LEVEL_3      4
#define MSTAR_ANI_ATTACT_LEFT_LEVEL_3       5

#define MSTAR_BBOX_WIDTH  27
#define MSTAR_BBOX_HEIGHT 15

// defint Money
#define MONEY_POSITION_MOVEMENT 40
#define MONEY_FLY_SPEED 0.05f
#define MONEY_BOX_WIDTH 16
#define MONEY_BOX_HEIGHT 15

#define MONEY_STATE_FLY 100
#define MONEY_STATE_DISAPPEAR 200
#define MONEY_ANI_DISAPPEAR 0
#define MONEY_ANI_FLY 1

// define Brick Floor
#define BRICK_FLOOR_BOX_WIDTH 16
#define BRICK_FLOOR_BOX_HEIGHT 16


// define Mario
#define DIRECTION_RIGHT_X 1
#define DIRECTION_LEFT_X -1
#define PLUS_POSITION_Y 20
#define TIME_RESET_ACTTACK 450
#define DEVIATION_ATTACK_BEHIND_X  7
#define DEVIATION_ATTACK_FRONT_X  23
#define DEVIATION_ACTTACK_Y 18
#define TIME_MARIO_UP_DOWN_LEVEL 700

#define TIME_MARIO_UNTOUCHABLE 2000

#define MARIO_WALKING_SPEED_NORMAL		0.07f 
#define MARIO_WALKING_SPEED_PAST		0.1f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_SPEED_Y_LEVEL_2		0.47f
#define MARIO_JUMP_SPEED_Y_SWING_TAIL		0.25f

#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_GRAVITY_SWING_TAIL			0.00005f

#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_RIGHT_PAST	150
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_SIT_DOWN		400
#define MARIO_STATE_ATTACT			500
#define MARIO_STATE_DIE				600
#define MARIO_STATE_LEVEL_1_TO_2			700
#define MARIO_STATE_LEVEL_2_TO_3			800

#define MARIO_STATE_LEVEL_3_ATTACK_FRAME_1			900
#define MARIO_STATE_LEVEL_3_ATTACK_FRAME_2			1000
#define MARIO_STATE_LEVEL_3_ATTACK_FRAME_3			1100
#define MARIO_STATE_SWING_TAIL			1200
#define MARIO_STATE_FLY			1300

#define	MARIO_LEVEL_1	1
#define	MARIO_LEVEL_2		2
#define	MARIO_LEVEL_3		3

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_LEVEL3_BBOX_WIDTH  22

#define MARIO_BIG_BBOX_HEIGHT 27
//#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_ATTACT_BBOX_WIDTH  23
#define MARIO_BIG_ATTACT_BBOX_HEIGHT 27
#define MARIO_BIG_ATTACT_SITDOWN_BBOX_WIDTH  16
#define MARIO_BIG_ATTACT_SITDOWN_BBOX_HEIGHT 21
#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

// define Cloud
#define CLOUD_BBOX_WIDTH 30
#define CLOUD_BBOX_HEIGHT 30
#define CLOUD_ANI 0

// define mushroom
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_ANI_WALKING 0
#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_WALKING_SPEED 0.05f
#define MUSHROOM_GRAVITY	0.03f

// define  turtle 
#define BORDER_LEFT 512
#define BORDER_RIGHT 592
#define TURTLE_WALKING_SPEED 0.05f;
#define TURTLE_WALKING_SPEED_DIE 0.3f;

#define TURTLE_BBOX_WIDTH_BIG 19
#define TURTLE_BBOX_HEIGHT_BIG 27
#define TURTLE_BBOX_WIDTH_SMAILL 19
#define TURTLE_BBOX_HEIGHT_SMAILL 18
#define TURTLE_STATE_WALKING_RIGHT 100
#define TURTLE_STATE_WALKING_LEFT 150

#define TURTLE_STATE_DIE 200
#define TURTLE_STATE_DIE_MOVING_RIGHT 300
#define TURTLE_STATE_DIE_MOVING_LEFT 400
#define TURTLE_ANI_WALKING_RIGHT  1
#define TURTLE_ANI_WALKING_LEFT  0
#define TURTLE_ANI_DIE 2
// #define TURTLE_ANI_FLY 3

// define turtle jump
#define TURTLE_JUMP_INTERVAL			1500
#define TURTLE_JUMP_SPEED_VX			0.03f

#define TURTLE_JUMP_STATE_FLY 100
#define TURTLE_JUMP_STATE_WALKING 200
#define TURTLE_JUMP_STATE_DIE 300
#define TURTLE_JUMP_STATE_DIE_MOVING_RIGHT 400
#define TURTLE_JUMP_STATE_DIE_MOVING_LEFT 500

#define TURTLE_JUMP_ANI_FLY_LEFT  0
#define TURTLE_JUMP_ANI_WALKING_LEFT 1
#define TURTLE_JUMP_ANI_DIE 2
#define TURTLE_JUMP_ANI_DIE_MOVING 3


// define square
 #define SQUAREE_BOX_WIDTH 27
#define SQUAREE_BOX_HEIGHT 2

// define Goomba
#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_FLY 2
#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9
#define GOOMBA_BBOX_HEIGHT_FLY 23
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_START_DIE 300
// define Goomba Fly
#define TIME_GOOMBA_FLY_UNTOUCHABLE 500
#define GOOMBA_FLY_SPEED_Y		0.2f
#define GOOMBA_FLY_DEVIATION_Y 30
#define GOOMBA_FLY_WALKING_SPEED 0.03f;
#define GOOMBA_FLY_GRAVITY			0.0005f
#define GOOMBA_FLY_JUMP_INTERVAL			1500

#define GOOMBA_FLY_BBOX_WIDTH 16
#define GOOMBA_FLY_BBOX_HEIGHT 15
#define GOOMBA_FLY_BBOX_HEIGHT_DIE 9
#define GOOMBA_FLY_BBOX_HEIGHT_FLY 23
#define GOOMBA_FLY_STATE_WALKING 200
#define GOOMBA_FLY_STATE_DIE 100
#define GOOMBA_FLY_STATE_FLY 300

#define GOOMBA_FLY_ANI_WALKING 0
#define GOOMBA_FLY_ANI_DIE 1
#define GOOMBA_FLY_ANI_FLY 2

// define Hold
#define HOLD_ANI_WIDTH 0
#define HOLD_ANI_HEIGHT 1

// play scence
#define STOP_TIME_DURATION 1000

// Item Damage
#define ITEM_DAMAGE_LEVEL_1 1
#define ITEM_DAMAGE_LEVEL_2 2
#define ITEM_DAMAGE_LEVEL_3 3

#define ITEM_DAMAGE_BOX_WIDTH_l1 10
#define ITEM_DAMAGE_BOX_HEIGHT_l1 7
#define ITEM_DAMAGE_BOX_WIDTH_l2 13
#define ITEM_DAMAGE_BOX_HEIGHT_l2 10
#define ITEM_DAMAGE_BOX_WIDTH_l3 16
#define ITEM_DAMAGE_BOX_HEIGHT_l3 10

#define ITEM_DAMAGE_ANI_Level_1  0
#define ITEM_DAMAGE_ANI_Level_2  1
#define ITEM_DAMAGE_ANI_Level_3 2

#define ITEMDAMAGE_STATE_DIE 0
#define ITEMDAMAGE_STATE_NORMAL 1

// define Leaf
#define LEAF_STATE_FLY 100
#define LEAF_STATE_DISAPPEAR 200
#define LEAF_ANI_DISAPPEAR 0
#define LEAF_ANI_FLY 1
#define LEAF_FLY_SPEED 0.05f
#define LEAF_BOX_WIDTH 16
#define LEAF_BOX_HEIGHT 15
#define LEAF_POSITION_MOVEMENT 40
#define TIME_FLY_LEAF 500

// define flower not bullet, animation
#define FLOWER_FLY_ANI_TYPE2 0
#define FLOWER_SPEED 0.05f

// define flower have bullet
#define FLOWER_FLY_ANI_0 0
#define FLOWER_FLY_ANI_1 1
#define FLOWER_FLY_ANI_DIE 2
#define FLOWER_FLY_ANI_DIE 3

#define FLOWER_STATE_INOPEN_MOUTH 100
#define FLOWER_STATE_OPEN_MOUTH 200
#define FLOWER_DIE_STATE 300

#define FLOWER_SPEED_Y 0.03f 
#define FLOWER_POSITION_MOVEMENT 35
#define TIME_APPEAR 3000
#define TIME_APPEAR1 1000

// 
#define FLOWER_RED_ANI_OPEN_MOUTH_BELOW_LEFT 0
#define FLOWER_RED_ANI_INOPEN_MOUTH_BELOW_LEFT 1
#define FLOWER_RED_ANI_OPEN_MOUTH_ABOVE_LEFT 2
#define FLOWER_RED_ANI_INOPEN_MOUTH_ABOVE_LEFT 3

#define FLOWER_RED_ANI_INOPEN_MOUTH_ABOVE_RIGHT 4
#define FLOWER_RED_ANI_OPEN_MOUTH_ABOVE_RIGHT 5
#define FLOWER_RED_ANI_INOPEN_MOUTH_BELOW_RIGHT 6
#define FLOWER_RED_ANI_OPEN_MOUTH_BELOW_RIGHT 7



#define FLOWER_BLUE_ANI_OPEN_MOUTH_BELOW_LEFT 8
#define FLOWER_BLUE_ANI_INOPEN_MOUTH_BELOW_LEFT 9
#define FLOWER_BLUE_ANI_OPEN_MOUTH_ABOVE_LEFT 10
#define FLOWER_BLUE_ANI_INOPEN_MOUTH_ABOVE_LEFT 11

#define FLOWER_BLUE_ANI_INOPEN_MOUTH_ABOVE_RIGHT 12
#define FLOWER_BLUE_ANI_OPEN_MOUTH_ABOVE_RIGHT 13
#define FLOWER_BLUE_ANI_INOPEN_MOUTH_BELOW_RIGHT 14
#define FLOWER_BLUE_ANI_OPEN_MOUTH_BELOW_RIGHT 15
////
#define FLOWER_RED_STATE_OPEN_MOUTH_BELOW_LEFT 0
#define FLOWER_RED_STATE_INOPEN_MOUTH_BELOW_LEFT 1
#define FLOWER_RED_STATE_OPEN_MOUTH_ABOVE_LEFT 2
#define FLOWER_RED_STATE_INOPEN_MOUTH_ABOVE_LEFT 3

#define FLOWER_RED_STATE_INOPEN_MOUTH_ABOVE_RIGHT 4
#define FLOWER_RED_STATE_OPEN_MOUTH_ABOVE_RIGHT 5
#define FLOWER_RED_STATE_INOPEN_MOUTH_BELOW_RIGHT 6
#define FLOWER_RED_STATE_OPEN_MOUTH_BELOW_RIGHT 7

#define FLOWER_BLUE_STATE_OPEN_MOUTH_BELOW_LEFT 8
#define FLOWER_BLUE_STATE_INOPEN_MOUTH_BELOW_LEFT 9
#define FLOWER_BLUE_STATE_OPEN_MOUTH_ABOVE_LEFT 10
#define FLOWER_BLUE_STATE_INOPEN_MOUTH_ABOVE_LEFT 11

#define FLOWER_BLUE_STATE_INOPEN_MOUTH_ABOVE_RIGHT 12
#define FLOWER_BLUE_STATE_OPEN_MOUTH_ABOVE_RIGHT 13
#define FLOWER_BLUE_STATE_INOPEN_MOUTH_BELOW_RIGHT 14
#define FLOWER_BLUE_STATE_OPEN_MOUTH_BELOW_RIGHT 15

// flower type 2
#define FLOWER_BLUE_ANI_OPEN 0
#define FLOWER_BLUE_ANI_INOPEN 1

#define FLOWER_BLUE_STATE_OPEN 0
#define FLOWER_BLUE_STATE_INOPEN 1


// define bullet
#define BULLET_FLY_SPEED_Y 0.03f
#define BULLET_FLY_SPEED_X 0.03f
#define BULLET_BBOX_HEIGHT 10
#define BULLET_BBOX_WIDTH 10
#define BULLET_FLY_ANI 0
#define BULLET_STATE_FLY 100
#define BULLET_POSITION_Y 3

// define 
#define BRICK_COLLISION_BROKENT_ANI 0

// Define Tile Map with ID
// world 1 phia trne
#define WORLD1 1
// world 1 phia duoi
#define WORLD2 2
#define WORLD4 4

// background intro tile map
#define INTRO_BACKGROUND 3

// ******************* //
// *    define intro   *// 
// ******************* //

// player First
#define INTRO_PLAYER_BIG_ANI_IDLE_RIGHT		    0
#define INTRO_PLAYER_BIG_ANI_IDLE_LEFT			1
#define INTRO_PLAYER_BIG_ANI_WALKING_RIGHT		2
#define INTRO_PLAYER_BIG_ANI_WALKING_LEFT	    3
#define INTRO_PLAYER_BIG_ANI_JUMP_RIGHT          4
#define INTRO_PLAYER_BIG_ANI_JUMP_LEFT           5
#define INTRO_PLAYER_BIG_ANI_SITDOWN_RIGHT           6
#define INTRO_PLAYER_BIG_ANI_SITDOWN_LEFT           7

#define INTRO_PLAYER_BIG_STATE_RIGHT	100
#define INTRO_PLAYER_BIG_STATE_LEFT			200
#define INTRO_PLAYER_BIG_STATE_WALKING_RIGHT		300
#define INTRO_PLAYER_BIG_STATE_WALKING_LEFT	    400
#define INTRO_PLAYER_BIG_STATE_IDLE_WALKING_RIGHT		500
#define INTRO_PLAYER_BIG_STATE_IDLE_WALKING_LEFT		600
#define INTRO_PLAYER_BIG_STATE_JUMP_RIGHT          700
#define INTRO_PLAYER_BIG_STATE_JUMP_LEFT           800
#define INTRO_PLAYER_BIG_STATE_DOWN_RIGHT          900
#define INTRO_PLAYER_BIG_STATE_DOWN_LEFT           1000
#define INTRO_PLAYER_BIG_STATE_JUMP_RIGHT_1 1100
#define INTRO_PLAYER_BIG_STATE_DOWN_RIGHT_1 1200
#define INTRO_PLAYER_BIG_STATE_OUT_MAP 1300
#define INTRO_PLAYER_BIG_STATE_LEVEL2_WALKING_LEFT		1400


// player Second
#define INTRO_PLAYER_SECOND_BIG_ANI_IDLE_RIGHT		    0
#define INTRO_PLAYER_SECOND_BIG_ANI_IDLE_LEFT			1
#define INTRO_PLAYER_SECOND_BIG_ANI_WALKING_RIGHT		2
#define INTRO_PLAYER_SECOND_BIG_ANI_WALKING_LEFT	    3
#define INTRO_PLAYER_SECOND_BIG_ANI_JUMP_RIGHT          4
#define INTRO_PLAYER_SECOND_BIG_ANI_JUMP_LEFT           5
#define INTRO_PLAYER_SECOND_BIG_ANI_SITDOWN_RIGHT       6
#define INTRO_PLAYER_SECOND_BIG_ANI_SITDOWN_LEFT        7
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_WAG_RIGHT        8
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_WAG_LEFT         9
#define INTRO_PLAYER_SECOND_LEVEL2_ANI_JUMP_RIGHT       10
#define INTRO_PLAYER_SECOND_LEVEL2_ANI_JUMP_LEFT        11
#define INTRO_PLAYER_SECOND_ANI_LEVEL2_LEVEL3           12
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_WALK_RIGHT       13
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_WALK_LEFT        14
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_KICK_RIGHT       15
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_KICK_LEFT        16
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_IDLE_RIGHT       17
#define INTRO_PLAYER_SECOND_LEVEL3_ANI_IDLE_LEFT       18

#define INTRO_PLAYER_SECOND_BIG_STATE_RIGHT	100
#define INTRO_PLAYER_SECOND_BIG_STATE_LEFT			200
#define INTRO_PLAYER_SECOND_BIG_STATE_WALKING_RIGHT		300
#define INTRO_PLAYER_SECOND_BIG_STATE_WALKING_LEFT	    400
#define INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_RIGHT		500
#define INTRO_PLAYER_SECOND_BIG_STATE_IDLE_WALKING_LEFT		600
#define INTRO_PLAYER_SECOND_BIG_STATE_JUMP_RIGHT          700
#define INTRO_PLAYER_SECOND_BIG_STATE_JUMP_LEFT           800
#define INTRO_PLAYER_SECOND_BIG_STATE_DOWN_RIGHT          900
#define INTRO_PLAYER_SECOND_BIG_STATE_DOWN_LEFT           1000
#define INTRO_PLAYER_SECOND_BIG_STATE_JUMP_RIGHT_1      1100
#define INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_RIGHT          1200
#define INTRO_PLAYER_SECOND_BIG_STATE_SITDOWN_LEFT           1300
#define INTRO_PLAYER_SECOND_BIG_STATE_JUMP_COLLISION_WITH_LEAF    1400
#define INTRO_PLAYER_SECOND_LEVEL3_STATE_JUMP_WAG_TAIL    1500
#define INTRO_PLAYER_SECOND_STATE_LEVEL2_TO_LEVEL3    1600
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_RIGHT    1700
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_WALK_LEFT    1800

#define INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_RIGHT    1900
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_KICK_LEFT    2000
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT    2100
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_LEFT    2200

#define INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_COLLISION_TURTLE    2300
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_COLLISION_TURTLE    2400
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_JUMP_TIME_2_COLLISION_TURTLE    2500
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_DOWN_TIME_2_COLLISION_TURTLE    2600

#define INTRO_PLAYER_SECOND_STATE_LEVEL3_IDLE_RIGHT_SESSION2    2700
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_LEFT_SESSION2    2800
#define INTRO_PLAYER_SECOND_STATE_LEVEL3_WALKING_RIGHT_SESSION2    2900

// define turtle
#define INTRO_TURTLE_ANI_IDLE    0
#define INTRO_TURTLE_ANI_WALK    1
#define INTRO_TURTLE_ANI_DIE     2

#define INTRO_TURTLE_STATE_IDLE	100
#define INTRO_TURTLE_STATE_WALK_RIGHT	200
#define INTRO_TURTLE_STATE_DIE	300
#define INTRO_TURTLE_STATE_OUT_MAP	400
#define INTRO_TURTLE_STATE_WALK_LEFT 500
#define INTRO_TURTLE_STATE_WALK_LEFT_FAST 600
#define INTRO_TURTLE_STATE_IDLE_COLIISION_ABOVE_PLAYERSECOND 700
#define INTRO_TURTLE_STATE_WALK_RIGHT_SESSION2 800
#define INTRO_TURTLE_STATE_WALK_RIGHT_FAST_SESSION2 900

// define turtle Black
#define INTRO_TURTLE_BLACK_ANI_IDLE    0
#define INTRO_TURTLE_BLACK_ANI_WALK    1

#define INTRO_TURTLE_BLACK_STATE_IDLE	100
#define INTRO_TURTLE_BLACK_STATE_WALK	200

// define turtle animation
#define INTRO_TURTLE_ANIMATION_ANI_WALK    0

#define INTRO_TURTLE_ANIMATION_STATE_WALK	100

// define Star
#define INTRO_STAR_STATE_INIT   100
#define INTRO_STAR_STATE_FLY   200
#define INTRO_STAR_STATE_DOWN   300

// define leaf
#define INTRO_LEAF_ANI_RIGHT    0
#define INTRO_LEAF_ANI_LEFT		1

#define INTRO_LEAF_STATE_INIT   100
#define INTRO_LEAF_STATE_DIRECTION_NAGETIVE  200 // CHANGE DIRECTION -X
#define INTRO_LEAF_STATE_DIRECTION_POSITIVE  300 // CHANGE DIRECTION X

// define goomba
#define INTRO_GOOMBA_ANI_IDLE    0
#define INTRO_GOOMBA_ANI_WALK    1
#define INTRO_GOOMBA_ANI_DIE    2

#define INTRO_GOOMBA_STATE_IDLE	100
#define INTRO_GOOMBA_STATE_WALK	200
#define INTRO_GOOMBA_STATE_DIE	300

// define turtle black
#define INTRO_TURTLE_BLACK_ANI_IDLE    0
#define INTRO_TURTLE_BLACK_ANI_FLY    1

#define INTRO_TURTLE_BLACK_STATE_IDLE	100
#define INTRO_TURTLE_BLACK_STATE_FLY	200
#define INTRO_TURTLE_BLACK_STATE_DOWN	300

// define background mau den phia sau
#define INTRO_BACKGROUND_ANI_INIT  0
#define INTRO_BACKGROUND_STATE_INIT	100

// define background Super mario
#define INTRO_BACKGROUND_SUPER_ANI_INIT  0
#define INTRO_BACKGROUND_SUPER_STATE_INIT	100

// ******************* //
// *    World Map   *// 
// ******************* //

// define Mario World Map
#define WORLD_MAP_MARIO_LEVEL1_ANI_IDLE 0

#define WORLD_MAP_MARIO_LEVEL1_STATE_IDLE 100
#define WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_RIGHT 200
#define WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_LEFT 300
#define WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_DOWN 400
#define WORLD_MAP_MARIO_LEVEL1_STATE_WALKING_UP 500
#define WORLD_MAP_MARIO_SWITCH_SCENE 600

#define WORLD_MAP_MARIO_LEVEL_1 1

// define ani
#define WORLD_MAP_ANI_MOVING 0
#define WORLD_MAP_ANI_DOOR1 1
#define WORLD_MAP_ANI_DOOR2 2
#define WORLD_MAP_ANI_DOOR3 3
#define WORLD_MAP_ANI_DOOR4 4
#define WORLD_MAP_ANI_DOOR5 5
#define WORLD_MAP_ANI_DOOR6 6
#define WORLD_MAP_ANI_WORD_HELP 7
// enemis moving
#define WORLD_MAP_ANI_ENEMIES_MOVE_RIGHT 8
#define WORLD_MAP_ANI_ENEMIES_MOVE_LEFT 9
// 3 bit
#define WORLD_MAP_ANI_CASINO 10
#define WORLD_MAP_ANI_START 11
#define WORLD_MAP_ANI_CAU 12

#define WORLD_MAP_STATE_INIT 100

// define tile Background
#define TILE_MAP_SCENE_1_SQUARE 176
#define TILE_MAP_SCENE_2_SQUARE 32
#define TILE_MAP_SCENE_WOLRD_MAP_SQUARE 16

