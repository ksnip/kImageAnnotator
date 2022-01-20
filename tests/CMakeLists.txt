find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test)
find_package(GTest CONFIG REQUIRED)

enable_testing()

set(UNITTEST_SRC
	annotations/core/AnnotationAreaTest.cpp
	annotations/core/AnnotationItemFactoryTest.cpp
	annotations/core/AnnotationPropertiesFactoryTest.cpp
	annotations/modifiers/AnnotationItemResizerTest.cpp
	annotations/modifiers/AnnotationMultiItemResizerTest.cpp
	annotations/modifiers/AnnotationItemSelectorTest.cpp
	annotations/modifiers/AnnotationItemModifierTest.cpp
	annotations/modifiers/AnnotationItemArrangerTest.cpp
	annotations/modifiers/AnnotationItemMoverTest.cpp
	annotations/modifiers/resizeHandles/LineResizeHandlesTest.cpp
	annotations/modifiers/resizeHandles/RectResizeHandlesTest.cpp
	annotations/modifiers/resizeHandles/PointerRectResizeHandlesTest.cpp
	annotations/undo/AddCommandTest.cpp
	annotations/undo/DeleteCommandTest.cpp
	annotations/undo/ModifyCanvasCommandTest.cpp
	annotations/undo/MoveCommandTest.cpp
	annotations/undo/ResizeCommandTest.cpp
	annotations/undo/ArrangeCommandTest.cpp
	annotations/undo/CropCommandTest.cpp
	annotations/undo/ScaleCommandTest.cpp
	annotations/undo/PasteCommandTest.cpp
	annotations/undo/RotateCommandTest.cpp
	annotations/items/helper/KeyInputHelperTest.cpp
	annotations/items/helper/TextCursorTest.cpp
	annotations/misc/AnnotationItemClipboardTest.cpp
	annotations/misc/NumberManagerTest.cpp
	backend/ConfigTest.cpp
	common/helper/KeyHelperTest.cpp
	common/helper/MathHelperTest.cpp
	common/helper/ItemHelperTest.cpp
	common/helper/ShapeHelperTest.cpp
	common/helper/PathHelperTest.cpp
	gui/cropper/CropSelectionRestrictorTest.cpp
	gui/canvasModifier/ModifyCanvasSelectionRestrictorTest.cpp
	gui/selection/SelectionMoveHelperTest.cpp
	gui/selection/SelectionHandlerTest.cpp
	gui/selection/SelectionHandlesAllTest.cpp
	gui/scaler/ScaleSizeHandlerTest.cpp
	gui/annotator/tabs/AnnotationTabCloserTest.cpp
	gui/annotator/tabs/AnnotationTabContextMenuTest.cpp
	widgets/CustomSpinBoxTest.cpp
	widgets/misc/AttachedSeparatorTest.cpp
	widgets/settingsPicker/ToolPickerTest.cpp
	widgets/settingsPicker/ColorPickerTest.cpp
	widgets/settingsPicker/NumberPickerTest.cpp
	widgets/settingsPicker/FillModePickerTest.cpp
	widgets/settingsPicker/ImageEffectPickerTest.cpp
	widgets/settingsPicker/StickerPickerTest.cpp
	widgets/settingsPicker/ZoomPickerTest.cpp
	)

set(TESTUTILS_SRC
	utils/TestRunner.h
    mocks/gui/selection/SelectionHandlesMock.h
    mocks/MockZoomValueProvider.cpp
	mocks/MockSettingsProvider.cpp
	mocks/MockDevicePixelRatioScaler.cpp
	mocks/MockDefaultParameters.h
	mocks/MockSelectionRestrictor.cpp
	)

add_library(KIMAGEANNOTATOR_STATIC STATIC ${KIMAGEANNOTATOR_SRCS})

target_link_libraries(KIMAGEANNOTATOR_STATIC
		Qt5::Widgets
		kImageAnnotator::kImageAnnotator
		kColorPicker::kColorPicker
		Qt5::Svg)

if (UNIX AND NOT APPLE)
	target_link_libraries(KIMAGEANNOTATOR_STATIC X11::X11)
endif ()

target_compile_definitions(KIMAGEANNOTATOR_STATIC PRIVATE KIMAGEANNOTATOR_LANG_INSTALL_DIR="${KIMAGEANNOTATOR_LANG_INSTALL_DIR}")

foreach (UnitTest ${UNITTEST_SRC})
	get_filename_component(UnitTestName ${UnitTest} NAME_WE)
	add_executable(${UnitTestName} ${UnitTest} ${TESTUTILS_SRC})
	target_link_libraries(${UnitTestName} KIMAGEANNOTATOR_STATIC GTest::gmock Qt5::Test)
	add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
