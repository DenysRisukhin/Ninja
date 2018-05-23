#include "MenuInfo.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;

MenuInfo::MenuInfo(Game* game, const path& filename): Info(game, filename)
{
	while (next());
}

MenuInfo::~MenuInfo(void)
{
	//SoundTex->drop();
}

void MenuInfo::OnNode(const stringw& name)
{
	if (name == "menu") {

		ColumnsCount = read<u32>("columnsCount");

		Margin = read<u32>("margin");

		ButtonSize.Width = read<u32>("buttonWidth");
		ButtonSize.Height = read<u32>("buttonHeight");

		ButtonTextures.Default = read<ITexture*>("defaultButtonTexture");
		ButtonTextures.Active = read<ITexture*>("activeButtonTexture");
		ButtonTextures.Clicked = read<ITexture*>("clickedButtonTexture");

	//	SoundTex = read<ITexture*>("ss");
	////	SoundTex = "C:/Den/Programming/TestProjects/PathGame/PathGameDemo/PathGame/Media/Images/sound.png";
	//	SoundTex = game->g driver->addRenderTargetTexture(core::dimension2d<u32>(256, 256), "RTT1");
	//		//read<ITexture*>("ss");

		Font = read<IGUIFont*>("font");
		FontColor = read<SColor>("fontColor");

	}
	else if (name == "button") {

		MenuInfo::Button button;

		button.Event = (GAME_EVENT)read<u32>("event");
		button.Text = read<stringw>("text");

		Buttons.push_back(button);

	}
	else if (name == "buttons") {

		SoundFilenames.Click = read<path>("clickSound");
		SoundFilenames.Select = read<path>("selectSound");

	}
}