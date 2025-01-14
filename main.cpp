/**
 * CSCI 200: Final Project - 1D Heat Distribution Simulation
 * 
 * Author: Byron Selvage
 * Date: 4/26/2024
 * 
 * Read final.txt to begin
*/

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "HeatSim.h"

using namespace std;
using namespace sf;

int main() {
    // Define constants and variables
    const int WIDTH = 1200;
    const int HEIGHT = 900;
    const string initialProfiles[5] = {"data\\linear.txt", "data\\normal.txt", "data\\point.txt", "data\\segmented.txt", "data\\sin.txt"};
    bool go = 0;
    double endTemp;
    double thermalDiffusivity;
    int choice;

    // Welcome message
    cout << endl << "Welcome to the 1D Heat Distribution Simulation!" << endl;
    cout << "Please provide the following parameters to start the simulation:" << endl << endl;

    // User inputs
    cout << "Enter thermal diffusivity (recommended range: 0.1 - 0.5): ";
    cin >> thermalDiffusivity;

    cout << "Enter end temperature (recommended range: -1 to 1): ";
    cin >> endTemp;

    cout << "Choose an initial profile. 1 - Linear, 2 - Normal, 3 - Point, 4 - Segmented, 5 - sinusiodal: ";
    cin >> choice;
    cin.ignore();

    cout << endl << "Loading initial simulation state in SFML window..." << endl << "Select SFML Window and press Enter to begin simulation" << endl;

    // Initialize SFML objects
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "1D Heat Distribution Simulation");
    Event event;

    // Initialize HeatSim object
    HeatSim simulation(thermalDiffusivity);
    simulation.setInitialProfile(initialProfiles[choice - 1]);

    // Generate initial state of SFML window
    VertexArray line(LinesStrip, 101);
    for (size_t i = 0; i < 101; ++i) {
        line[i].position = Vector2f((float)i / 101 * WIDTH, (1 - simulation.getTemperatures()[i]) * HEIGHT);
        line[i].color = Color::Red;
    }

    // Generate zero line
    VertexArray zeroLine(LinesStrip, 2);
    zeroLine[0].position = Vector2f(0, HEIGHT / 2);
    zeroLine[1].position = Vector2f(WIDTH, HEIGHT / 2);
    zeroLine[0].color = zeroLine[1].color = Color::White;

    // SFML loop
    while (window.isOpen()) {
        window.clear();

        // Check window interaction
        while (window.pollEvent(event)) {

            // Window close
            if (event.type == Event::Closed) {
                window.close();
            }

            // Start Simulation
            if (!go && Keyboard::isKeyPressed(Keyboard::Key::Enter)){
                go = 1;
                cout << endl << "Simulating..." << endl << "Close window to end simulation." << endl;
            }
        }
        
        // Move simulation to next time step
        if (go){
            simulation.simulate(endTemp);
        }

        // Draw simulation
        for (size_t i = 0; i < 101; ++i) {
            float normalizedTemp = 2 * (simulation.getTemperatures()[i] - simulation.getMin()) / (simulation.getMax() - simulation.getMin()) - 1;
            line[i].position = Vector2f((float)i / 101 * WIDTH, (1 - normalizedTemp) * HEIGHT/2);
        }

        // Display to SFML window
        window.draw(zeroLine);
        window.draw(line);
        window.display();

        // Delay 5ms (~200 fps)
        sleep( milliseconds(5) );
    }

    return 0;
}