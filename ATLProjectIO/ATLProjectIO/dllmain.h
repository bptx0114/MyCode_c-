// dllmain.h : 模块类的声明。

class CATLProjectIOModule : public ATL::CAtlDllModuleT< CATLProjectIOModule >
{
public :
	DECLARE_LIBID(LIBID_ATLProjectIOLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTIO, "{398621CF-26E8-407F-91CF-675B2257CB8D}")
};

extern class CATLProjectIOModule _AtlModule;
