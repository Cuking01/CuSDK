#pragma once

#define CUSDK_VERSION_ID "0.1.0"
#define CUSDK_VERSION_TAG "beta-safe operator"

#ifndef APP_VERSION_ID
	#warning "APP_VERSION_ID don't be defined."
	#define APP_VERSION_ID "default version"
#endif

#ifndef APP_VERSION_TAG
	#warning "APP_VERSION_TAG don't be defined."
	#define APP_VERSION_TAG "default tag"
#endif

