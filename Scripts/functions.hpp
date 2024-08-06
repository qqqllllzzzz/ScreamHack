void DoS() {
   LPCSTR exePath = "Scripts/tools/dos/dos.exe";

      STARTUPINFOA si;
      PROCESS_INFORMATION pi;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      // Создание процесса
      if (!CreateProcessA(
         NULL,
         (LPSTR)exePath,
         NULL,
         NULL,
         FALSE,
         0,
         NULL,
         NULL,
         &si,
         &pi
      )) {
         std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
      }

      WaitForSingleObject(pi.hProcess, INFINITE);

      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
}
void InternetProtocol() {
   LPCSTR exePath = "Scripts/tools/InternetProtocol.exe";

      STARTUPINFOA si;
      PROCESS_INFORMATION pi;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      // Создание процесса
      if (!CreateProcessA(
         NULL,
         (LPSTR)exePath,
         NULL,
         NULL,
         FALSE,
         0,
         NULL,
         NULL,
         &si,
         &pi
      )) {
         std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
      }

      WaitForSingleObject(pi.hProcess, INFINITE);

      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
}

void BuildStealer() {
   LPCSTR exePath = "Scripts/StealerBuilder.exe";

      STARTUPINFOA si;
      PROCESS_INFORMATION pi;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      // Создание процесса
      if (!CreateProcessA(
         NULL,
         (LPSTR)exePath,
         NULL,
         NULL,
         FALSE,
         0,
         NULL,
         NULL,
         &si,
         &pi
      )) {
         std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
      }

      WaitForSingleObject(pi.hProcess, INFINITE);

      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
}