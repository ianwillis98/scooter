//
// Created by Ian on 7/6/2024.
//

#ifndef SCOOTER_TILEMAP_H
#define SCOOTER_TILEMAP_H

#include <string>
#include <iostream>
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"


class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,  unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset) {
        if (!m_tileset.loadFromFile(tileset)) {
            std::cout << "didn't load tileset properly" << std::endl;
            return false;
        } else {
            std::cout << "loaded texture successfully" << std::endl;
        }

        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(width * height * 6);

        for (unsigned int i = 0; i < width; i++) {
            for (unsigned int j = 0; j < height; j++) {
                int tileNumber = tiles[i + j * width];

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(xOffset + i * tileSize.x, yOffset + j * tileSize.y);
                triangles[1].position = sf::Vector2f(xOffset + (i + 1) * tileSize.x,yOffset +  j * tileSize.y);
                triangles[2].position = sf::Vector2f(xOffset + i * tileSize.x, yOffset + (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(xOffset + i * tileSize.x,yOffset +  (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f(xOffset + (i + 1) * tileSize.x,yOffset +  j * tileSize.y);
                triangles[5].position = sf::Vector2f(xOffset + (i + 1) * tileSize.x, yOffset + (j + 1) * tileSize.y);

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
        return true;
    }
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
};


#endif //SCOOTER_TILEMAP_H
