#pragma once
#include <dsound.h>
#include <unordered_map>
#include "dsutil.h"

class SoundManager
{
public:
	enum SoundList
	{
		main_theme,
		actiton_theme,
		boss_wizard_theme,
		boss_gragas_theme,
		entity_explode,
		enemy_fire,
		boss_moving_firing,
		wizard_laze,
		door,
		item_holder,
		item_nomal,
		item_exit_orb,
		item_hp,
		player_dash,
		player_dead,
		player_diving,
		player_drown,
		player_punch_kick,
		player_rolling,
		player_stand,
		shield_attack,
		shield_collision,
	};

	static SoundManager *GetInstance();
	HRESULT Init(HWND hwnd);
	void LoadResources();
	void Release();

	HRESULT Play(int index);
	HRESULT PlayRepeat(int index);
	HRESULT Stop(int index);
	void StopAllSound();
private:
	SoundManager();
	~SoundManager();

	static SoundManager* Instance;
	std::unordered_map<int, CSound *> sounds;
	CSoundManager *csound;
};