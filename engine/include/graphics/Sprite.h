#include <Component.h>

class Texture;

class Sprite : public Component {
public:
    Sprite(Texture* texture) : Component(), m_texture(texture) {

    }
    
    Texture* m_texture;

private:
    // vec2 clipStart
    // vec3 clipSize;
};
