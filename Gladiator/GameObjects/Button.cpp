#include "Button.h"

Button::Button(int x, int y, const char * labelText) {
	go = new GameObject("Assets/gui/button.png", x, y, 150, 40, 1);
	label = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, labelText, { 0, 0, 0});

	go->setPos(x, y);
}


void Button::update() {
	go->update();
	//std::cout << "clicked: " << clicked() << std::endl;
}

void Button::render() {
	go->render();
	label->render(go->x(), go->y() + 5);
}

//zkontroluje klik
bool Button::clicked() {

	const Uint8 * state = SDL_GetKeyboardState(NULL);

		if (Game::myEvent.motion.x > go->getCollisionX() && Game::myEvent.motion.x < go->getCollisionX2() && Game::myEvent.motion.y > go->getCollisionY() && Game::myEvent.motion.y < go->getCollisionY2()) {


			if (Game::myEvent.type == SDL_MOUSEBUTTONDOWN) {
				if (state[SDL_BUTTON_LEFT]) {
					return true; 
				}
			}
			else {
				return false;
			}
		}
		else
			return false;


}