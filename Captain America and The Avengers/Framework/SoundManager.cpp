#include "SoundManager.h"

SoundManager *SoundManager::Instance = NULL;

SoundManager *SoundManager::GetInstance()
{
	if (!Instance)
		Instance = new SoundManager();
	return Instance;
}

HRESULT SoundManager::Init(HWND hwnd)
{
	return csound->Initialize(hwnd, DSSCL_PRIORITY);
}

void SoundManager::LoadResources()
{
	csound->Create(&sounds[main_theme], const_cast<LPTSTR>(L"Resources/Sound/main_theme.wav"));
	csound->Create(&sounds[actiton_theme], const_cast<LPTSTR>(L"Resources/Sound/action_theme.wav")); 
	csound->Create(&sounds[boss_wizard_theme], const_cast<LPTSTR>(L"Resources/Sound/boss_wizard_theme.wav"));
	csound->Create(&sounds[boss_gragas_theme], const_cast<LPTSTR>(L"Resources/Sound/boss_gragas_theme.wav"));
	csound->Create(&sounds[entity_explode], const_cast<LPTSTR>(L"Resources/Sound/entity_explode.wav"));
	csound->Create(&sounds[enemy_fire], const_cast<LPTSTR>(L"Resources/Sound/enemy_fire.wav"));
	csound->Create(&sounds[boss_moving_firing], const_cast<LPTSTR>(L"Resources/Sound/boss_moving_firing.wav"));
	csound->Create(&sounds[wizard_laze], const_cast<LPTSTR>(L"Resources/Sound/wizard_laze.wav"));
	csound->Create(&sounds[door], const_cast<LPTSTR>(L"Resources/Sound/door.wav"));
	csound->Create(&sounds[item_holder], const_cast<LPTSTR>(L"Resources/Sound/item_holder.wav"));
	csound->Create(&sounds[item_nomal], const_cast<LPTSTR>(L"Resources/Sound/item_nomal.wav"));
	csound->Create(&sounds[item_exit_orb], const_cast<LPTSTR>(L"Resources/Sound/item_exit_orb.wav"));
	csound->Create(&sounds[item_hp], const_cast<LPTSTR>(L"Resources/Sound/item_hp.wav"));
	csound->Create(&sounds[player_dash], const_cast<LPTSTR>(L"Resources/Sound/player_dash.wav"));
	csound->Create(&sounds[player_dead], const_cast<LPTSTR>(L"Resources/Sound/player_dead.wav"));
	csound->Create(&sounds[player_diving], const_cast<LPTSTR>(L"Resources/Sound/player_diving.wav"));
	csound->Create(&sounds[player_drown], const_cast<LPTSTR>(L"Resources/Sound/player_drown.wav"));
	csound->Create(&sounds[player_punch_kick], const_cast<LPTSTR>(L"Resources/Sound/player_punch_kick.wav"));
	csound->Create(&sounds[player_rolling], const_cast<LPTSTR>(L"Resources/Sound/player_rolling.wav"));
	csound->Create(&sounds[player_stand], const_cast<LPTSTR>(L"Resources/Sound/player_stand.wav"));
	csound->Create(&sounds[shield_attack], const_cast<LPTSTR>(L"Resources/Sound/shield_attack.wav"));
	csound->Create(&sounds[shield_collision], const_cast<LPTSTR>(L"Resources/Sound/shield_collision.wav"));
}

HRESULT SoundManager::Play(int index)
{
	if (sounds[index]->IsSoundPlaying())
		sounds[index]->Reset();
	return sounds[index]->Play();
}

HRESULT SoundManager::PlayRepeat(int index)
{
	if (sounds[index]->IsSoundPlaying())
		sounds[index]->Reset();
	return sounds[index]->Play(0, DSBPLAY_LOOPING);
}

HRESULT SoundManager::Stop(int index)
{
	HRESULT ret = sounds[index]->Stop();
	if (ret != S_OK) return ret;
	ret = sounds[index]->Reset();
	return ret;
}

void SoundManager::StopAllSound()
{
	for (auto item : sounds)
		if (item.second->IsSoundPlaying())
			this->Stop(item.first);
}

void SoundManager::Release()
{
	delete Instance;
	Instance = NULL;
}

SoundManager::SoundManager()
{
	csound = new CSoundManager();
}

SoundManager::~SoundManager()
{
	for (auto item : sounds)
	{
		if (item.second->IsSoundPlaying())
			item.second->Stop();
		delete item.second;
	}
	delete csound;
}

