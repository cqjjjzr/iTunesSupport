#pragma once
#ifndef ITS_ITUNES_SUPPORT_PLUGIN
#define ITS_ITUNES_SUPPORT_PLUGIN

#include <NERvGear\plugin.h>
#include <NERvGear\NERvSDK.h>
#include <NERvGear\COM.h>
#include <NERvGear\object.h>

#include "stdafx.h"
#include "ref.h"

using namespace NERvGear;

class iTunesSupport : public PluginImpl {
public:

	virtual long NVG_METHOD OnInitial();
	virtual long NVG_METHOD OnReady();
	virtual long NVG_METHOD OnRelease();
	static int PrepareiTunesLib();

	static BOOL initalized;
private:
	NVG_DECLARE_PLUGIN(iTunesSupport)
};

#endif