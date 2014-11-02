#ifdef DLL_EXPORTS
#define RRENDERER_API __declspec(dllexport) 
#else
#define RRENDERER_API __declspec(dllimport) 
#endif