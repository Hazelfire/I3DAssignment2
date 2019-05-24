#include "scene.hpp"


Scene::Scene(){
  gameObjects = std::vector<std::pair<std::shared_ptr<GameObject>, std::string>>();
}

void Scene::add(std::shared_ptr<GameObject> obj, std::string tag){
  gameObjects.push_back(std::pair<std::shared_ptr<GameObject>, std::string>(obj, tag));
}

std::vector<std::shared_ptr<GameObject>> Scene::getObjectsByTag(std::string tag){
  std::vector<std::shared_ptr<GameObject>> re;

  for(auto& pair : gameObjects){
    if(pair.second == tag){
      re.push_back(pair.first);
    }
  }
  return re;
}

void Scene::draw(){
  for(auto& pair : gameObjects){
    pair.first->draw();
  }
}
void Scene::update(double delta){
  for(auto& pair : gameObjects){
    pair.first->update(delta);
  }
}

