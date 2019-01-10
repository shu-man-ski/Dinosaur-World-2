# Dinosaur World 2 v0.05

Reworked version of game Dinosaur World using C++ SFML.

![screenshot of sample](https://github.com/dima-shm/Dinosaur-World-2/blob/master/Preview1.png)

![screenshot of sample](https://github.com/dima-shm/Dinosaur-World-2/blob/master/Preview2.png)

SFML is a simple to use and portable API written in C++.

## Usage examples
Here is a short example, to show you how simple it is to use SFML :
```C++
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cute_image.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("nice_music.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
```

## Supported Platforms
### SFML is multi-platform
With SFML, your application can compile and run out of the box on the most common operating systems: Windows, Linux, Mac OS X and soon Android & iOS.
### SFML is multi-language
SFML has official bindings for the C and .Net languages. And thanks to its active community, it is also available in many other languages such as Java, Ruby, Python, Go, and more.

## More information about SFML
Information is available at http://www.sfml-dev.org/index.php.