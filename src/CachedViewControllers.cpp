#include "CachedViewControllers.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "UnityEngine/Object.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

namespace CachedViewControllers
{
    ViewController *topViewController = nullptr;
    ViewController *bottomScreenViewController = nullptr;
    ViewController *topScreenViewController = nullptr;
    ViewController *rightScreenViewController = nullptr;
    ViewController *leftScreenViewController = nullptr;

    void GetViewControllers() {
        auto mainFlowCoordinator = UnityEngine::Object::FindObjectOfType<MainFlowCoordinator *>();
        auto deepestChildFlowCoordinator = mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf();
        topViewController = deepestChildFlowCoordinator->get_topViewController();
        bottomScreenViewController = deepestChildFlowCoordinator->bottomScreenViewController;
        topScreenViewController = deepestChildFlowCoordinator->topScreenViewController;
        rightScreenViewController = deepestChildFlowCoordinator->rightScreenViewController;
        leftScreenViewController = deepestChildFlowCoordinator->leftScreenViewController;
    }

    void ShowViewControllers()
    {
        auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
        levelSelectFlowCoord->SetLeftScreenViewController(leftScreenViewController, ViewController::AnimationType::In);
        levelSelectFlowCoord->SetRightScreenViewController(rightScreenViewController, ViewController::AnimationType::In);
        levelSelectFlowCoord->SetTopScreenViewController(topScreenViewController, ViewController::AnimationType::In);
        levelSelectFlowCoord->SetBottomScreenViewController(bottomScreenViewController, ViewController::AnimationType::In);
    }

    void Clear() {
        topViewController = nullptr;
        bottomScreenViewController = nullptr;
        topScreenViewController = nullptr;
        rightScreenViewController = nullptr;
        leftScreenViewController = nullptr;
    }
}