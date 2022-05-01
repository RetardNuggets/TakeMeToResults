#include "main.hpp"
#include "CachedViewControllers.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "System/Action.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo;

UnityEngine::UI::Button *resultsButton;

Logger &getLogger()
{
    static Logger *logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(ResultsViewController_ContinueButtonPressed, &ResultsViewController::ContinueButtonPressed, void, ResultsViewController *self)
{
    CachedViewControllers::GetViewControllers();

    ResultsViewController_ContinueButtonPressed(self);

    if(resultsButton)
    {
        resultsButton->set_interactable(true);
    }
}

MAKE_HOOK_MATCH(PlatformLeaderboardViewController_DidActivate, &PlatformLeaderboardViewController::DidActivate, void, PlatformLeaderboardViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (firstActivation)
    {
        CachedViewControllers::Clear();
        resultsButton = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "View Results", []()
        {
            auto flowCoordinator = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
            static auto delegate = il2cpp_utils::MakeDelegate<System::Action *>((std::function<void()>) [] { CachedViewControllers::ShowViewControllers(); });
            if (CachedViewControllers::topViewController)
            {
                flowCoordinator->PresentViewController(CachedViewControllers::topViewController, delegate, HMUI::ViewController::AnimationDirection::Vertical, false);
            }
        });
        getLogger().info("Created View Results UIButton.");
        auto rect = reinterpret_cast<UnityEngine::RectTransform *>(resultsButton->get_transform());
        rect->set_anchoredPosition({-47.3, -27});
        getLogger().info("Set the anchoredPosition of the View Results UIButton.");
        resultsButton->set_interactable(false);
        getLogger().info("Set View Results UIButton to be uninteractable.");
    }
    
    PlatformLeaderboardViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

extern "C" void setup(ModInfo &info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getLogger().info("Completed setup!");
}

extern "C" void load()
{
    il2cpp_functions::Init();
    QuestUI::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), ResultsViewController_ContinueButtonPressed);
    INSTALL_HOOK(getLogger(), PlatformLeaderboardViewController_DidActivate);
    getLogger().info("Installed all hooks!");
}