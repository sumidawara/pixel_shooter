#pragma once

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
	Sc_Gameover
};

namespace EnemyType
{
	enum EnemyType
	{
		Slime
	};
}
