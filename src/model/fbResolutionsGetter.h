#ifndef FB_RESOLUTIONS_GETTER
#define FB_RESOLUTIONS_GETTER
#include <string>
#include <list>
#include <iostream>
#include <cstdio>
#include "../interface/evt_model.h"

class FbResolutionsGetter {
	std::list<std::string> data;
	EventListener_model* eventListener;
public:
	FbResolutionsGetter();
	const std::list<std::string>& getData() const;
	void load();
	void setEventListener(EventListener_model& eventListener);
};

#endif
