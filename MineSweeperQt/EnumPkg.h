#ifndef ENUMPKG_H
#define ENUMPKG_H

enum DifficultyEnum
{
    Difficulty_Easy = 0,
    Difficulty_Medium = 1,
    Difficulty_Hard = 2,
    Difficulty_NotSelected = 3
};

enum MineStatusEnum
{
	MineStatus_NotExist = 0,
	MineStatus_Exist = 1
};

enum TileStatusEnum
{
	TileStatus_Unopened = 0,
	TileStatus_Flagged = 1,
	TileStatus_Opened = 2
};

enum ResultEnum
{
	Result_Success = 0,
	Result_MemoryAllocationError = 1
};

enum UserActionEnum
{
	UserAction_Flag = 0,
	UserAction_Open = 1,
	UserAction_Count = 2
};

enum GameStatusEnum
{
	GameStatus_InProgress = 0,
	GameStatus_Lose = 1,
	GameStatus_Win = 2
};

#endif // ENUMPKG_H
