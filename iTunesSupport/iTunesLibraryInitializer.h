#pragma once
typedef int BOOL;

class iTunesLibraryInitializer
{
public:
	static long init();
	static BOOL isInitialized();
private:
	static BOOL initialized;
	iTunesLibraryInitializer();
	~iTunesLibraryInitializer();
};

