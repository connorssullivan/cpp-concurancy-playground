#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>

const int ROWS = 2;
const int COLS = 2;

std::vector<std::vector<std::unique_ptr<sf::Shape>>> shapes(ROWS);
std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));
bool is_running = true;


void update(const int x, const int y)
{
    while (is_running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        grid[x][y] = rand() % 4;
    }
}


int main()
{
    for (auto& r : shapes)
        r.resize(COLS);
    std::vector<std::thread> threads;

    // Make the shapes
    for (int i {}; i < ROWS; i++)
    {
        for (int j {}; j < COLS; j++)
        {
            shapes[i][j] = std::make_unique<sf::CircleShape>(100.0);
        }
    }


    // Create our threads
    for (int i {}; i < ROWS; i++)
    {
        for (int j {}; j < COLS; j++)
        {
            threads.emplace_back(&update, i, j);
        }
    }

    sf::RenderWindow window(sf::VideoMode({400,400}), "Threads!");

    while (window.isOpen() && is_running)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                is_running = false;
            }
        }

        window.clear();
            for (int i {}; i < ROWS; i++)
            {
                for (int j {}; j < COLS; j++)
                {
                    shapes[i][j]->setPosition({static_cast<float>(i*200), static_cast<float>(j*200)});

                    if (grid[i][j] == 0)
                        shapes[i][j]->setFillColor(sf::Color::Red);
                    else if (grid[i][j] == 1)
                        shapes[i][j]->setFillColor(sf::Color::Green);
                    else if (grid[i][j] == 2)
                        shapes[i][j]->setFillColor(sf::Color::Blue);
                    else if (grid[i][j] == 3)
                        shapes[i][j]->setFillColor(sf::Color::Yellow);
                    
                    window.draw(*shapes[i][j]);
                }
                
            }

            
            window.display();
    }

    for (int i {}; i < threads.size(); i++)
    {
        threads[i].join();
    }

    std::cout << "Main Complete\n";

    return 0;
}