/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** test_MapGenerator
*/

#include "criterion/criterion.h"
#include "../src/MapGenerator/MapGenerator.hpp"

Test(StartGeneration, test1)
{
    MapGenerator generator;

    generator.startGeneration();
}

Test(StartGeneration, test2)
{
    MapGenerator generator(SMALL, NORMAL, NORMAL);

    generator.startGeneration();
}

Test(StartGeneration, test3)
{
    MapGenerator generator(SMALL, HIGH, NORMAL);

    generator.startGeneration();
}

Test(StartGeneration, test4)
{
    MapGenerator generator(SMALL, HIGH, NORMAL);

    generator.startGeneration();
}

Test(StartGeneration, test5)
{
    MapGenerator generator(MEDIUM, LITTLE, LITTLE);

    generator.startGeneration();
}

Test(StartGeneration, test6)
{
    MapGenerator generator(MEDIUM, HIGH, HIGH);

    generator.startGeneration();
}

Test(StartGeneration, test7)
{
    MapGenerator generator(MEDIUM, NONE, NONE);

    generator.startGeneration();
}

Test(StartGeneration, test8)
{
    MapGenerator generator(LARGE, LITTLE, LITTLE);

    generator.startGeneration();
}

Test(StartGeneration, test9)
{
    MapGenerator generator(LARGE, HIGH, HIGH);

    generator.startGeneration();
}

Test(StartGeneration, test10)
{
    MapGenerator generator(LARGE, NONE, NONE);

    generator.startGeneration();
}