# SlickWIC
Windows Imaging Codec backed by DevIL to load TGA, PSD, and DDS files

## How To Use
1. Compile SlickWIC.sln
    * Note: you may need to set "SDK_DIR" environment variable to a parent folder containing DevIL.
    * https://github.com/DentonW/DevIL
2. Copy DevIL binaries into shared folder
3. In Admin prompt run: **regsvr32.exe SlickWIC.dll**
4. Windows Explorer should now show Thumbnails for TGA, PSD, and DDS files
