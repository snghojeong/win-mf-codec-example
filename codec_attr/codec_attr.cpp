
#include <iostream>

#include <wrl.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

int main()
{
	HRESULT hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	MFT_REGISTER_TYPE_INFO io_typeinfo;
	io_typeinfo.guidMajorType = MFMediaType_Video;
	io_typeinfo.guidSubtype = MFVideoFormat_H264;
	IMFActivate **devices = NULL;
	UINT32 num_devices;
	hr = MFTEnumEx(MFT_CATEGORY_VIDEO_ENCODER, MFT_ENUM_FLAG_ALL, // MFT_ENUM_FLAG_HARDWARE | MFT_ENUM_FLAG_ASYNCMFT | MFT_ENUM_FLAG_SORTANDFILTER | MFT_ENUM_FLAG_SORTANDFILTER_APPROVED_ONLY,
		NULL, &io_typeinfo,
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

	hr = MFTEnumEx(MFT_CATEGORY_VIDEO_DECODER, MFT_ENUM_FLAG_ALL,
		&io_typeinfo, NULL,
		&devices, &num_devices);

	std::cout << "Decoder: " << num_devices << std::endl;
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
