#include "engine.h"

using namespace sf;
using namespace std;

Engine::Engine()
{
    m_Window.create(VideoMode::getDesktopMode(), "Particle Engine", Style::Default);
}

void Engine::run()
{

    sf::Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;


    while (m_Window.isOpen())
    {

        sf::Time dt = clock.restart();

        // Convert the clock time to seconds
        float dtAsSeconds = dt.asSeconds();

        // Call input
        input();

        // Call update
        update(dtAsSeconds);

        // Call draw
        draw();
    }
}


void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        {
            m_Window.close();
        }

        if (event.type == Event::Closed)
        {
            m_Window.close();
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i = 0; i < 5; ++i)  // creating 5 particles
            {
                int numPoints = rand() % 26 + 25;


                Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
                m_particles.push_back(Particle(m_Window, numPoints, mousePosition));
            }
        }
    }
}



void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        if (it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    // Clear the window
    m_Window.clear();

    // Loop through each Particle in m_Particles
    for (auto& particle : m_particles)
    {
        // Pass each element into m_Window.draw()
        m_Window.draw(particle);
    }

    // Display the window
    m_Window.display();
}
