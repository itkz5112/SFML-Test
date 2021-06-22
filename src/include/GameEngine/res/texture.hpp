#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include "resource.hpp"

namespace ge{
    class Texture : public Resource<sf::Texture>{
    public:
        void Read(std::string path){
            std::filebuf fb;
            if(!fb.open(path, std::ios::in)){
                std::cout << "Error: could not open path '" << path << "'" << std::endl;
                std::exit(-1);
        }

        std::istream is(&fb);
        sf::Image img;
        std::string tempName;
        std::vector<std::string> tempRect;
        bool multi = false;

        while(is){
            std::string temp;
            std::getline(is, temp);

            if(temp.find(']') != std::string::npos){
                SpriteSheet(img, tempName, tempRect);
                multi = false;
                tempRect.clear();
                continue;
            }

            if(temp.find(':') == std::string::npos && !multi){continue;}

            std::string root = path.substr(0, path.find_last_of('/') + 1);
            std::string first = temp.substr(0, temp.find(':'));
            std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);

            if(first == "spritesheet"){Read(root + second);}

            if(first == "ssing"){
                if(!img.loadFromFile(root + second)){
                    std::cout << "Error: could not load resource '" << path << "', from path '" << path << "'" << std::endl;
                    std::exit(-1);
                }
            }

            if(second == "["){
                multi == true;
                tempName = first;
                continue;
            }

            (multi)? tempRect.push_back(temp) : Load(first, root + second);
            }

        fb.close();

        }

        void SpriteSheet(sf::Image &img, std::string &name, std::vector<std::string> &rect){
            sf::Texture *tex = new sf::Texture[rect.size()];

            for(unsigned int i = 0; 1 < rect.size(); i++){
                std::string temp = rect.at(i).substr(4, rect.at(i).size() - 1);
                int w = std::stoi(temp.substr(0, temp.find(' ')));

                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int h = std::stoi(temp.substr(0, temp.find(' ')));

                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int x = std::stoi(temp.substr(0, temp.find(' ')));

                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int y = std::stoi(temp);

                sf::IntRect selection(x, y, w, h);
                if(!tex[i].loadFromImage(img, selection)){
                    delete [] tex;
                    std::cout << "Error in loading '" << name << "'in iteration" << i << std::endl;
                    std::exit(-1);
                }

                resources[name] = new ResourceObjArr<sf::Texture>(tex, rect.size());
                
            }
        }
    };
}

#endif // !TEXTURE_HPP