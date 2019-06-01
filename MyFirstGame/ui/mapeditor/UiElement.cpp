#include "UiElement.hpp"
#include <imgui.h>

UiElement::UiElement(const float width, const float height, const float x, const float y)
	:
	width_(width),
	height_(height),
	x_(x),
	y_(y)
{
}

bool UiElement::is_mouse_inside() const
{
	const auto mouse = ImGui::GetMousePos();

	const auto start_x = x_;
	const auto start_y = y_;

	const auto end_x = x_ + width_;
	const auto inside_x = mouse.x > start_x && mouse.x < end_x;

	if (!isVisible_)
	{
		const auto inside_tb_x = inside_x;
		const auto inside_tb_y = mouse.y > start_y && mouse.y < (start_y + 30);

		return inside_tb_x && inside_tb_y;
	}

	const auto end_y = y_ + height_;
	const auto inside_y = mouse.y > start_y && mouse.y < end_y;

	return inside_x && inside_y;
}

void UiElement::connect_callback(UiElementCallbackInterface* cb)
{
	cb_ = cb;
}
