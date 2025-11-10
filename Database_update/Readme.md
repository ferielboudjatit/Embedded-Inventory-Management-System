(Use Ctrl+Shift+V to switch to markdown preview)

# User Guide: Database Update Setup

This guide explains how to set up the database update mechanism on your PC. It is divided into three main sections: folder structure, Python script, and Excel file configuration.

## Contents of this folder  
**- Subfolder 1 (Database) :** It contains:  
  - `Furnitures_Automated.csv`, `NUCLEO_Automated`, `DISCOVERY-EVAL_Automated`: The CSV files updated by the Python script.  
  - `User_map.csv`: The file that maps userIDs with collaborators' names.  
  - `STM32 Boards List Automated - Paris.xlsm`: The Excel file that will be updated with the CSV data.  
  *(Important: This file is saved as .xlsm to enable macros.)*  
**- Subfolder 2 (Python) :** containing python virtual environment, python script, wheel files of Python packages that has already been installed, archive python scripts (cause why not).

## Folders Structure  
What you need to do :  
**- Local folder (Database):**  
 Save it locally somewhere under a local directory, your user directory for example: `C:\Users\your_username\Database_update\Database`.  
  1- If needed, modify the **CSV files** under this database directory (for adding all the boards and collaborator names with their respective IDs for example).  
  2- Modify python script in order to put the right column names and lines to match your modifications (if you did any).   
  3- Save these sheets as CSV. They will automatically be imported to the .xlsm file, if you created a new sheet, you need to import it as indicated in the Excel file section.  
   
**- Sharepoint folder (currently located in [ internship_folder](https://stmicroelectronics.sharepoint.com/sites/EMEAMCD/Shared%20Documents/Forms/AllItems.aspx?id=%2Fsites%2FEMEAMCD%2FShared%20Documents%2F7%2E%20Hotline%20and%20support%2FTOMAS%2FTOMAS%20Paris%20Shared%2FInternship%5Ffolder&viewid=5098bdc4%2Dc00e%2D465c%2D9b64%2Dd00de0f5947d)):**   
  1- Open it in the sharepoint website.  
  2- Click **"Add shortcut to OneDrive"**.  
  3- Open shortcut in your local file explorer.  
  4- Copy the modified .csv files from your local folder into this SharePoint folder.  

- **Important:** Modify both local and SharePoint .xlsm files as explained in the **Excel file** section below.

## Python script  
- Copies CSV files from a **'LOCAL_FOLDER'** (modify as needed) to a **'SHAREPOINT_FOLDER'** (modify as needed), retrying on errors.  
- Listens to a serial port (**'COM_PART'** (modify variable as needed)) for messages indicating boards being put into or taken out of stock, matching specific message patterns.  
- Parses incoming serial messages to extract board and user IDs and stock states.  
- Updates the local CSV spreadsheet with the new stock state and user information accordingly.  
- Syncs the updated CSV file to SharePoint after each update (copies from local folder to sharepoint folder (OneDrive shortcut))  

To launch the python script, navigate to the Python folder (either in PowerShell or open folder in VScode if you have Python package installed, and launch a terminal).
Activate the virtual environment : 
```
.venv\Scripts\Activate.ps1
```
Launch the script:
```
python update_database_final.py
```
Press on the reset button of the nucleo to test if the script receives and logs the uart messages.

## Excel file (.xlsm)  
This section helps to integrate the new paths of the current CSV files (since you copied them in your machine) into the system.  
This section also helps you to import any newly created CSV files into the `.xlsm` file and seemlessly integrate within the rest of the system.  
**Remark:** If you also modified the names of the CSV files that are already important, you need to change the names in VBA editor (RefreshModule) module.  
### Step 1: Enable Developer tab if not already visible  
 - File → Options → Customize Ribbon  
 - Check "Developer" in the right panel  
 - Click OK  

### Step 2: Add the CSV file  
If you added a new CSV file, import it to the .xlsm file this way:  
 - Go to Data -> Get Data from Text\CSV.  
 - Import the CSV file from both your local and SharePoint folders into their respective .xlsm files.  
 - Click on Transform Data.   
 - If needed (Sometimes the interface adds a row with column numbers in it as a header, this happend when some columns are empty) click on the little sheet icon next to the first column header and choose Use First Row as Headers.   
 - Click on close and load on upper left part of the screen.   
 - Modify the appearance of the table as needed.

**Important (limitation):** If any modifications are needed to be done manually in this database, you should modify the CSV file directly, not the imported version of it in the .xlsm file

### Step 3: Add Microsoft Visual Basic for Application VBA Code  
This step is supposedly not needed, unless you created a whole new Excel file. The only thing you need to modify here are the Sheet names (`NUCLEO_Automated`,`DISCOVERY-EVAL_Automated`,`Furnitures_Automated`) in case you modified their CSV file names.  

Microsoft VBA here helps to automatically refresh the Queries (a refresh when opening the file and each 30 seconds) without passing by the limitations of the Queries and Connections platform (the limitation I am referring to is the fact that when the excel file is opened by multiple users at a time the automatic refresh is paused).  

1. Open VBA Editor: Press `Alt + F11` Or go to Developer → Visual Basic  

2. Insert a new Module:  
 - Right-click on VBA project in Project Explorer (left panel)  
 - Insert → Module  

3. Paste this VBA code:  
```vba
Public Sub RefreshQuery()
    Dim ws As Worksheet
        
    ' Change to your actual sheet names
    Set ws_nucleo = ThisWorkbook.Sheets("NUCLEO_Automated")
    Set ws_disco = ThisWorkbook.Sheets("DISCOVERY-EVAL_Automated")
    Set ws_furnitures = ThisWorkbook.Sheets("Furnitures_Automated")
        
        
    ' Here replace with your sheet names
    ActiveWorkbook.Queries("NUCLEO_Automated").Refresh
    ActiveWorkbook.Queries("DISCOVERY-EVAL_Automated").Refresh
    ActiveWorkbook.Queries("Furnitures_Automated").Refresh
    
    Call ScheduleNextRefresh
End Sub
```
4. **Add Auto-Run Code:**  
 - In Project Explorer, click on **ThisWorkbook**  
 - Paste this code: 
```vba
Dim nextRefreshTime As Date
Dim RefreshScheduled As Boolean

Sub Workbook_Open()
    Call RefreshQuery
    Call ScheduleNextRefresh
End Sub

Sub StopAutoRefresh()
    ' Cancel the scheduled refresh if one is pending
    If RefreshScheduled Then
        On Error Resume Next
        Application.OnTime nextRefreshTime, "RefreshQuery", , False
        On Error GoTo 0
        RefreshScheduled = False
    End If
End Sub
```



### Step 4: Set Up Power Query 
The only thing you need to modify here are the hardcoded paths on the Power Query code for each query (`NUCLEO_Automated`,`DISCOVERY-EVAL_Automated`,`Furnitures_Automated`)
  - Data → Get Data → Launch Power Query Editor  
  - find the wanted query and edit it  
  - Click on Advanced Editor (to the right of Refresh Preview on upper left part of the screen)  
  - Modify the paths so that they point to the location where you put the CSV files.


After that, run VBA (select RefreshQuery) a first time, save and close.  

## Desktop Shortcut of Sharepoint .xlsm file

  - Make a copy of one of the Sharepoint desktop shortcuts you have (STSupport 2025).  
  - Click on Properties
  - Copy the following :
  ```
  "EXCEL.EXE" https://stmicroelectronics.sharepoint.com/:x:/r/sites/EMEAMCD/_layouts/15/Doc.aspx?sourcedoc=%7B91A68B3E-9DAE-4D9F-99CA-B833728ADCE6%7D&file=STM32%20Boards%20List%20Automated%20-%20Paris.xlsm&action=default&mobileredirect=true
  ```
  under "Target", and make sure you have the path `C:\Program Files\Microsoft Office\root\Office16` under Start in.


## Test the setup 
  - Run the Python script.  
  - Open the Excel .xlsm file. 
  - Make sure you have AutoSave powered Off.   
  - Confirm that the user path is correctly written in the specified cell.  
  - Confirm that the Power Query loads data from the correct CSV file dynamically.  