#include "TakeMeToResults.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "GlobalNamespace/SinglePlayerLevelSelectionFlowCoordinator.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

auto CachedViewControllers = TakeMeToResults::_CachedViewControllers();
UnityEngine::UI::Button *resultsButton;

UnityEngine::UI::Button *CreateResultsButton(ViewController *self)
{
    auto resultsButton = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "View Results", [](){
        auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SinglePlayerLevelSelectionFlowCoordinator *>();
        levelSelectFlowCoord->PresentViewController(CachedViewControllers->topViewController, NULL, ViewController::AnimationDirection::Vertical, false); });
    return resultsButton;
}

void ShowOtherViewControllers()
{
    auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SinglePlayerLevelSelectionFlowCoordinator *>();
    levelSelectFlowCoord->SetLeftScreenViewController(CachedViewControllers->leftScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetRightScreenViewController(CachedViewControllers->rightScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetTopScreenViewController(CachedViewControllers->topScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetBottomScreenViewController(CachedViewControllers->bottomScreenViewController, ViewController::AnimationType::In);
}

MAKE_HOOK_MATCH(levelSelectDidActivate, &SinglePlayerLevelSelectionFlowCoordinator::SinglePlayerLevelSelectionFlowCoordinatorDidActivate, void, SinglePlayerLevelSelectionFlowCoordinator *self, bool firstActivation, bool addedToHierarchy)
{
    auto mainFlowCoord = UnityEngine::Object::FindObjectOfType<MainFlowCoordinator *>();
    if (firstActivation)
    {
        resultsButton = CreateResultsButton(mainFlowCoord->get_topViewController());
        getLogger().info("Create button.");
        resultsButton->set_interactable(false);
        getLogger().info("Make button unable to be pressed.");
    }
    else if (!firstActivation && CachedViewControllers)
    {
        resultsButton->set_interactable(true);
        getLogger().info("Set button interactable to true.");
    }
    else if (!firstActivation && !CachedViewControllers)
    {
        resultsButton->set_interactable(false);
        getLogger().info("Also set button interactable to false but different lol.");
    }

    levelSelectDidActivate(self, firstActivation, addedToHierarchy);
    getLogger().info("Call level fucker idk");
}

void TakeMeToResults::HookInstallers::SinglePlayerLevelSelectionFlowCoordinator(Logger &logger) {
    INSTALL_HOOK(logger, levelSelectDidActivate);
}