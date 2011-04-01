#include <iostream>
using namespace std;

#include "motor/graphics/window.hpp"
#include "motor/io/input.hpp"
#include "state.hpp"
#include "title.hpp"
#include "game.hpp"
using namespace motor;

int main(int argc, char **argv)
{
	cout << "awesome!	:D" << endl << endl;

	Input *keys = new Input();
	Window *window = new Window();
	window->open(683, 384, "awesome+");

	State *current = new Game();
	current->main(window, keys);

	delete keys;
	delete window;
}
