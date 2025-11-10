@echo off

:: Reading USERNAME
set /p username="USERNAME: "

:: Hidden reading PASSWORD
set "psCommand=powershell -Command "$pword = read-host 'PASSWORD' -AsSecureString ; ^
 $BSTR=[System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($pword); ^
          [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($BSTR)""
for /f "usebackq delims=" %%p in (`%psCommand%`) do set pw=%%p

:: URL encoding to convert special characters (:/?#[]@!$&'()*+,;=%)
set "beginJS=mshta "javascript:code(close(new ActiveXObject('Scripting.FileSystemObject').GetStandardStream(1).Write("
set "endJS=)));""

for /f %%N in (
  '%beginJS% encodeURIComponent("%pw%") %endJS%'
) do set password=%%N

:: Set PROXY with credentials
set ProxyIP=appgw.gnb.st.com
set proxy_username=%username%
set proxy_password=%password%
set http_proxy=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080
set https_proxy=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080
set ftp_proxy=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080
set HTTP_PROXY=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080
set HTTPS_PROXY=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080
set FTP_PROXY=http://%proxy_username%:%proxy_password%@%ProxyIP%:8080

echo.
echo Proxy environment variables set (http_proxy, https_proxy, ftp_proxy).

:: Go to C:\ directory
cd /d C:\