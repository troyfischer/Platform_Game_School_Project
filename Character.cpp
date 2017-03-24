//Character implementation

Character::Character()
{
	rect.x = 0;
	rect.y = 0;
	rect.width = 32;
	rect.height = 32;
}

SDL_Rect Character::getRect()
{
	return rect;
}