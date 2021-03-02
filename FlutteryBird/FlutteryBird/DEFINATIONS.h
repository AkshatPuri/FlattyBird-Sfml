#pragma once


#define SCREEN_WIDTH 768/1.5
#define SCREEN_HEIGHT 1024/1.5
	
#define SPLASH_STATE_SHOW_TIME 2.0

#define SPLASH_SCREEN_BACKGROUND_FILEPATH "Resources/LogoWeb.png"

#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/MainMenuBg.png"
#define GAME_BACKGROUND_FILEPATH "Resources/MainMenuBg.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/MainMenuBg.png"

#define PLAY_BUTTON_FILEPATH "Resources/PlayButton.png"
#define MAIN_MENU_TITLE_FILEPATH "Resources/Title.png"
#define GAME_OVER_BODY_FILEPATH "Resources/GameOverContainer.png"

#define GAME_OVER_TITLE_FILEPATH "Resources/GameOverTitle.png"
#define RETRY_BUTTON_FILEPATH "Resources/PlayButton.png"


#define BIRD_FRAME1_FILEPATH "Resources/Bird1.png"
#define BIRD_FRAME2_FILEPATH "Resources/Bird2.png"
#define BIRD_FRAME3_FILEPATH "Resources/Bird3.png"
#define BIRD_FRAME4_FILEPATH "Resources/Bird4.png"

#define FONT "Resources/AldotheApache.ttf"

#define OBSTACLE_UP_FILEPATH "Resources/PipeUp.png"
#define OBSTACLE_BOTTOM_FILEPATH "Resources/PipeDown.png"
#define SCORE_PIPE_FILEPATH "Resources/ScorePipe.png"
#define LAND_FILEPATH "Resources/Land.png"

#define PIPE_MOVEMENT_SPEED  250.0f

#define PIPE_SPAWN_FREQUENCY  3.0f
#define BIRD_ANIMATION_DURATION .6f

#define GRAVITY 300.0f
#define FlYING_SEED 300.0f

#define FLYING_DURATION 0.2f
#define ROTATION_SPEED 100.0f

#define FLASH_SPEED 1500.0f
#define TIME_BEFORE_GAME_OVER 1.0f
#define SCORE_TEXT_ANIMATION_TIME 0.2f

#define HIT_SOUND_FILEPATH "Resources/Hit.wav"
#define POINT_SOUND_FILEPATH "Resources/Point.wav"
#define FLY_SOUND_FILEPATH "Resources/Fly.wav"


enum GameStates
{
	eReady,
	ePlaying,
	eGameOver
};