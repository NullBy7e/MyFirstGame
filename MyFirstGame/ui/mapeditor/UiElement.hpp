#pragma once
#include "UiElementCallbackInterface.hpp"

class UiElement  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
{
public:
	explicit UiElement(float width, float height, float x, float y);
	bool is_mouse_inside() const;
	virtual ~UiElement() = default;

	virtual void draw() = 0;
	void connect_callback(UiElementCallbackInterface *cb);

	bool isVisible_{};
protected:
	float width_;
	float height_;

	float x_;
	float y_;

	UiElementCallbackInterface* cb_{};
};

