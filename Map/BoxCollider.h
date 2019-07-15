#pragma once
#include <d3dx9.h>
class BoxCollider {
public :
	float top;
	float left;
	float bot;
	float right;
	BoxCollider() {
		top = left = bot = right = 0;
	}
	BoxCollider(float _top, float _left, float _bot, float _right) {
		top = _top;
		left = _left;
		bot = _bot;
		right = _right;
	}
	BoxCollider(D3DXVECTOR2 position, float width, float height) {
		// toạ độ tâm
		top = position.y + height / 2;
		bot = top - height;
		left = position.x - width / 2;
		right = left + width;
	}
	D3DXVECTOR2 GetCenterPosition() {
		return D3DXVECTOR2((left + right) / 2.0f, (top + bot) / 2.0f);
	}

	float GetWidth() { return right - left; }
	float GetHeight() { return top - bot; }
	void Multiply(float x) {
		top *= x;bot *= x;left *= x;right *= x;
	}
	void Moving(D3DXVECTOR2 velocity, float dt) {
		top += velocity.y*dt;
		left += velocity.x*dt;
		bot += velocity.y*dt;
		right += velocity.x;
	}


};