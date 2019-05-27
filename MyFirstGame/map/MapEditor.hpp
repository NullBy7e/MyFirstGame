#pragma once

#include "../drawables/Grid.hpp"
#include "Map.hpp"
#include <optional>
#include "TileSet.hpp"
#include "../ui/MapEditorUI.hpp"
#include "Sprite.hpp"
#include "../external/SFML-2.5.1/x86/include/SFML/Window/Mouse.hpp"
#include "Tile.hpp"

namespace sf {
	class Event;
}

class Window;

class MapEditor
{
public:
	/**
	 * \brief Constructs a new map editor.
	 * \param map The map that this editor is for.
	 */
	explicit MapEditor(const Map& map);

	/**
	 * \brief Constructs a new map editor but without a map to edit.
	 */
	MapEditor();

	/**
	 * \brief renders the map editor, should be called every game loop.
	 * \param window the window to render this map editor unto.
	 */
	void render(Window& window);
	
	/**
	 * \brief processes an event.
	 * \param event the event to process.
	 */
	void process_event(const sf::Event& event);

	/**
	 * \return vector of available tilesets.
	 */
	std::vector<TileSet>& get_tilesets();

	/**
	 * \return the name of the map that this editor is for.
	 */
	std::string& get_map_name();

	/**
	 * \return the description of the map that this editor is for.
	 */
	std::string& get_map_desc();

	/**
	 * \brief sets the selected sprite.
	 * \param tile_set the tileset that the sprite belongs to.
	 * \param sprite_index the tileset index of the sprite.
	 */
	void set_selected_sprite(TileSet& tile_set, const int sprite_index);

	/**
	 * \return the selected sprite wrapped in a shared_ptr.
	 */
	std::shared_ptr<Sprite>& get_selected_sprite();

	/**
	 * \brief returns the column and row number relative to the given mouse pos.
	 * \param mouse_pos the position of the mouse.
	 * \return 
	 */
	std::pair<unsigned int, unsigned int> get_column_row_at_mouse_pos(sf::Vector2i mouse_pos);

	/**
	 * \brief adds the selected sprite to the tile that's positioned relative to the mouse pos.
	 * \param mouse_pos the position of the mouse.
	 */
	void add_selected_sprite_to_tile(sf::Vector2i mouse_pos);

	/**
	 * \brief removes the clicked tile.
	 * \param mouse_pos the position of the mouse.
	 */
	void clear_clicked_tile(sf::Vector2i mouse_pos);

	/**
	 * \brief clears the selected sprite.
	 */
	void clear_selected_sprite();
private:
	/**
	 * \brief loads the tilesets for this map editor.
	 * \return true or false depending on whether the tilesets could be loaded.
	 */
	bool load_tilesets();

	/**
	 * \brief the MapEditorUi UI component.
	 */
	MapEditorUi ui_{ *this };

	/**
	 * \brief the Grid UI component of the map editor.
	 */
	std::optional<Grid> grid_;

	/**
	 * \brief the map that this map editor edits, optional because a map editor isn't required to have a map to edit by default.
	 */
	std::optional<Map> map_;

	/**
	 * \brief the tilesets that are available in the map editor.
	 */
	std::vector<TileSet> tilesets_;

	/**
	 * \brief the selected sprite (accessed and changed by UI components).
	 */
	std::shared_ptr<Sprite> selectedSprite_;

	/**
	 * \brief used to track whether a mouse button is currently pressed.
	 */
	bool mouseButtonPressed_{};

	/**
	 * \brief contains the last recorded mouse button on a mouseButtonPressed event.
	 */
	sf::Mouse::Button mouseButton_{};
};

