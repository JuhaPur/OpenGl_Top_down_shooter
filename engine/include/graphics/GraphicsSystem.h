#pragma once
#include <System.h>
#include <graphics/Sprite.h>
#include <map>
#include <graphics/SpriteBatch.h>
#include <Entity.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <stb_image.h>
#include <graphics/TextRendering.h>
#include <Application.h>



class GraphicsSystem : public System {
public:
    GraphicsSystem() : m_camera(0)
    , m_shader(0)
 {

        const char* vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 in_position;\n"
            "layout (location = 1) in vec2 in_texCoord;\n"
            "out vec2 texCoord;"
            "void main()\n"
            "{\n"
            "   texCoord = in_texCoord;\n"
            "   gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0);\n"
            "}";

        const char* fragmentShaderSource =
            "#version 330 core\n"
            "uniform sampler2D texture0;\n"
            "in vec2 texCoord;"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = texture2D(texture0, texCoord);\n"
            "}";

        // build and compile our shader program
        m_shader = new Shader(vertexShaderSource, fragmentShaderSource);
    };

    ~GraphicsSystem() {};

    Texture* loadTexture(const std::string& filename) {
        int width, height, nrChannels;
        GLubyte* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
        return new Texture(width, height, nrChannels, data);

        if (data == NULL) { printf("Cannot load image"); } //DEBUG code for image not found
    }


	virtual std::shared_ptr<Component> createComponent(const std::string& type, const std::vector<std::string>& args) {
        if( type == "Sprite") {
            std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(loadTexture(args[0]));
            m_allSprites.push_back(sprite);        
            return sprite;
        }           
        if (type == "Camera") {        
            m_camera = std::make_shared<Camera>(0.0f, 800.0f, 600.0f, 0.0f);
            return m_camera;
        }
        if (type == "Background") {
            std::shared_ptr<Sprite> background = std::make_shared<Sprite>(loadTexture(args[0]));
            m_allBackGrounds.push_back(background);
            return background;
        }
        
        return 0;
	}

    // Call at the start of program
    virtual void start() {

        for (auto& it : m_allBackGroundsBatches) {
            it.second.clear();
        }

        for (auto background : m_allBackGrounds) {
            auto& backGroundBatch = m_allBackGroundsBatches[background->m_texture];
            auto p = background->getEntity()->getComponent<Transform>()->getPosition();
            auto model = background->getEntity()->getComponent<Transform>()->getWorldTransform();
            auto view = m_camera->getEntity()->getComponent<Transform>()->getWorldTransform();
            backGroundBatch.addSprite(model, view, m_camera->getProjectionMatrix());
        }

        for (auto& it : m_allBackGroundsBatches) {
            it.second.render(m_shader, it.first->getTextureId());
        }
        
    }

	virtual void update(float deltaTime) {
    
        for (auto& it : m_allSpriteBatches) {
            it.second.clear();
        }

        for(auto sprite : m_allSprites){
            auto& spriteBatch = m_allSpriteBatches[sprite->m_texture];
            auto p = sprite->getEntity()->getComponent<Transform>()->getPosition();
            auto model = sprite->getEntity()->getComponent<Transform>()->getWorldTransform();
            auto view = m_camera->getEntity()->getComponent<Transform>()->getWorldTransform();
            spriteBatch.addSprite(model, view, m_camera->getProjectionMatrix());

        }

        for (auto& it : m_allSpriteBatches) {
            it.second.render(m_shader, it.first->getTextureId());
        }   
        

        /*for (auto text : m_text) {
            m_text = new text->Textrenderiunokfdmnokj<sa nbfdgsojfdojvsangokjerngoierngoiewokjewq  cx.ners l
                
        }*/
        
        
        
        
            
	}

    
private:
    std::vector<std::shared_ptr<Sprite>>    m_allSprites;
    std::vector<std::shared_ptr<Sprite>>    m_allBackGrounds;
    std::map<Texture*, SpriteBatch>         m_allSpriteBatches;
    std::map<Texture*, SpriteBatch>         m_allBackGroundsBatches;
    std::shared_ptr < Camera>               m_camera;
    Shader*                                 m_shader;
    std::shared_ptr<Entity>                 m_sceneRoot;
    /*std::map<Texture*,TextRendering> m_text;
    TextRendering* m_text;*/
};

