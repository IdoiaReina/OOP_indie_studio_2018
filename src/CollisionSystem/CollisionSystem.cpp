/*
** EPITECH PROJECT, 2019
** CollisionSystem.cpp
** File description:
** CollisionSystem class implementation
*/

#include <iostream>
#include "CollisionSystem.hpp"

bool CollisionSystem::collide_X(scene::ISceneNode *node1, std::vector<std::string> map, float move)
{
    irr::core::vector3df pos = node1->getPosition();
    int map_x = (pos.X + 0.5f + move) / 2.0f;;
    int map_y = pos.Z / 1.55f;

    if (move > 0) {
        map_x = (pos.X + 1.50f + move) / 2.0f;
    }
    if (map[map_y][map_x] == ' ' && map[(pos.Z + 1.2f) / 1.55f][map_x] == ' ')
        return true;
    return false;
}

bool CollisionSystem::collide_Z(scene::ISceneNode *node1, std::vector<std::string> map, float move)
{
    irr::core::vector3df pos = node1->getPosition();
    int map_x = (pos.X + 0.5f) / 2.0f;
    int map_y = (pos.Z + move) / 1.55f;

    if (move > 0) {
        map_y = (pos.Z + move + 1.2f) / 1.55f;
    }
    if (map[map_y][map_x] == ' ' && map[map_y][(pos.X + 1.50f) / 2.0f] == ' ')
        return true;
    return false;
}

bool CollisionSystem::collide(std::vector<scene::ISceneNode *> &nodes, core::vector3df &point, elemType type)
{
    for (auto node : nodes) {
        if (node->getID() == type) {
            node->updateAbsolutePosition();
            if (node->getTransformedBoundingBox().isPointInside(point) == true) {
                return true;
            }
        }
    }
    return false;
}

bool CollisionSystem::collide(scene::ISceneNode *node1, scene::ISceneNode *node2)
{
    node1->updateAbsolutePosition();
    node2->updateAbsolutePosition();
    return node1->getTransformedBoundingBox().intersectsWithBox(node2->getTransformedBoundingBox());
}

bool CollisionSystem::collide(scene::ISceneNode *node, core::vector3df &point)
{
    node->updateAbsolutePosition();
    return node->getTransformedBoundingBox().isPointInside(point);
}

bool CollisionSystem::collide(core::aabbox3df box, core::vector3df &pos, scene::ISceneNode *node)
{
    node->updateAbsolutePosition();
    box.MaxEdge.X += pos.X;
    box.MinEdge.X += pos.X;
    box.MaxEdge.Y += pos.Y;
    box.MinEdge.Y += pos.Y;
    box.MaxEdge.Z += pos.Z;
    box.MinEdge.Z += pos.Z;
    return node->getTransformedBoundingBox().intersectsWithBox(box);
}

bool CollisionSystem::destroyable_Z(scene::ISceneNode *node1, std::vector<std::string> map, float move)
{
    irr::core::vector3df pos = node1->getPosition();
    int map_x = (pos.X + 0.5f) / 2.0f;
    int map_y = (pos.Z + move) / 1.55f;

    if (map[map_y][map_x] == '1' || map[map_y][map_x] == '0') {
        return true;
    }
    return false;
}

bool CollisionSystem::destroyable_X(scene::ISceneNode *node1, std::vector<std::string> map, float move)
{
    irr::core::vector3df pos = node1->getPosition();
    int map_x = (pos.X + 0.5f + move) / 2.0f;;
    int map_y = pos.Z / 1.55f;

    if (map[map_y][map_x] == '1' || map[map_y][map_x] == '0') {
        return true;
    }
    return false;
}
