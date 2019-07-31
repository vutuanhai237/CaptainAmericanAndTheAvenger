#pragma once
#define BOSS_WIZARD_SCREEN_WIDTH 256
#define BOSS_WIZARD_SCREEN_HEIGHT 224
// U-MAX ZONE
#define BOSS_WIZARD_U_MAX_LEFT_X 24
#define BOSS_WIZARD_U_MAX_LEFT_Y 40
#define BOSS_WIZARD_U_MAX_RIGHT_X 230
#define BOSS_WIZARD_U_MAX_RIGHT_Y 40
// U-MIN ZONE

class BossWizardRoad
{
public:
	enum RoadType {
		idle, // đ** làm gì
		u_max, // bay hết máp
		u_normal, // bay cự li hơn nữa máp
		u_min, // tắt điện
		jump, // nhảy cự li gần theo parapol
		switch_off, // tắt điện
		beaten
	};
	virtual void Update(float dt) = 0;
	void SetType(RoadType type);
	RoadType GetCurrentRoad();
	void SetCurrentRoad(RoadType road);
	// general zone
	bool IsContinute;
	bool GetOneTime;
	RoadType type;
	BossWizardRoad();
	~BossWizardRoad();
protected:
	RoadType current_road;

};

