#include "testApp.h"
#include "testFrame.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

testApp::testApp(void)
{
}

testApp::~testApp(void)
{
}

UiApp*
testApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new testApp();
}

bool
testApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize Frame and App specific data.
	// The App's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the App will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// TODO:
	// Add your initialization code here

	return true;
}

bool
testApp::OnAppInitialized(void)
{
	// TODO:
        // Add code to do after initialization here. 

	// Create a Frame
	testFrame* ptestFrame = new testFrame();
	ptestFrame->Construct();
	ptestFrame->SetName(L"test");
	AddFrame(*ptestFrame);

	ptestFrame->AddKeyEventListener(*this);

	{
		__player = new Tizen::Graphics::Opengl::GlPlayer;
		__player->Construct(Tizen::Graphics::Opengl::EGL_CONTEXT_CLIENT_VERSION_1_X, ptestFrame->GetCurrentForm());

		__player->SetFps(60);
		__player->SetEglAttributePreset(Tizen::Graphics::Opengl::EGL_ATTRIBUTES_PRESET_RGB565);

		__player->Start();
	}

	__renderer = new GlRendererTemplate();
	__player->SetIGlRenderer(__renderer);

	return true;
}

bool
testApp::OnAppWillTerminate(void)
{
	// TODO:
        // Add code to do somethiing before application termination. 

	return true;
}


bool
testApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this App for termination.
	// The App's permanent data and context can be saved via appRegistry.

	__player->Stop();

	if(__renderer != null)
	{
		delete __renderer;
	}
	delete __player;

	return true;
}

void
testApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
testApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
testApp::OnLowMemory(void)
{
	// TODO:
	// Free unnecessary resources or close the application.
}

void
testApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
testApp::OnScreenOn(void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
testApp::OnScreenOff(void)
{
	// TODO:
	// Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device
	// to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a
	// callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}

void
testApp::OnKeyPressed(const Control& source, KeyCode keyCode)
{
}

void
testApp::OnKeyReleased(const Control& source, KeyCode keyCode)
{
	if (keyCode == Tizen::Ui::KEY_BACK || keyCode == Tizen::Ui::KEY_ESC)
	{
		Terminate();
	}
}

void
testApp::OnKeyLongPressed(const Control& source, KeyCode keyCode)
{
}
