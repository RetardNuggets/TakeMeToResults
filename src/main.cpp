#include "main.hpp"
#include "CachedViewControllers.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"
#include "System/Action.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo;

UnityEngine::UI::Button *resultsButton;
bool suppressActivations = false;

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
        auto canvas = QuestUI::BeatSaberUI::CreateCanvas();
        canvas->get_transform()->SetParent(self->get_transform(), false);
        canvas->get_transform()->set_localScale({1, 1, 1});
        canvas->GetComponent<UnityEngine::RectTransform *>()->set_anchoredPosition({-25, 48});
        resultsButton = QuestUI::BeatSaberUI::CreateUIButton(canvas, "View Last Results", UnityEngine::Vector2(0, 0), UnityEngine::Vector2(30, 10), []
        {
            auto flowCoordinator = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
            static auto delegate = il2cpp_utils::MakeDelegate<System::Action *>((std::function<void()>) [] { CachedViewControllers::ShowViewControllers(); });
            if (CachedViewControllers::topViewController)
            {
                suppressActivations = true;
                flowCoordinator->PresentViewController(CachedViewControllers::topViewController, delegate, HMUI::ViewController::AnimationDirection::Vertical, false);
                suppressActivations = false;
            }
        });
        resultsButton->set_interactable(false);
    }
    
    PlatformLeaderboardViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(ViewController___Activate, &HMUI::ViewController::__Activate, void, HMUI::ViewController *self, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (suppressActivations)
    {
        self->isActivated = true;
        if (!self->get_gameObject()->get_activeSelf())
        {
            self->get_gameObject()->SetActive(true);
        }
    }
    else
    {
        ViewController___Activate(self, addedToHierarchy, screenSystemEnabling);
    }
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
    INSTALL_HOOK(getLogger(), ViewController___Activate);
    getLogger().info("Installed all hooks!");
}