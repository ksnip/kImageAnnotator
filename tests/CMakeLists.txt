set(UnitTests
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
	annotations/items/helper/KeyInputHelperTest.cpp
	annotations/items/helper/TextCursorTest.cpp
	widgets/ToolPickerTest.cpp
	widgets/ColorPickerTest.cpp
	widgets/SizePickerTest.cpp
	widgets/FillTypePickerTest.cpp
	common/helper/KeyHelperTest.cpp
	common/helper/MathHelperTest.cpp
	common/helper/ItemHelperTest.cpp
	common/helper/ShapeHelperTest.cpp
	backend/ConfigTest.cpp
	gui/cropper/CropSelectionRestrictorTest.cpp
	gui/cropper/CropSelectionMoveHelperTest.cpp
	)

add_library(kImageAnnotatorStatic STATIC ${kimageannotator_SRCS})

target_link_libraries(kImageAnnotatorStatic Qt5::Widgets kImageAnnotator)

foreach (UnitTest ${UnitTests})
	get_filename_component(UnitTestName ${UnitTest} NAME_WE)
	add_executable(${UnitTestName} ${UnitTest})
	target_link_libraries(${UnitTestName} kImageAnnotatorStatic Qt5::Test)
	add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
