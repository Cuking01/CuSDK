#pragma once

#define CUSDK_VERSION_ID "0.0.0"
#define CUSDK_VERSION_TAG "begin"

#ifndef APP_VERSION_ID
	#warning "APP_VERSION_ID don't be defined."
	#define APP_VERSION_ID "default version"
#endif

#ifndef APP_VERSION_TAG
	#warning "APP_VERSION_TAG don't be defined."
	#define APP_VERSION_TAG "default tag"
#endif

