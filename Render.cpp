#include "Render.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>

using namespace ftxui;

void startGameUI(World& world){
    auto screen = ScreenInteractive::TerminalOutput();
   
   
    // 1. Creat a Canvas based on world size
    auto renderer = Renderer([&]{
        auto c = Canvas(80, 24);
        // 2. Lock the MUTEX
        //prevents logic thread from moving enemies while drawing
        {
        std::lock_guard<std::mutex> lock(world.getMutex());
        //Draw Player
        c.DrawText(world.getPlayer().getX(), world.getPlayer().getY(), "  @.@"); //get x and y and assign character
        //Draw Weapon
        c.DrawText(world.getPlayer().getWeaponX(), world.getPlayer().getWeaponY(), "\\");
        //Draw Enemies
        for (const auto& enemy : world.getEnemies()){
            c.DrawText(enemy.getX(), enemy.getY(), "X.x");
        }
        }
        return canvas(std::move(c)) | border | color(Color::Green);
    });

    //3 CatchEvent defines how to handle input
    auto component = CatchEvent(renderer, [&](Event event){
        if (event == Event::Character('w')) world.movePlayer(world.getPlayer().getX(), world.getPlayer().getY() - 1);
        if (event == Event::Character('s')) world.movePlayer(world.getPlayer().getX(), world.getPlayer().getY() + 1);
        if (event == Event::Character('a')) world.movePlayer(world.getPlayer().getX() - 1, world.getPlayer().getY());
        if (event == Event::Character('d')) world.movePlayer(world.getPlayer().getX() + 1, world.getPlayer().getY());

        if (event == Event::Escape) screen.Exit();
        return true;
    });

    screen.Loop(component);
}