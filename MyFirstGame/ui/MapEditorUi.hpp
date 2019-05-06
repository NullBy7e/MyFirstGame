#pragma once
#include <imgui.h>

class MapEditor;

class MapEditorUi
{
public:
	explicit MapEditorUi(MapEditor& map_editor);
	void render();

private:
	void map_name_text_input() const;
	void map_desc_text_input() const;

	void tileset_combo();
	void tileset_info() const;
	void tileset_sprites() const;

	int tilesetComboSelectedItemIndex_ = -1;

	bool propertiesTabEnabled_ = true;
	bool tilesetsTabEnabled_ = true;

	MapEditor& mapEditor_;
};

