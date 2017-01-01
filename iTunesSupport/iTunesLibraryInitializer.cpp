#include "iTunesLibraryInitializer.h"
#include "iTunesSupport.h"

BOOL iTunesLibraryInitializer::initialized = false;

long iTunesLibraryInitializer::init()
{
	if (!initialized) {
		long result = iTunesSupport::PrepareiTunesLib();
		initialized = true;
		return result;
	}
	return S_OK;
}

iTunesLibraryInitializer::iTunesLibraryInitializer()
{
}


iTunesLibraryInitializer::~iTunesLibraryInitializer()
{
}
