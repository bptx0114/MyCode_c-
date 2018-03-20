// dllmain.h : 模块类的声明。

class CATLProject1Module : public ATL::CAtlDllModuleT< CATLProject1Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProject1Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT1, "{4C08FF96-C873-4FBD-979C-79F3E4E09679}")
};

extern class CATLProject1Module _AtlModule;
