***TITLE*** 
---
Byron Selvage, CSCI 200 Section D, 1D Heat Distribution Simulation

***PROBLEM DESCRIPTION*** 
---
This project visualizes the one-dimensional heat distribution of a bar over time using the 1D heat equation. Users can control simulation variables like 
thermal diffusivity and select an initial temperature profile. The program reads the initial profile from a file, performs a time-stepping simulation using 
the explicit finite difference method, and visualizes the evolving bar temperature using SFML.

***PROGRAM DOCUMENTATION***
---
To run the program, compile the main.cpp file and run the resulting final.exe file. The program will prompt user inputs for thermal diffusivity, end 
temperature, and initial temperature profile choice. 

Thermal diffusivity controls the rate of heat dispersion in the bar. Recommended values are between 0.1 and 0.5 as higher values can cause irregularities 
with the finte difference method. If you are seeing explosive sinusiodal behavior, it is most likely due to having set thermal diffusivity too high. Note that 
this is not an issue with the coding of the system, but rather a limitation of the finite difference method used to calculate the temperatures over time. 

End temperature represents the fixed temperature at the ends of the bar. As the simulation runs, this is the value the temperature in the bar is expected to 
tend towards. For the purpose of visualization, temperatures are normalized to a range of [-1,1]. You can absolutely enter end temperature values outside this 
range, but doing so will eventually lead to the temperature visualization being outside the range of the SFML window. 

Initial temperature profile choice will allow you to choose from one of five initial temperature distributions: Linear, Normal, Point, Segmented, and 
Sinusiodal. Enter an integer 1-5 to make your choice. 

After entering these values, an SFML window will appear showing the initial temperature state. The white bar represents the zero line, while the red line
represents the temperature at each position along the bar. Select the SFML window and press Enter to begin the simulation, which will evolve the temperature 
over time based on the inputs until the window is closed.

The program is structured with a HeatSim class that encapsulates the simulation logic. Future extensions could enhance the visualization, allow for multiple 
boundary conditions, expand to 2D, or allow user definition of the initial profile.

***CLASS DESCRIPTION*** 
---
The custom HeatSim class contains the _temperatures vector representing the discrete temperature values along the bar, the thermal diffusivity _alpha, 
and helper variables _min and _max tracking the temperature range. Key member functions are the constructor to initialize values, setInitialProfile to read 
the starting _temperatures from a file, simulate to update _temperatures for the next time step via finite differences, and getter functions.

***LIST DATA STRUCTURE***
---
A satic array is used to store the _temperatures values, providing fast random access for the finite difference calculations at each time step without the 
time inefficiencies that come from the dynamic resizing of a vector. 

***FILE I/O***
---
The program reads the initial temperature profile from a user-selected file in the data/ directory using std::ifstream. The file contains a series of 
temperature values representing the discrete spatial points along the bar.

***REFLECTIONS***
---
This project helped solidify understanding of core C++ concepts like classes, file I/O, and the std::vector container. Using the SFML graphics library was a 
challenge, but allowed the creation of an interesting visualization. Given more time, enhancing the visual representation with color maps and allowing 
user-defined initial profiles could improve the simulation's usability. Overall, breaking down the problem into defined components like the HeatSim class made 
the implementation more manageable for this project.
