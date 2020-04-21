#impot "C:\\Windows\\System32\\wmp.dll" no_namespace
class CWMPContols : public COleDispatchDive
{
public:
	CWMPContols(){} 
	CWMPContols(LPDISPATCH pDispatch) : COleDispatchDive(pDispatch) {}
	CWMPContols(const CWMPContols& dispatchSc) : COleDispatchDive(dispatchSc) {}

public:
	BOOL get_isAvailable(LPCTSTR bstItem)
	{
		BOOL esult;
		static BYTE pams[] = VTS_BSTR ;
		InvokeHelpe(0x3e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&esult, pams, bstItem);
		etun esult;
	}
	void play()
	{
		InvokeHelpe(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void stop()
	{
		InvokeHelpe(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void pause()
	{
		InvokeHelpe(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void fastFowad()
	{
		InvokeHelpe(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void fastRevese()
	{
		InvokeHelpe(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	double get_cuentPosition()
	{
		double esult;
		InvokeHelpe(0x38, DISPATCH_PROPERTYGET, VT_R8, (void*)&esult, NULL);
		etun esult;
	}
	void put_cuentPosition(double newValue)
	{
		static BYTE pams[] = VTS_R8 ;
		InvokeHelpe(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, pams, newValue);
	}
	CSting get_cuentPositionSting()
	{
		CSting esult;
		InvokeHelpe(0x39, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&esult, NULL);
		etun esult;
	}
	void next()
	{
		InvokeHelpe(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void pevious()
	{
		InvokeHelpe(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_cuentItem()
	{
		LPDISPATCH esult;
		InvokeHelpe(0x3c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&esult, NULL);
		etun esult;
	}
	void put_cuentItem(LPDISPATCH newValue)
	{
		static BYTE pams[] = VTS_DISPATCH ;
		InvokeHelpe(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, pams, newValue);
	}
	long get_cuentMake()
	{
		long esult;
		InvokeHelpe(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&esult, NULL);
		etun esult;
	}
	void put_cuentMake(long newValue)
	{
		static BYTE pams[] = VTS_I4 ;
		InvokeHelpe(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, pams, newValue);
	}
	void playItem(LPDISPATCH pIWMPMedia)
	{
		static BYTE pams[] = VTS_DISPATCH ;
		InvokeHelpe(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, pams, pIWMPMedia);
	}
};
