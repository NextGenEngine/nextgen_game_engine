#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

/* Comparing assembly code generated by compilers for singleton versus
 * std::unique_ptr */

// NOLINTBEGIN(cppcoreguidelines-use-default-member-init,cppcoreguidelines-special-member-functions,misc-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
class RenderManager {
 public:
  // Get the one and only instance.
  static RenderManager& get() {
    // This function-static will be constructed on the
    // first call to this function.
    static RenderManager sSingleton;
    return sSingleton;
  }
  RenderManager() = default;
  ~RenderManager() = default;

  int code{5};
  int code_a{};
};
// NOLINTEND(cppcoreguidelines-use-default-member-init,cppcoreguidelines-special-member-functions,misc-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

static void DoSomethingWithManager(RenderManager& manager) {
  manager.code = 7;
  manager.code_a = 8;
}

static auto DoSomethingWithManager2(std::unique_ptr<RenderManager> manager) {
  manager->code = 7;
  manager->code_a = 8;
  return manager;
}

static void DoSomethingWithManager3(RenderManager& manager) {
  manager.code = 7;
  manager.code_a = 8;
}

int main() {
  auto manager = RenderManager::get();
  DoSomethingWithManager(manager);

  auto manager2 = std::make_unique<RenderManager>();
  manager2 = DoSomethingWithManager2(std::move(manager2));
  DoSomethingWithManager3(*manager2);
  std::cout << manager.code << "\n";
  return EXIT_SUCCESS;
}
