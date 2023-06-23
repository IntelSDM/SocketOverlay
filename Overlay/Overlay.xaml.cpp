//#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>

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

Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;

namespace sdk
{
	float WindowWidth;
	float WindowHeight;
}

Overlay::Overlay()
{
	InitializeComponent();
}

//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	static auto ds = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);

	ds->Clear(Colors::Transparent);

	/* RENDER*/

	ds->DrawText("Hello", 0, 0, Colors::Red);
	/*END OF RENDERING*/


	ds->Flush();

	CanvasObject->SwapChain->Present();

	ds->Clear(Colors::Transparent);
}


void Overlay::canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;

	std::thread RenderThread(RenderingThread);
	RenderThread.detach();

}
