#pragma once
#include <string>
namespace DiplomaPCA
{


	/*XXE Helper class*/
	static class Xhelper {
	public:
		/*Convert String^ to std::string*/
		static std::string sysStrToStdStr(System::String ^ s) {
			using namespace System::Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string res = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
			return res;
		}

		/*Convert std::string to String^*/
		static System::String^ stdStrToSysStr(std::string s)
		{
			System::String^ res = gcnew System::String(s.c_str());
			return res;
		}

	};
}