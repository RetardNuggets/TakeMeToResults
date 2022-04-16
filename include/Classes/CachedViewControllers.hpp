#pragma once

#include "GlobalNamespace/ResultsViewController.hpp"
#include "HMUI/ViewController.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

class CachedViewControllers
{
    public:
    static ViewController *leftScreenViewController;
    static ViewController *rightScreenViewController;
    static ViewController *topScreenViewController;
    static ViewController *bottomScreenViewController;
    static ViewController *topViewController;
    static void Init();
    static void Clear();
};