#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
  //CreateFile

  LPCSTR fileName;
  fileName = "";
  HANDLE hFile = CreateFileA(
    fileName,
    GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (hFile == INVALID_HANDLE_VALUE) {
    printf("Failed to open file. Error code: %lu\n", GetLastError());
    return 1;
  } else {
    printf("Succesfully opened file handle.\n");
  }

  

  //ReadFile
  LARGE_INTEGER fileSize;
  GetFileSizeEx(hFile, &fileSize);
  char *buffer = (char*)malloc(fileSize.QuadPart);
  if (buffer == NULL) {
    printf("Memory allocation failed.\n");
    CloseHandle(hFile);
    return 1;
  }

  DWORD bytesToRead = (DWORD)fileSize.QuadPart;
  DWORD bytesRead = 0;

  BOOL readResult = ReadFile(
    hFile,
    buffer,
    bytesToRead,
    &bytesRead,
    NULL
  );

  if (readResult) {
    printf("Successfully read %lu bytes.\n", bytesRead);
  } else {
    printf("ReadFile failed. Error code: %lu\n", GetLastError());
  }


  CloseHandle(hFile);
  free(buffer);
  return 0;
}