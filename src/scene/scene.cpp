#include "scene.hpp"


Scene::Scene(){
  gameObjects = std::vector<std::pair<std::shared_ptr<GameObject>, tag::object_tag>>();
}

void Scene::add(std::shared_ptr<GameObject> obj, tag::object_tag tag){
  gameObjects.push_back(std::pair<std::shared_ptr<GameObject>, tag::object_tag>(obj, tag));
}

std::vector<std::shared_ptr<GameObject>> Scene::getObjectsByTag(tag::object_tag tag){
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

