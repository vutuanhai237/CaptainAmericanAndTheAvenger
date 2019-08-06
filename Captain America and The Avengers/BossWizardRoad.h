#pragma once

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
		beaten // bị đánh trúng
	};

	virtual void Update(float dt) = 0;
	RoadType current_road;
	// get
	RoadType GetCurrentRoad();
	// set
	void SetCurrentRoad(RoadType road);
	// properties
	bool IsContinute;
	bool GetOneTime;
	BossWizardRoad();
	~BossWizardRoad();
};

