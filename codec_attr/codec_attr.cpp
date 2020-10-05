
#include <iostream>

#include <wrl.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

int main()
{
	HRESULT hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	MFT_REGISTER_TYPE_INFO output_typeinfo;
	output_typeinfo.guidMajorType = MFMediaType_Video;
	output_typeinfo.guidSubtype = MFVideoFormat_H264;
	IMFActivate **devices = NULL;
	UINT32 num_devices;
	hr = MFTEnumEx(MFT_CATEGORY_VIDEO_ENCODER, MFT_ENUM_FLAG_ALL,
		NULL, &output_typeinfo,
		&devices, &num_devices);

	std::cout << "Encoder: " << num_devices << std::endl;
	for (UINT32 i = 0; i < num_devices; i++) {
		LPWSTR name = NULL;
		hr = devices[i]->GetAllocatedString(MFT_FRIENDLY_NAME_Attribute,
			&name, NULL);

		if (hr == S_OK) {
			printf_s("%ls\n", name);
			CoTaskMemFree(name);
		}

		devices[i]->Release();
	}

	CoTaskMemFree(devices);
}
