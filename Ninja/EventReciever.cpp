#include "EventReciever.h"

EventReciever::EventReciever(SAppContext & Context) : context(Context)
{
	for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
	{
		keyDown[i] = false;
	}
}

bool EventReciever::OnEvent(const SEvent& event)
{
	switch (event.EventType)
	{
		case EET_KEY_INPUT_EVENT:
		{
			keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;
		}

		case EET_GUI_EVENT:
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = context.device->getGUIEnvironment();

			switch (event.GUIEvent.EventType)
			{

				case EGET_BUTTON_CLICKED:
				{
					switch (id)
					{
					case GUI_ID_PLAY_BUTTON:
						env->clear();
						*(context.gameStatePtr) = WAVE_0;
						break;
					
					case GUI_ID_INSTRUCTIONS_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/Instructions.bmp"), vector2d<s32>(0, 0), false);
						env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_INSTRUCTIONS_BACK_BUTTON, L"Back");
						break;

					case GUI_ID_INSTRUCTIONS_BACK_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/background.png"), vector2d<s32>(0, 0), false);
						env->addButton(rect<s32>(510, 200, 750, 270), NULL, GUI_ID_PLAY_BUTTON, L"Play");
						env->addButton(rect<s32>(510, 300, 750, 370), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"About");
						env->addButton(rect<s32>(510, 400, 750, 470), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
						env->addButton(rect<s32>(510, 500, 750, 570), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
						break;

					case GUI_ID_CONTROLS_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/Controls.bmp"), vector2d<s32>(0, 0), false);
						env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_CONTROLS_BACK_BUTTON, L"Back");
						break;

					case GUI_ID_CONTROLS_BACK_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/background.png"), vector2d<s32>(0, 0), false);
						env->addButton(rect<s32>(510, 200, 750, 270), NULL, GUI_ID_PLAY_BUTTON, L"Play");
						env->addButton(rect<s32>(510, 300, 750, 370), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"About");
						env->addButton(rect<s32>(510, 400, 750, 470), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
						env->addButton(rect<s32>(510, 500, 750, 570), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
						break;

					case GUI_ID_QUIT_BUTTON:
						env->clear();
						context.device->closeDevice();
						break;
					}
				}
			}
		}

		default:
			break;
	}
	return false;
}

bool EventReciever::isKeyDown(EKEY_CODE keyCode) const
{
	return keyDown[keyCode];
}

bool EventReciever::isKeyUp(EKEY_CODE keyCode) const
{
	return !keyDown[keyCode];
}