#include "Classes/CachedViewControllers.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/Object.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

ViewController *CachedViewControllers::topViewController;
ViewController *CachedViewControllers::bottomScreenViewController;
ViewController *CachedViewControllers::topScreenViewController;
ViewController *CachedViewControllers::rightScreenViewController;
ViewController *CachedViewControllers::leftScreenViewController;

void CachedViewControllers::Init() {
    auto mainFlowCoordinator = Object::FindObjectOfType<MainFlowCoordinator *>();
    auto deepestChildFlowCoordinator = mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf();
    CachedViewControllers::topViewController = deepestChildFlowCoordinator->get_topViewController();
    CachedViewControllers::bottomScreenViewController = deepestChildFlowCoordinator->bottomScreenViewController;
    CachedViewControllers::topScreenViewController = deepestChildFlowCoordinator->topScreenViewController;
    CachedViewControllers::rightScreenViewController = deepestChildFlowCoordinator->rightScreenViewController;
    CachedViewControllers::leftScreenViewController = deepestChildFlowCoordinator->leftScreenViewController;
}