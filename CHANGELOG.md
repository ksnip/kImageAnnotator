# Change log

## Release 0.4.0
* New: Add Pixelate image area tool. ([#140](https://github.com/ksnip/kImageAnnotator/issues/140))
* New: Zoom in and out. ([#123](https://github.com/ksnip/kImageAnnotator/issues/123))
* New: Add interface for adding custom tab context menu actions. ([#96](https://github.com/ksnip/kImageAnnotator/issues/96))
* New: Add drop shadow to captured images. ([#133](https://github.com/ksnip/kImageAnnotator/issues/133))
* New: Add grayscale image effect. ([#151](https://github.com/ksnip/kImageAnnotator/issues/151))
* New: Add numeric pointer with arrow annotation item. ([#152](https://github.com/ksnip/kImageAnnotator/issues/152))
* New: Add text pointer annotation item. ([#154](https://github.com/ksnip/kImageAnnotator/issues/154))
* Changed: Draw point when clicking and releasing without moving cursor. ([#136](https://github.com/ksnip/kImageAnnotator/issues/136))
* Changed: Zoom out less than 100%. ([#150](https://github.com/ksnip/kImageAnnotator/issues/150))
* Fixed: Blur radius not updated when changing current items settings. ([#142](https://github.com/ksnip/kImageAnnotator/issues/142))
* Fixed: Text tool opens many unix sockets. ([#144](https://github.com/ksnip/kImageAnnotator/issues/144))
* Fixed: Text No Border and No Fill shows shadow beneath text. ([#148](https://github.com/ksnip/kImageAnnotator/issues/148))

## Release 0.3.2
* Fixed: Tests fail to build with shared library. ([#128](https://github.com/ksnip/kImageAnnotator/issues/128))

## Release 0.3.1
* Fixed: Crashes after undoing a number annotation. ([#114](https://github.com/ksnip/kImageAnnotator/issues/114))
* Fixed: Text overlapping when resizing text box. ([#53](https://github.com/ksnip/kImageAnnotator/issues/53))
* Fixed: Snap lines to degrees not working when CTRL pressed before clicking annotation area. ([#113](https://github.com/ksnip/kImageAnnotator/issues/113))
* Fixed: "Border and Fill" submenu cutting off text under windows. ([#117](https://github.com/ksnip/kImageAnnotator/issues/117))
* Fixed: Undo removes several or all items. ([#121](https://github.com/ksnip/kImageAnnotator/issues/121))
* Fixed: Marker Rect and Ellipse draw only border but no fill. ([#126](https://github.com/ksnip/kImageAnnotator/issues/126))

## Release 0.3.0
* New: Tabs for images. ([#48](https://github.com/ksnip/kImageAnnotator/issues/48))
* New: Add option to translate UI. ([#54](https://github.com/ksnip/kImageAnnotator/issues/54))
* New: Saved image expand to include annotations out of border. ([#90](https://github.com/ksnip/kImageAnnotator/issues/90))
* New: Add support for stickers. ([#74](https://github.com/ksnip/kImageAnnotator/issues/74))
* New: Add tab context menu for close all tabs and close other tabs. ([#93](https://github.com/ksnip/kImageAnnotator/issues/93))
* New: Add Number with Arrow/pointer tool. ([#79](https://github.com/ksnip/kImageAnnotator/issues/79))
* Changed: Make dropdown buttons show popup on click. ([#89](https://github.com/ksnip/kImageAnnotator/issues/89))
* Changed: Hide unavailable setting widgets. ([#101](https://github.com/ksnip/kImageAnnotator/issues/101))
* Changed: Make arrow size decrease with stroke size. ([#84](https://github.com/ksnip/kImageAnnotator/issues/84))
* Fixed: Using select tool marks image as changed. ([#97](https://github.com/ksnip/kImageAnnotator/issues/97))
* Fixed: Emoticon selector shows a half of current emoticon. ([#104](https://github.com/ksnip/kImageAnnotator/issues/104))
* Fixed: FillPicker text or icon sometimes not visible. ([#105](https://github.com/ksnip/kImageAnnotator/issues/105))
* Fixed: Wrong image scaling on hdpi screen. ([#81](https://github.com/ksnip/kImageAnnotator/issues/81))
* Fixed: Copy area size differs from last capture. ([#107](https://github.com/ksnip/kImageAnnotator/issues/107))
* Fixed: Number Tool not reset when switching between tabs. ([#106](https://github.com/ksnip/kImageAnnotator/issues/106))

## Release 0.2.1
* Fixed: Edit border around text box doesn't disappear when done with editing. ([#71](https://github.com/ksnip/kImageAnnotator/issues/71))
* Fixed: Edit border not shown under Windows when NoFillNoBorder selected for Text Tool. ([#72](https://github.com/ksnip/kImageAnnotator/issues/72))
* Fixed: When adding text with background under Windows a filled rect is show in top left corner. ([#73](https://github.com/ksnip/kImageAnnotator/issues/73))
* Fixed: Drawing text tool rect from right to left and bottom top create no rect. ([#76](https://github.com/ksnip/kImageAnnotator/issues/76))
* Fixed: Text Tool FillType selection not saved. ([#75](https://github.com/ksnip/kImageAnnotator/issues/75))
* Fixed: Icons not scaled with HiDPI. ([#77](https://github.com/ksnip/kImageAnnotator/issues/77))
* Fixed: Text Cursor not show on Linux. ([#70](https://github.com/ksnip/kImageAnnotator/issues/70))

## Release 0.2.0
* New: Add image item and interface for adding them externally. ([#45](https://github.com/ksnip/kImageAnnotator/issues/45))
* New: Edit text box content. ([#51](https://github.com/ksnip/kImageAnnotator/issues/51))
* New: Add cmake uninstall target. ([#47](https://github.com/ksnip/kImageAnnotator/issues/47))
* New: Panning image by holding space or mouse middle button and dragging. ([#9](https://github.com/ksnip/kImageAnnotator/issues/9))
* New: Change annotation element config after drawing. ([#44](https://github.com/ksnip/kImageAnnotator/issues/44))
* Changed: Increase blur level so that large text is not visible. ([#62](https://github.com/ksnip/kImageAnnotator/issues/62))
* Changed: Crop widget updates shows via cursor if something is movable. ([#64](https://github.com/ksnip/kImageAnnotator/issues/64))
* Changed: Multi-tool buttons select current (last) tool on single click. ([#66](https://github.com/ksnip/kImageAnnotator/issues/66))
* Fixed: Ctrl Modifier stuck on second or third screenshot with Ctrl-N. ([#58](https://github.com/ksnip/kImageAnnotator/issues/58))
* Fixed: Unable to select number annotation when clicking on the number without background. ([#46](https://github.com/ksnip/kImageAnnotator/issues/46))
* Fixed: Undo/Redo is now disabled during crop and scale operation. ([#56](https://github.com/ksnip/kImageAnnotator/issues/56))
* Fixed: Mess with russian letters in text tool when typing in Russian. ([#59](https://github.com/ksnip/kImageAnnotator/issues/59))
* Fixed: Text tool does not allow me to type accents. ([#57](https://github.com/ksnip/kImageAnnotator/issues/57))
* Fixed: Highlighter rect and ellipse have only border but no fill. ([#65](https://github.com/ksnip/kImageAnnotator/issues/65))
* Fixed: Saved tool selection not loaded on startup. ([#67](https://github.com/ksnip/kImageAnnotator/issues/67))
* Fixed: On startup does not highlight tool, when this tool not the first item in the list. ([#63](https://github.com/ksnip/kImageAnnotator/issues/63))
* Fixed: Cursor image cannot be grabbed for moving. ([#69](https://github.com/ksnip/kImageAnnotator/issues/69))
* Fixed: Accents still not work in text tool on Linux. ([#61](https://github.com/ksnip/kImageAnnotator/issues/61))

## Release 0.1.0
* New: Double Arrow annotation tool. ([#23](https://github.com/ksnip/kImageAnnotator/issues/23))
* New: Marker Rectangle and Ellipse annotation tool. ([#26](https://github.com/ksnip/kImageAnnotator/issues/26))
* New: Add icons for dark theme. ([#37](https://github.com/ksnip/kImageAnnotator/issues/37))
* New: Add config option to setup blur radius. ([#25](https://github.com/ksnip/kImageAnnotator/issues/25))
* Changed: Blur tool is now preciser and fits the rect. ([#28](https://github.com/ksnip/kImageAnnotator/issues/28))
* Changed: Enter finishes text input and shift-enter adds new line in Text Tool. ([#30](https://github.com/ksnip/kImageAnnotator/issues/30))
* Changed: Text item draws border around the text when in text edit mode. ([#34](https://github.com/ksnip/kImageAnnotator/issues/34))
* Fixed: Double-click on annotation area causes SIGSEGV crash. ([#29](https://github.com/ksnip/kImageAnnotator/issues/29))
* Fixed: CAPS LOCK doesnt work on image editor. ([#27](https://github.com/ksnip/kImageAnnotator/issues/27))
* Fixed: Unable to select text item when clicking on text. ([#32](https://github.com/ksnip/kImageAnnotator/issues/32))
* Fixed: Some blurs get removed when losing focus. ([#35](https://github.com/ksnip/kImageAnnotator/issues/35))
* Fixed: Items cannot be resized when drawn from bottom right to top left. ([#38](https://github.com/ksnip/kImageAnnotator/issues/38))
* Fixed: Right click on annotation items selects item but doesn't switch tool. ([#40](https://github.com/ksnip/kImageAnnotator/issues/40))
* Fixed: Copy number annotation item doesn't increment number. ([#41](https://github.com/ksnip/kImageAnnotator/issues/41))
* Fixed: Crash on startup after adding Blur Radius Picker. ([#43](https://github.com/ksnip/kImageAnnotator/issues/43))

## Release 0.0.2
* New: Added blur annotation tool. ([#20](https://github.com/ksnip/kImageAnnotator/issues/20))
* New: Keep number tool sequence consecutive after deleting item. ([#7](https://github.com/ksnip/kImageAnnotator/issues/7))
* New: Added control for setting first number for numbering tool. ([#7](https://github.com/ksnip/kImageAnnotator/issues/7))
* New: Text and Number tool have now noBorderAndNoFill type. ([#22](https://github.com/ksnip/kImageAnnotator/issues/22))

## Release 0.0.1
* New: Initial release
