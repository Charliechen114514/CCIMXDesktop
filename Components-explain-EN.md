# 🧩 Module Descriptions

​	These are the module descriptions for the developers if you wanna modified to transplant better for your embedded device

## 🔧 `app_wrapper`

​	Application launcher and system bootstrapper. It initializes Qt environment, sets global styles, and manages startup and shutdown sequences. 

------

## 🧬 `builtin`

Contains the core system tools and default utilities embedded within the desktop environment.

- `core/icm20608`
  Drivers and logic for the **ICM-20608 IMU sensor**, handling real-time data acquisition from gyroscope and accelerometer, interfaced via I2C. (Bonus: If you are using other chips, you should also modified and rewriten the internal functions)
- `gadgets`
  UI-friendly gadgets such as clocks, CPU/network meters, or quick launch tiles for user interaction.
- `page`
  Logical page management for internal UI routing (e.g., switching between home, apps page etc.).
- `sources/localweather`
  Weather information provider module that fetches or simulates local weather data.
- `sources/netcard`
  Handles network card information, status display, and possibly provides IP/network diagnostics.
- `ui`
  UI components specific to the built-in modules, these are the files support for the Desktop itself ui style

------

## ⚙️ `core`

System-level services and shared base classes such as global context management, signal buses, or singleton infrastructure. May contain system abstractions used across modules.

------

## 🚀 `extern_app`

Third-party or user-extensible apps, integrated into the desktop but modularized for easy addition/removal.

- `FileRamber`
  A custom file management tool.
  - `Core`: Core logic for file operations.
  - `source`: Interaction with filesystem, path parsing, etc.
  - `Ui`: Frontend for browsing and managing files.
- `GeneralLocalCamera`
  A generalized camera app with support for both preview and recording.
  - `Core`: Camera control logic.
  - `sources`: Device interfacing.
  - `Ui`: Visual display and user interaction.
- `LocalCamera`
  A minimal or legacy version of the local camera, probably used for fallback or testing.(Thus in default, it won't get into the buildroot as QMultiMedia backends are less supoort in I.MX6ULs, if you finish transplant these backends, then the build is acceptable)
- `pdfReader`
  A lightweight PDF reader built on **MuPDF**.
  - `mupdf_adapter`: Adapter code connecting MuPDF to Qt.
  - `mupdf_tools`: Utility functions to extract, render, or manipulate pages.
  - `sources`: Viewer logic and file management.
  - `ui`, `ui_tools`: GUI components and UI utilities.
- `WeatherApp`
  A full-featured weather application separate from the built-in gadget version.
  - `Core`: Handles weather APIs or sensor input.
  - `MainWindow`: Window controller.
  - `sources`: Functional modules.
  - `Ui`: Interface rendering.

------

## 🧩 `sources`

Ui Sources for the desktop itself

------

## 🎨 `ui`

Top-level UI templates, themes, or layout definitions. May serve as a base for styling or skinning the whole desktop.

