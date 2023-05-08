#include "Engine.h"
#include <cstdlib>

// The Engine Constructor
Engine::Engine()
{
	// Create window with size and title
	m_Window.create(VideoMode(800, 600), "Particles");	
}

// Run calls all the private fxns
void Engine::run()
{
	// Clock object to track time per frame
	Clock clk;

	// Particle used for unit tests
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	// Game loop
	while (m_Window.isOpen())
	{
		// Restart Clock - Return Time elapsed since the last frame
		Time dt = clk.restart();

		// Convert clock time to seconds
		float toSeconds = dt.asSeconds();

		// Call input to handle user input
		input();
		// Call update to update the game state using elapsed time
		update(toSeconds);
		// Call draw to render game
		draw();
	}
	
}

// Handle User input
void Engine::input()
{
	// store event info
	Event event;

	// poll event queue until empty
	while (m_Window.pollEvent(event))
	{
		// handle esc key press or closed even to exit program
		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		// Handle the left mouse button pressed event
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				// Create particles
				for (int i = 0; i < 5; i++)
				{			
					int numPoints = rand() % 26 + 25;  // Random num -> [25:50]

					// Pass position of mouse click to contructor
                    Particle p(m_Window, numPoints, {event.mouseButton.x, event.mouseButton.y});
                    this->m_particles.push_back(p);
				}
			}
		}
	}
}

// Update game state using elapsed time
void Engine::update(float dtAsSeconds)
{
	// Loop thru m_particles and update each one
	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		// Call update on each particle whose ttl has not expired
		if (it->getTTL() > 0.0f)
		{
			//update position
			it->update(dtAsSeconds);
			// increment iterator
			++it;

		}// If particle's ttl has expired -> erase from vector
		else
		{
			it = m_particles.erase(it);
		}
	}
}

// Render game
void Engine::draw()
{
	// Clear the window
	m_Window.clear();

	// Loop thru each particle 
	/*loop iterates over each Particle object in the m_particles vector,
	assigning it to the variable particle on each iteration. 
	*/
	for (const auto& particle : m_particles)
	{
		m_Window.draw(particle);
	}

	// Display the window
	m_Window.display();
}