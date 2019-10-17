#include "Utilities.h"
#include "Entity.h"


class  Background : public Entity {

public:

	Background(Vector2 position);
	~Background();

	void Initialise(b2World* world, std::shared_ptr<Sprite> coinSprite);
	void Update(Camera* gameCamera);
	void Render(SDL_Renderer * renderer);


private:

	float width = 2500.0f;
	float height = 1080.0f;
};