#include "scene.hpp"

std::unique_ptr<Scene> Scene::instance = nullptr;

Scene::Scene(){
  gameObjects = std::vector<std::pair<std::shared_ptr<GameObject>, tag::object_tag>>();
}

Scene::~Scene(){
}


const Scene& Scene::get_instance() {
  if(instance == nullptr) {
    instance = std::make_unique<Scene>(Scene());
  }

  return *instance.get();
}

void Scene::add(std::shared_ptr<GameObject> obj, tag::object_tag tag){
  instance.get()->gameObjects.push_back(std::pair<std::shared_ptr<GameObject>, tag::object_tag>(obj, tag));
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

void Scene::draw(DrawOptions options) const {
  for(auto& pair : gameObjects){
    pair.first->draw(options);
  }
}
void Scene::update(double delta){
  for(auto& pair : instance.get()->gameObjects){
    pair.first->update(delta);
  }
}

