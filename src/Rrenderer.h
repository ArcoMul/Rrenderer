#ifdef DLL_EXPORTS
#define RRENDERER_API __declspec(dllexport) 
#else
#define RRENDERER_API __declspec(dllimport) 
#endif

# define M_PI           3.14159265358979323846  /* pi */