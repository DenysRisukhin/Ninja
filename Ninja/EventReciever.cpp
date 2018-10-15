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
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/Instructions.jpg"), vector2d<s32>(-195, 0), false);
						env->addButton(rect<s32>(440, 680, 540, 720), NULL, GUI_ID_INSTRUCTIONS_BACK_BUTTON, L"Back");
						break;

					case GUI_ID_INSTRUCTIONS_BACK_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/background.jpg"), vector2d<s32>(-195, 0), false);
						env->addButton(rect<s32>(380, 200, 620, 270), NULL, GUI_ID_PLAY_BUTTON, L"Play");
						env->addButton(rect<s32>(380, 300, 620, 370), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"About");
						env->addButton(rect<s32>(380, 400, 620, 470), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
						env->addButton(rect<s32>(380, 500, 620, 570), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
						break;

					case GUI_ID_CONTROLS_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/Controls.jpg"), vector2d<s32>(-195, 0), false);
						env->addButton(rect<s32>(440, 680, 540, 720), NULL, GUI_ID_CONTROLS_BACK_BUTTON, L"Back");
						break;

					case GUI_ID_CONTROLS_BACK_BUTTON:
						env->clear();
						env->addImage(context.device->getVideoDriver()->getTexture("Textures/background.jpg"), vector2d<s32>(-195, 0), false);
						env->addButton(rect<s32>(380, 200, 620, 270), NULL, GUI_ID_PLAY_BUTTON, L"Play");
						env->addButton(rect<s32>(380, 300, 620, 370), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"About");
						env->addButton(rect<s32>(380, 400, 620, 470), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
						env->addButton(rect<s32>(380, 500, 620, 570), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
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