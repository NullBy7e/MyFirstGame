#pragma once
class TileSet;

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
/**
 * \brief Callback interface used to communicate with UiElement objects.
 */
class UiElementCallbackInterface
{
public:
	virtual void cb_tilepicker_sprite_selected(TileSet& tileset, unsigned int sprite_index) = 0;
};
