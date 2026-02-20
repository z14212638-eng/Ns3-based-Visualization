# Ns3Visualizer User Guide
- [Back to README](README_en.md)
---
### Component Versions and Dependencies
- Qt 6.10.2
- ns-3.46
- C++17 or later
- Linux environment
  
---
### Initial Page
![Page1](./img/page1.jpg)
- Use the **ns-3 path** button at the top to set the ns-3 folder path. The app will automatically validate the selected ns-3 path.
- After setting it successfully, click **continue** to enter the **Simulation Mode Selection** page.

---
### Simulation Mode Selection
![Page2](./img/page2.jpg)

- You can choose **Existing Scenario Simulation** or **Custom Scenario Simulation**.
- > Existing Scenario Simulation: click "Simple Scenes", "Complex Scenes", or "Scratch" to select a predefined scenario, click **Select**, then **Apply** to start the simulation. "Scratch" automatically reads scripts from the ns-3 directory.
  
	![Page2_default](./img/page2_default.jpg)

- > Simple/Complex Scenes are designed to help users get started with ns-3 quickly and showcase typical wireless scenarios plus the PPDU Timeline view.
- > Scratch: if you already have your own simulation scripts and want to use the PPDU timeline for analysis, place your script under ns3/scratch and select it here.
	```cpp
	/*=======Requirements for using the PPDU timeline=======*/
	// Include header:
	include "ns3/SniffUtils.h"
	/*
	your simulation 
	*/
	// Before simulation stop:
	Ptr<SniffUtils> Sniff_Utils = CreateObject<SniffUtils>();
	Sniff_Utils->Initialize(staDevices, apDevices, duration);
	```

- The **New** button allows you to create a no-code custom simulation (DIY) [see below].
- The **Load from File** button lets you load a custom scenario from a project file (.nsproj) [see below].

---
### Custom Scenario Editor
![Page3](./img/page3.jpg)

- > There are three tabs: General, Access Point, and Station. They correspond to overall scenario settings, AP settings, and STA settings.
- > After configuring parameters, you can drag node positions in the building view on the right, and zoom to adjust details. Click **Update** to apply the scene configuration.
- > The **Save** button saves the current configuration to a project file (.nsproj) for later use.
- > The **Start** button launches the simulation and opens the PPDU timeline view (./ns3 build may take some time; a short delay before switching pages is normal).
  
### PPDU Timeline View
![Page4](./img/page4.jpg)
- > This view shows the transmission and reception of each PPDU during simulation. Each horizontal line represents a node; each rectangle represents a PPDU; the rectangle length indicates PPDU duration. Hover over a rectangle to view PPDU details.
- > The four buttons at the top-left are: **Save current view**, **Set time range**, **Switch channel/node view**, **Exit current simulation**.
- > The button in the top-right is: **Legend**.
- > Bottom-left is the throughput line chart; bottom-right is detailed PPDU parameters.
