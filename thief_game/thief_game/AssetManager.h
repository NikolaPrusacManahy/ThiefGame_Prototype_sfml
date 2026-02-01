#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "ResourceManager.h"

class AssetManager
{
public:
	//simple wrapper functions around resourceManager for the textures and fonts

	void loadTexture(std::string const& t_id, std::string const& t_path);

	void loadFont(std::string const& t_id, std::string const& t_path);

	const sf::Texture& getTexture(std::string const& t_id) const;

	const sf::Font& getFont(std::string const& t_id) const;

	void releaseTexture(std::string const& t_id);

	void releaseFont(std::string const& t_id);

private:
	ResourceManager<sf::Texture> m_textures;
	ResourceManager<sf::Font> m_fonts;
};