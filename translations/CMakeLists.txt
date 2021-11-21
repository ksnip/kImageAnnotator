find_package(Qt5LinguistTools)

set(KIMAGEANNOTATOR_LANG_TS
	kImageAnnotator_ca.ts
	kImageAnnotator_cs.ts
	kImageAnnotator_da.ts
	kImageAnnotator_de.ts
	kImageAnnotator_el.ts
	kImageAnnotator_es.ts
	kImageAnnotator_eu.ts
	kImageAnnotator_fr.ts
	kImageAnnotator_fr_CA.ts
	kImageAnnotator_gl.ts
	kImageAnnotator_hr.ts
	kImageAnnotator_hu.ts
	kImageAnnotator_id.ts
	kImageAnnotator_it.ts
	kImageAnnotator_ja.ts
	kImageAnnotator_ko.ts
	kImageAnnotator_nl.ts
	kImageAnnotator_no.ts
	kImageAnnotator_pl.ts
	kImageAnnotator_pt.ts
	kImageAnnotator_pt_BR.ts
	kImageAnnotator_ro.ts
	kImageAnnotator_ru.ts
	kImageAnnotator_si.ts
	kImageAnnotator_sq.ts
	kImageAnnotator_sv.ts
	kImageAnnotator_tr.ts
	kImageAnnotator_uk.ts
    kImageAnnotator_zh_CN.ts)

if (DEFINED UPDATE_TS_FILES)
	qt5_create_translation(KIMAGEANNOTATOR_LANG_QM ${CMAKE_SOURCE_DIR}/translations ${KIMAGEANNOTATOR_SRCS} ${KIMAGEANNOTATOR_LANG_TS} OPTIONS "-no-obsolete")
else ()
	qt5_add_translation(KIMAGEANNOTATOR_LANG_QM ${KIMAGEANNOTATOR_LANG_TS})
endif ()

add_custom_target(translations ALL DEPENDS ${KIMAGEANNOTATOR_LANG_QM})

install(FILES ${KIMAGEANNOTATOR_LANG_QM} DESTINATION ${KIMAGEANNOTATOR_LANG_INSTALL_DIR})

