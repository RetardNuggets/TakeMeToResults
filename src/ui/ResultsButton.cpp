#include "TakeMeToResults.hpp"
#include "Classes/CachedViewControllers.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

UnityEngine::UI::Button *resultsButton;
UnityEngine::UI::Button *CreateResultsButton(ViewController *self)
{
    auto resultsButton = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "View Results", [](){
        auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
        levelSelectFlowCoord->PresentViewController(CachedViewControllers::topViewController, ShowOtherViewControllers(), ViewController::AnimationDirection::Vertical, false); });
    return resultsButton;
}

System::Action *ShowOtherViewControllers()
{
    auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
    levelSelectFlowCoord->SetLeftScreenViewController(CachedViewControllers::leftScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetRightScreenViewController(CachedViewControllers::rightScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetTopScreenViewController(CachedViewControllers::topScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetBottomScreenViewController(CachedViewControllers::bottomScreenViewController, ViewController::AnimationType::In);
}

MAKE_HOOK_MATCH(levelSelectDidActivate, &SoloFreePlayFlowCoordinator::SinglePlayerLevelSelectionFlowCoordinatorDidActivate, void, SoloFreePlayFlowCoordinator *self, bool firstActivation, bool addedToHierarchy)
{
    if (firstActivation)
    {
        resultsButton = CreateResultsButton(self->get_topViewController());
        resultsButton->set_interactable(false);
    }
    else if (!firstActivation && CachedViewControllers::topViewController)
    {
        resultsButton->set_interactable(true);
    }
    else if (!firstActivation && !CachedViewControllers::topViewController)
    {
        resultsButton->set_interactable(false);
    }

    levelSelectDidActivate(self, firstActivation, addedToHierarchy);
}

void TakeMeToResults::HookInstallers::SinglePlayerLevelSelectionFlowCoordinator(Logger &logger) {
    INSTALL_HOOK(logger, levelSelectDidActivate);
}