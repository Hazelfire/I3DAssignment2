#include <boost/test/unit_test.hpp>
#define TEST_ACCESS
#include "gameobject.hpp"

bool children_are_loyal(std::shared_ptr<GameObject> parent) {
  for(auto child_sp : parent->get_children()) {
    if(child_sp->get_parent() != parent) {
      return false;
    }
  }
  return true;
}

BOOST_AUTO_TEST_CASE( child )
{

  auto parent = std::make_shared<GameObject>(nullptr);
  // we don't own the child, so the parent must be doing it
  std::weak_ptr<GameObject> child_w;
  {
    auto child = std::make_shared<GameObject>(nullptr);
    child_w = child;
    child->setParent(parent);
  }

  // does the child exist?
  BOOST_TEST(child_w.lock());

  // does the parent have a child?
  BOOST_TEST(parent->get_children().size() == 1);
  // is the parents childs parent equal to the parent?
  BOOST_TEST(children_are_loyal(parent));

}

BOOST_AUTO_TEST_CASE( clone_child )
{
  auto parent = std::make_shared<GameObject>(nullptr);
  // we don't own the child, so the parent must be doing it
  std::weak_ptr<GameObject> child_w;
  {
    auto child = std::make_shared<GameObject>(nullptr);
    child_w = child;
    child->setParent(parent);
  }

  // we don't own the 2nd child, so the parent must be doing it
  std::weak_ptr<GameObject> second_child_w = child_w.lock()->clone();

  // does the second child exist?
  BOOST_TEST(second_child_w.lock());

  // does the parent have 2 children?
  BOOST_TEST(parent->get_children().size() == 2);
  // is the parents 2nd childs parent equal to the parent?
  BOOST_TEST(children_are_loyal(parent));
}


BOOST_AUTO_TEST_CASE( clone_parent )
{

  auto parent = std::make_shared<GameObject>(nullptr);
  // we don't own the child, so the parent must be doing it
  std::weak_ptr<GameObject> child_w;
  {
    auto child = std::make_shared<GameObject>(nullptr);
    child_w = child;
    child->setParent(parent);
  }

  auto second_parent = parent->clone();

  // does the second_parent exist?
  BOOST_TEST(second_parent);
  // does the second_parent have a child?
  BOOST_TEST(second_parent->get_children().size() == 1);
  // is the second_parents childs second_parent equal to the second_parent?
  BOOST_TEST(children_are_loyal(second_parent));
}

BOOST_AUTO_TEST_CASE( re_assign_parent )
{
  auto parent = std::make_shared<GameObject>(nullptr);
  // we don't own the child, so the parent must be doing it
  std::weak_ptr<GameObject> child_w;
  {
    auto child = std::make_shared<GameObject>(nullptr);
    child_w = child;
    child->setParent(parent);
  }

  // we don't own the 2nd child, so the parent must be doing it
  std::weak_ptr<GameObject> second_child_w = child_w.lock()->clone();

  auto second_parent = std::make_shared<GameObject>(nullptr);

  // re-assign the second child to the second parent
  second_child_w.lock()->setParent(second_parent);

  // check the first child test
  BOOST_TEST(child_w.lock());
  BOOST_TEST(parent->get_children().size() == 1);
  BOOST_TEST(children_are_loyal(parent));

  // check the second child test
  BOOST_TEST(second_child_w.lock());
  BOOST_TEST(second_parent->get_children().size() == 1);
  BOOST_TEST(children_are_loyal(second_parent));
#if 0
#endif
}

BOOST_AUTO_TEST_CASE( grand_kids )
{
  auto grand_parent = std::make_shared<GameObject>(nullptr);

  // we don't own the child, so the parent must be doing it
  std::weak_ptr<GameObject> parent_w;
  {
    auto parent = std::make_shared<GameObject>(nullptr);
    parent_w = parent;
    parent->setParent(grand_parent);
  }


  std::weak_ptr<GameObject> child_w;
  {
    auto child = std::make_shared<GameObject>(nullptr);
    child_w = child;
    child->setParent(parent_w.lock());
  }

  // should only have one child
  std::weak_ptr<GameObject> second_parent = parent_w.lock()->clone();

  // first parent should have 2 children now
  std::weak_ptr<GameObject> _first_parent_second_child = child_w.lock()->clone();

  BOOST_TEST(grand_parent->get_children().size() == 2);
  BOOST_TEST(children_are_loyal(grand_parent));

  BOOST_TEST(children_are_loyal(parent_w.lock()));
  BOOST_TEST(parent_w.lock()->get_children().size() == 2);

  BOOST_TEST(children_are_loyal(second_parent.lock()));
  BOOST_TEST(second_parent.lock()->get_children().size() == 1);

}
