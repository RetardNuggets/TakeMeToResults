#include "Classes/CachedViewControllers.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/Object.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

void CachedViewControllers::Init() {
    auto mainFlowCoordinator = Object::FindObjectOfType<MainFlowCoordinator *>();
    this->topViewController = mainFlowCoordinator->get_topViewController();
    this->bottomScreenViewController = mainFlowCoordinator->bottomScreenViewController;
    this->topScreenViewController = mainFlowCoordinator->topScreenViewController;
    this->rightScreenViewController = mainFlowCoordinator->rightScreenViewController;
    this->leftScreenViewController = mainFlowCoordinator->leftScreenViewController;
}

CachedViewControllers::CachedViewControllers()
{
    CachedViewControllers::Init();
}
