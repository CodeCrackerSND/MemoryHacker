// GenericPurposeMethods.cpp: implementation of the GenericPurposeMethods class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemoryHacker.h"
#include "GenericPurposeMethods.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GenericPurposeMethods::GenericPurposeMethods()
{

}

GenericPurposeMethods::~GenericPurposeMethods()
{

}

int GenericPurposeMethods::StringToNumber(char *buffer)
{
   int result = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }

   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

      if(buffer[i] >= '0' && buffer[i] <= '9')
      {
         int digit = buffer[i] - '0';
         result = result * 10 + digit;
      }
      else
      return 0;

   }

   if (negativeNumber == true)
      result *= -1;

   return result;
}

unsigned int GenericPurposeMethods::ConvertHexStringToInt(CString sHexNum)
{
   unsigned int iSum = 0;
   if (sHexNum.GetLength() == 0) return 0;

   for(int i=sHexNum.GetLength()-1; i >= 0; i--)
   {
	  if (!GenericPurposeMethods::IsHexNumber(sHexNum[i])) return 0;

      if(sHexNum[i])
      {
	  unsigned int current_char = sHexNum[i]-'0';
	  if (current_char>=0x011&&current_char<=0x016)  // is it 'A'- 'F'
	  current_char = current_char - 07;

	  if (current_char>=0x031&&current_char<=0x036)  // is it 'a'- 'f'
	  current_char = current_char - 0x27;

      iSum += current_char*Pow(16,sHexNum.GetLength()-1-i);
      }
   }
   return iSum;

}

bool GenericPurposeMethods::IsHexNumber(char tobetested)
{
if (tobetested >= '0' && tobetested <= '9')
return true;

if (tobetested >= 'A' && tobetested <= 'F')
return true;

if (tobetested >= 'a' && tobetested <= 'f')
return true;

return false;
}

unsigned int GenericPurposeMethods::Pow(int value,int exponent)
{
	unsigned int result = 1;

	for (int i = 0; i < exponent; ++i)
	result *= value;

	return (result);
}


unsigned __int64 GenericPurposeMethods::BigPow(unsigned __int64 value,unsigned __int64 exponent)
{
	unsigned __int64 result = 1;

	for (int i = 0; i < exponent; ++i)
	result *= value;

	return (result);
}

void GenericPurposeMethods::ToUpperCase(char *buffer)
{
   for (int i = 0; i < (int)strlen(buffer); i++)
   {

      if(buffer[i] >= 'a' && buffer[i] <= 'z')
      {
	   buffer[i] -= 'a'-'A';
	  }
   }
}

unsigned int GenericPurposeMethods::UnsignedArrayToUInt(unsigned char *buffer,int position)
{
return ((buffer[position+3]<<24)|(buffer[position+2]<<16)|(buffer[position+1]<<8)|(buffer[position+0]));
}

unsigned int GenericPurposeMethods::UnsignedArrayToShort(unsigned char *buffer,int position)
{
return ((buffer[position+1]<<8)|(buffer[position+0]));
}

unsigned char* GenericPurposeMethods::UIntToUnsignedArray(unsigned int value)
{
unsigned char* array = new unsigned char[4];
array[0] = value & 0x000000ff;
array[1] = (value & 0x0000ff00) >> 8;
array[2] = (value & 0x00ff0000) >> 16;
array[3] = (value & 0xff000000) >> 24;

return array;

}

unsigned char* GenericPurposeMethods::StringToBytes(char *value, char *type, char *base, int *out_len)
{
out_len[0] = 0;  // set out len to 0
unsigned char* array = new unsigned char[0];

if (strlen(value)>0&&strlen(type)>0&&strlen(base)>0)
{

if (strcmp(type,CString(_T("byte")).GetBuffer(0))==0)
{  // if type is byte
out_len[0] = 1;  // set out len to 1
array = new unsigned char[1];
array[0] = GenericPurposeMethods::GetCharFromStr(value,base);
}

if (strcmp(type,CString(_T("word")).GetBuffer(0))==0)
{  // if type is word
out_len[0] = 2;  // set out len to 2
array = new unsigned char[2];
unsigned short svalue = GenericPurposeMethods::GetShortFromStr(value,base);

array[0] = svalue & 0x000000ff;
array[1] = (svalue & 0x0000ff00) >> 8;

}

if (strcmp(type,CString(_T("dword")).GetBuffer(0))==0)
{  // if type is dword
out_len[0] = 4;  // set out len to 4
array = new unsigned char[4];
unsigned int ivalue = GenericPurposeMethods::GetIntFromStr(value,base);

array[0] = ivalue & 0x000000ff;
array[1] = (ivalue & 0x0000ff00) >> 8;
array[2] = (ivalue & 0x00ff0000) >> 16;
array[3] = (ivalue & 0xff000000) >> 24;

}

if (strcmp(type,CString(_T("qword")).GetBuffer(0))==0)
{  // if type is qword
out_len[0] = 8;  // set out len to 8
array = new unsigned char[8];
unsigned __int64 lvalue = GenericPurposeMethods::GetLongFromStr(value,base);

array[0] = (unsigned char)(lvalue & 0x00000000000000ff);
array[1] = (unsigned char)((lvalue & 0x000000000000ff00) >> 8);
array[2] = (unsigned char)((lvalue & 0x0000000000ff0000) >> 16);
array[3] = (unsigned char)((lvalue & 0x00000000ff000000) >> 24);
array[4] = (unsigned char)((lvalue & 0x000000ff00000000) >> 32);
array[5] = (unsigned char)((lvalue & 0x0000ff0000000000) >> 40);
array[6] = (unsigned char)((lvalue & 0x00ff000000000000) >> 48);
array[7] = (unsigned char)((lvalue & 0xff00000000000000) >> 56);

}

if (strcmp(type,CString(_T("bytes")).GetBuffer(0))==0)
{ // if type is bytes
int chars_per_byte = 0;
if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
chars_per_byte = 3;
else
chars_per_byte = 2;

int ostrlen = (int)strlen(value);
int bsize = ostrlen/chars_per_byte;

out_len[0] = bsize;  // set out len
array = new unsigned char[bsize];

int start_index = 0;
int end_index = 0;

for (int i=0;i<bsize;i++)
{
end_index = start_index+chars_per_byte;
char* currentsub = GenericPurposeMethods::Substring(value, start_index, end_index);
start_index = start_index+chars_per_byte;
array[i] = GenericPurposeMethods::GetCharFromStr(currentsub,base);
}



}

if (strcmp(type,CString(_T("ASCII string")).GetBuffer(0))==0)
{ // if type is ASCII string
out_len[0] = (int)strlen(value);  // set out len
array = new unsigned char[out_len[0]];

for (int i=0;i<out_len[0];i++)
array[i] = value[i];

}

if (strcmp(type,CString(_T("UNICODE string")).GetBuffer(0))==0)
{ // if type is UNICODE string
int olen = strlen(value);
out_len[0] = olen*2;  // set out len, UNICODE have double size of ASCII
array = new unsigned char[out_len[0]];

for (int i=0;i<olen;i++)
{
array[i*2] = value[i];
array[i*2+1] = 00; // 00 since is a UNICODE STRING
}

}

if (strcmp(type,CString(_T("float")).GetBuffer(0))==0)
{ // if type is float
out_len[0] = sizeof(float);  // set out len
array = new unsigned char[out_len[0]];

float fvalue = GenericPurposeMethods::str2float(value,base);
unsigned char* pointer = (unsigned char*)&fvalue;

  for(int i = 0; i < out_len[0]; i++)
  {
    array[i] = pointer[i];
  }

}

if (strcmp(type,CString(_T("double")).GetBuffer(0))==0)
{ // if type is float
out_len[0] = sizeof(double);  // set out len
array = new unsigned char[out_len[0]];

double dvalue = GenericPurposeMethods::str2double(value,base);
unsigned char* pointer = (unsigned char*)&dvalue;

  for(int i = 0; i < out_len[0]; i++)
  {
    array[i] = pointer[i];
  }

}

}  // end of if we even have something to convert

return array;
}

char GenericPurposeMethods::NumberToCharString(char input)
{

	char rchar = input;

	if (rchar>=0&&rchar<=9)
	rchar = rchar+'0';
	else if (rchar>=0x0A&&rchar<=0x0F)
	rchar = rchar+'A'-0x0A;

	return rchar;

}

char* GenericPurposeMethods::BytesToString(unsigned char* bytes, int bytes_len, char *type, char *base)
{
char* cstring = new char[1];
cstring[0] = 0;

if (bytes_len>0&&strlen(type)>0&&strlen(base)>0)
{

if (strcmp(type,CString(_T("byte")).GetBuffer(0))==0||strcmp(type,CString(_T("bytes")).GetBuffer(0))==0)
{  // if type is byte

if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
cstring = new char[bytes_len*2+1];

  for (int i = 0; i < bytes_len; i++)
  {

	char firstchar = (bytes[i] & 0xF0) >> 4;
	char secondchar = bytes[i] & 0x0F;

	firstchar = GenericPurposeMethods::NumberToCharString(firstchar);
	secondchar = GenericPurposeMethods::NumberToCharString(secondchar);

    cstring[2 * i]     = firstchar;
    cstring[2 * i + 1] = secondchar;
  }

cstring[bytes_len*2] = 00; // the end marker of string
}  // end of hex

else if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
cstring = new char[bytes_len*3+1];

  for (int i = 0; i < bytes_len; i++)
  {
	cstring[3*i] = '0' + bytes[i] / 100;
	cstring[3*i + 1] = '0' + (bytes[i] / 10) % 10;
	cstring[3*i + 2] = '0' + bytes[i] % 10;
  }

  cstring[3*i] = 0;

}

}

if (strcmp(type,CString(_T("word")).GetBuffer(0))==0)
{  // if type is word
unsigned short svalue = bytes[0] | (bytes[1] << 8);

if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
cstring = new char[2*2+1];

	char firstchar = (bytes[1] & 0xF0) >> 4;
	char secondchar = bytes[1] & 0x0F;

	firstchar = GenericPurposeMethods::NumberToCharString(firstchar);
	secondchar = GenericPurposeMethods::NumberToCharString(secondchar);

	if (secondchar>=0&&secondchar<=9)
	secondchar = secondchar+'0';
	else if (secondchar>=0x0A&&secondchar<=0x0F)
	secondchar = secondchar+'A'-0x0A;

    cstring[0] = firstchar;
    cstring[1] = secondchar;

	firstchar = (bytes[0] & 0xF0) >> 4;
	secondchar = bytes[0] & 0x0F;

	firstchar = GenericPurposeMethods::NumberToCharString(firstchar);
	secondchar = GenericPurposeMethods::NumberToCharString(secondchar);

    cstring[2] = firstchar;
    cstring[3] = secondchar;

    cstring[4] = 00; // mark the end of string

}

else if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
	cstring = new char[2*3+1];
	cstring[0] = 00;
	wsprintf(cstring,"%d",svalue);  // convert short number to decimal string

}

}

if (strcmp(type,CString(_T("dword")).GetBuffer(0))==0)
{  // if type is dword
unsigned int ivalue = 0;
ivalue = (ivalue << 8) + bytes[3];
ivalue = (ivalue << 8) + bytes[2];
ivalue = (ivalue << 8) + bytes[1];
ivalue = (ivalue << 8) + bytes[0];

if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
	cstring = new char[4*2+1];
	cstring[0] = 00;
	wsprintf(cstring,"%X",ivalue);  // convert int number to hexadecimal string
}
else if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
	cstring = new char[4*3+1];
	cstring[0] = 00;
	wsprintf(cstring,"%d",ivalue);  // convert int number to decimal string
}

}

if (strcmp(type,CString(_T("qword")).GetBuffer(0))==0)
{  // if type is qword
unsigned __int64 lvalue = 0;
lvalue = (lvalue << 8) + bytes[7];
lvalue = (lvalue << 8) + bytes[6];
lvalue = (lvalue << 8) + bytes[5];
lvalue = (lvalue << 8) + bytes[4];
lvalue = (lvalue << 8) + bytes[3];
lvalue = (lvalue << 8) + bytes[2];
lvalue = (lvalue << 8) + bytes[1];
lvalue = (lvalue << 8) + bytes[0];

if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
	cstring = new char[8*2+1];
	cstring[0] = 00;
	wsprintf(cstring,"%I64X",lvalue);  // convert long number to hexadecimal string
}
else if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
	cstring = new char[8*3+1];
	cstring[0] = 00;
	wsprintf(cstring,"%I64u",lvalue);  // convert long number to decimal string
}

}

if (strcmp(type,CString(_T("ASCII string")).GetBuffer(0))==0)
{ // if type is ASCII string
cstring = new char[bytes_len+1];

for (int i=0;i<bytes_len;i++)
cstring[i] = bytes[i];

cstring[bytes_len] = 0 ; // mark the end of string
}

if (strcmp(type,CString(_T("UNICODE string")).GetBuffer(0))==0)
{ // if type is UNICODE string
cstring = new char[bytes_len/2+1];

for (int i=0;i<bytes_len;i++)
{
if (i%2==0)
cstring[i/2] = bytes[i];
}

cstring[bytes_len/2] = 0 ; // mark the end of string

}


if (strcmp(type,CString(_T("float")).GetBuffer(0))==0)
{ // if type is float

float* pointer = (float*)bytes;
float fvalue = pointer[0];

cstring = GenericPurposeMethods::double2str((double)fvalue,base);

}

if (strcmp(type,CString(_T("double")).GetBuffer(0))==0)
{ // if type is float
double* dpointer = (double*)bytes;
double fvalue = dpointer[0];

cstring = GenericPurposeMethods::double2str(fvalue,base);

}

}  // if we even have something

return cstring;
}


unsigned char GenericPurposeMethods::GetCharFromStr(char *value, char *base)
{
unsigned char converted = 0;
int max_len = 0;
if (value[0] == '-') max_len++;  // for negative number increment
if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if decimal as base
max_len = max_len+3;
}
else if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
max_len = max_len+2;
}

char *truncated_value = GenericPurposeMethods::TruncateString(value, max_len);
converted = GenericPurposeMethods::GetCharFromTStr(value, base);
return converted;
}

unsigned char GenericPurposeMethods::GetCharFromTStr(char *buffer, char *base)
{
   unsigned char result = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }

   bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

	if (isdecimal)
	{
      if (buffer[i] >= '0' && buffer[i] <= '9')
      {
         unsigned char digit = buffer[i] - '0';
         result = result * 10 + digit;
      }
      else
      return 0;
	  
	}
	else  // hexadecimal parse:
	{
	if (!GenericPurposeMethods::IsHexNumber(buffer[i])) return 0;

	  if(buffer[i])
      {
	  unsigned char current_char = buffer[i]-'0';
	  if (current_char>=0x011&&current_char<=0x016)  // is it 'A'- 'F'
	  current_char = current_char - 07;

	  if (current_char>=0x031&&current_char<=0x036)  // is it 'a'- 'f'
	  current_char = current_char - 0x27;

      result += current_char*Pow(16,strlen(buffer)-1-i);
      }
	}

   }

   if (negativeNumber == true)
      result *= -1;

   return result;
}

unsigned short GenericPurposeMethods::GetShortFromStr(char *value, char *base)
{
unsigned short converted = 0;
int max_len = 0;
if (value[0] == '-') max_len++;  // for negative number increment
if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if decimal as base
max_len = max_len+3*2;
}
else if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
max_len = max_len+2*2;
}

char *truncated_value = GenericPurposeMethods::TruncateString(value, max_len);
converted = GenericPurposeMethods::GetShortFromTStr(value, base);
return converted;
}

unsigned short GenericPurposeMethods::GetShortFromTStr(char *buffer, char *base)
{
   unsigned short result = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }

   bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

	if (isdecimal)
	{
      if (buffer[i] >= '0' && buffer[i] <= '9')
      {
         unsigned short digit = buffer[i] - '0';
         result = result * 10 + digit;
      }
      else
      return 0;
	  
	}
	else  // hexadecimal parse:
	{
	if (!GenericPurposeMethods::IsHexNumber(buffer[i])) return 0;

	  if(buffer[i])
      {
	  unsigned short current_char = buffer[i]-'0';
	  if (current_char>=0x011&&current_char<=0x016)  // is it 'A'- 'F'
	  current_char = current_char - 07;

	  if (current_char>=0x031&&current_char<=0x036)  // is it 'a'- 'f'
	  current_char = current_char - 0x27;

      result += current_char*Pow(16,strlen(buffer)-1-i);
      }
	}

   }

   if (negativeNumber == true)
      result *= -1;

   return result;
}

unsigned int GenericPurposeMethods::GetIntFromStr(char *value, char *base)
{
unsigned int converted = 0;
int max_len = 0;
if (value[0] == '-') max_len++;  // for negative number increment
if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if decimal as base
max_len = max_len+3*4;
}
else if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
max_len = max_len+2*4;
}

char *truncated_value = GenericPurposeMethods::TruncateString(value, max_len);
converted = GenericPurposeMethods::GetIntFromTStr(value, base);
return converted;
}

unsigned int GenericPurposeMethods::GetIntFromTStr(char *buffer, char *base)
{
   unsigned int result = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }

   bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

	if (isdecimal)
	{
      if (buffer[i] >= '0' && buffer[i] <= '9')
      {
         unsigned int digit = buffer[i] - '0';
         result = result * 10 + digit;
      }
      else
      return 0;
	  
	}
	else  // hexadecimal parse:
	{
	if (!GenericPurposeMethods::IsHexNumber(buffer[i])) return 0;

	  if(buffer[i])
      {
	  unsigned int current_char = buffer[i]-'0';
	  if (current_char>=0x011&&current_char<=0x016)  // is it 'A'- 'F'
	  current_char = current_char - 07;

	  if (current_char>=0x031&&current_char<=0x036)  // is it 'a'- 'f'
	  current_char = current_char - 0x27;

      result += current_char*Pow(16,strlen(buffer)-1-i);
      }
	}

   }

   if (negativeNumber == true)
      result *= -1;

   return result;
}

unsigned __int64 GenericPurposeMethods::GetLongFromStr(char *value, char *base)
{
unsigned __int64 converted = 0;
int max_len = 0;
if (value[0] == '-') max_len++;  // for negative number increment
if (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0)
{  // if decimal as base
max_len = max_len+3*8;
}
else if (strcmp(base,CString(_T("hexadecimal")).GetBuffer(0))==0)
{  // if hexadecimal as base
max_len = max_len+2*8;
}

char *truncated_value = GenericPurposeMethods::TruncateString(value, max_len);
converted = GenericPurposeMethods::GetLongFromTStr(value, base);
return converted;
}

unsigned __int64 GenericPurposeMethods::GetLongFromTStr(char *buffer, char *base)
{
   unsigned __int64 result = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }

   bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

	if (isdecimal)
	{
      if (buffer[i] >= '0' && buffer[i] <= '9')
      {
         unsigned __int64 digit = buffer[i] - '0';
         result = result * 10 + digit;
      }
      else
      return 0;
	  
	}
	else  // hexadecimal parse:
	{
	if (!GenericPurposeMethods::IsHexNumber(buffer[i])) return 0;

	  if(buffer[i])
      {
	  unsigned __int64 current_char = buffer[i]-'0';
	  if (current_char>=0x011&&current_char<=0x016)  // is it 'A'- 'F'
	  current_char = current_char - 07;

	  if (current_char>=0x031&&current_char<=0x036)  // is it 'a'- 'f'
	  current_char = current_char - 0x27;

      result += current_char*BigPow(16,strlen(buffer)-1-i);
      }
	}

   }

   if (negativeNumber == true)
      result *= -1;

   return result;
}

// convert string to float (base 10)
float GenericPurposeMethods::str2float(char* s)
{
  char* newp = s;
  float rez = 0, fact = 1;
  if (*newp == '-')
  {
    newp++;
    fact = -1;
  };


  for (int point_seen = 0; *newp; newp++)
  {

    if (*newp == '.')
	{
      point_seen = 1; 
      continue;
    };


    int d = *newp - '0';
    if (d >= 0 && d <= 9)
	{
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };


  };
  return rez * fact;

}

float GenericPurposeMethods::str2float(char* s, char *base)
{
bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

if (isdecimal) return GenericPurposeMethods::str2float(s);

int ostrlen = (int)strlen(s);

int start_index = 0;
if (s[0] == '-') start_index++;


int point_index = -1;

  for (int i = 0; i<ostrlen; i++)
  {
    if (s[i] == '.')
	{
	point_index = i;
	break;
	}
  }

char* final_string = new char[1];
final_string[0] = 00;

if (start_index==1)
{
final_string = new char[2];
final_string[0] = '-';
final_string[1] = 0;
}

if (point_index!=-1)  // Parte intreaga + parte fractionara
{  // if we have "."
// integer part:
char* integer_hex_str = GenericPurposeMethods::Substring(s, start_index, point_index);
unsigned int integer_part = GenericPurposeMethods::GetIntFromStr(integer_hex_str, base);
char intpartdec[50];
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);
final_string = GenericPurposeMethods::JoinChars(final_string,CString(_T(".")).GetBuffer(0));  // separator

// fractional part:
integer_hex_str = GenericPurposeMethods::Substring(s, point_index+1, ostrlen);
integer_part = GenericPurposeMethods::GetIntFromStr(integer_hex_str, base);
intpartdec[0] = 00;  // kill old string!
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);

}
else // Numai Parte intreaga
{
char* integer_parthex_str = GenericPurposeMethods::Substring(s, start_index, ostrlen);
unsigned int integer_part = GenericPurposeMethods::GetIntFromStr(integer_parthex_str, base);
char intpartdec[50];
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);

}

return GenericPurposeMethods::str2float(final_string);  // finnaly convert the decimal string!
}


// convert string to double (base 10)
double GenericPurposeMethods::str2double(char* s)
{
  char* newp = s;
  double rez = 0, fact = 1;
  if (*newp == '-')
  {
    newp++;
    fact = -1;
  };


  for (int point_seen = 0; *newp; newp++)
  {

    if (*newp == '.')
	{
      point_seen = 1; 
      continue;
    };


    int d = *newp - '0';
    if (d >= 0 && d <= 9)
	{
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };


  };
  return rez * fact;

}

double GenericPurposeMethods::str2double(char* s, char *base)
{
bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);

if (isdecimal) return GenericPurposeMethods::str2double(s);

int ostrlen = (int)strlen(s);

int start_index = 0;
if (s[0] == '-') start_index++;


int point_index = -1;

  for (int i = 0; i<ostrlen; i++)
  {
    if (s[i] == '.')
	{
	point_index = i;
	break;
	}
  }

char* final_string = new char[1];
final_string[0] = 00;

if (start_index==1)
{
final_string = new char[2];
final_string[0] = '-';
final_string[1] = 0;
}

if (point_index!=-1)  // Parte intreaga + parte fractionara
{  // if we have "."
// integer part:
char* integer_hex_str = GenericPurposeMethods::Substring(s, start_index, point_index);
unsigned int integer_part = GenericPurposeMethods::GetIntFromStr(integer_hex_str, base);
char intpartdec[50];
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);
final_string = GenericPurposeMethods::JoinChars(final_string,CString(_T(".")).GetBuffer(0));  // separator

// fractional part:
integer_hex_str = GenericPurposeMethods::Substring(s, point_index+1, ostrlen);
integer_part = GenericPurposeMethods::GetIntFromStr(integer_hex_str, base);
intpartdec[0] = 00;  // kill old string!
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);

}
else // Numai Parte intreaga
{
char* integer_parthex_str = GenericPurposeMethods::Substring(s, start_index, ostrlen);
unsigned int integer_part = GenericPurposeMethods::GetIntFromStr(integer_parthex_str, base);
char intpartdec[50];
wsprintf(intpartdec,"%d",integer_part);  // convert number to dec string
final_string = GenericPurposeMethods::JoinChars(final_string,intpartdec);

}

return GenericPurposeMethods::str2double(final_string);  // finnaly convert the decimal string!
}

inline int int_floor(double x)
{  // return previous element
  int i = (int)x; /* truncate */
  return i - ( i > x ); /* convert trunc to floor */
}

char* GenericPurposeMethods::double2str(double number, char *base)
{
long double premz = (long double)number;
bool isdecimal = (strcmp(base,CString(_T("decimal")).GetBuffer(0))==0);
char* conversion = new char[1076];  // this is NOT actualy alocate as memory on stack (local var)
char intPart_reversed[311];
int i, charCount = 0;

//Separate integer/fractional parts
int int_part = (int)number;
double integer_part = (long double)int_part;
double fractional_part = number-integer_part;

 
   while (integer_part > 0) //Convert integer part, if any
   {
    intPart_reversed[charCount++] = '0' + (int)fmod(integer_part,10);
    integer_part = floor(integer_part/10);
   }

   for (i=0; i<charCount; i++) //Reverse the integer part, if any
   conversion[i] = intPart_reversed[charCount-i-1];

 conversion[charCount++] = '.'; //Decimal point

 double new_integer_part;

  while (fractional_part > 0) // Convert fractional part, if any
   {
    fractional_part*=10;
    fractional_part = modf(fractional_part,&new_integer_part);
    conversion[charCount++] = '0' + (int)new_integer_part;
   }

 conversion[charCount] = 0; //String terminator

return conversion;
}

char* GenericPurposeMethods::TruncateString(char *value, int newlen)
{
int ostrlen = strlen(value);
if (ostrlen<=newlen) return value;  // no truncate needed!

char* array = new char[newlen+1];
for (int i=0;i<newlen;i++)
array[i] = value[i];

array[newlen] = 0; // end marker char

return array;
}

char* GenericPurposeMethods::Substring(char *value, int start_index, int end_index)  // start_index = 0 end_index = 1
{
int ostrlen = strlen(value);

if (start_index>=end_index) return new char[0];
if (start_index<0||start_index>=ostrlen) return new char[0];  // if start_index is invalid
if (start_index<0||start_index>ostrlen) return new char[0];   // if end_index is invalid

int newlen = end_index-start_index;

char* array = new char[newlen+1];  // +1 since also include end char
for (int i=0;i<newlen;i++)
array[i] = value[start_index+i];

array[newlen] = 0; // end marker char

return array;

}


TCHAR* GenericPurposeMethods::GetShortModuleName(TCHAR fullname[])
{
TCHAR* shortname = new TCHAR[MAX_PATH];
int i=0;
int ostringlen = _tcslen(fullname);
int slash_position = 0;

for (i = ostringlen - 1; i >= 0; --i)
{
if (fullname[i]==92)  // if char == "\"
{
slash_position=i+1;
break;
}

}

for (i=slash_position;i<=ostringlen;i++)  // including null (00) terminating char!
shortname[i-slash_position]=fullname[i];

return shortname;

}

TCHAR* GenericPurposeMethods::GetDirectory(TCHAR fullname[])
{
TCHAR* directory = new TCHAR[MAX_PATH];
int i=0;
int ostringlen = _tcslen(fullname);
int slash_position = 0;

for (i = ostringlen - 1; i >= 0; --i)
{
if (fullname[i]==92)  // if char == "\"
{
slash_position=i+1;
break;
}

}

for (i=0;i<slash_position;i++)  // copy original chars include "\" char
directory[i]=fullname[i];

directory[slash_position] = 00; // null ending char

return directory;

}

TCHAR* GenericPurposeMethods::GetDumpFileName(TCHAR shortname[])
{
TCHAR* dumpname = new TCHAR[MAX_PATH];
int i=0;
int ostringlen = _tcslen(shortname);
int point_position = 0;

for (i = ostringlen - 1; i >= 0; --i)
{
if (shortname[i]==46)  // if char == "."
{
point_position=i;
break;
}

}

for (i=0;i<point_position;i++)  // copy before point (.)
dumpname[i]=shortname[i];

TCHAR* dump_prefix ="_dump";
int prefix_len = _tcslen(dump_prefix);

for (i=0;i<prefix_len;i++)  // copy prefix
dumpname[point_position+i]=dump_prefix[i];

//for (i=point_position;i<ostringlen;i++)  // copy extension
//dumpname[prefix_len+i]=shortname[i];

dumpname[prefix_len+point_position] = 00;  // mark the end of string!

return dumpname;

}

TCHAR* GenericPurposeMethods::GetExtension(TCHAR shortname[])
{
TCHAR* extension = new TCHAR[MAX_PATH];
int i=0;
int ostringlen = _tcslen(shortname);
int point_position = 0;

for (i = ostringlen - 1; i >= 0; --i)
{
if (shortname[i]==46)  // if char == "."
{
point_position=i;
break;
}

}

for (i=point_position;i<ostringlen;i++)  // copy after point (.)
extension[i-point_position]=shortname[i];

extension[ostringlen-point_position] = 00;  // mark the end of string!

return extension;

}

TCHAR* GenericPurposeMethods::JoinChars(TCHAR first[],TCHAR second[])
{
TCHAR* joined = new TCHAR[MAX_PATH];

int firstlen = _tcslen(first);
int secondlen = _tcslen(second);

for (int i=0;i<firstlen;i++)
joined[i]=first[i];

for (int j=0;j<secondlen;j++)
joined[j+firstlen]=second[j];

joined[firstlen+secondlen] = 0; // end of string char

return joined;
}


bool GenericPurposeMethods::ContainsExtension(TCHAR filename[])
{

int i=0;
int stringlen = _tcslen(filename);
if (stringlen==0) return false;
int point_position = -1;

for (i = stringlen - 1; i >= 0; --i)
{
if (filename[i]==46)  // if char == "."
{
point_position=i;
break;
}

}

if (point_position == -1) return false;

int extpos = stringlen-point_position;
if (extpos==4)  // if 3 chars as extension
return true;

if (extpos==3)  // if 2 chars as extension
return true;

if (extpos==2)  // if 1 chars as extension
return true;

return false;
}

/*
    public enum MemoryProtection : uint
    {
        AccessDenied = 0x0,
        Execute = 0x10,
        ExecuteRead = 0x20,
        ExecuteReadWrite = 0x40,
        ExecuteWriteCopy = 0x80,
        Guard = 0x100,
        NoCache = 0x200,
        WriteCombine = 0x400,
        NoAccess = 0x01,
        ReadOnly = 0x02,
        ReadWrite = 0x04,
        WriteCopy = 0x08
    }
*/

TCHAR* GenericPurposeMethods::GetMemoryProtectionInfo(unsigned int value)
{
CString str = TEXT("");
if (value==0x0)
str = TEXT("AccessDenied");
else if (value==0x10)
str = TEXT("Execute");
else if (value==0x20)
str = TEXT("ExecuteRead");
else if (value==0x40)
str = TEXT("ExecuteReadWrite");
else if (value==0x80)
str = TEXT("ExecuteWriteCopy");
else if (value==0x100)
str = TEXT("Guard");
else if (value==0x200)
str = TEXT("NoCache");
else if (value==0x400)
str = TEXT("WriteCombine");
else if (value==0x01)
str = TEXT("NoAccess");
else if (value==0x02)
str = TEXT("ReadOnly");
else if (value==0x04)
str = TEXT("ReadWrite");
else if (value==0x08)
str = TEXT("WriteCopy");

TCHAR* buf = new TCHAR[str.GetLength()+1];
lstrcpy(buf, str);

return buf;
}