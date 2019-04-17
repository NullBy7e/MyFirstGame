/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "tmx_parser.hpp"

using namespace tinyxml2;

TmxParser::TmxParser()
{
}

TmxParser::~TmxParser()
{
}

std::map<std::string, std::string> TmxParser::getMapElementProperties(const XMLElement& mapElement)
{
	std::map<std::string, std::string> propMap;

	/* map tiledversion attribute */
	auto map_tiledversion = mapElement.Attribute("tiledversion");
	propMap["tiledversion"] = map_tiledversion;

	if (map_tiledversion != target_tiled_version)
	{
		std::cout << "tmx_parser ONLY supports version " << target_tiled_version << " of the Tiled TMX format but the target map is made with version " << map_tiledversion << std::endl;
		system("pause");

		exit(EXIT_FAILURE);
	}

	/* map version attribute */
	auto map_version = mapElement.Attribute("version");
	propMap["version"] = map_version;

	/* map orientation attribute */
	auto map_orientation = mapElement.Attribute("orientation");
	propMap["orientation"] = map_orientation;

	/* map renderorder attribute */
	auto map_renderorder = mapElement.Attribute("renderorder");
	propMap["renderorder"] = map_renderorder;

	/* map width attribute */
	auto map_width = mapElement.Attribute("width");
	propMap["width"] = map_width;

	/* map height attribute */
	auto map_height = mapElement.Attribute("height");
	propMap["height"] = map_height;

	/* map tilewidth attribute */
	auto map_tilewidth = mapElement.Attribute("tilewidth");
	propMap["tilewidth"] = map_tilewidth;

	/* map tileheight attribute */
	auto map_tileheight = mapElement.Attribute("tileheight");
	propMap["tileheight"] = map_tileheight;

	return propMap;
}

std::vector<TmxTileset> TmxParser::getMapTilesets(const XMLElement & mapElement)
{
	std::vector<TmxTileset> tilesets;

	for (auto child = mapElement.FirstChildElement("tileset"); child != NULL; child = child->NextSiblingElement("tileset"))
	{
		/* map tileset firstgid attribute */
		auto map_tileset_firstgid = cStrToInt(child->Attribute("firstgid"));

		/* map tileset name attribute */
		auto map_tileset_name = child->Attribute("name");

		/* map tileset tilewidth attribute */
		auto map_tileset_tilewidth = cStrToInt(child->Attribute("tilewidth"));

		/* map tileset tileheight attribute */
		auto map_tileset_tileheight = cStrToInt(child->Attribute("tileheight"));

		/* map tileset tilecount attribute */
		auto map_tileset_tilecount = cStrToInt(child->Attribute("tilecount"));

		/* map tileset columns attribute */
		auto map_tileset_columns = cStrToInt(child->Attribute("columns"));

		auto image = child->FirstChildElement("image");

		if (image == NULL)
		{
			std::cout << "tmx_parser failed to parse the tileset image " << map_tileset_name << std::endl;
			system("pause");

			exit(EXIT_FAILURE);
		}

		std::filesystem::path image_path = image->Attribute("source");
		auto map_tileset_image_source = std::filesystem::absolute(image_path).string();

		auto map_tileset_image_width = cStrToInt(image->Attribute("width"));
		auto map_tileset_image_height = cStrToInt(image->Attribute("height"));

		/* let's create the TmxTileset */
		TmxTileset tileset(
			map_tileset_firstgid,
			map_tileset_name,
			map_tileset_tilewidth,
			map_tileset_tileheight,
			map_tileset_tilecount,
			map_tileset_columns,
			map_tileset_image_source,
			map_tileset_image_width,
			map_tileset_image_height
		);

		/* add it to the vector */
		tilesets.push_back(tileset);
	}

	return tilesets;
}

std::vector<TmxTileLayer> TmxParser::getMapTileLayers(const XMLElement & mapElement)
{
	std::vector<TmxTileLayer> layers;

	for (auto child = mapElement.FirstChildElement("layer"); child != NULL; child = child->NextSiblingElement("layer"))
	{
		auto map_layer_id = cStrToInt(child->Attribute("id"));
		auto map_layer_name = child->Attribute("name");
		auto map_layer_width = cStrToInt(child->Attribute("width"));
		auto map_layer_height = cStrToInt(child->Attribute("height"));

		auto data_child = child->FirstChildElement("data");
		if (data_child == NULL)
		{
			std::cout << "tmx_parser failed to parse layer data of " << map_layer_name << std::endl;
			system("pause");

			exit(EXIT_FAILURE);
		}

		if (strcmp(data_child->Attribute("encoding"), "csv") == -1)
		{
			std::cout << "tmx_parser failed to parse layer data of " << map_layer_name << " - only CSV encoding is supported!" << std::endl;
			system("pause");

			exit(EXIT_FAILURE);
		}

		auto chunknullcheck = data_child->FirstChildElement("chunk");
		if (chunknullcheck != NULL)
		{
			std::vector<TmxChunk> chunks;

			for (auto chunk = data_child->FirstChildElement("chunk"); chunk != NULL; chunk = chunk->NextSiblingElement("chunk"))
			{
				auto chunk_x = cStrToFloat(chunk->Attribute("x"));
				auto chunk_y = cStrToFloat(chunk->Attribute("y"));

				auto chunk_width = cStrToInt(chunk->Attribute("width"));
				auto chunk_height = cStrToInt(chunk->Attribute("height"));

				auto chunk_csv = std::string(chunk->GetText());

				/* CSV data can contain newlines, so let's make sure to get rid of them! */
				chunk_csv.erase(std::remove(chunk_csv.begin(), chunk_csv.end(), '\n'), chunk_csv.end());

				/* split CSV data into array */
				std::vector<TmxTile> chunk_tiles;
				std::stringstream ss(chunk_csv);

				int x;
				while (ss >> x)
				{
					TmxTile tile(x);
					chunk_tiles.push_back(tile);

					if (ss.peek() == ',')
						ss.ignore();
				}

				TmxChunk tmx_chunk(chunk_x, chunk_y, chunk_width, chunk_height, chunk_tiles);
				chunks.push_back(tmx_chunk);
			}

			/* let's create the tmx layer */
			TmxTileLayer layer(map_layer_id, map_layer_name, map_layer_width, map_layer_height, chunks);

			/* add it to the vector */
			layers.push_back(layer);
		}
		else
		{
			auto map_layer_csv = std::string(data_child->GetText());

			/* CSV data can contain newlines, so let's make sure to get rid of them! */
			map_layer_csv.erase(std::remove(map_layer_csv.begin(), map_layer_csv.end(), '\n'), map_layer_csv.end());

			/* split CSV data into array */
			std::vector<TmxTile> used_tiles;
			std::stringstream ss(map_layer_csv);

			int x;
			while (ss >> x)
			{
				TmxTile tile(x);
				used_tiles.push_back(tile);

				if (ss.peek() == ',')
					ss.ignore();
			}

			/* let's create the tmx layer */
			TmxTileLayer layer(map_layer_id, map_layer_name, map_layer_width, map_layer_height, used_tiles);

			/* add it to the vector */
			layers.push_back(layer);
		}
	}

	return layers;
}

std::vector<TmxObjectLayer> TmxParser::getMapObjectLayers(const XMLElement & mapElement)
{
	std::vector<TmxObjectLayer> layers;

	for (auto child = mapElement.FirstChildElement("objectgroup"); child != NULL; child = child->NextSiblingElement("objectgroup"))
	{
		auto map_object_layer_id = cStrToInt(child->Attribute("id"));
		auto map_object_layer_name = child->Attribute("name");

		if (child->FirstChildElement("object") == NULL)
		{
			/* no reason to parse an empty object layer */
			continue;
		}

		TmxObjectLayer layer(map_object_layer_id, map_object_layer_name);
		std::vector<TmxObject> objects;

		for (auto child2 = child->FirstChildElement("object"); child2 != NULL; child2 = child2->NextSiblingElement("object"))
		{
			auto object_id = cStrToInt(child2->Attribute("id"));
			auto object_name = child2->Attribute("name");
			auto object_type = child2->Attribute("type");
			auto object_x = cStrToFloat(child2->Attribute("x"));
			auto object_y = cStrToFloat(child2->Attribute("y"));
			auto object_width = cStrToInt(child2->Attribute("width"));
			auto object_height = cStrToInt(child2->Attribute("height"));
			auto object_gid = -1;

			bool flipped_horizontally = false;
			bool flipped_vertically = false;
			bool flipped_diagonally = false;

			auto gid = child2->Attribute("gid");
			if (gid != NULL)
			{
				object_gid = cStrToUInt(gid);

				const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
				const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
				const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

				flipped_horizontally = (object_gid & FLIPPED_HORIZONTALLY_FLAG);
				flipped_vertically = (object_gid & FLIPPED_VERTICALLY_FLAG);
				flipped_diagonally = (object_gid & FLIPPED_DIAGONALLY_FLAG);

				object_gid &= ~(FLIPPED_HORIZONTALLY_FLAG |
					FLIPPED_VERTICALLY_FLAG |
					FLIPPED_DIAGONALLY_FLAG);

				if (flipped_vertically || flipped_diagonally)
				{
					std::cout << "tmx_parser failed to parse gid of object " << object_name << " - only the horizontal rotation is currently supported!" << std::endl;
					object_gid = -1;
				}
			}

			if (object_name == NULL)
			{
				object_name = "";
			}

			if (object_type == NULL)
			{
				object_type = "";
			}

			TmxObject object(
				object_id,
				object_name,
				object_type,
				object_x,
				object_y,
				object_width,
				object_height,
				object_gid,
				flipped_horizontally,
				flipped_vertically,
				flipped_diagonally);

			auto props = child2->FirstChildElement("properties");
			if (props != NULL)
			{
				std::vector<TmxObjectProperty> object_properties;

				for (auto prop = props->FirstChildElement("property"); prop != NULL; prop = prop->NextSiblingElement("property"))
				{
					auto prop_name = prop->Attribute("name");
					auto prop_type = prop->Attribute("type");
					auto prop_value = prop->Attribute("value");

					TmxObjectProperty property(prop_name, prop_type, prop_value);
					object_properties.push_back(property);
				}

				object.properties = object_properties;
			}

			objects.push_back(object);
		}

		layer.objects = objects;
		layers.push_back(layer);
	}

	return layers;
}

TmxMap TmxParser::parse(const std::string& filename)
{
	XMLDocument doc;
	doc.LoadFile(filename.c_str());

	auto& root_element = *doc.RootElement();
	_chdir(std::filesystem::absolute(filename).remove_filename().string().c_str());

	/* YAY! */
	TmxMap map(
		getMapElementProperties(root_element),
		getMapTilesets(root_element),
		getMapTileLayers(root_element),
		getMapObjectLayers(root_element)
	);

	return map;
}