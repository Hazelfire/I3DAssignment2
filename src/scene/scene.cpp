#include "scene.hpp"


Scene::Scene(){
  gameObjects = std::vector<std::pair<std::shared_ptr<GameObject>, tag::object_tag>>();
}

void Scene::add(std::shared_ptr<GameObject> obj, tag::object_tag tag){
  gameObjects.push_back(std::pair<std::shared_ptr<GameObject>, tag::object_tag>(obj, tag));
}

std::vector<std::shared_ptr<GameObject>> Scene::getObjectsByTag(tag::object_tag tag) const {
  std::vector<std::shared_ptr<GameObject>> re;

  for(auto& pair : gameObjects){
    if(pair.second == tag){
      re.push_back(pair.first);
    }
  }
  return re;
}

std::vector<std::shared_ptr<GameObject>> Scene::getCollidingObjectsByTag(const GameObject &obj, tag::object_tag tag) const {
  std::vector<std::shared_ptr<GameObject>> to_search = getObjectsByTag(tag);
  std::vector<std::shared_ptr<GameObject>> ret;

  for(auto& object : to_search) {
    if(obj.collidesWith(*object.get())) {
      ret.push_back(object);
    }
  }
  return ret;
}

void Scene::draw(DrawOptions options){
  for(auto& pair : gameObjects){
    pair.first->draw(options);
  }
}
void Scene::update(double delta){
  for(auto& pair : gameObjects){
    pair.first->update(delta);
  }
}

