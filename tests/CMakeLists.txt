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
	annotations/undo/AddCommandTest.cpp
	annotations/undo/DeleteCommandTest.cpp
	annotations/undo/MoveCommandTest.cpp
	annotations/undo/ResizeCommandTest.cpp
	annotations/undo/ArrangeCommandTest.cpp
	annotations/undo/CropCommandTest.cpp
	annotations/undo/ScaleCommandTest.cpp
	annotations/undo/PasteCommandTest.cpp
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
	gui/cropper/CropSelectionMoveHelperTest.cpp
	gui/cropper/CropSelectionHandlerTest.cpp
	gui/cropper/CropHandlesTest.cpp
	gui/scaler/ScaleSizeHandlerTest.cpp
	gui/annotator/tabs/AnnotationTabCloserTest.cpp
	widgets/ToolPickerTest.cpp
	widgets/ColorPickerTest.cpp
	widgets/NumberPickerTest.cpp
	widgets/FillTypePickerTest.cpp
	widgets/CustomSpinBoxTest.cpp
	widgets/StickerPickerTest.cpp
	)

set(TESTUTILS_SRC
	mocks/MockSettingsProvider.cpp
	)

add_library(KIMAGEANNOTATOR_STATIC STATIC ${KIMAGEANNOTATOR_SRCS})

target_link_libraries(KIMAGEANNOTATOR_STATIC Qt5::Widgets Qt5::Svg kImageAnnotator)

foreach (UnitTest ${UNITTEST_SRC})
	get_filename_component(UnitTestName ${UnitTest} NAME_WE)
	add_executable(${UnitTestName} ${UnitTest} ${TESTUTILS_SRC})
	target_link_libraries(${UnitTestName} KIMAGEANNOTATOR_STATIC Qt5::Test)
	add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
