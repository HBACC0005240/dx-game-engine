#pragma once
namespace AHLIN {

	class Exception {
		private:
			const wchar_t* file;
			const wchar_t* msg;
			unsigned int line;
			wchar_t buf[256];
		public:
			Exception(const wchar_t* file, unsigned int line, const wchar_t* msg)
				:file(file), msg(msg), line(line)
			{
				wsprintf(buf, L"%s \nLine [%d] %s ", msg,line, file);
			}

			~Exception() {

			}

			const wchar_t* what() const
			{
				return buf;
			}
	};
}