﻿#pragma once

enum ICollidableType
{
    T_Player,
    T_Enemy,
    T_Block,
    T_Bullet,
	T_Exit
};

enum LayerType
{
	L_EntityPlacement,
    L_TerrainObject,
    L_Ground,
};

enum DirectionType
{
	Dir_Up = 0,
	Dir_Right = 1,
	Dir_Down = 2,
	Dir_Left = 3
};

enum SceneType
{
	Sc_None,
	Sc_Title,
	Sc_Game,
	Sc_Gameover,
    Sc_GameClear,
};

namespace EnemyType
{
	enum EnemyType
	{
		Slime,
		WhiteEye,
		Ghost,
		Skelton
	};
}

namespace GameSceneTransitionType
{
	enum State
	{
		None,
		Starting,
		Ending,
	};
}
