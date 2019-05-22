#include "scene.hpp"


Scene::Scene(){
  gameObjects = std::vector<std::pair<GameObject, std::string>>();
}

void Scene::add(GameObject obj, std::string tag){
  gameObjects.push_back(std::pair<GameObject, std::string>(obj, tag));
}

std::vector<GameObject> Scene::getObjectsByTag(std::string tag){
  std::vector<GameObject> re;

  for(auto& pair : gameObjects){
    if(pair.second == tag){
      re.push_back(pair.first);
    }
  }
  return re;
}

void Scene::draw(){
  for(auto& pair : gameObjects){
    pair.first.draw();
  }
}

