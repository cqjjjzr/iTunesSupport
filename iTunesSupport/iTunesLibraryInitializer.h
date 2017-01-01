#pragma once
typedef int BOOL;

class iTunesLibraryInitializer
{
public:
	static long init();
private:
	static BOOL initialized;
	iTunesLibraryInitializer();
	~iTunesLibraryInitializer();
};

