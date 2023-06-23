﻿//#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>
#include <string>

using namespace std;

using namespace Cheat;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;

using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Text;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Gaming::XboxGameBar;

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;

namespace sdk
{
	float WindowWidth;
	float WindowHeight;
}

Overlay::Overlay()
{
	InitializeComponent();

	// Hide Title Bar
	auto  coretitlebar = CoreApplication::GetCurrentView()->TitleBar;
	coretitlebar->ExtendViewIntoTitleBar = true;
	auto titlebar = ApplicationView::GetForCurrentView()->TitleBar;
	titlebar->ButtonBackgroundColor = Colors::Transparent;
	titlebar->ButtonInactiveBackgroundColor = Colors::Transparent;
	titlebar->ButtonPressedBackgroundColor = Colors::Transparent;
	titlebar->ButtonHoverBackgroundColor = Colors::Transparent;
}

//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	static auto ds = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);
	ds->Clear(Colors::Transparent);

	/* RENDER*/
	std::string test = std::to_string(sdk::WindowWidth) + "x" + std::to_string(sdk::WindowHeight);
	std::wstring wideText(test.begin(), test.end());
	Platform::String^ text = ref new Platform::String(wideText.c_str());
	ds->DrawText(text, 0, 0, Colors::Red);
	//
	ds->FillRectangle(0, sdk::WindowHeight - 50, sdk::WindowWidth,50,Colors::Red);





	ds->Flush();
	CanvasObject->SwapChain->Present();
}

void InputThread(CoreWindow corewindw)
{
	
}
void Overlay::canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;


	std::thread renderthread(RenderingThread);
	renderthread.detach();
	std::thread inputthread(InputThread);
	inputthread.detach();

}
