#include <GameEngine/GameEngine.hpp>

class Temp : public ge::State{
public:
    Temp(ge::Data *data): ge::State(data){
        ge::Texture texture;
        texture.Read("tempTexture.config");

        temp.setTexture(texture.getResource("ImgOne")[0]);
    }

    void update(){}
    void render(){
        data->window.draw(temp);
    }

private:
    sf::Sprite temp;
};

int main(){
    ge::Data *data = new ge::Data();
    ge::CreateWindow(data, 1920, 1080, "temp");

    data->state.addState(new Temp(data));

    ge::Run(data);
    return 0;
}