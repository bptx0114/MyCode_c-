// CInterfaceIO.h : CCInterfaceIO ������

#pragma once
#include "resource.h"       // ������



#include "ATLProjectIO_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CCInterfaceIO

class ATL_NO_VTABLE CCInterfaceIO :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCInterfaceIO, &CLSID_CInterfaceIO>,
	public IDispatchImpl<ICInterfaceIO, &IID_ICInterfaceIO, &LIBID_ATLProjectIOLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCInterfaceIO()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CINTERFACEIO)


BEGIN_COM_MAP(CCInterfaceIO)
	COM_INTERFACE_ENTRY(ICInterfaceIO)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(Test)(BSTR Arg1, BSTR Arg2, BSTR* Output, VARIANT_BOOL* Rst);
};

OBJECT_ENTRY_AUTO(__uuidof(CInterfaceIO), CCInterfaceIO)
