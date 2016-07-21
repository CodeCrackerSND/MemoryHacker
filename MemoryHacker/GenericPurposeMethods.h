// GenericPurposeMethods.h: interface for the GenericPurposeMethods class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICPURPOSEMETHODS_H__DB5CA191_5583_4171_9A54_3B45355468DF__INCLUDED_)
#define AFX_GENERICPURPOSEMETHODS_H__DB5CA191_5583_4171_9A54_3B45355468DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GenericPurposeMethods  
{
public:
	GenericPurposeMethods();
	virtual ~GenericPurposeMethods();
	static unsigned int ConvertHexStringToInt(CString sHexNum);
	static bool IsHexNumber(char tobetested);
	static unsigned int Pow(int value,int exponent);
	static unsigned __int64 BigPow(unsigned __int64 value,unsigned __int64 exponent);
	static int StringToNumber(char *buffer);
	static void ToUpperCase(char *buffer);
	static unsigned int UnsignedArrayToUInt(unsigned char *buffer,int position);
	static unsigned char* UIntToUnsignedArray(unsigned int value);
	static unsigned int UnsignedArrayToShort(unsigned char *buffer,int position);
	static unsigned char* StringToBytes(char *value, char *type, char *base, int *out_len);
	static unsigned char GetCharFromStr(char *value, char *base);
	static unsigned char GetCharFromTStr(char *value, char *base);
	static unsigned short GetShortFromStr(char *value, char *base);
	static unsigned short GetShortFromTStr(char *buffer, char *base);
	static unsigned int GetIntFromStr(char *value, char *base);
	static unsigned int GetIntFromTStr(char *buffer, char *base);
	static unsigned __int64 GetLongFromStr(char *value, char *base);
	static unsigned __int64 GetLongFromTStr(char *buffer, char *base);
	static float str2float(char* s);
	static float str2float(char* s, char *base);
	static double str2double(char* s);
	static double str2double(char* s, char *base);
	static char* BytesToString(unsigned char* bytes, int bytes_len, char *type, char *base);
	static char* TruncateString(char *value, int newlen);
	static char* Substring(char *value, int start_index, int end_index);
	static char NumberToCharString(char input);
	static char* double2str(double number, char *base);
	static TCHAR* GetShortModuleName(TCHAR fullname[]);
	static TCHAR* GetDirectory(TCHAR fullname[]);
	static TCHAR* GetDumpFileName(TCHAR shortname[]);
	static TCHAR* GetExtension(TCHAR shortname[]);
	static TCHAR* JoinChars(TCHAR first[],TCHAR second[]);
	static bool ContainsExtension(TCHAR filename[]);
 	static TCHAR* GetMemoryProtectionInfo(unsigned int value);

};

#endif // !defined(AFX_GENERICPURPOSEMETHODS_H__DB5CA191_5583_4171_9A54_3B45355468DF__INCLUDED_)
