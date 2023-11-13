#include "Camera.h"
#include "ExternDecl.h"

Camera::Camera() {

}

Camera::Camera(const int width, const int height) {
	rect = {0, 0, width, height};
}

Camera::~Camera() {

}

void Camera::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void Camera::setBounds(const SDL_Point& min, const SDL_Point& max) {
	minPosition = min;
	maxPosition = max;
}

void Camera::setPos(const SDL_Point& position) {
	rect.x = position.x - (rect.w / 2);
	rect.y = position.y - (rect.h / 2);

	// Keep the camera inside the pre-defined bounds

	if (rect.x < minPosition.x)					rect.x = minPosition.x;
	else if (rect.x > maxPosition.x - rect.w)	rect.x = maxPosition.x - rect.w;
	if (rect.y < minPosition.y)					rect.y = minPosition.y;
	else if (rect.y > maxPosition.y - rect.h)	rect.y = maxPosition.y - rect.h;
}